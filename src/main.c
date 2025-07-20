#include <stdio.h>
#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void flash_light(int GPIO_NUM)
{
    int flashes = 0;

    while(flashes < 10)
    {
        gpio_set_level(GPIO_NUM, 1);
        vTaskDelay(pdMS_TO_TICKS(50));
        gpio_set_level(GPIO_NUM, 0);
        vTaskDelay(pdMS_TO_TICKS(50));

        flashes ++;
    }
}

void app_main(void)
{
    // Set GPIO Modes
    gpio_set_direction(GPIO_NUM_33, GPIO_MODE_INPUT);
    gpio_set_pull_mode(GPIO_NUM_33, GPIO_PULLUP_ONLY);

    gpio_set_direction(GPIO_NUM_25, GPIO_MODE_OUTPUT);

    const char *TAG = "main";
    while (1) {
        // Logic to turn on LED
        if (gpio_get_level(GPIO_NUM_33) == 0)
        {
            flash_light(25);
        } else {
            gpio_set_level(GPIO_NUM_25, 0);
        }

        // // Debugging
        // int level = gpio_get_level(GPIO_NUM_33);

        // if (level == 0) {
        //     ESP_LOGI(TAG, "Button pressed: %d", gpio_get_level(GPIO_NUM_33));
        // } else {
        //     ESP_LOGI(TAG, "Button released: %d", gpio_get_level(GPIO_NUM_33));
        // }

        // vTaskDelay(pdMS_TO_TICKS(200)); // check every 200ms
    }
}