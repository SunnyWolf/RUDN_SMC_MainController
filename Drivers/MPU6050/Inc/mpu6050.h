/**
 ******************************************************************************
 * File Name    : mpu6050.h
 * Description  : This file contains the defines for MPU6050 driver
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MPU6050_H
#define __MPU6050_H
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
/* Private define ------------------------------------------------------------*/
#define MPU_DEFAULT_ADDR (uint16_t)208
#define MPU_DEFAULT_WHO_AM_I_RESULT 0x68

/* Define registers ----------------------------------------------------------*/
typedef enum{
    MPU_REG_SELF_TEST_X  = 13,
    MPU_REG_SELF_TEST_Y  = 14,
    MPU_REG_SELF_TEST_Z  = 15,
    MPU_REG_SELF_TEST_A  = 15,
    MPU_REG_SMPLRT_DIV   = 25,
    MPU_REG_CONFIG       = 26,
    MPU_REG_GYRO_CONFIG  = 27,
    MPU_REG_ACCEL_CONFIG = 28,
    MPU_REG_MOT_THR      = 31,
    MPU_REG_FIFO_EN      = 35,
    MPU_REG_ACCEL_XOUT_H = 59,
    MPU_REG_ACCEL_XOUT_L = 60,
    MPU_REG_ACCEL_YOUT_H = 61,
    MPU_REG_ACCEL_YOUT_L = 62,
    MPU_REG_ACCEL_ZOUT_H = 63,
    MPU_REG_ACCEL_ZOUT_L = 64,
    MPU_REG_TEMP_OUT_H   = 65,
    MPU_REG_TEMP_OUT_L   = 66,
    MPU_REG_PWR_MGMT_1   = 107,
    MPU_REG_PWR_MGMT_2   = 108,
    MPU_REG_WHO_AM_I     = 117
} MPU_RegistersTypeDef;

typedef enum {
    MPU_SCALE_ACCEL_2G = 0,
    MPU_SCALE_ACCEL_4G = 1,
    MPU_SCALE_ACCEL_8G = 2,
    MPU_SCALE_ACCEL_16G = 3
} MPU_ScaleATypeDef;

typedef enum {
    MPU_SCALE_GYRO_250 = 0, // 250 grad/s
    MPU_SCALE_GYRO_500 = 1, // 500 grad/s
    MPU_SCALE_GYRO_1000 = 2, // 1000 grad/s
    MPU_SCALE_GYRO_2000 = 3  // 2000 grad/s
} MPU_ScaleGTypeDef;

typedef enum {
    MPU_FIFO_NONE  = 0,
    MPU_FIFO_SLV_0 = 1,
    MPU_FIFO_SLV_1 = 2,
    MPU_FIFO_SLV_2 = 4,
    MPU_FIFO_ACCEL = 8,
    MPU_FIFO_GYROZ = 16,
    MPU_FIFO_GYROY = 32,
    MPU_FIFO_GYROX = 64,
    MPU_FIFO_TEMP  = 128
} MPU_ConfigFIFOFlags;

typedef struct {
    I2C_HandleTypeDef *hi2c;
    int16_t addr;
    MPU_ScaleATypeDef scaleAccel;
    MPU_ScaleGTypeDef scaleGyro;
} MPU_HandleTypeDef;

typedef enum {
    ACCEL_X,
    ACCEL_Y,
    ACCEL_Z
} MPU_AccelFlags;

/* Interface ----------------------------------------------------------*/
HAL_StatusTypeDef MPU_WriteRegister(MPU_HandleTypeDef *device, MPU_RegistersTypeDef reg, uint8_t data);
uint8_t MPU_ReadRegister(MPU_HandleTypeDef *device, MPU_RegistersTypeDef reg);
HAL_StatusTypeDef MPU_SetScaleA(MPU_HandleTypeDef *device, MPU_ScaleATypeDef scale);
HAL_StatusTypeDef MPU_SetScaleG(MPU_HandleTypeDef *device, MPU_ScaleGTypeDef scale);
HAL_StatusTypeDef MPU_SetFIFOConfig(MPU_HandleTypeDef *device, uint8_t flags);
HAL_StatusTypeDef MPU_Init(MPU_HandleTypeDef *device);

int16_t MPU_getAccel(MPU_HandleTypeDef *device, MPU_AccelFlags accel);
int16_t MPU_getTemp(MPU_HandleTypeDef *device);
#ifdef __cplusplus
}
#endif
#endif /* __MPU6050_H */
