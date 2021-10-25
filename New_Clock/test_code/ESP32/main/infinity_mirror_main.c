#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#define NUM_LEDS 60
#include "ws2812_control.h"

#define RED   0xFF0000
#define GREEN 0x00FF00
#define BLUE  0x0000FF
#define BLACK 0x000000

int led_test(void) 
{
    ws2812_control_init();
    struct led_state new_state;
    while(1)
    {
        printf("beginning leds\n");
        
        for(int i = 0; i < NUM_LEDS; i = i + 1)
        {
            printf("i = %d\n", i);
            new_state.leds[i] = RED;
        }

        ws2812_write_leds(new_state);
        vTaskDelay(1000 / portTICK_PERIOD_MS);

         for(int i = 0; i < NUM_LEDS; i = i + 1)
        {
            printf("i = %d\n", i);
            new_state.leds[i] = GREEN;
        }

        ws2812_write_leds(new_state);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        printf("end leds\n");
    }
    return(1);
}

void app_main(void)
{
    led_test();
}
