#pragma once
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

typedef struct Motor
{
    int in1;
    int in2;
    int enableA;
} Motor;

/*! \brief Initialise the output pins to drive the motor
 *
 * \param motor     The motor handle
 * \param in1       The GPIO pin that goes to the l298's input1
 * \param in2       The GPIO pin that goes to the l298's input2
 * \param enableA   The GPIO pin that goes to the l298's enable A
 */
void motor_driver_init(Motor *motor, int in1, int in2, int enableA);

void pwm_setup();

void turn_right(Motor *motor, float a);

void turn_left(Motor *motor, float a);

void stop(Motor *motor);

void motor_drive(Motor *motor, float result_norm);