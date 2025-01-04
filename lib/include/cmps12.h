#ifndef CMPS12_H
#define CMPS12_H

#include "main.h"  // Adjust this include based on your STM32 series

#define CMPS12_I2C_ADDRESS 0x60

// Register definitions
#define SOFTWARE_REVISION_REG    0x00
#define COMPASS_BEARING_WORD_REG 0x02
#define COMPASS_BEARING16_WORD_REG 0x1A
#define COMPASS_PITCH_WORD_REG   0x1C
#define COMPASS_ROLL_WORD_REG    0x05
#define ACCEL_X_WORD_REG         0x0C
#define ACCEL_Y_WORD_REG         0x0E
#define ACCEL_Z_WORD_REG         0x10
#define MAGNET_X_WORD_REG        0x06
#define MAGNET_Y_WORD_REG        0x08
#define MAGNET_Z_WORD_REG        0x0A
#define GYRO_X_WORD_REG          0x12
#define GYRO_Y_WORD_REG          0x14
#define GYRO_Z_WORD_REG          0x16
#define TEMP_WORD_REG            0x18

typedef struct {
    I2C_HandleTypeDef *hi2c;  // Pointer to the I2C handle instance
    float offset_compass_value;
    float theta_origin;
    float theta_offset;
} CMPS12_Data;

// Function prototypes
void CMPS12_Init(CMPS12_Data *cmps12, I2C_HandleTypeDef *hi2c);
uint16_t CMPS12_GetAngle(CMPS12_Data *cmps12);
uint16_t CMPS12_GetAngle16(CMPS12_Data *cmps12);
int8_t CMPS12_GetPitch(CMPS12_Data *cmps12);
int8_t CMPS12_GetRoll(CMPS12_Data *cmps12);
char CMPS12_GetCalibrationStatus(CMPS12_Data *cmps12);
void CMPS12_Calibrate(CMPS12_Data *cmps12);
void CMPS12_StopCalibrate(CMPS12_Data *cmps12);
int16_t CMPS12_GetAccelX(CMPS12_Data *cmps12);
int16_t CMPS12_GetAccelY(CMPS12_Data *cmps12);
int16_t CMPS12_GetAccelZ(CMPS12_Data *cmps12);
int16_t CMPS12_GetMagnetX(CMPS12_Data *cmps12);
int16_t CMPS12_GetMagnetY(CMPS12_Data *cmps12);
int16_t CMPS12_GetMagnetZ(CMPS12_Data *cmps12);
int16_t CMPS12_GetGyroX(CMPS12_Data *cmps12);
int16_t CMPS12_GetGyroY(CMPS12_Data *cmps12);
int16_t CMPS12_GetGyroZ(CMPS12_Data *cmps12);
int16_t CMPS12_GetTemp(CMPS12_Data *cmps12);
void CMPS12_ResetOffsetValue(CMPS12_Data *cmps12);
void CMPS12_UpdateValue(CMPS12_Data *cmps12);
float CMPS12_GetCompassValue(CMPS12_Data *cmps12);
void CMPS12_ChangeThetaValue(CMPS12_Data *cmps12, float theta_robot);

#endif // CMPS12_H
