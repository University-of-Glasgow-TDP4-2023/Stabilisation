#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "include/IMU.h"
//#include "include/motor.h"

#define IMU_RX_PIN 4
#define IMU_TX_PIN 5

#define MOTOR_PIN_1         6
#define MOTOR_PIN_2         7
#define MOTOR_PIN_ENABLE_A  8

IMU_Data imu_data;

int main(void){
    stdio_init_all(); // Initialise STD I/O for printing over serial

    
    sleep_ms(5000);

    // Call accelerometer initialisation function
    IMU_I2C_init(IMU_RX_PIN, IMU_TX_PIN);

    // Setup the motor driver
    // Motor motor;
    // motor_driver_init(&motor, MOTOR_PIN_1, MOTOR_PIN_2, MOTOR_PIN_ENABLE_A); 

    // Infinite Loop
    while(1){
        IMU_get_abs_eul_angle(&imu_data);

        printf("%f, %f, %f", imu_data.pitch, imu_data.roll, imu_data.yaw);
        //printf("hello\n\r");
    }
}