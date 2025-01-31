#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

QueueHandle_t xQueue;

void Task1(void *pvParameters) {
    int data = 0;
    while (1) { //loop infinito
        data++;
        xQueueSend(xQueue, &data, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(1000)); // Pausa di 1 secondo
    }
}

void Task2(void *pvParameters) {
    int receivedData;
    while (1) { //loop infinito
        if (xQueueReceive(xQueue, &receivedData, portMAX_DELAY)) {
            printf("Dati ricevuti: %d\n", receivedData);
        }
    }
}

int main(void) {
    xQueue = xQueueCreate(10, sizeof(int));

    xTaskCreate(Task1, "Task 1", 1000, NULL, 1, NULL);
    xTaskCreate(Task2, "Task 2", 1000, NULL, 1, NULL);

    vTaskStartScheduler();

    while (1);
}