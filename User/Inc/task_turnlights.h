#ifndef TASK_TURNLIGHTS_H
#define TASK_TURNLIGHTS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Defenitions */
#define TURN_LIGHTS_FREQUENCY 700
/* Enums */
typedef enum {
    TURN_LIGHTS_OFF = 0,
    TURN_LIGHTS_L,
    TURN_LIGHTS_R,
    TURN_LIGHTS_ALARM
} TurnLightsEnum_t;

/* Prototypes */
void startTaskTurnLights();
void setTurnLights(TurnLightsEnum_t sig);

#ifdef __cplusplus
}
#endif

#endif // TASK_TURNLIGHTS_H
