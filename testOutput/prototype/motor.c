#include "include/motor.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define delay 100
#define out1 6
#define out2 7
#define enA 8
#define pot 26
#define bounds 0.05
#define wrap 1000


const float conversion_factor = 3.3f / (1 << 12);
const float normalised_conversion_factor = conversion_factor / 3.3f ;


void motor_driver_init(Motor *motor, int in1, int in2, int enableA){
    // Setup the GPIO pins
    gpio_init(in1);
    gpio_init(in2);
    gpio_set_dir(in1, GPIO_OUT);
    gpio_set_dir(in2, GPIO_OUT);

    // Setup the PWN pin
    gpio_set_function(enableA, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(enA);
    pwm_set_wrap(slice_num, wrap);

    // Intial states for pins
    gpio_put(in1,0);
    gpio_put(in2,0);
    pwm_set_gpio_level(enableA, wrap);
    // pwm_set_chan_level(slice_num, PWM_CHAN_A, 100);
    pwm_set_enabled(slice_num, true);

    // Populate the motor handle
    motor->in1 = in1;
    motor->in2 = in2;
    motor->enableA = enableA;
}

void turn_right(float a){
    gpio_put(out1,0);
    gpio_put(out2,1);
    pwm_set_gpio_level(enA, a);
}

void turn_left(float a){
    gpio_put(out1,1);
    gpio_put(out2,0);
    pwm_set_gpio_level(enA, (int)(-a));
}

void stop(){
    gpio_put(out1,0);
    gpio_put(out2,0);
    pwm_set_gpio_level(enA, 0);
}

void motor_drive(Motor *motor, uint16_t result_norm){
    // float result_norm = ((float)result * 2 * normalised_conversion_factor) - 1;
    printf("result -1 to 1 : %f \n", result_norm);
    float power = (result_norm * (wrap+1)); // gets -1 later
    printf("power %f: ", power);
    if (result_norm <= bounds && result_norm >= (- bounds)) {
        stop();
        printf("stop\n\r");
    }else if (result_norm < - bounds){
        turn_left(power);
        printf("Turn left\n\r");
    }else if (result_norm > bounds){
        turn_right(power);
        printf("Turn right\n\r");
    }
}


int main(){
    stdio_init_all();
    setup();
    
    while(1){
         uint16_t result = adc_read();
         // 12-bit conversion, assume max value == ADC_VREF == 3.3 V
         //  printf("Raw value: 0x%03x, voltage: %f V\n", result, result * conversion_factor); // result in voltage mode
         get_
         motor_drive(result);
         sleep_ms(delay);
    }
}
