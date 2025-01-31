#include <Arduino.h>

void core0Task(void *pvParameters) {
  while (1) {
    printf("Task sul Core 0\n");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void core1Task(void *pvParameters) {
  while (1) {
    printf("Task sul Core 1\n");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void setup() {
  xTaskCreatePinnedToCore(core0Task, "Core 0 Task", 2048, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(core1Task, "Core 1 Task", 2048, NULL, 1, NULL, 1);
}

void loop() {}