#ifndef RTOS_H
#define RTOS_H
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

extern SemaphoreHandle_t interruptSemaphore;
void TaskExec(void *pvParameters);
void TaskLimits(void *pvParameters);
void TaskBlink(void *pvParameters);
void TaskDemoRotate(void *pvParameters);

void interruptHandler();
void TaskKey(void *pvParameters);
#endif
