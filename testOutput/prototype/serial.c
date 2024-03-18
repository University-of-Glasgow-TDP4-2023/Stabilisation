#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "include/serial.h"
#include "include/motor.h"
#include "hardware/pwm.h"


PIDController input(PIDController pid, Motor *motor) {
    char userInput[4];
    double k;

    while(1){
        printf("give me an input (kp,ki,kd,pwm,f(fullspeed),l(left),r(right),s(stop)) otherwise break\n");
        scanf("%19s", userInput);
        printf("Entered: %s\n", userInput);

        if (strcmp(userInput,"kp") == 0) {
            printf("Altering kp, please input a float otherwise break)\n");
            scanf("%lf", &k);
            printf("Entered: %lf\n", k);

            if (!k) {
                return pid;
            }
            else{
                pid.Kp = k;
                pid.integral_error = 0;
                pid.previous_error = 0;
                return pid;
            }
        }
        if (strcmp(userInput,"ki") == 0) {
            printf("Altering ki, please input a float otherwise break\n");
            scanf("%lf", &k);
            printf("Entered: %lf\n", k);

            if (!k) {
                return pid;
            }
            else{
                pid.Ki = k;
                pid.integral_error = 0;
                pid.previous_error = 0;
                return pid;
            }
        }
        if (strcmp(userInput,"kd") == 0) {
            printf("Altering kd, please input a float otherwise break\n");
            scanf("%lf", &k);
            printf("Entered: %lf\n", k);

            if (!k) {
                return pid;
            }
            else{
                pid.Kd = k;
                pid.integral_error = 0;
                pid.previous_error = 0;
                return pid;
            }
        }
        if (strcmp(userInput,"pwm") == 0) {
            printf("Testing PWM output\n");
            scanf("%lf", &k);
            printf("Entered: %lf\n", k);

            if (!k) {
                return pid;
            }
            else{
                char interupt = getchar_timeout_us(0);
                while (interupt == 255){
                    pwm_set_gpio_level(16, (int)k);
                    interupt = getchar_timeout_us(0);
                }
                return pid;
            }
        }
        if (strcmp(userInput,"f") == 0) {
            printf("Full speed\n");
            printf("l(left), r(right), s(stop), e(exit)\n");
            char last_input = 255;
            while (1){
                char new_input = getchar_timeout_us(0);
                if (new_input != 255){
                    last_input = new_input;
                }
                if (last_input == 'l') {
                    turn_left(motor, 1);
                }
                if (last_input == 'r') {
                    turn_right(motor, -1);
                }
                if (last_input == 's') {
                    stop(motor);
                }
                if (last_input == 'e') {
                    break;
                }
            }
            pid.integral_error = 0;
            pid.previous_error = 0;
            return pid;
        }
        if (strcmp(userInput,"l") == 0) {
            printf("Full speed left\n");
            
            char interupt = getchar_timeout_us(0);
            while (interupt == 255){
                turn_left(motor, 1);
                interupt = getchar_timeout_us(0);
            }
            pid.integral_error = 0;
            pid.previous_error = 0;
            return pid;
        }
        if (strcmp(userInput,"r") == 0) {
            printf("Full speed right\n");
            turn_right(motor, 1);

            char interupt = getchar_timeout_us(0);
            while (interupt == 255){
                turn_right(motor, -1);
                interupt = getchar_timeout_us(0);
            }
            pid.integral_error = 0;
            pid.previous_error = 0;
            return pid;
        }
        if (strcmp(userInput,"s") == 0) {
            printf("Full stop\n");
            turn_right(motor, 1);

            char interupt = getchar_timeout_us(0);
            while (interupt == 255){
                stop(motor);
                interupt = getchar_timeout_us(0);
            }
            pid.integral_error = 0;
            pid.previous_error = 0;
            return pid;
        }
        else{
            return pid;
        }
    }
}