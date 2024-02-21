#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "include/serial.h"


int input(PIDController *pid) {
    char userInput[4];
    double k;

    while(1){
        printf("give me an input (kp,ki,kd) otherwise break\n");
        scanf("%19s", userInput);
        printf("Entered: %s\n", userInput);

        if (strcmp(userInput,"kp") == 0) {
            printf("Altering kp, please input a float otherwise break)\n");
            scanf("%lf", &k);
            printf("Entered: %lf\n", k);

            if (!k) {
                break;
            }
            else{
                pid->Kp;
            }
        }
        if (strcmp(userInput,"ki") == 0) {
            printf("Altering ki, please input a float otherwise break\n");
            scanf("%lf", &k);
            printf("Entered: %lf\n", k);

            if (!k) {
                break;
            }
            else{
                pid->Ki;
            }
        }
        if (strcmp(userInput,"kd") == 0) {
            printf("Altering kd, please input a float otherwise break\n");
            scanf("%lf", &k);
            printf("Entered: %lf\n", k);

            if (!k) {
                break;
            }
            else{
                pid->Kd;
            }
        }
        else{
            break;
        }
    }
}