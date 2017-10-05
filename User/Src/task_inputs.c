#include "FreeRTOS.h"
#include "task.h"

#include "task_inputs.h"
#include "stm32f1xx_hal.h"
#include "board_config.h"

#include "task_turnlights.h"

/* Private prototypes */

/* Private variables */
const TickType_t xInputFrequency = INPUTS_CHECK_FREQUENCY;
TaskHandle_t hInputs;

void startTaskInputs()
{
    BaseType_t xResult = xTaskCreate(taskInputs, "taskInputs", configMINIMAL_STACK_SIZE, NULL , 2, &hInputs);
    startTaskTurnLights();
}

void taskInputs(void * params){
    int data;

    for (;;){
        data = GPIOB->IDR;
        if ((data & GPIO_PIN_I_TURN_L) == (uint32_t)0 ){
            setTurnLights(TURN_LIGHTS_L);
        }
        if ((data & GPIO_PIN_I_TURN_R) == (uint32_t)0 ) {
            setTurnLights(TURN_LIGHTS_R);
        } else {
            setTurnLights(TURN_LIGHTS_OFF);
        }
        if((data & GPIO_PIN_I_STOP) == (uint32_t)0) {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_O_STOP, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_O_STOP, GPIO_PIN_RESET);
        }
        if ((data & GPIO_PIN_I_LIGHT) == (uint32_t)0) {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_O_LIGHT, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_O_LIGHT, GPIO_PIN_RESET);
        }

        vTaskDelay(xInputFrequency);
    }
}
