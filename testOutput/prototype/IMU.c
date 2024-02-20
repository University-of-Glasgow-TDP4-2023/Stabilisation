#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "include/IMU.h"

// Initialise Accelerometer Function
void IMU_I2C_init(int rx_pin, int tx_pin){

    printf("configuring the IMU\n\r");

    // Configure the I2C Communication
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(rx_pin, GPIO_FUNC_I2C);
    gpio_set_function(tx_pin, GPIO_FUNC_I2C);
    gpio_pull_up(rx_pin);
    gpio_pull_up(tx_pin);

    // Check to see if connection is correct by reading chipIP
    sleep_ms(1000); // Add a short delay to help BNO005 boot up
    uint8_t reg = 0x00;
    uint8_t chipID[1];
    i2c_write_blocking(I2C_PORT, IMU_I2C_ADDR, &reg, 1, true);
    i2c_read_blocking(I2C_PORT, IMU_I2C_ADDR, chipID, 1, false);

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
    i2c_write_blocking(I2C_PORT, IMU_I2C_ADDR, data, 2, true);

    // Reset all interrupt status bits
    data[0] = 0x3F;
    data[1] = 0x01;
    i2c_write_blocking(I2C_PORT, IMU_I2C_ADDR, data, 2, true);

    // Configure Power Mode
    data[0] = 0x3E;
    data[1] = 0x00;
    i2c_write_blocking(I2C_PORT, IMU_I2C_ADDR, data, 2, true);
    sleep_ms(50);

    // Defaul Axis Configuration
    data[0] = 0x41;
    data[1] = 0x24;
    i2c_write_blocking(I2C_PORT, IMU_I2C_ADDR, data, 2, true);

    // Default Axis Signs
    data[0] = 0x42;
    data[1] = 0x00;
    i2c_write_blocking(I2C_PORT, IMU_I2C_ADDR, data, 2, true);

    // Set units to m/s^2
    data[0] = 0x3B;
    data[1] = 0b0000000;
    i2c_write_blocking(I2C_PORT, IMU_I2C_ADDR, data, 2, true);
    sleep_ms(30);

    // Set operation to acceleration only
    data[0] = 0x3D;
    data[1] = 0x0C;
    i2c_write_blocking(I2C_PORT, IMU_I2C_ADDR, data, 2, true);
    sleep_ms(100);
    printf("configuring done\n\r");
}

// Get the absolute orientation from the IMU
void IMU_get_abs_eul_angle(IMU_Data *data)
{
    // printf("getting the angle\n\r");
    uint8_t euler[6]; // Store data from the 6 acceleration registers
    int16_t eulX, eulY, eulZ; // Combined 3 axis data
    uint8_t eul_val = 0x1a; // Start register address 0x1A

    i2c_write_blocking(I2C_PORT, IMU_I2C_ADDR, &eul_val, 1, true);
    i2c_read_blocking(I2C_PORT, IMU_I2C_ADDR, euler, 6, false);

    eulX = ((euler[1]<<8) | euler[0]);
    eulY = ((euler[3]<<8) | euler[2]);
    eulZ = ((euler[5]<<8) | euler[4]);

    data->pitch = eulX / 10.00;
    data->roll = eulY / 10.00;
    data->yaw = eulZ / 10.00;
}