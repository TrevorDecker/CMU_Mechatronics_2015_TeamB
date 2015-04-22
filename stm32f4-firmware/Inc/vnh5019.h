#ifndef __VNH5019_H
#define __VNH5019_H

#ifdef __cplusplus
extern "C" {
#endif


// Structure definitions
typedef struct vnh5019_hw_assign {
  GPIO_TypeDef      *ina_gpio;
  uint32_t           ina_pin;
  GPIO_TypeDef      *inb_gpio;
  uint32_t           inb_pin;
  GPIO_TypeDef      *pwm_gpio;
  uint32_t           pwm_pin;
  uint32_t           pwm_af;
  GPIO_TypeDef      *cs_gpio;
  uint32_t           cs_pin;
  uint32_t           cs_af;
  TIM_TypeDef       *timer_instance;
  uint32_t           timer_channel;
} vnh5019_hw_assign_t;

typedef enum vnh5019_direction {
  FORWARD,
  REVERSE,
} vnh5019_direction_t;

typedef struct vnh5019_state {
  vnh5019_hw_assign_t hw_assign;
  uint16_t speed;
  vnh5019_direction_t direction;
  uint16_t cs_value;
  TIM_HandleTypeDef timer_handle;
  TIM_OC_InitTypeDef timer_oc_config;
} vnh5019_state_t;

// Methods
int vnh5019_init(vnh5019_state_t *state, vnh5019_hw_assign_t *hw_assign);
uint16_t vnh5019_get_speed(vnh5019_state_t *state);
vnh5019_direction_t vnh5019_get_direction(vnh5019_state_t *state);
uint16_t vnh5019_get_cs_value(vnh5019_state_t *state);
int vnh5019_set(vnh5019_state_t *state,
                uint16_t speed,
                vnh5019_direction_t direction);
int vnh5019_set_speed(vnh5019_state_t *state, uint16_t speed);
int vnh5019_set_direction(vnh5019_state_t *state,
                          vnh5019_direction_t direction);


#ifdef __cplusplus
}
#endif

#endif /* __VNH5019_H */
