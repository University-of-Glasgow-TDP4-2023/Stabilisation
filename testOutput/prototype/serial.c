#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"


int input() {
    char userInput[20];
    // char interupt;
    // interupt = getchar();
    // if (interupt == '\n')

    while(1){
        printf("give me an input (kp,ki) ;.. break\n");
        scanf("%19s", userInput);
        printf("Entered: %s\n", userInput);

        if (strcmp(userInput,"kp") == 0) {
            while (1)
            {
                printf("Altering kp, please input a value('b' to break)\n");
                scanf("%19s", userInput);
                printf("Entered: %s\n", userInput);

                if (strcmp(userInput,"b") == 0) {
                    break;
                }


            }
        }
        if (strcmp(userInput,"ki") == 0) {
            while (1)
            {
                printf("Altering ki, please input a value('b' to break)\n");
                scanf("%19s", userInput);
                printf("Entered: %s\n", userInput);

                if (strcmp(userInput,"b") == 0) {
                    break;
                }

            }
        }
        else{
            break;
        }
    }
}