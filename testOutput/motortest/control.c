#include <stdio.h>
#include "pico/stdlib.h"

#define out1 6
#define out2 7
#define enA 8

// Code to test the setup, later we will want to make the code use PWM for finer control
// Then integrate the two code bases


// Defining motor pins
int setup(){
    gpio_init(out1);
    gpio_init(out2);
    gpio_init(enA);
    
    gpio_put(out1,0);
    gpio_put(out2,0);
    gpio_put(enA, 1);
}

int turn_right(){
    gpio_put(out1,0);
    gpio_put(out2,1);
}

int turn_left(){
    gpio_put(out1,1);
    gpio_put(out2,0);
}

int stop(){
    gpio_put(out1,0);
    gpio_put(out2,0);
}


int main(void){
    stdio_init_all();
    setup();
    
    while(1){
        turn_right();
        printf("Turn right");
        sleep_ms(5000);
        stop();
        printf("Stop");
        sleep_ms(5000);
        turn_left();
        printf("Turn left");
        sleep_ms(5000);
        stop();
        printf("Stop");
        sleep_ms(5000);
    }
}
