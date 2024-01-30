 #include <stdio.h>
 #include "pico/stdlib.h"
 #include "hardware/adc.h"


#define delay 1000
#define out1 6
#define out2 7
#define enA 8
#define pot 26


// Defining motor pins
void setup(){
    adc_init(); // for the pot input
    gpio_init(out1);
    gpio_init(out2);
    gpio_init(enA);
    adc_gpio_init(pot);

    gpio_set_dir(out1, GPIO_OUT);
    gpio_set_dir(out2, GPIO_OUT);
    gpio_set_dir(enA, GPIO_OUT);
    adc_select_input(0);
    
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
        // 12-bit conversion, assume max value == ADC_VREF == 3.3 V
         const float conversion_factor = 3.3f / (1 << 12);
         uint16_t result = adc_read();
         printf("Raw value: 0x%03x, voltage: %f V\n", result, result * conversion_factor);
         sleep_ms(delay);

        // turn_right();
        // printf("Turn right\n\r");
        // sleep_ms(1000);
        // stop();
        // printf("stop\n\r");
        // sleep_ms(1000);
    }
}
