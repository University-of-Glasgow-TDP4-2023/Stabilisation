#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "math.h"

typedef struct PIDController {
    double Kp;
    double Ki;
    double Kd;

    double previous_error;
    double integral_error;
    double u;
    double y;
    double ref;

    uint64_t previous_time;
} PIDController;

int get_orientation_degrees()
{
    return 45;
}

void drive_motor(double u) {
    printf("Motor go brrr\n\r");
}

void step_PID_controller(PIDController *PID);
{   
    // Find dt using the hardware timer
    uint64_t current_time = time_us_64();
    double dt = (current_time - PID->previous_time) * pow(10, -6); // dt in seconds
    PID->previous_time = current_time;

    // Find the error
    double error = PID->y - PID->ref;

    // Calculate the derivative and integral numerically
    PID->previous_error = error;
    PID->integral_error += error;
    double derivative_error = PID->previous_error - error;

    // Find the control value, u.
    PID->u = (PID->Kp * error) + (PID->Ki * PID->integral_error * dt) + (PID->Kd * derivative_error / dt);
}

int main()
{
    PIDController controller = {0};

    while (1)
    {
        controller.y = get_orientation_degrees();
        step_PID_controller(&controller);
        drive_motor(controller.u);
    }
}