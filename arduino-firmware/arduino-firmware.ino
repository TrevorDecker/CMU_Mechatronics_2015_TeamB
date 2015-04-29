
/*******************************************************************
 ******************* SETTINGS.h ************************************
 ******************************************************************/
//left gripper speed controller 
#define LEFT_GRIPPER_INA_PIN     50   //1 
#define LEFT_GRIPPER_INB_PIN     52   //2 
#define LEFT_GRIPPER_PWM_PIN     2   //3
#define LEFT_GRIPPER_CS_PIN      48   //4

//right gripper speed controller
#define RIGHT_GRIPPER_INA_PIN    -1  //5
#define RIGHT_GRIPPER_INB_PIN    -1  //6
#define RIGHT_GRIPPER_PWM_PIN    -1  //7
#define RIGHT_GRIPPER_CS_PIN     -1  //8

//extsion speed controller 
#define EXTENSION_MOTOR_INA_PIN  -1  //9
#define EXTENSION_MOTOR_INB_PIN  -1  //10
#define EXTENSION_MOTOR_PWM_PIN  -1  //11
#define EXTENSION_MOTOR_CS_PIN   -1  //12

//cleaner speed contoller
#define CLEANER_MOTOR_INA_PIN    -1  //13
#define CLEANER_MOTOR_INB_PIN    -1  //14
#define CLEANER_MOTOR_PWM_PIN    -1  //15
#define CLEANER_MOTOR_CS_PIN     -1  //16

#define LEFT_GRIPPER_POT_PIN     -1  //17
#define RIGHT_GRIPPER_POT_PIN    -1  //18
#define EXTESNION_SENSOR_POT_PIN -1  //19


#define USER_BTN_TWO_PIN         -1   //20
#define USER_BTN_ONE_PIN         -1   //21
#define USER_POT_PIN             -1   //22

/*****************************************************************
 ********************************* VNH5019.h *********************
 ****************************************************************/
typedef enum vnh5019_direction {
  FORWARD,
  REVERSE,
} vnh5019_direction_t;

typedef struct vnh5019_state {
  uint8_t ina_pin;
  uint8_t inb_pin;
  uint8_t pwm_pin;
  uint8_t cs_pin;
  uint8_t speed;
  vnh5019_direction_t direction;
} vnh5019_state_t;

// Methods
int vnh5019_init(vnh5019_state_t *state, uint8_t ina_pin,uint8_t inb_pin,uint8_t pwm_pin,uint8_t cs_pin);
uint8_t vnh5019_get_speed(vnh5019_state_t *state);
vnh5019_direction_t vnh5019_get_direction(vnh5019_state_t *state);
uint8_t vnh5019_get_cs_value(vnh5019_state_t *state);
int vnh5019_set(vnh5019_state_t *state,
                uint8_t speed,
                vnh5019_direction_t direction);
int vnh5019_set_speed(vnh5019_state_t *state, uint8_t speed);
int vnh5019_set_direction(vnh5019_state_t *state,
                          vnh5019_direction_t direction);                          
/****************************************************************
 ****************************** gripper.h ***********************
 ***************************************************************/
 typedef struct gripper_state
{
    vnh5019_state_t motor;   
} gripper_state_t;


void gripper_init(gripper_state_t *gripper,int ina_pin,int inb_pin,int pwm_pin,int cs_pin);
/****************************************************************
 ***************************** vnh5019.c   *********************
 ***************************************************************/ 
 // Initializer for the vnh5019 structures. Sets up the timer, output compare,
 // and gpio peripherals based on the given hardware assignments. The provided
 // state must be unique to each set of hardware assignments but can be blank.
 // The hardware assignments must have all fields complete, but this struct can
 // be re-used for multiple initializers since it is copied into the state.
 // NOTE: Calling code is responsible for starting the GPIO and Timer clocks.
 // @param state: controller state structure.
 // @param hw_assign: hardware assignment structure that should be attached to
 //                   this state.
 // @return: 0 on successful completion, -1 on HAL error.
 int vnh5019_init(vnh5019_state_t *state, uint8_t ina_pin,uint8_t inb_pin,uint8_t pwm_pin,uint8_t cs_pin){
  // Copy initialization data. 
  state->ina_pin = ina_pin;
  state->inb_pin = inb_pin;
  state->pwm_pin = pwm_pin;
  state->cs_pin  = cs_pin;
  state->speed = 0;
  state->direction = FORWARD;
   
  //sets up pins for OUTPUT 
  pinMode(state->ina_pin,OUTPUT);
  pinMode(state->inb_pin,OUTPUT);

  // completed without errors
  return 0;
}

 // Read the current speed from controller state structure.
 // @param state: controller state structure.
 // @return: the current speed.
uint8_t vnh5019_get_speed(vnh5019_state_t *state) {
  return state->speed;
}

 // Read the current direction from controller state structure.
 // @param state: controller state structure.
 // @return: the current direction.
vnh5019_direction_t vnh5019_get_direction(vnh5019_state_t *state) {
  return state->direction;
}



 // Read the most recent current sense reading from controller state structure.
 // @param state: controller state structure.
 // @return: current sense value.
uint8_t vnh5019_get_cs_value(vnh5019_state_t *state) {
  return digitalRead(state->cs_pin);
}

 // Sets new outputs to the given controller. Controller state must have been
 // initialized already.
 // @param state: controller state structure.
 // @param speed: new speed to set.
 // @param direction: new direction to set.
 // @return: 0 on successful completion, -1 on HAL error.
int vnh5019_set(vnh5019_state_t *state,
                uint8_t speed,
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

 // Sets new outputs to the given controller. Controller state must have been
 // initialized already.
 // @param state: controller state structure.
 // @param speed: new speed to set.
 // @return: 0 on successful completion, -1 on HAL error.
int vnh5019_set_speed(vnh5019_state_t *state, uint8_t speed) {
  // update saved state
  state->speed = speed;

  // update hardware
  analogWrite(state->pwm_pin,speed); 

  // completed without errors
  return 0;
}

 // Sets new outputs to the given controller. Controller state must have been
 // initialized already.
 // @param state: controller state structure.
 // @param direction: new direction to set.
 // @return: 0 on successful completion, -1 on HAL error.
int vnh5019_set_direction(vnh5019_state_t *state,
                          vnh5019_direction_t direction) {
  // update saved state
  state->direction = direction;

  // set hw outputs
  if(state->direction == FORWARD) {
     digitalWrite(state->ina_pin,true);
     digitalWrite(state->inb_pin,false);
  } else {
    digitalWrite(state->ina_pin,false);
    digitalWrite(state->inb_pin,true); 
  }

  // completed without errors
  return 0;
}
/*****************************************************************
*********************** Gripper.c ********************************
*****************************************************************/
void gripper_init(gripper_state_t *gripper,int ina_pin,int inb_pin,int pwm_pin,int cs_pin){
  vnh5019_init(&gripper->motor,ina_pin,inb_pin,pwm_pin,cs_pin); 
}



/*****************************************************************
 **************************** main.c *****************************
 ****************************************************************/

  gripper_state_t left_gripper; 
  gripper_state_t right_gripper;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  

  
  gripper_init(&left_gripper,LEFT_GRIPPER_INA_PIN,LEFT_GRIPPER_INB_PIN,LEFT_GRIPPER_PWM_PIN,LEFT_GRIPPER_CS_PIN);
  gripper_init(&right_gripper,RIGHT_GRIPPER_INA_PIN,RIGHT_GRIPPER_INB_PIN,RIGHT_GRIPPER_PWM_PIN,RIGHT_GRIPPER_CS_PIN);
  vnh5019_set(&left_gripper.motor,128,FORWARD); 
  /*
  vnh5019_hw_assign_t hw_assign;
  hw_assign.ina_pin = 22;
  hw_assign.inb_pin = 23;
  hw_assign.pwm_pin = 2;
  hw_assign.cs_pin = A0;
  vnh5019_init(&g_motor_pivot_l, &hw_assign);
  vnh5019_set(&g_motor_pivot_l, 128, FORWARD);
  */  
}

// the loop routine runs over and over again forever:
void loop() {
  // print out the value you read:
 Serial.println(vnh5019_get_cs_value(&left_gripper.motor));
  delay(20);        // delay in between reads for stability
}
