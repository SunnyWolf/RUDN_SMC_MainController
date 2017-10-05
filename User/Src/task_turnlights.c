/***********************************
 * @authon Roman Shcheglov
 * @email roman.shcheglov@gmail.com
 ***********************************/
#include "FreeRTOS.h"
#include "task.h"
#include "stm32f1xx_hal.h"

#include "board_config.h"

#include "task_turnlights.h"

/* Private prototypes */
void taskTurnLights(void * params);

static TurnLightsEnum_t turn_signal = TURN_LIGHTS_OFF;
TaskHandle_t hTurnLights;

const TickType_t xFrequency = TURN_LIGHTS_FREQUENCY;

void startTaskTurnLights(){
    BaseType_t xResult = xTaskCreate(taskTurnLights, "taskTurnLights", configMINIMAL_STACK_SIZE, NULL, 2, &hTurnLights);
}

void setTurnLights(TurnLightsEnum_t sig){
    turn_signal = sig;
}

void taskTurnLights(void * params){
    uint32_t data;
    TickType_t xLastWakeTime;

    for(;;){
        data = 0;
        switch (turn_signal) {
        case TURN_LIGHTS_L:
            data = GPIO_PIN_O_TURN_L;
            //terminalSendStatus(terminalSENDER_TURN_LIGHTS,  TURN_LIGHTS_L);
            break;
        case TURN_LIGHTS_R:
            data = GPIO_PIN_O_TURN_R;
            //terminalSendStatus(terminalSENDER_TURN_LIGHTS, TURN_LIGHTS_R);
            break;
        case TURN_LIGHTS_ALARM:
            //terminalSendStatus(terminalSENDER_TURN_LIGHTS, TURN_LIGHTS_ALARM);
            data = GPIO_PIN_O_TURN_L|GPIO_PIN_O_TURN_R;
            break;
        default:
            //terminalSendStatus(terminalSENDER_TURN_LIGHTS, TURN_LIGHTS_OFF);
            data = (uint32_t)0;
        }
        if(data){
            HAL_GPIO_WritePin(GPIOB, data, GPIO_PIN_SET);
            xLastWakeTime = xTaskGetTickCount();
            vTaskDelayUntil(&xLastWakeTime, xFrequency);
            HAL_GPIO_WritePin(GPIOB, data, GPIO_PIN_RESET);
        }
        xLastWakeTime = xTaskGetTickCount();
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}
