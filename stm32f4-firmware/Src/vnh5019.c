#include "vnh5019.h"

/*
 * Driver for the ST VNH5019 motor driver.
 */ 


/**
 * Initializer for the vnh5019 structures. Sets up the timer, output compare,
 * and gpio peripherals based on the given hardware assignments. The provided
 * state must be unique to each set of hardware assignments but can be blank.
 * The hardware assignments must have all fields complete, but this struct can
 * be re-used for multiple initializers since it is copied into the state.
 * @param state: controller state structure.
 * @param hw_assign: hardware assignment structure that should be attached to
 *                   this state.
 * @return: 0 on successful completion, -1 on HAL error.
 */
int vnh5019_init(vnh5019_state_t *state, vnh5019_hw_assign_t *hw_assign) {
  /* Copy initialization data. */
  state->hw_assign = *hw_assign; // intentional copy
  state->speed = 0;
  state->direction = FORWARD;
  state->cs_value = 0;

  /* Initialize TIMx peripheral as follows:
     + Prescaler = (SystemCoreClock/2)/2000
     + Period = 65535 for 16 bit output
     + ClockDivision = 2 <- this doesn't seem to divide things
     + Counter direction = Up
  */
  state->timer_handle.Instance = state->hw_assign.timer_instance;
  state->timer_handle.Init.Period        = 65535;
  state->timer_handle.Init.Prescaler     = 2;
  state->timer_handle.Init.ClockDivision = 0;
  state->timer_handle.Init.CounterMode   = TIM_COUNTERMODE_UP;
  if(HAL_TIM_OC_Init(&(state->timer_handle)) != HAL_OK) {
    return -1;
  }

  /* Configure the output compare channels for PWM:
     + polarity = low so that smaller duty gives smaller on time
     + pulse sets duty cycle out of 
   */ 
  state->timer_oc_config.OCMode = TIM_OCMODE_PWM1;
  state->timer_oc_config.OCPolarity = TIM_OCPOLARITY_LOW;

  /* Configure GPIO pins we are using for output. */
  GPIO_InitTypeDef gpio_init;

  // pwm
  gpio_init.Pin = state->hw_assign.pwm_pin;
  gpio_init.Mode = GPIO_MODE_AF_PP;
  gpio_init.Pull = GPIO_NOPULL;
  gpio_init.Speed = GPIO_SPEED_FAST;
  gpio_init.Alternate = state->hw_assign.pwm_af;
  HAL_GPIO_Init(state->hw_assign.pwm_gpio, &gpio_init);

  // ina
  gpio_init.Pin = state->hw_assign.ina_pin;
  gpio_init.Mode = GPIO_MODE_OUTPUT_PP;
  gpio_init.Pull = GPIO_NOPULL;
  gpio_init.Speed = GPIO_SPEED_FAST;
  gpio_init.Alternate = 0;
  HAL_GPIO_Init(state->hw_assign.ina_gpio, &gpio_init);

  // inb
  gpio_init.Pin = state->hw_assign.inb_pin;
  gpio_init.Mode = GPIO_MODE_OUTPUT_PP;
  gpio_init.Pull = GPIO_NOPULL;
  gpio_init.Speed = GPIO_SPEED_FAST;
  gpio_init.Alternate = 0;
  HAL_GPIO_Init(state->hw_assign.inb_gpio, &gpio_init);

  // todo: set up adc for current sense

  // set default values
  if(vnh5019_set(state, 0, FORWARD) != 0) {
    return -1;
  }

  // completed without errors
  return 0;
}


/**
 * Read the current speed from controller state structure.
 * @param state: controller state structure.
 * @return: the current speed.
 */
uint16_t vnh5019_get_speed(vnh5019_state_t *state) {
  return state->speed;
}


/**
 * Read the current direction from controller state structure.
 * @param state: controller state structure.
 * @return: the current direction.
 */
vnh5019_direction_t vnh5019_get_direction(vnh5019_state_t *state) {
  return state->direction;
}


/**
 * Read the most recent current sense reading from controller state structure.
 * @param state: controller state structure.
 * @return: current sense value.
 */
uint16_t vnh5019_get_cs_value(vnh5019_state_t *state) {
  return state->cs_value;
}


/**
 * Sets new outputs to the given controller. Controller state must have been
 * initialized already.
 * @param state: controller state structure.
 * @param speed: new speed to set.
 * @param direction: new direction to set.
 * @return: 0 on successful completion, -1 on HAL error.
 */
int vnh5019_set(vnh5019_state_t *state,
                uint16_t speed,
                vnh5019_direction_t direction) {
  if(vnh5019_set_speed(state, speed) != 0) {
    return -1;
  }
  if(vnh5019_set_direction(state, direction) != 0) {
    return -1;
  }

  // completed without errors
  return 0;
}


/**
 * Sets new outputs to the given controller. Controller state must have been
 * initialized already.
 * @param state: controller state structure.
 * @param speed: new speed to set.
 * @return: 0 on successful completion, -1 on HAL error.
 */
int vnh5019_set_speed(vnh5019_state_t *state, uint16_t speed) {
  // update saved state
  state->speed = speed;

  // Set the pulse (duty) value for channel we're using.
  state->timer_oc_config.Pulse = state->speed;  
  if(HAL_TIM_PWM_ConfigChannel(&(state->timer_handle),
                               &(state->timer_oc_config),
                               state->hw_assign.timer_channel) != HAL_OK) {
    return -1;
  }

  // Start signal generation
  if(HAL_TIM_PWM_Start(&(state->timer_handle),
                       state->hw_assign.timer_channel) != HAL_OK) {
    return -1;
  }

  // completed without errors
  return 0;
}


/**
 * Sets new outputs to the given controller. Controller state must have been
 * initialized already.
 * @param state: controller state structure.
 * @param direction: new direction to set.
 * @return: 0 on successful completion, -1 on HAL error.
 */
int vnh5019_set_direction(vnh5019_state_t *state,
                          vnh5019_direction_t direction) {
  // update saved state
  state->direction = direction;

  // set hw outputs
  if(state->direction == FORWARD) {
    HAL_GPIO_WritePin(state->hw_assign.ina_gpio,
                      state->hw_assign.ina_pin,
                      GPIO_PIN_SET);
    HAL_GPIO_WritePin(state->hw_assign.inb_gpio,
                      state->hw_assign.inb_pin,
                      GPIO_PIN_RESET);
  } else {
    HAL_GPIO_WritePin(state->hw_assign.ina_gpio,
                      state->hw_assign.ina_pin,
                      GPIO_PIN_RESET);
    HAL_GPIO_WritePin(state->hw_assign.inb_gpio,
                      state->hw_assign.inb_pin,
                      GPIO_PIN_SET);
  }

  // completed without errors
  return 0;
}
