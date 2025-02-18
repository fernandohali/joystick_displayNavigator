#include "led.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include "hardware/pwm.h"

// Inicializa os LEDs
void init_led(void)
{
	gpio_init(LED_GREEN_PIN);
	gpio_init(LED_BLUE_PIN);
	gpio_init(LED_RED_PIN);

	gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);
	gpio_set_dir(LED_BLUE_PIN, GPIO_OUT);
	gpio_set_dir(LED_RED_PIN, GPIO_OUT);

	gpio_put(LED_GREEN_PIN, false);
	gpio_put(LED_BLUE_PIN, false);
	gpio_put(LED_RED_PIN, false);
}

// Utilizar o PWM para controlar a intensidade de dois LEDs RGB com base nos valores do joystick.
void toggle_leds()
{
	// Inicializa os LEDs
	init_led();

	// Inicializa o Joystick
	init_joystick();

	// Inicializa o PWM
	gpio_set_function(LED_RED_PIN, GPIO_FUNC_PWM);
	gpio_set_function(LED_GREEN_PIN, GPIO_FUNC_PWM);

	// Inicializa o PWM
	pwm_config config = pwm_get_default_config();
	pwm_config_set_wrap(&config, 255);
	pwm_init(pwm_gpio_to_slice_num(LED_RED_PIN), &config, true);
	pwm_init(pwm_gpio_to_slice_num(LED_GREEN_PIN), &config, true);

	// Inicializa o PWM
	pwm_set_gpio_level(LED_RED_PIN, 0);
	pwm_set_gpio_level(LED_GREEN_PIN, 0);

	// Inicializa o PWM
	while (true)
	{
		// Lê os valores do Joystick
		int x = read_joystick_x();
		int y = read_joystick_y();

		// Calcula a intensidade dos LEDs
		int red = 255 - (x + 127);
		int green = 255 - (y + 127);

		// Atualiza a intensidade dos LEDs
		pwm_set_gpio_level(LED_RED_PIN, red);
		pwm_set_gpio_level(LED_GREEN_PIN, green);
	}
}
