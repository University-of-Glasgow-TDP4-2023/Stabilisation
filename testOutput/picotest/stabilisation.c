// /**
//  * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
//  *
//  * SPDX-License-Identifier: BSD-3-Clause
//  */

// #include <stdio.h>
// #include <string.h>
// #include "pico/stdlib.h"
// #include "pico/binary_info.h"
// #include "hardware/i2c.h"

// const uint8_t ADDRESS = 0x58;

// const uint8_t ADDRESS = 0x1D;

// //hardware registers
// const uint8_t REG_X_MSB = 0x01;
// const uint8_t REG_X_LSB = 0x02;
// const uint8_t REG_Y_MSB = 0x03;
// const uint8_t REG_Y_LSB = 0x04;
// const uint8_t REG_Z_MSB = 0x05;
// const uint8_t REG_Z_LSB = 0x06;
// const uint8_t REG_DATA_CFG = 0x0E;
// const uint8_t REG_CTRL_REG1 = 0x2A;

// // Set the range and precision for the data 
// const uint8_t range_config = 0x01; // 0x00 for ±2g, 0x01 for ±4g, 0x02 for ±8g
// const float count = 2048; // 4096 for ±2g, 2048 for ±4g, 1024 for ±8g

// uint8_t buf[2];


// #ifdef i2c_default
// void mma8451_set_state(uint8_t state) {
//     buf[0] = REG_CTRL_REG1;
//     buf[1] = state; // Set RST bit to 1
//     i2c_write_blocking(i2c_default, ADDRESS, buf, 2, false);
// }
// #endif


// int main() {
//     stdio_init_all();
//     while (true) {
//         printf("Marina is Gorgus!\n");
//         sleep_ms(1000);
//     }
// }


#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define I2C_PORT i2c0

static int addr = 0x28;

// Initialise Accelerometer Function
void accel_init(void){
    // Check to see if connection is correct
    sleep_ms(1000); // Add a short delay to help BNO005 boot up
    uint8_t reg = 0x00;
    uint8_t chipID[1];
    i2c_write_blocking(I2C_PORT, addr, &reg, 1, true);
    i2c_read_blocking(I2C_PORT, addr, chipID, 1, false);

    if(chipID[0] != 0xA0){
        while(1){
            printf("Chip ID Not Correct - Check Connection!");
            sleep_ms(5000);
        }
    }

    // Use internal oscillator
    uint8_t data[2];
    data[0] = 0x3F;
    data[1] = 0x40;
    i2c_write_blocking(I2C_PORT, addr, data, 2, true);

    // Reset all interrupt status bits
    data[0] = 0x3F;
    data[1] = 0x01;
    i2c_write_blocking(I2C_PORT, addr, data, 2, true);

    // Configure Power Mode
    data[0] = 0x3E;
    data[1] = 0x00;
    i2c_write_blocking(I2C_PORT, addr, data, 2, true);
    sleep_ms(50);

    // Defaul Axis Configuration
    data[0] = 0x41;
    data[1] = 0x24;
    i2c_write_blocking(I2C_PORT, addr, data, 2, true);

    // Default Axis Signs
    data[0] = 0x42;
    data[1] = 0x00;
    i2c_write_blocking(I2C_PORT, addr, data, 2, true);

    // Set units to m/s^2
    data[0] = 0x3B;
    data[1] = 0b0000000;
    i2c_write_blocking(I2C_PORT, addr, data, 2, true);
    sleep_ms(30);

    // Set operation to acceleration only
    data[0] = 0x3D;
    data[1] = 0x0C;
    i2c_write_blocking(I2C_PORT, addr, data, 2, true);
    sleep_ms(100);
}

int main(void){
    stdio_init_all(); // Initialise STD I/O for printing over serial

    // Configure the I2C Communication
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(4, GPIO_FUNC_I2C);
    gpio_set_function(5, GPIO_FUNC_I2C);
    gpio_pull_up(4);
    gpio_pull_up(5);

    // Call accelerometer initialisation function
    accel_init();

    uint8_t accel[6]; // Store data from the 6 acceleration registers
    int16_t accelX, accelY, accelZ; // Combined 3 axis data
    float f_accelX, f_accelY, f_accelZ; // Float type of acceleration data
    uint8_t val = 0x08; // Start register address 0x1A


    uint8_t euler[6]; // Store data from the 6 acceleration registers
    int16_t eulX, eulY, eulZ; // Combined 3 axis data
    float f_eulX, f_eulY, f_eulZ; // Float type of acceleration data
    uint8_t eul_val = 0x1a; // Start register address 0x1A

    // Infinite Loop
    while(1){
        i2c_write_blocking(I2C_PORT, addr, &val, 1, true);
        i2c_read_blocking(I2C_PORT, addr, accel, 6, false);

        accelX = ((accel[1]<<8) | accel[0]);
        accelY = ((accel[3]<<8) | accel[2]);
        accelZ = ((accel[5]<<8) | accel[4]);

        f_accelX = accelX / 100.00;
        f_accelY = accelY / 100.00;
        f_accelZ = accelZ / 100.00;

        // Print to serial monitor
        printf("AX: %6.2f    AY: %6.2f    AZ: %6.2f\n", f_accelX, f_accelY, f_accelZ);



        i2c_write_blocking(I2C_PORT, addr, &eul_val, 1, true);
        i2c_read_blocking(I2C_PORT, addr, euler, 6, false);

        eulX = ((euler[1]<<8) | euler[0]);
        eulY = ((euler[3]<<8) | euler[2]);
        eulZ = ((euler[5]<<8) | euler[4]);

        f_eulX = eulX / 10.00;
        f_eulY = eulY / 10.00;
        f_eulZ = eulZ / 10.00;

        // Print to serial monitor
        printf("EX: %6.2f    EY: %6.2f    EZ: %6.2f\n", f_eulX, f_eulY, f_eulZ);
        sleep_ms(300);
    }
}