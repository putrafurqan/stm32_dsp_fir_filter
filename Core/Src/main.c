/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "can.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "arm_math.h"
#include "cmps12.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define FILTER_LENGTH 50
#define FIR_LENGTH      11
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

// FIR filter instances ========================
float32_t fir_coefficients[FIR_LENGTH] = {-0.0220, -0.0339, 0.0072, 0.1235, 0.2618, 0.3244, 0.2618, 0.1235, 0.0072, -0.0339, -0.0220};
arm_fir_instance_f32 fir_instance_accel_x;
arm_fir_instance_f32 fir_instance_accel_y;
arm_fir_instance_f32 fir_instance_accel_z;
arm_fir_instance_f32 fir_instance_gyro_x;
arm_fir_instance_f32 fir_instance_gyro_y;
arm_fir_instance_f32 fir_instance_gyro_z;

float32_t fir_state_accel_x[FIR_LENGTH];
float32_t fir_state_accel_y[FIR_LENGTH];
float32_t fir_state_accel_z[FIR_LENGTH];
float32_t fir_state_gyro_x[FIR_LENGTH];
float32_t fir_state_gyro_y[FIR_LENGTH];
float32_t fir_state_gyro_z[FIR_LENGTH];

float32_t fir_in_accel_x, fir_in_accel_y, fir_in_accel_z;
float32_t fir_in_gyro_x, fir_in_gyro_y, fir_in_gyro_z;

float32_t fir_out_accel_x, fir_out_accel_y, fir_out_accel_z;
float32_t fir_out_gyro_x, fir_out_gyro_y, fir_out_gyro_z;

float32_t filtered_accel_x, filtered_accel_y, filtered_accel_z;
float32_t filtered_gyro_x, filtered_gyro_y, filtered_gyro_z;

// Sensor Variables ============================
CMPS12_Data cmps12;  
uint16_t angle, temp;
int16_t accel_x, accel_y, accel_z;  // Raw accelerometer data
int16_t gyro_x, gyro_y, gyro_z;      // Raw gyroscope data

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_CAN_Init();
  MX_USART1_UART_Init();
  MX_I2C2_Init();
  MX_TIM3_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
    // Initialize FIR filter instances
    arm_fir_init_f32(&fir_instance_accel_x, FIR_LENGTH, fir_coefficients, fir_state_accel_x, 1);
    arm_fir_init_f32(&fir_instance_accel_y, FIR_LENGTH, fir_coefficients, fir_state_accel_y, 1);
    arm_fir_init_f32(&fir_instance_accel_z, FIR_LENGTH, fir_coefficients, fir_state_accel_z, 1);
    arm_fir_init_f32(&fir_instance_gyro_x, FIR_LENGTH, fir_coefficients, fir_state_gyro_x, 1);
    arm_fir_init_f32(&fir_instance_gyro_y, FIR_LENGTH, fir_coefficients, fir_state_gyro_y, 1);
    arm_fir_init_f32(&fir_instance_gyro_z, FIR_LENGTH, fir_coefficients, fir_state_gyro_z, 1);

    // Initialize your sensor (replace with actual initialization function)
    CMPS12_Init(&cmps12, &hi2c2); 
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1) {
        // Read raw sensor data (replace with actual functions to read accelerometer and gyroscope)
        accel_x = CMPS12_GetAccelX(&cmps12);
        accel_y = CMPS12_GetAccelY(&cmps12);
        accel_z = CMPS12_GetAccelZ(&cmps12);
        gyro_x = CMPS12_GetGyroX(&cmps12);
        gyro_y = CMPS12_GetGyroY(&cmps12);
        gyro_z = CMPS12_GetGyroZ(&cmps12);

        // Apply FIR filter to accelerometer data
        fir_in_accel_x = (float32_t)accel_x;
        arm_fir_f32(&fir_instance_accel_x, &fir_in_accel_x, &fir_out_accel_x, 1);
        filtered_accel_x = fir_out_accel_x;  // Store the filtered accelerometer x

        fir_in_accel_y = (float32_t)accel_y;
        arm_fir_f32(&fir_instance_accel_y, &fir_in_accel_y, &fir_out_accel_y, 1);
        filtered_accel_y = fir_out_accel_y;  // Store the filtered accelerometer y

        fir_in_accel_z = (float32_t)accel_z;
        arm_fir_f32(&fir_instance_accel_z, &fir_in_accel_z, &fir_out_accel_z, 1);
        filtered_accel_z = fir_out_accel_z;  // Store the filtered accelerometer z

        // Apply FIR filter to gyroscope data
        fir_in_gyro_x = (float32_t)gyro_x;
        arm_fir_f32(&fir_instance_gyro_x, &fir_in_gyro_x, &fir_out_gyro_x, 1);
        filtered_gyro_x = fir_out_gyro_x;  // Store the filtered gyroscope x

        fir_in_gyro_y = (float32_t)gyro_y;
        arm_fir_f32(&fir_instance_gyro_y, &fir_in_gyro_y, &fir_out_gyro_y, 1);
        filtered_gyro_y = fir_out_gyro_y;  // Store the filtered gyroscope y

        fir_in_gyro_z = (float32_t)gyro_z;
        arm_fir_f32(&fir_instance_gyro_z, &fir_in_gyro_z, &fir_out_gyro_z, 1);
        filtered_gyro_z = fir_out_gyro_z;  // Store the filtered gyroscope z

        // Prepare the data to send over USART
        char data_buffer[200];  // Buffer to hold the formatted string
        int len = snprintf(data_buffer, sizeof(data_buffer), "x_f %.2f y_f %.2f z_f %.2f x %d y %d z %d\r\n",
                           filtered_accel_x, filtered_accel_y, filtered_accel_z,
                           accel_x, accel_y, accel_z);

        // Send the data over USART
        if (len > 0) {
            HAL_UART_Transmit(&huart1, (uint8_t*)data_buffer, len, HAL_MAX_DELAY);
        }

        // Optional: Add a delay if needed to control the output rate
        // HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
        // HAL_Delay(50);  // Adjust the delay as necessary
    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL8;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
    }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
