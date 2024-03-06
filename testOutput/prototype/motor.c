#include "include/motor.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define delay 100
#define pot 26
#define bounds 0.05
#define wrap 5000


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
    uint slice_num = pwm_gpio_to_slice_num(enableA);
    pwm_set_wrap(slice_num, wrap);

    // Intial states for pins
    gpio_put(in1, 0);
    gpio_put(in2, 0);
    pwm_set_gpio_level(enableA, 0);
    pwm_set_enabled(slice_num, true);

    // Populate the motor handle
    motor->in1 = in1;
    motor->in2 = in2;
    motor->enableA = enableA;
}

void turn_right(Motor *motor, float a){
    gpio_put(motor->in1,0);
    gpio_put(motor->in2,1);
    pwm_set_gpio_level(motor->enableA, (int)a);
}

void turn_left(Motor *motor, float a){
    gpio_put(motor->in1,1);
    gpio_put(motor->in2,0);
    pwm_set_gpio_level(motor->enableA, (int)(-a));
}

void stop(Motor *motor){
    gpio_put(motor->in1,0);
    gpio_put(motor->in2,0);
    pwm_set_gpio_level(motor->enableA, 0);
}

void motor_drive(Motor *motor, float result_norm){
    printf("result -1 to 1 : %f , ", result_norm);
    float power = (result_norm  * wrap); 
    printf("power %f: ", power);
    if (result_norm <= bounds && result_norm >= (- bounds)) {
        stop(motor);
        printf("stop\n\r");
    }else if (result_norm < - bounds){
        turn_left(motor, power);
        printf("Turn left\n\r");
    }else if (result_norm > bounds){
        turn_right(motor, power);
        printf("Turn right\n\r");
    }
}