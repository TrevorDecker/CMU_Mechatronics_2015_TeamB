//class for a digital input 
//digitalInput.c
#include "digitalInput.h"
void digitalInputInit(digital_input_state_t* state,int gpio,int gpioPin){
  digitalInputSetGpio(state,gpio);
  digitalInputSetGpioPin(state,gpioPin);
  //TODO setup intrupts 
}

void digitalInputRelease(digital_input_state_t*state){
  //TODO 
}

//will block until a button is pressed 
//this function will block 
void digitalInputButtonPressed(digital_input_state_t*state){
  digitalInputAck(state);
  while(!digitalInputGetWasHigh(state)){
    //    delay(20);  TODO
  }
  digitalInputAck(state);
  while(!digitalInputGetWasLow(state)){
    //   delay(2);    TODO 
  }
  digitalInputAck(state);
}

inline int digitalInputGetGpio(digital_input_state_t* state){
  return state->gpio;
}

inline void digitalInputSetGpio(digital_input_state_t* state, int newGpio){
  state->gpio = newGpio;
}

inline int digitalInputGetGpioPin(digital_input_state_t* state){
  return state->gpioPin;
}

inline void digitalInputSetGpiPin(digital_input_state_t* state,int newPin){
  state->gpioPin = newPin;
}

int digitalInputGetCurrentValue(digital_input_state_t* state){
  return  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
 }

inline int digitalInputGetWasHigh(digital_input_state_t* state){
  return state->wasHigh;
}

inline int digitalInputGetWasLow(digital_input_state_t* state){
  return state->wasLow;
}

inline int digitalInputSetThreashold(digital_input_state_t* state, int newThreashold){
  state->threashold = newThreashold;
}

inline void digitalInputAck(digital_input_state_t* state){
  state->wasHigh = FALSE;
  state->wasLow = FALSE;
}


//TODO add interupt code 

