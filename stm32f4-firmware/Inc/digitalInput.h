//class for digital input
//digitalInput.h

#include "logicvalues.h"

typedef struct digtalInput{
  int gpio;
  int gpioPin;
  int wasHigh;//reset on ack
  int wasLow;//reset on ack
  int threashold;
} digital_input_state_t;

void digitalInputInit(digital_input_state_t* state,int gpio,int gpioPin);
int digitalInputGetGpio(digital_input_state_t* state);
void digitalInputSetGpio(digital_input_state_t* state,int newGpio);
int digitalInputGetGpioPin(digital_input_state_t* state);
void digitalInputSetGpiPin(digital_input_state_t* state,int newPin);
int digitalInputGetCurrentValue(digital_input_state_t* state);
int digitalInputGetWasHigh(digital_input_state_t* state);
int digitalInputGetWasLow(digital_input_state_t* state);
int digitalInputSetThreashold(digital_input_state_t* state, int newThreashold);
void digitalInputAck(digital_input_state_t* state);

//TODO add intrupt code 
