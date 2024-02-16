#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "math.h"
#include "include/PID.h"


void step_PID_controller(PIDController *PID)
{   
    // Find dt using the hardware timer
    // uint64_t current_time = time_us_64();
    // double dt = (current_time - PID->previous_time) * pow(10, -6); // dt in seconds
    // PID->previous_time = current_time;

    // Find the error
    double error = PID->y - PID->ref;

    // Calculate the derivative and integral numerically
    PID->previous_error = error;
    PID->integral_error += error;
    double derivative_error = PID->previous_error - error;

    // Find the control value, u.
    PID->u = (PID->Kp * error) + (PID->Ki * PID->integral_error * PID->dt) + (PID->Kd * derivative_error / PID->dt);
}