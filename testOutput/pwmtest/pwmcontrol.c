 #include <stdio.h>
 #include "pico/stdlib.h"
 #include "hardware/adc.h"
 #include "hardware/pwm.h"
// https://github.com/raspberrypi/pico-examples/blob/master/pwm/measure_duty_cycle/measure_duty_cycle.c

#define delay 1000
#define out1 6
#define out2 7
#define enA 8
#define pot 26
#define bounds 0.1


// Defining motor pins
void setup(){
    adc_init(); // for the pot input
    gpio_init(out1);
    gpio_init(out2);
    gpio_set_function(enA, GPIO_FUNC_PWM);
    adc_gpio_init(pot);

    gpio_set_dir(out1, GPIO_OUT);
    gpio_set_dir(out2, GPIO_OUT);
    gpio_set_dir(enA, GPIO_OUT);
    uint slice_num = pwm_gpio_to_slice_num(enA);
    adc_select_input(0);
    
    pwm_config config = pwm_get_default_config();
    pwm_init(slice_num, &config, true);

    gpio_put(out1,0);
    gpio_put(out2,0);
    pwm_set_gpio_level(enA, 1);
}

void turn_right(float a){
    gpio_put(out1,0);
    gpio_put(out2,1);
    pwm_set_gpio_level(enA, a);
}

void turn_left(float a){
    gpio_put(out1,1);
    gpio_put(out2,0);
    pwm_set_gpio_level(enA, a);
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
         const float normalised_conversion_factor = conversion_factor / 3.3f ;
         uint16_t result = adc_read();
         float result_norm = ((float)result * 2 * normalised_conversion_factor) - 1;
         printf("result -1 to 1 : %f \n", result_norm);
        //  printf("Raw value: 0x%03x, voltage: %f V\n", result, result * conversion_factor); // result in voltage mode
         if (result_norm <= bounds && result_norm >= (- bounds)) {
            stop();
            printf("stop\n\r");
         }else if (result_norm < - bounds){
            turn_left(result * -1);
            printf("Turn left\n\r");
         }else if (result_norm > bounds){
            turn_right(result);
            printf("Turn right\n\r");
         }

         sleep_ms(delay);

        // turn_right();
        // printf("Turn right\n\r");
        // sleep_ms(1000);
        // stop();
        // printf("stop\n\r");
        // sleep_ms(1000);
    }
}
