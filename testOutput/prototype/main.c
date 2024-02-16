#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "include/IMU.h"
#include "include/motor.h"
#include "math.h"

#define IMU_RX_PIN 4
#define IMU_TX_PIN 5

#define USING_BREADBOARD
//#define USING_PCB

#ifdef USING_BREADBOARD
#define MOTOR_PIN_1         6
#define MOTOR_PIN_2         7
#define MOTOR_PIN_ENABLE_A  8
#endif

#ifdef USING_PCB
#define MOTOR_PIN_1         21
#define MOTOR_PIN_2         20
#define MOTOR_PIN_ENABLE_A  16
#endif

IMU_Data imu_data;

int main(void){
    stdio_init_all(); // Initialise STD I/O for printing over serial

    sleep_ms(5000);

    // Call accelerometer initialisation function
    IMU_I2C_init(IMU_RX_PIN, IMU_TX_PIN);

    // Setup the motor driver
    Motor motor;
    motor_driver_init(&motor, MOTOR_PIN_1, MOTOR_PIN_2, MOTOR_PIN_ENABLE_A);

    // Infinite Loop
    while(1){
        IMU_get_abs_eul_angle(&imu_data);

        printf("IMU: %f, %f, %f\n\r", imu_data.pitch, imu_data.roll, imu_data.yaw);

        //normalise the value to between -1 and 1
        float pitch_norm = ((imu_data.pitch / 580) * 2 ) - 1;

        motor_drive(&motor,pitch_norm);
        sleep_ms(10);
    }
}