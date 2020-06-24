#include <Arduino.h>
#include "rtos.h"
#include "travel.h"

SemaphoreHandle_t interruptSemaphore;

void interruptHandler() {
      xSemaphoreGiveFromISR(interruptSemaphore, NULL);
}

void TaskKey(void *pvParameters){
  (void) pvParameters;
  for (;;) {
    if (xSemaphoreTake(interruptSemaphore, portMAX_DELAY) == pdPASS) {
      if(elevator.moveAllow()){
       elevator.GeneralMove();
      }
      elevator.uslip();
    }
  }
}

void TaskLimits(void *pvParameters){
  (void) pvParameters;
  for (;;){
    elevator.limit();
    vTaskDelay( 100 / portTICK_PERIOD_MS );
  }
}

void TaskExec(void *pvParameters){
  (void) pvParameters;
  for (;;){
    elevator.mainRelay();
    vTaskDelay( 500 / portTICK_PERIOD_MS );
  }
}

void TaskBlink(void *pvParameters){
  (void) pvParameters;
  pinMode(LED_BUILTIN, OUTPUT);
  for (;;){
    digitalWrite(LED_BUILTIN, HIGH);
    vTaskDelay( 45 / portTICK_PERIOD_MS );
    digitalWrite(LED_BUILTIN, LOW);
    vTaskDelay( 60 / portTICK_PERIOD_MS );
    digitalWrite(LED_BUILTIN, HIGH);
    vTaskDelay( 45 / portTICK_PERIOD_MS );
    digitalWrite(LED_BUILTIN, LOW);
    vTaskDelay( 1860 / portTICK_PERIOD_MS );
  }
}
