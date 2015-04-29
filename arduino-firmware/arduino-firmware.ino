//ALL units are in milimeters 
typedef enum vnh5019_direction {
  FORWARD,
  REVERSE,
} vnh5019_direction_t;

/*******************************************************************
 ******************* SETTINGS.h ************************************
 ******************************************************************/
//left gripper speed controller 
#define LEFT_GRIPPER_INA_PIN     22   //1 
#define LEFT_GRIPPER_INB_PIN     23   //2 
#define LEFT_GRIPPER_PWM_PIN     2   //3
#define LEFT_GRIPPER_CS_PIN      A8   //4

//right gripper speed controller
#define RIGHT_GRIPPER_INA_PIN    -1  //5       //TODO set
#define RIGHT_GRIPPER_INB_PIN    -1  //6       //TODO set
#define RIGHT_GRIPPER_PWM_PIN    -1  //7       //TODO set
#define RIGHT_GRIPPER_CS_PIN     -1  //8       //TODO set

//extsion speed controller 
#define EXTENSION_MOTOR_INA_PIN  -1  //9       //TODO set
#define EXTENSION_MOTOR_INB_PIN  -1  //10      //TODO set
#define EXTENSION_MOTOR_PWM_PIN  -1  //11      //TODO set
#define EXTENSION_MOTOR_CS_PIN   -1  //12      //TODO set

//cleaner speed contoller
#define CLEANER_MOTOR_INA_PIN    -1  //13      //TODO set
#define CLEANER_MOTOR_INB_PIN    -1  //14      //TODO set
#define CLEANER_MOTOR_PWM_PIN    -1  //15      //TODO set
#define CLEANER_MOTOR_CS_PIN     -1  //16      //TODO set
#define CLEANER_LEFT_BTN_PIN     -1  //17      //TODO set
#define CLEANER_RIGHT_BTN_PIN    -1  //18      //TODO set

#define LEFT_GRIPPER_POT_PIN     -1  //19      //TODO set
#define RIGHT_GRIPPER_POT_PIN    -1  //20      //TODO set
#define EXTESNION_SENSOR_POT_PIN -1  //21      //TODO set


#define USER_BTN_TWO_PIN         -1   //22     //TODO set
#define USER_BTN_ONE_PIN         -1   //23     //TODO set
#define USER_POT_PIN             -1   //24     //TODO set

#define WINDOW_WIDTH             0             //TODO set
#define WINDOW_HEIGHT            0             //TODO set

#define LEFT_GRIPPER_P           0             //TODO set
#define LEFT_GRIPPER_I           0             //TODO set
#define LEFT_GRIPPER_D           0             //TODO set

#define RIGHT_GRIPPER_P          0             //TODO set
#define RIGHT_GRIPPER_I          0             //TODO set
#define RIGHT_GRIPPER_D          0             //TODO set

#define EXTENSION_P              0             //TODO set
#define EXTENSION_I              0             //TODO set
#define EXTENSION_D              0             //TODO set
#define EXTENSION_THRESHOLD      0             //TODO set

#define GRIPPER_SPEED             30          //TODO set

#define GRIPPER_LOCK_DIR          FORWARD      //TODO set
#define GRIPPER_UNLOCK_DIR        REVERSE      //TODO set
#define MOVE_DOWN_BETWEEN_CLEANS  0            //TODO set
#define ROBOT_HEIGHT              0            //TODO set
#define CLEANER_SPEED             0            //TODO set
#define CLEANER_RIGHT_DIR         FORWARD      //TODO set
#define CLEANER_LEFT_DIR          REVERSE      //TODO set
#define MOVEING_AVERAGE_ARRAY_SIZE 20          //TODO set

#define GRIPPER_CS_GRIP_THRESHOLD 50            //TODO set 
/***************************************************************
 ******************* button.h **********************************
 **************************************************************/
     typedef struct button_state{
         uint8_t pin;
         bool was_high;
         bool was_low;
     }   button_state_t;
     
 void btn_init(button_state_t* btn,uint8_t pin);
 bool btn_get_value(button_state_t *btn);
 bool btn_get_was_high(button_state_t* btn );
 bool btn_get_was_low(button_state_t* btn);
 void btn_ack(button_state_t* btn);
 void update_btn_state(button_state_t* btn);

/*****************************************************************
 ********************************* VNH5019.h *********************
 ****************************************************************/
typedef struct moving_average_filter_state{
 int dataPoints[MOVEING_AVERAGE_ARRAY_SIZE];
 int oldestIndex; 
} moving_average_filter_state_t;

void moving_average_init(moving_average_filter_state_t* filter);
int  moving_average_get_average(moving_average_filter_state_t* filter);
void moving_average_add_data_point(moving_average_filter_state_t* filter,int newDataPoint); 

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
void gripper_lock(gripper_state_t *gripper);
void gripper_unlock(gripper_state_t *gripper);
/***************************************************************
*************************** cleaner.h **************************
***************************************************************/
typedef struct cleaner_state
  {  
      vnh5019_state_t motor;
      button_state_t left_limit_switch;
      button_state_t right_limit_switch;
      
  }  cleaner_state_t;
  
void cleaner_init(cleaner_state_t *cleaner,int ina_pin,int inb_pin,int pwm_pin,int cs_pin);
void cleanLeft(cleaner_state_t* cleaner);
void cleanRight(cleaner_state_t* cleaner);
void cleanThisLevel(cleaner_state_t* cleaner);
void cleanWindow(cleaner_state_t* cleaner);
bool cleaner_right_contact(cleaner_state_t* cleaner);
bool cleaner_left_contact(cleaner_state_t* cleaner);


/***************************************************************
***************** extension.h *********************
******************************************************************/
typedef struct extension_state
{  
    vnh5019_state_t motor;
    uint8_t sensor_pin;
} extension_state_t;

void extension_init(extension_state_t *extension,int ina_pin,int inb_pin,int pwm_pin,int cs_pin,int sensor_pin);
void extend_to(extension_state_t *extension,int point_to_move_to);
int extension_get_current_position(extension_state_t *extension);


/****************************************************************
 *********** Global defintions **********************************
 ****************************************************************/
  gripper_state_t left_gripper; 
  gripper_state_t right_gripper;
  extension_state_t extension_system;
  cleaner_state_t  cleaner_system;
  button_state_t  user_btn_one;
  int current_height;
  
  //for concurent motor operation 
 void update(){
   update_btn_state(&user_btn_one);
    //TODO
 } 
  
void moving_average_init(moving_average_filter_state_t* filter){
   filter->oldestIndex = 0;
   for(int i =0; i< MOVEING_AVERAGE_ARRAY_SIZE;i++){
      filter->dataPoints[i] = 0;
   } 
}

 
 int  moving_average_get_average(moving_average_filter_state_t* filter){
   int sum = 0;
   for(int i = 0;i<MOVEING_AVERAGE_ARRAY_SIZE;i++){
      sum += filter->dataPoints[i]/MOVEING_AVERAGE_ARRAY_SIZE; 
   }
   return sum;   
 }
 
void moving_average_add_data_point(moving_average_filter_state_t* filter,int newDataPoint){
    filter->oldestIndex = (filter->oldestIndex + 1) % MOVEING_AVERAGE_ARRAY_SIZE;
    filter->dataPoints[filter->oldestIndex] = newDataPoint;  
}


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
  return analogRead(state->cs_pin);
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
/****************************************************************
 **************** button.c **************************************
 ***************************************************************/
  void btn_init(button_state_t* btn,uint8_t pin){
      btn->pin = pin; 
   }  
   
  bool btn_get_was_high(button_state_t* btn ){
     update_btn_state(btn);
    return btn->was_high;
  }

  bool btn_get_was_low(button_state_t* btn){
     update_btn_state(btn);
    return btn->was_low;
  }

   void btn_ack(button_state_t* btn){
       btn->was_low = false;
       btn->was_high = false;
   } 
   
    void update_btn_state(button_state_t* btn){
      if(digitalRead(btn->pin)){
          //true
          btn->was_high = true;
      }else{
          btn->was_low = true;
      }
    }
    
  bool btn_get_value(button_state_t *btn){
     return digitalRead(btn->pin);
  }


/*****************************************************************
*********************** Gripper.c ********************************
*****************************************************************/
void gripper_init(gripper_state_t *gripper,int ina_pin,int inb_pin,int pwm_pin,int cs_pin){
  vnh5019_init(&gripper->motor,ina_pin,inb_pin,pwm_pin,cs_pin); 
}

//blocking
void gripper_lock(gripper_state_t *gripper){
   moving_average_filter_state_t cs_filter;
  moving_average_init(&cs_filter);
  //add init values 
  for(int i = 0;i<MOVEING_AVERAGE_ARRAY_SIZE;i++){
      moving_average_add_data_point(&cs_filter,vnh5019_get_cs_value(&gripper->motor));
  }
  while(moving_average_get_average(&cs_filter) < GRIPPER_CS_GRIP_THRESHOLD){
      Serial.println(moving_average_get_average(&cs_filter));
      moving_average_add_data_point(&cs_filter,vnh5019_get_cs_value(&gripper->motor));
     vnh5019_set(&gripper->motor,GRIPPER_SPEED,GRIPPER_LOCK_DIR);
     delay(20);
  }  
     vnh5019_set(&gripper->motor,0,GRIPPER_LOCK_DIR);

}

//blocking
void gripper_unlock(gripper_state_t *gripper){
  moving_average_filter_state_t cs_filter;
  moving_average_init(&cs_filter);
  //add init values 
  for(int i = 0;i<MOVEING_AVERAGE_ARRAY_SIZE;i++){
      moving_average_add_data_point(&cs_filter,vnh5019_get_cs_value(&gripper->motor));
  }
  while(moving_average_get_average(&cs_filter) > GRIPPER_CS_GRIP_THRESHOLD){
      moving_average_add_data_point(&cs_filter,vnh5019_get_cs_value(&gripper->motor));
     vnh5019_set(&gripper->motor,GRIPPER_SPEED,GRIPPER_UNLOCK_DIR);
     delay(20);
  }  
     vnh5019_set(&gripper->motor,0,GRIPPER_UNLOCK_DIR);

}
/*****************************************************************
 ********************** Cleaner.c.c ********************************
 ****************************************************************/
 void cleaner_init(cleaner_state_t *cleaner,int ina_pin,int inb_pin,int pwm_pin,int cs_pin){
    vnh5019_init(&cleaner->motor,ina_pin,inb_pin,pwm_pin,cs_pin);
 }
 
 
 /****************************************************************
 *********************** Extension.c *******************************
 *****************************************************************/
  void extension_init(extension_state_t *extension,int ina_pin,int inb_pin,int pwm_pin,int cs_pin,int sensor_pin){
    extension->sensor_pin = sensor_pin;
    vnh5019_init(&extension->motor,ina_pin,inb_pin,pwm_pin,cs_pin);
 }
  
 int extension_get_current_position(extension_state_t *extension){
     return analogRead(extension->sensor_pin);//TODO
 }
   
   
 
 //blocking
 void extend_to(extension_state_t *extension,int point_to_move_to){
     int current_point =extension_get_current_position(extension); 
     int error =  current_point - point_to_move_to;
     while(abs(error) > EXTENSION_THRESHOLD){
        current_point = extension_get_current_position(extension);
        if(error > 0){
          vnh5019_set(&extension->motor,EXTENSION_P*error,FORWARD);
        }else{
          vnh5019_set(&extension->motor,EXTENSION_P*error,REVERSE);
        }
     }  
      vnh5019_set(&extension->motor,0,REVERSE);    
  }

/*****************************************************************
 ************************* Robot functions ***********************
 ****************************************************************/
 void teleopMode(){
   int mode = 0;
   int input = 0;
   int pot_value = 0;
   while(1){
   //TODO add sensor reporting by serial 
 
   if(input % 2 == 0){
    if(btn_get_was_high(&user_btn_one)){
        input++;
        btn_ack(&user_btn_one);
    }
   }else{
     if(btn_get_was_low(&user_btn_one)){
       input++;
       btn_ack(&user_btn_one);
     }
   }
 
   mode = input/2 % 4;
   
   switch(mode){
    case  0:  //off
      vnh5019_set(&extension_system.motor,0,REVERSE);
      vnh5019_set(&cleaner_system.motor,0,REVERSE);
      vnh5019_set(&left_gripper.motor,0,REVERSE);
      vnh5019_set(&right_gripper.motor,0,REVERSE);
      break;  
    case 1: // extension
      pot_value = analogRead(USER_POT_PIN);
      if(pot_value < 128){
              vnh5019_set(&extension_system.motor,pot_value,REVERSE);
      }else{
              vnh5019_set(&extension_system.motor,pot_value - 128,FORWARD);
      }
      vnh5019_set(&cleaner_system.motor,0,REVERSE);
      vnh5019_set(&left_gripper.motor,0,REVERSE);
      vnh5019_set(&right_gripper.motor,0,REVERSE);
      break;  
     case 2: //cleaner
     vnh5019_set(&extension_system.motor,0,REVERSE);

           pot_value = analogRead(USER_POT_PIN);
      if(pot_value < 128){
              vnh5019_set(&cleaner_system.motor,pot_value,REVERSE);
      }else{
              vnh5019_set(&cleaner_system.motor,pot_value - 128,FORWARD);
      }
      vnh5019_set(&left_gripper.motor,0,REVERSE);
      vnh5019_set(&right_gripper.motor,0,REVERSE);
      break; 
     case 3: //gripper1
       vnh5019_set(&extension_system.motor,0,REVERSE);
       vnh5019_set(&cleaner_system.motor,0,REVERSE);
       pot_value = analogRead(USER_POT_PIN);
      if(pot_value < 128){
              vnh5019_set(&left_gripper.motor,pot_value,REVERSE);
      }else{
              vnh5019_set(&left_gripper.motor,pot_value - 128,FORWARD);
      }
      vnh5019_set(&right_gripper.motor,0,REVERSE);
      break; 
     case 4: //gripper2
       vnh5019_set(&extension_system.motor,0,REVERSE);
       vnh5019_set(&cleaner_system.motor,0,REVERSE);
       vnh5019_set(&left_gripper.motor,0,REVERSE);
       pot_value = analogRead(USER_POT_PIN);
      if(pot_value < 128){
              vnh5019_set(&right_gripper.motor,pot_value,REVERSE);
      }else{
              vnh5019_set(&right_gripper.motor,pot_value - 128,FORWARD);
      }
      break;
   }
   }
   
 }

bool cleaner_right_contact(cleaner_state_t* cleaner){
   return btn_get_value(&cleaner->right_limit_switch); 
}

bool cleaner_left_contact(cleaner_state_t* cleaner){
   return btn_get_value(&cleaner->left_limit_switch); 
}
 
 //blocking 
 void cleanLeft(cleaner_state_t* cleaner){
     while(!cleaner_left_contact(cleaner)){ 
         vnh5019_set(&cleaner->motor,CLEANER_SPEED,CLEANER_LEFT_DIR);
       }
         vnh5019_set(&cleaner->motor,0,CLEANER_LEFT_DIR);

 }

 
 //blocking 
 void cleanRight(cleaner_state_t* cleaner){
     while(!cleaner_right_contact(cleaner)){ 
          vnh5019_set(&cleaner->motor,CLEANER_SPEED,CLEANER_RIGHT_DIR);
      }
          //turn off the motor since we are done
          vnh5019_set(&cleaner->motor,0,CLEANER_RIGHT_DIR);

 }
 
 
 void cleanThisLevel(cleaner_state_t* cleaner){
     cleanLeft(cleaner);
     for(int pass = 0;pass < 3; pass ++){
          cleanRight(cleaner);
          cleanLeft(cleaner);
     }
 }


 void moveToHeight(int newHeight){
  current_height = newHeight;  
  
  //TODO
   
   
 }
 
 void cleanWindow(cleaner_state_t* cleaner){
    int atBottom = false;
     while(!atBottom){
        cleanThisLevel(cleaner);
        if(current_height + MOVE_DOWN_BETWEEN_CLEANS < WINDOW_HEIGHT){
            moveToHeight(current_height+MOVE_DOWN_BETWEEN_CLEANS);
        }else{
            moveToHeight(WINDOW_HEIGHT-ROBOT_HEIGHT);
        }  
     }
     cleanThisLevel(cleaner); 
 }


/*****************************************************************
 **************************** main.c *****************************
 ****************************************************************/


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  

  current_height = WINDOW_HEIGHT;
  gripper_init(&left_gripper,LEFT_GRIPPER_INA_PIN,LEFT_GRIPPER_INB_PIN,LEFT_GRIPPER_PWM_PIN,LEFT_GRIPPER_CS_PIN);
  gripper_init(&right_gripper,RIGHT_GRIPPER_INA_PIN,RIGHT_GRIPPER_INB_PIN,RIGHT_GRIPPER_PWM_PIN,RIGHT_GRIPPER_CS_PIN);
  vnh5019_set(&left_gripper.motor,50,FORWARD); 

  gripper_lock(&left_gripper);
   
  
}

// the loop routine runs over and over again forever:
void loop() {
  /*
  // print out the value you read:
 Serial.println(moving_average_get_average(&test_filter));
 if() > 90){
     vnh5019_set(&left_gripper.motor,0,FORWARD); 
 }
 */
 
  delay(20);        // delay in between reads for stability
}

