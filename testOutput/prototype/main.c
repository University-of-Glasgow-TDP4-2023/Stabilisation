#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "include/IMU.h"
#include "include/motor.h"

#define IMU_RX_PIN 4
#define IMU_TX_PIN 5

// #define MOTOR_PIN_1         6
// #define MOTOR_PIN_2         7
// #define MOTOR_PIN_ENABLE_A  8
#define MOTOR_PIN_1         21
#define MOTOR_PIN_2         20
#define MOTOR_PIN_ENABLE_A  16

IMU_Data imu_data;

int main(void){
    stdio_init_all(); // Initialise STD I/O for printing over serial

    
    sleep_ms(5000);

    // Call accelerometer initialisation function
    IMU_I2C_init(IMU_RX_PIN, IMU_TX_PIN);

    // Setup the motor driver
    // Motor motor;
    struct Motor motor;
    motor.in1 = 0;
    motor.in2 = 0;
    motor.enableA = 1;
    motor_driver_init(&motor, MOTOR_PIN_1, MOTOR_PIN_2, MOTOR_PIN_ENABLE_A); 

    // Infinite Loop
    while(1){
        IMU_get_abs_eul_angle(&imu_data);

        printf("%f, %f, %f\n", imu_data.pitch, imu_data.roll, imu_data.yaw);

        // //normalise the value to between -1 and 1
        float pitch_norm = ((imu_data.pitch / 580) * 2 ) - 1;

        printf("Pitch norm: %f\n", pitch_norm);
        motor_drive(&motor,pitch_norm);
        sleep_ms(5000);
        //printf("hello\n\r");
    }
}