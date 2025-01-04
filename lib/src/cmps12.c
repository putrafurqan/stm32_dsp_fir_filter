#include "cmps12.h"

void CMPS12_Init(CMPS12_Data *cmps12, I2C_HandleTypeDef *hi2c) {
    cmps12->hi2c = hi2c;
    cmps12->offset_compass_value = 0;
    cmps12->theta_origin = 0;
    cmps12->theta_offset = 0;
}

static void CMPS12_WriteRegister(CMPS12_Data *cmps12, uint8_t reg, uint8_t *data, uint16_t size) {
    HAL_I2C_Master_Transmit(cmps12->hi2c, CMPS12_I2C_ADDRESS << 1, &reg, 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Transmit(cmps12->hi2c, CMPS12_I2C_ADDRESS << 1, data, size, HAL_MAX_DELAY);
}

static void CMPS12_ReadRegister(CMPS12_Data *cmps12, uint8_t reg, uint8_t *data, uint16_t size) {
    HAL_I2C_Master_Transmit(cmps12->hi2c, CMPS12_I2C_ADDRESS << 1, &reg, 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(cmps12->hi2c, CMPS12_I2C_ADDRESS << 1, data, size, HAL_MAX_DELAY);
}

uint16_t CMPS12_GetAngle(CMPS12_Data *cmps12) {
    uint8_t registerNumber = COMPASS_BEARING_WORD_REG;
    uint8_t registerContents[2] = {0};

    CMPS12_ReadRegister(cmps12, registerNumber, registerContents, 2);
    return ((uint16_t)registerContents[0] << 8) | registerContents[1];
}

uint16_t CMPS12_GetAngle16(CMPS12_Data *cmps12) {
    uint8_t registerNumber = COMPASS_BEARING16_WORD_REG;
    uint8_t registerContents[2] = {0};

    CMPS12_ReadRegister(cmps12, registerNumber, registerContents, 2);
    return ((uint16_t)registerContents[0] << 8) | registerContents[1];
}

int8_t CMPS12_GetPitch(CMPS12_Data *cmps12) {
    uint8_t registerNumber = COMPASS_PITCH_WORD_REG;
    uint8_t registerContents[2] = {0};

    CMPS12_ReadRegister(cmps12, registerNumber, registerContents, 2);
    return (int8_t)((int16_t)registerContents[0] << 8 | registerContents[1]);
}

int8_t CMPS12_GetRoll(CMPS12_Data *cmps12) {
    uint8_t registerNumber = COMPASS_ROLL_WORD_REG;
    uint8_t registerContents[1] = {0};

    CMPS12_ReadRegister(cmps12, registerNumber, registerContents, 1);
    return (int8_t)registerContents[0];
}

char CMPS12_GetCalibrationStatus(CMPS12_Data *cmps12) {
    uint8_t registerNumber = 0x1E;  // Calibration status register
    uint8_t status = 0;

    CMPS12_WriteRegister(cmps12, registerNumber, NULL, 0);
    CMPS12_ReadRegister(cmps12, registerNumber, &status, 1);
    return status;
}

void CMPS12_Calibrate(CMPS12_Data *cmps12) {
    uint8_t registerNumber = SOFTWARE_REVISION_REG;
    uint8_t calibrate_data1 = 0xF0;
    uint8_t calibrate_data2 = 0xF5;
    uint8_t calibrate_data3 = 0xF6;

    CMPS12_WriteRegister(cmps12, registerNumber, &calibrate_data1, 1);
    // HAL_Delay(25);
    CMPS12_WriteRegister(cmps12, registerNumber, &calibrate_data2, 1);
    // HAL_Delay(25);
    CMPS12_WriteRegister(cmps12, registerNumber, &calibrate_data3, 1);
}

void CMPS12_StopCalibrate(CMPS12_Data *cmps12) {
    uint8_t registerNumber = SOFTWARE_REVISION_REG;
    uint8_t calibrate_data1 = 0xF8;

    CMPS12_WriteRegister(cmps12, registerNumber, &calibrate_data1, 1);
}

int16_t CMPS12_GetAccelX(CMPS12_Data *cmps12) {
    uint8_t registerNumber = ACCEL_X_WORD_REG;
    uint8_t registerContents[2] = {0};

    CMPS12_ReadRegister(cmps12, registerNumber, registerContents, 2);
    return (int16_t)((int16_t)registerContents[0] << 8 | registerContents[1]);
}

int16_t CMPS12_GetAccelY(CMPS12_Data *cmps12) {
    uint8_t registerNumber = ACCEL_Y_WORD_REG;
    uint8_t registerContents[2] = {0};

    CMPS12_ReadRegister(cmps12, registerNumber, registerContents, 2);
    return (int16_t)((int16_t)registerContents[0] << 8 | registerContents[1]);
}

int16_t CMPS12_GetAccelZ(CMPS12_Data *cmps12) {
    uint8_t registerNumber = ACCEL_Z_WORD_REG;
    uint8_t registerContents[2] = {0};

    CMPS12_ReadRegister(cmps12, registerNumber, registerContents, 2);
    return (int16_t)((int16_t)registerContents[0] << 8 | registerContents[1]);
}

int16_t CMPS12_GetMagnetX(CMPS12_Data *cmps12) {
    uint8_t registerNumber = MAGNET_X_WORD_REG;
    uint8_t registerContents[2] = {0};

    CMPS12_ReadRegister(cmps12, registerNumber, registerContents, 2);
    return (int16_t)((int16_t)registerContents[0] << 8 | registerContents[1]);
}

int16_t CMPS12_GetMagnetY(CMPS12_Data *cmps12) {
    uint8_t registerNumber = MAGNET_Y_WORD_REG;
    uint8_t registerContents[2] = {0};

    CMPS12_ReadRegister(cmps12, registerNumber, registerContents, 2);
    return (int16_t)((int16_t)registerContents[0] << 8 | registerContents[1]);
}

int16_t CMPS12_GetMagnetZ(CMPS12_Data *cmps12) {
    uint8_t registerNumber = MAGNET_Z_WORD_REG;
    uint8_t registerContents[2] = {0};

    CMPS12_ReadRegister(cmps12, registerNumber, registerContents, 2);
    return (int16_t)((int16_t)registerContents[0] << 8 | registerContents[1]);
}

int16_t CMPS12_GetGyroX(CMPS12_Data *cmps12) {
    uint8_t registerNumber = GYRO_X_WORD_REG;
    uint8_t registerContents[2] = {0};

    CMPS12_ReadRegister(cmps12, registerNumber, registerContents, 2);
    return (int16_t)((int16_t)registerContents[0] << 8 | registerContents[1]);
}

int16_t CMPS12_GetGyroY(CMPS12_Data *cmps12) {
    uint8_t registerNumber = GYRO_Y_WORD_REG;
    uint8_t registerContents[2] = {0};

    CMPS12_ReadRegister(cmps12, registerNumber, registerContents, 2);
    return (int16_t)((int16_t)registerContents[0] << 8 | registerContents[1]);
}

int16_t CMPS12_GetGyroZ(CMPS12_Data *cmps12) {
    uint8_t registerNumber = GYRO_Z_WORD_REG;
    uint8_t registerContents[2] = {0};

    CMPS12_ReadRegister(cmps12, registerNumber, registerContents, 2);
    return (int16_t)((int16_t)registerContents[0] << 8 | registerContents[1]);
}

int16_t CMPS12_GetTemp(CMPS12_Data *cmps12) {
    uint8_t registerNumber = TEMP_WORD_REG;
    uint8_t registerContents[2] = {0};

    CMPS12_ReadRegister(cmps12, registerNumber, registerContents, 2);
    return (int16_t)((int16_t)registerContents[0] << 8 | registerContents[1]);
}

void CMPS12_ResetOffsetValue(CMPS12_Data *cmps12) {
    cmps12->offset_compass_value = (float)CMPS12_GetAngle(cmps12) / 10.0f;
}

void CMPS12_UpdateValue(CMPS12_Data *cmps12) {
    cmps12->theta_origin = (float)CMPS12_GetAngle(cmps12) / 10.0f;
    cmps12->theta_offset = cmps12->theta_origin - cmps12->offset_compass_value;
}

float CMPS12_GetCompassValue(CMPS12_Data *cmps12) {
    float theta_transformed;

    if (cmps12->theta_offset > 180.0f && cmps12->theta_offset <= 360.0f) {
        theta_transformed = (cmps12->theta_origin - 360.0f - cmps12->offset_compass_value) / -1.0f; // Convert to degrees
    } else if (cmps12->theta_offset < -180.0f && cmps12->theta_offset >= -360.0f) {
        theta_transformed = (cmps12->theta_origin + 360.0f - cmps12->offset_compass_value) / -1.0f; // Convert to degrees
    } else {
        theta_transformed = (cmps12->theta_origin - cmps12->offset_compass_value) / -1.0f; // Convert to degrees
    }

    return theta_transformed;
}

void CMPS12_ChangeThetaValue(CMPS12_Data *cmps12, float theta_robot) {
    if (theta_robot >= -180 && theta_robot < 0) {
        theta_robot = 360 + theta_robot;
    }

    cmps12->theta_offset = cmps12->theta_origin - theta_robot;

    if (cmps12->theta_offset < 0) {
        cmps12->theta_offset += 360;
    }
}
