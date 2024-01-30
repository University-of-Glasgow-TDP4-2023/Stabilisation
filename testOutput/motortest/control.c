#include <stdio.h>
#include "pico/stdlib.h"

#define out1 6
#define out2 7
#define enA 8


// Defining motor pins
void setup(){
    gpio_init(out1);
    gpio_init(out2);
    gpio_init(enA);

    gpio_set_dir(out1, GPIO_OUT);
    gpio_set_dir(out2, GPIO_OUT);
    gpio_set_dir(enA, GPIO_OUT);
    
    gpio_put(out1,0);
    gpio_put(out2,0);
    gpio_put(enA, 1);
}

void turn_right(){
    gpio_put(out1,0);
    gpio_put(out2,1);
}

void turn_left(){
    gpio_put(out1,1);
    gpio_put(out2,0);
}

void stop(){
    gpio_put(out1,0);
    gpio_put(out2,0);
}


int main(){
    stdio_init_all();
    setup();
    
    while(1){
        turn_right();
        printf("Turn right\n\r");
        sleep_ms(1000);
        stop();
        printf("stop\n\r");
        sleep_ms(1000);
    }
}
