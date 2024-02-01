#pragma once

#define I2C_PORT i2c0
#define IMU_I2C_ADDR 0x28

typedef struct IMU_Data {
    float pitch;
    float yaw;
    float roll;
} IMU_Data;

void IMU_I2C_init();

void IMU_get_abs_eul_angle(IMU_Data *data);