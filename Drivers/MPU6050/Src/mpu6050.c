/**
  ******************************************************************************
  * File Name          : mpu6050.c
  * Description        : Accelerometr MPU6050 Driver
  ******************************************************************************
  * @author     Roman Shcheglov
  * @copyright  Formula Student RUDN
  * @date       22-May-2017
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "mpu6050.h"

HAL_StatusTypeDef MPU_WriteRegister(MPU_HandleTypeDef *device, MPU_RegistersTypeDef reg, uint8_t data){
    return HAL_I2C_Mem_Write(device->hi2c, device->addr, reg, I2C_MEMADD_SIZE_8BIT, &data, 1, 10);
}

uint8_t MPU_ReadRegister(MPU_HandleTypeDef *device, MPU_RegistersTypeDef reg){
    uint8_t data;
    HAL_StatusTypeDef status;
    status = HAL_I2C_Mem_Read(device->hi2c, device->addr, reg, I2C_MEMADD_SIZE_8BIT, &data, 1, 10);
    if (status != HAL_OK){
        return 0;
    }
    else {
        return data;
    }
}

HAL_StatusTypeDef MPU_SetScaleA(MPU_HandleTypeDef *device, MPU_ScaleATypeDef scale){
    device->scaleAccel = scale;
    return MPU_WriteRegister(device, MPU_REG_ACCEL_CONFIG, (uint8_t)scale << 3);
}

HAL_StatusTypeDef MPU_SetScaleG(MPU_HandleTypeDef *device, MPU_ScaleGTypeDef scale){
    device->scaleGyro = scale;
    return MPU_WriteRegister(device, MPU_REG_GYRO_CONFIG, (uint8_t)scale << 3);
}

HAL_StatusTypeDef MPU_SetFIFOConfig(MPU_HandleTypeDef *device, uint8_t flags){
    return MPU_WriteRegister(device, MPU_REG_FIFO_EN, flags);
}

HAL_StatusTypeDef MPU_Init(MPU_HandleTypeDef *device){
    uint16_t code = 0;

    if (MPU_ReadRegister(device, MPU_REG_WHO_AM_I) != MPU_DEFAULT_WHO_AM_I_RESULT){
        return HAL_ERROR;
    }
    code |= MPU_WriteRegister(device, MPU_REG_PWR_MGMT_1,   0x00);
    code |= MPU_WriteRegister(device, MPU_REG_PWR_MGMT_2,   0xC0);
    code |= MPU_WriteRegister(device, MPU_REG_CONFIG,       0x06);
    code |= MPU_SetScaleA(device, device->scaleAccel);

    if (code > 0) {
        return HAL_BUSY;
    }
    else {
        return HAL_OK;
    }
}

int16_t MPU_getAccel(MPU_HandleTypeDef *device, MPU_AccelFlags accel){
    uint8_t data[2] = {0};
    uint16_t addr_h, addr_l;
    switch (accel) {
    case ACCEL_X:
        addr_h = MPU_REG_ACCEL_XOUT_H;
        addr_l = MPU_REG_ACCEL_XOUT_L;
        break;
    case ACCEL_Y:
        addr_h = MPU_REG_ACCEL_YOUT_H;
        addr_l = MPU_REG_ACCEL_YOUT_L;
        break;
    case ACCEL_Z:
        addr_h = MPU_REG_ACCEL_ZOUT_H;
        addr_l = MPU_REG_ACCEL_ZOUT_L;
        break;
    default:
        return 0;
    }
    HAL_I2C_Mem_Read(device->hi2c, device->addr, addr_h, I2C_MEMADD_SIZE_8BIT, &data[0], 1, 100);
    HAL_I2C_Mem_Read(device->hi2c, device->addr, addr_l, I2C_MEMADD_SIZE_8BIT, &data[1], 1, 100);
    return ((int16_t)(data[0] << 8 | data[1]));
}

int16_t MPU_getTemp(MPU_HandleTypeDef *device){
    uint8_t data[2] = {0};
    HAL_I2C_Mem_Read(device->hi2c, device->addr, MPU_REG_TEMP_OUT_H, I2C_MEMADD_SIZE_8BIT, &data[0], 1, 100);
    HAL_I2C_Mem_Read(device->hi2c, device->addr, MPU_REG_TEMP_OUT_L, I2C_MEMADD_SIZE_8BIT, &data[1], 1, 100);
    return ((int16_t)(data[0] << 8 | data[1])) / 340 + 37 ;
}
