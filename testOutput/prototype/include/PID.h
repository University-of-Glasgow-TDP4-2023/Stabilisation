#pragma once

typedef struct PIDController {
    double Kp;
    double Ki;
    double Kd;

    double previous_error;
    double integral_error;
    double u;
    double y;
    double ref;

    int dt;

    uint64_t previous_time;
} PIDController;

void step_PID_controller(PIDController *controller);
