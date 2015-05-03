//ALL units are in milimeters 
typedef enum vnh5019_direction {
  FORWARD,
  REVERSE,
} vnh5019_direction_t;


//TODO add safty to extension arm 
//TODO add pid controllers
//TODO clean up code 

/*******************************************************************
 ******************* SETTINGS.h ************************************
 ******************************************************************/
 #define DL_PER_STEP 10
 #define DR_PER_STEP 10
 #define DE_PER_STEP 0.25
 
 //left gripper speed controller 
#define LEFT_GRIPPER_INA_PIN     27   //1 
#define LEFT_GRIPPER_INB_PIN     26   //2 
#define LEFT_GRIPPER_PWM_PIN     5    //3
#define LEFT_GRIPPER_CS_PIN      A2   //4
#define LEFT_GRIPPER_POT_PIN     4   //analog pin 
#define LEFT_GRIPPER_POT_ZERO    515

//right gripper speed controller
#define RIGHT_GRIPPER_INA_PIN    23  //5       
#define RIGHT_GRIPPER_INB_PIN    22  //6      
#define RIGHT_GRIPPER_PWM_PIN    3  //7      
#define RIGHT_GRIPPER_CS_PIN     A0  //8     
#define RIGHT_GRIPPER_POT_PIN    5 //analog pin 
#define RIGHT_GRIPPER_POT_ZERO    500


//extsion speed controller 
#define EXTENSION_MOTOR_INA_PIN  29  //9     
#define EXTENSION_MOTOR_INB_PIN  28  //10    
#define EXTENSION_MOTOR_PWM_PIN  6  //11     
#define EXTENSION_MOTOR_CS_PIN   A3  //12     

//cleaner speed contoller
#define CLEANER_MOTOR_INA_PIN    25  //13   
#define CLEANER_MOTOR_INB_PIN    24  //14     
#define CLEANER_MOTOR_PWM_PIN    4  //15     
#define CLEANER_MOTOR_CS_PIN     A1  //16     

#define CLEANER_LEFT_BTN1_PIN     40  //17      
#define CLEANER_LEFT_BTN2_PIN     41  //18
#define CLEANER_RIGHT_BTN1_PIN    42  //19      
#define CLEANER_RIGHT_BTN2_PIN    43  //20

#define EXTESNION_SENSOR_POT_PIN 7  //23      //TODO set 

#define EXTENSION_MAX_SPEED      128


#define USER_BTN_TWO_PIN         31   //24     
#define USER_BTN_ONE_PIN         30   //25     
#define USER_POT_PIN             6   //26     //TODO set

#define WINDOW_WIDTH             0             //TODO set
#define WINDOW_HEIGHT            0             //TODO set

#define LEFT_GRIPPER_P           1             //TODO set
#define LEFT_GRIPPER_I           0             //TODO set
#define LEFT_GRIPPER_D           0             //TODO set

#define RIGHT_GRIPPER_P          1             //TODO set
#define RIGHT_GRIPPER_I          0             //TODO set
#define RIGHT_GRIPPER_D          0             //TODO set

#define EXTENSION_P              2             //TODO set
#define EXTENSION_I              0             //TODO set
#define EXTENSION_D              0             //TODO set
#define EXTENSION_THRESHOLD      .5             //TODO set

#define GRIPPER_SPEED             128          //TODO set

#define GRIPPER_LOCK_DIR          FORWARD      //TODO set
#define GRIPPER_UNLOCK_DIR        REVERSE      //TODO set
#define GRIPPER_THRESHOLD        5 
#define MOVE_DOWN_BETWEEN_CLEANS  0            //TODO set
#define ROBOT_HEIGHT              0            //TODO set
#define CLEANER_SPEED             255            //TODO set
#define CLEANER_RIGHT_DIR         FORWARD      //TODO set
#define CLEANER_LEFT_DIR          REVERSE      //TODO set
#define MOVEING_AVERAGE_ARRAY_SIZE 20          //TODO set

#define GRIPPER_CS_GRIP_THRESHOLD 200            //TODO set 
/***************************************************************
 ******************* button.h **********************************
 **************************************************************/
class Button{
 private:
  uint8_t pin;
  bool was_high;
  bool was_low;
  bool invert;
 
 public:
   Button(uint8_t pin,bool invert);
   bool get_value();
   bool get_was_high();
   bool get_was_low();
   void ack();
   void update_state(); 
   String get_state_string();
};
/*****************************************************************
 ************************ moving average *************************
 ****************************************************************/
 class MovingAverageFilter{
  private:
    int dataPoints[MOVEING_AVERAGE_ARRAY_SIZE];
    int oldestIndex;
  
  public:
    int get_average();
    void add_data_point(int newDataPoint);
    MovingAverageFilter();
 };

/*****************************************************************
 ********************************* VNH5019.h *********************
 ****************************************************************/
class Vnh5019{
  private:
    uint8_t ina_pin;
    uint8_t inb_pin;
    uint8_t pwm_pin;
    uint8_t cs_pin;
    uint8_t speed;
    vnh5019_direction_t direction;
    MovingAverageFilter* cs_filter;
  
  // Methods
  public:
    Vnh5019(uint8_t ina_pin,uint8_t inb_pin,uint8_t pwm_pin,uint8_t cs_pin);
    uint8_t get_speed();
    vnh5019_direction_t get_direction();
    uint8_t get_cs_value(); //must be run after get_cs_value_begin() for a sampling time
    uint8_t get_cs_value_begin();
    int set(uint8_t speed,vnh5019_direction_t direction);
    int set_speed(uint8_t speed);
    int set_direction(vnh5019_direction_t direction);    
};

                      
/****************************************************************
 ****************************** Gripper.h ***********************
 ***************************************************************/
 class Gripper
{
 private:
    MovingAverageFilter cs_filter;
    int sensor_pin;
 public: 
    Vnh5019* motor;
    Gripper(int ina_pin,int inb_pin,int pwm_pin,int cs_pin,int pot_pin);
    void turnRight();
    void turnLeft();
    void turnOff();
    void lock(vnh5019_direction_t);
    void unlock(vnh5019_direction_t);
    String get_state_string();
    int get_current_rotation();
    int turnTo(int desiredRotation);
};


/***************************************************************
*************************** cleaner.h **************************
***************************************************************/
class Cleaner{  
 private:
    Vnh5019* motor;
    Button* left_limit_switch1;
    Button* left_limit_switch2;
    Button* right_limit_switch1;
    Button* right_limit_switch2;   

 public:
    Cleaner(int ina_pin,int inb_pin,int pwm_pin,int cs_pin);
    void cleanLeft();
    void cleanRight();
    void turnOff();
    void cleanThisLevel();
    void cleanWindow();
    bool right_contact();
    bool left_contact();
    String get_state_string();
 };
  



/***************************************************************
***************** extension.h *********************
******************************************************************/
class ExtensionSystem{
  //member variables
  private:
  uint8_t sensor_pin;
  
  //methods 
  public:
  Vnh5019* motor; 
  ExtensionSystem(int ina_pin,int inb_pin,int pwm_pin,int cs_pin);
  void contract();
  void expand();
  void turnOff();
  void extend_to(float point_to_move_to);
  float  get_current_position();
  String get_state_string();
  void contract_unitl_current_limit();
};
/***************************************************************
***************** Robot.h **************************************
***************************************************************/
class Robot{
  private:
   Gripper* left_gripper;
   Gripper* right_gripper;
   ExtensionSystem* extension_system;
   Cleaner* cleaner_system;
   Button* usr_btn1; 
   Button* usr_btn2;
   int current_height;
   
  public: 
   Robot();
   void goTo(int leftGripper,int rightGripper,float extension);
   void move_to_height(int newHeight);
   void clean_window();
   void reportState();
   void teleop();
   void attachToWindow();
   void stepDown();
};


/****************************************************************
 *********** Global defintions **********************************
 ****************************************************************/
   Robot* thisRobot;

  //for concurent motor operation 
 void update(){
//   update_btn_state(&user_btn_one);
    //TODO
 } 
 
 /**************************************************************
 ************************ Moving average Filter ****************
 **************************************************************/
 MovingAverageFilter::MovingAverageFilter(){
   oldestIndex = 0;
   for(int i =0; i< MOVEING_AVERAGE_ARRAY_SIZE;i++){
      dataPoints[i] = 0;
   } 
}

 
 int  MovingAverageFilter::get_average(){
   int sum = 0;
   for(int i = 0;i<MOVEING_AVERAGE_ARRAY_SIZE;i++){
      sum += dataPoints[i]/MOVEING_AVERAGE_ARRAY_SIZE; 
   }
   return sum;   
 }
 
void MovingAverageFilter::add_data_point(int newDataPoint){
    oldestIndex = (oldestIndex + 1) % MOVEING_AVERAGE_ARRAY_SIZE;
    dataPoints[oldestIndex] = newDataPoint;  
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
 Vnh5019::Vnh5019(uint8_t ina_pin,uint8_t inb_pin,uint8_t pwm_pin,uint8_t cs_pin){
  // Copy initialization data. 
  this->ina_pin = ina_pin;
  this->inb_pin = inb_pin;
  this->pwm_pin = pwm_pin;
  this->cs_pin  = cs_pin;
  this->speed = 0;
  this->direction = FORWARD;
  cs_filter = new MovingAverageFilter();
   
  //sets up pins for OUTPUT 
  pinMode(ina_pin,OUTPUT);
  pinMode(inb_pin,OUTPUT);
}

 // Read the current speed from controller state structure.
 // @param state: controller state structure.
 // @return: the current speed.
uint8_t Vnh5019::get_speed() {
  return speed;
}

 // Read the current direction from controller state structure.
 // @param state: controller state structure.
 // @return: the current direction.
vnh5019_direction_t Vnh5019::get_direction() {
  return direction;
}

 // Read the most recent current sense reading from controller state structure.
 // @param state: controller state structure.
 // @return: current sense value.
uint8_t Vnh5019::get_cs_value() {
  cs_filter->add_data_point(analogRead(cs_pin));
  return cs_filter->get_average();
}

uint8_t Vnh5019::get_cs_value_begin(){
  //add init values 
  for(int i = 0;i<MOVEING_AVERAGE_ARRAY_SIZE;i++){
      get_cs_value();
  }
}


 // Sets new outputs to the given controller. Controller state must have been
 // initialized already.
 // @param state: controller state structure.
 // @param speed: new speed to set.
 // @param direction: new direction to set.
 // @return: 0 on successful completion, -1 on HAL error.
int Vnh5019::set(uint8_t speed,vnh5019_direction_t direction) {
  if(set_speed(speed) != 0) {
    return -1;
  }
  if(set_direction(direction) != 0) {
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
int Vnh5019::set_speed(uint8_t speed) {
  // update saved state
  speed = speed;

  // update hardware
  analogWrite(pwm_pin,speed); 

  // completed without errors
  return 0;
}

 // Sets new outputs to the given controller. Controller state must have been
 // initialized already.
 // @param state: controller state structure.
 // @param direction: new direction to set.
 // @return: 0 on successful completion, -1 on HAL error.
int Vnh5019::set_direction(vnh5019_direction_t direction) {
  // update saved state
  direction = direction;

  // set hw outputs
  if(direction == FORWARD) {
     digitalWrite(ina_pin,true);
     digitalWrite(inb_pin,false);
  } else {
    digitalWrite(ina_pin,false);
    digitalWrite(inb_pin,true); 
  }

  // completed without errors
  return 0;
}
/****************************************************************
 **************** button.c **************************************
 ***************************************************************/
  Button::Button(uint8_t input_pin,bool invert){
      pin = input_pin; 
      pinMode(pin,INPUT_PULLUP);
      this->invert = invert;
   }  
   
  bool Button::get_was_high(){
     update_state();
    return was_high;
  }

  bool Button::get_was_low(){
     update_state();
    return was_low;
  }

   void Button::ack(){
       was_low = false;
       was_high = false;
       delay(200);
   } 
   
    void Button::update_state(){
      if(get_value()){
          //true
          was_high = true;
      }else{
          was_low = true;
      }
    }
    
  bool Button::get_value(){
    if(invert){
     return digitalRead(pin) == false;
    }else{
      return digitalRead(pin);
    }
  }
  
  String Button::get_state_string(){
   if(get_value()){
    return "true";
   }else{
    return "false";
   } 
  }


/*****************************************************************
*********************** Gripper.c ********************************
*****************************************************************/
Gripper::Gripper(int ina_pin,int inb_pin,int pwm_pin,int cs_pin,int pot_pin){
  motor = new Vnh5019(ina_pin,inb_pin,pwm_pin,cs_pin); 
  sensor_pin = pot_pin;
}

void Gripper::turnRight(){
 thisRobot->reportState(); //TODO temp remove
 motor->set(GRIPPER_SPEED,FORWARD);
}

void Gripper::turnLeft(){
  thisRobot->reportState(); //TODO temp remove
  motor->set(GRIPPER_SPEED,REVERSE);
}

void Gripper::turnOff(){
  motor->set(0,REVERSE);
}

//blocking
void Gripper::lock(vnh5019_direction_t dir){
  motor->get_cs_value_begin();
  while(motor->get_cs_value() < GRIPPER_CS_GRIP_THRESHOLD && get_current_rotation() > 300 && get_current_rotation() < 700){
     motor->set(GRIPPER_SPEED,dir);
     delay(20);
  }  
     motor->set(0,GRIPPER_LOCK_DIR);
}

//blocking
void Gripper::unlock(vnh5019_direction_t dir){
  motor->get_cs_value_begin();
  while(motor->get_cs_value() > GRIPPER_CS_GRIP_THRESHOLD){
     motor->set(GRIPPER_SPEED,dir);
     delay(20);
  }  
     motor->set(0,GRIPPER_UNLOCK_DIR);


}

int Gripper::get_current_rotation(){
  return analogRead(sensor_pin);
}

 String Gripper::get_state_string(){
   String s1 = String(get_current_rotation());
   String s2 = String(motor->get_cs_value());   
   return "r("+s1+") c("+s2+")";
 }
 
 int  Gripper::turnTo(int desiredRotation){
   if(desiredRotation >= 1024 || desiredRotation <= 0){
    Serial.print("desiredRotation of ");
    Serial.print(desiredRotation);
    Serial.println(" is out of possible range");
    return false; 
   }
   int error = desiredRotation - get_current_rotation();
   while(abs(error) > GRIPPER_THRESHOLD){
     error = desiredRotation - get_current_rotation();
     thisRobot->reportState();
     if(error > 0){
       motor->set(50,REVERSE);
     }else{
       motor->set(50,FORWARD);
     }
   }
   //turn off motors at the end
     motor->set(0,FORWARD); 
     return true;
 }
 
/*****************************************************************
 ********************** Cleaner.c ********************************
 ****************************************************************/
 Cleaner::Cleaner(int ina_pin,int inb_pin,int pwm_pin,int cs_pin){
   left_limit_switch1 = new Button(CLEANER_LEFT_BTN1_PIN,true);
   left_limit_switch2 = new Button(CLEANER_LEFT_BTN2_PIN,true);
   right_limit_switch1 = new Button(CLEANER_RIGHT_BTN1_PIN,true);
   right_limit_switch2 = new Button(CLEANER_RIGHT_BTN2_PIN,false);
   motor = new Vnh5019(ina_pin,inb_pin,pwm_pin,cs_pin);
 }
 
 
bool Cleaner::right_contact(){
   return right_limit_switch1->get_value()  == true|| right_limit_switch2->get_value() == true ; 
}

bool Cleaner::left_contact(){
   return left_limit_switch1->get_value() == true || left_limit_switch2->get_value() == true; 
}

void Cleaner::turnOff(){
  motor->set(0,FORWARD);
}
 
 //blocking 
 void Cleaner::cleanLeft(){
     while(!left_contact()){ 
         thisRobot->reportState(); //TODO temp remove
         motor->set(CLEANER_SPEED,CLEANER_LEFT_DIR);
       }
         motor->set(0,CLEANER_LEFT_DIR);
 }

 
 //blocking 
 void Cleaner::cleanRight(){
     while(!right_contact()){ 
         thisRobot->reportState();  //TDOO temp remvoe
          motor->set(CLEANER_SPEED,CLEANER_RIGHT_DIR);
      }
          //turn off the motor since we are done
          motor->set(0,CLEANER_RIGHT_DIR);

 }
 
 
 void Cleaner::cleanThisLevel(){
     cleanLeft();
     for(int pass = 0;pass < 3; pass ++){
          cleanRight();
          cleanLeft();
     }
 }
 
 String Cleaner::get_state_string(){
   String s1 = left_limit_switch1->get_state_string();
   String s2 = left_limit_switch2->get_state_string();
   String s3 = right_limit_switch1->get_state_string();
   String s4 = right_limit_switch2->get_state_string();
   return s1 + s2 + s3 + s4; //TODO 
 }
 
 
 /****************************************************************
 *********************** Extension.c *******************************
 *****************************************************************/
  ExtensionSystem::ExtensionSystem(int ina_pin,int inb_pin,int pwm_pin,int cs_pin){
    motor = new Vnh5019(ina_pin,inb_pin,pwm_pin,cs_pin);
    sensor_pin = EXTESNION_SENSOR_POT_PIN;
 }
  
 float ExtensionSystem::get_current_position(){
   return -0.031*((float)analogRead(sensor_pin))+61.269;
    // return -0.0309375*analogRead(sensor_pin)+62.0438;
 }
  
 void ExtensionSystem::contract(){
   //todo add limit swtiches
     motor->set(EXTENSION_MAX_SPEED,FORWARD);
 }
 
 void ExtensionSystem::expand(){
   //TODO add limit switches
    motor->set(EXTENSION_MAX_SPEED,REVERSE);

 }
 
 void ExtensionSystem::turnOff(){
   motor->set(0,REVERSE);
 }
   
 
 //blocking
 void ExtensionSystem::extend_to(float point_to_move_to){
     int current_point = get_current_position(); 
     float error;
     Serial.println("starting extension");
     while(abs(error) > EXTENSION_THRESHOLD){
       current_point = get_current_position();
       error =  current_point - point_to_move_to;
        Serial.println(error);
          thisRobot->reportState();
        if(error > 0){
          motor->set(EXTENSION_P*abs(error)+60,FORWARD);
        }else{
          motor->set(EXTENSION_P*abs(error)+60,REVERSE);
        }
     }
      Serial.println("done");  
      motor->set(0,REVERSE);    
  }
 
 //TODO 
void ExtensionSystem::contract_unitl_current_limit(){
  
}

String ExtensionSystem::get_state_string(){
   return String(get_current_position()); //TODO 
 }
 


 

 /****************************************************************
  ************************ Robot.c *******************************
  ***************************************************************/
  Robot::Robot(){
   extension_system = new ExtensionSystem(EXTENSION_MOTOR_INA_PIN,EXTENSION_MOTOR_INB_PIN,EXTENSION_MOTOR_PWM_PIN,EXTENSION_MOTOR_CS_PIN);
   cleaner_system = new Cleaner(CLEANER_MOTOR_INA_PIN,CLEANER_MOTOR_INB_PIN,CLEANER_MOTOR_PWM_PIN,CLEANER_MOTOR_CS_PIN);
   left_gripper = new Gripper(LEFT_GRIPPER_INA_PIN,LEFT_GRIPPER_INB_PIN,LEFT_GRIPPER_PWM_PIN,LEFT_GRIPPER_CS_PIN,LEFT_GRIPPER_POT_PIN);
   right_gripper = new Gripper(RIGHT_GRIPPER_INA_PIN,RIGHT_GRIPPER_INB_PIN,RIGHT_GRIPPER_PWM_PIN,RIGHT_GRIPPER_CS_PIN,RIGHT_GRIPPER_POT_PIN);
   usr_btn1 = new Button(USER_BTN_ONE_PIN,true);
   usr_btn2 = new Button(USER_BTN_TWO_PIN,true);
   int desired_left_gripper = left_gripper->get_current_rotation();    //TODO implment 
   int desired_right_gripper = right_gripper->get_current_rotation();  //TODO implment 
   float desired_extension = extension_system->get_current_position(); //TODO implment
  }
  
  
 
  void Robot::teleop(){
   int mode = 0;
   int pot_value;
   int LG = left_gripper->get_current_rotation();
   int RG = right_gripper->get_current_rotation();
   float E = extension_system->get_current_position();
   while(1){
    //TODO add state reporting by serial  
    //infinite loop 
      thisRobot->reportState();

    //update mode 
    if(usr_btn1->get_was_high() && usr_btn1->get_was_low()){
     //button was pressed
      mode = (mode + 1) % 5;
      usr_btn1->ack(); 
    }
    pot_value = analogRead(USER_POT_PIN);     
     switch(mode){
      case 0: 
          Serial.println("mode 0");
         //All off 
          extension_system->turnOff();
          cleaner_system->turnOff();
          left_gripper->turnOff();
          right_gripper->turnOff();
         break; 
      case 1:
        Serial.println("mode 1");
        //extension
        if(usr_btn2->get_value()){
          E = 0.0244140625*((float)pot_value)+36.75;
          goTo(LG,RG,E);  //TODO set offset for pot_value
          cleaner_system->turnOff();
        }else{
          extension_system->turnOff();
          cleaner_system->turnOff();
          left_gripper->turnOff();
          right_gripper->turnOff();
        }
        
         break;
      case 2:
         Serial.println("mode 2");
         // right gripper
         if(usr_btn2->get_value()){

           cleaner_system->turnOff();
           RG = pot_value;
           goTo(LG,RG,E);  //TODO set offset for pot_value
         }else{
           extension_system->turnOff();
          cleaner_system->turnOff();
          left_gripper->turnOff();
          right_gripper->turnOff(); 
           
         }
         break;
       case 3:
          Serial.println("mode 3");
          //left gripper
          //TODO set left gripper based on some sensor
          if(usr_btn2->get_value()){
            cleaner_system->turnOff();
            LG = pot_value;
            goTo(LG,RG,E);  //TODO set offset for pot_value
          }else{
           extension_system->turnOff();
          cleaner_system->turnOff();
          left_gripper->turnOff();
          right_gripper->turnOff();  
         }            
          break;
       case 4:
          Serial.println("mode 4");
          // cleaner
          //TODO set cleaner system based on some sensor 
           if(usr_btn2->get_value()){

          
          extension_system->turnOff();
           if(pot_value > 600){
                    cleaner_system->cleanLeft(); 
         }else if(pot_value < 400){
           cleaner_system->cleanRight();
         }else{
           cleaner_system->turnOff();
         }
          left_gripper->turnOff();
          right_gripper->turnOff();
           }else{
            extension_system->turnOff();
          cleaner_system->turnOff();
          left_gripper->turnOff();
          right_gripper->turnOff();             
             
           }
           break;
       //TODO add auton 
     }
     
     
   }
 }
 
 void Robot::attachToWindow(){
   int value;
   // make Both Grippers verticale 
   usr_btn1->ack();
   while(!usr_btn1->get_was_high() || !usr_btn1->get_was_low()){
    delay(20); 
   }
   left_gripper->turnTo(LEFT_GRIPPER_POT_ZERO);
   right_gripper->turnTo(RIGHT_GRIPPER_POT_ZERO);
   // contract extension unit until current is above threashold
   usr_btn1->ack(); 
   Serial.println("startToAttach");
    while(!usr_btn1->get_was_high() || !usr_btn1->get_was_low()){
      Serial.println("in mode 1");
     thisRobot->reportState();
     value = analogRead(USER_POT_PIN);
     if(value > 600){
       extension_system->expand();
     }else if(value < 400){
       extension_system->contract();
     }else{
      extension_system->turnOff();
     }
   }
   extension_system->turnOff();
   // turn both grippers inwards (left gripper right, right gripper left)
   usr_btn1->ack();
   while(!usr_btn1->get_was_high() || !usr_btn1->get_was_low()){
     Serial.println("in mode 2");
     extension_system->contract();
   }
   extension_system->turnOff();
   usr_btn1->ack();
   delay(200);
   left_gripper->lock(FORWARD);
   right_gripper->lock(REVERSE);
 }
   
 
 void Robot::clean_window(){
 //attachToWindow();
 //while(true){
 //    thisRobot->reportState();
 //    thisRobot->stepDown();
     
/*      if(usr_btn1->get_value()){
     extension_system->extend_to(55);
      }
      */

/*
 while(true){
     thisRobot->reportState();
   if(usr_btn1->get_value()){
    if(usr_btn2->get_value()){
       extension_system->expand();
    }else{
      extension_system->contract();
    }
   }else{
      extension_system->turnOff(); 
   }
 }
 */
 
   
// extension_system->contract();
//  left_gripper->turnTo(LEFT_GRIPPER_POT_ZERO);
//  delay(200);
  /*
  while(true){
    left_gripper->turnTo(600);
    left_gripper->turnTo(400);
  }
  */
//  left_gripper->lock(FORWARD);
 // right_gripper->turnLeft();
   //cleaner_system->cleanRight();
   //cleaner_system->cleanRight();
   //cleaner_system->cleanLeft();
   /*
    int atBottom = false;
     while(!atBottom){
        cleaner_system->cleanThisLevel();
        if(current_height + MOVE_DOWN_BETWEEN_CLEANS < WINDOW_HEIGHT){
            move_to_height(current_height+MOVE_DOWN_BETWEEN_CLEANS);
        }else{
            move_to_height(WINDOW_HEIGHT-ROBOT_HEIGHT);
        }  
     }
     cleaner_system->cleanThisLevel(); 
     */
 }
 
 //TODO fix that this function copys code 
 void Robot::goTo(int left_goal,int right_goal,float extension_goal){
   int error_left = left_goal - left_gripper->get_current_rotation();
   int error_right  = right_goal - right_gripper->get_current_rotation();
   float error_e = extension_goal - extension_system->get_current_position();
     
     if(abs(error_left) > GRIPPER_THRESHOLD){
        //update the left gripper 
        if(error_left > 0){
           left_gripper->motor->set(LEFT_GRIPPER_P*abs(error_left),REVERSE);
        }else{
           left_gripper->motor->set(LEFT_GRIPPER_P*abs(error_left),FORWARD);
        }
     }else{
       left_gripper->turnOff();
     }
     
     
      if(abs(error_right) > GRIPPER_THRESHOLD){
        //update the right gripper
        if(error_right > 0){
           right_gripper->motor->set(RIGHT_GRIPPER_P*abs(error_right),REVERSE);
        }else{
           right_gripper->motor->set(RIGHT_GRIPPER_P*abs(error_right),FORWARD);
        }
      }else{
        right_gripper->turnOff();
      }
      
      
      if(abs(error_e) > EXTENSION_THRESHOLD){
       //update the extension amount
        if(error_e > 0){
          extension_system->motor->set(EXTENSION_P*abs(error_e)+60,REVERSE);
        }else{
          extension_system->motor->set(EXTENSION_P*abs(error_e)+60,FORWARD);
         }
      }else{
       extension_system->turnOff(); 
      }
 }
 
 void Robot::stepDown(){
  //TODO
 goTo(left_gripper->get_current_rotation() + DL_PER_STEP,right_gripper->get_current_rotation()+DR_PER_STEP,extension_system->get_current_position()+DE_PER_STEP); 
  //turn left gripper a little bit
  //extend a little bit
  //turn right gripper a little bit 
  
 }
 
 void Robot::move_to_height(int newHeight){
  current_height = newHeight;  
  
  //TODO
   
   
 }

//prints the robot state to the serial port
void Robot::reportState(){
  Serial.print("C: ");
  Serial.print(cleaner_system->get_state_string());
  Serial.print("LG:");
  Serial.print(left_gripper->get_state_string());
  Serial.print("\t RG:");
  Serial.print(right_gripper->get_state_string());
  Serial.print("\t E:");
  Serial.print(extension_system->get_state_string());
  Serial.print("\t btn1:");
  Serial.print(usr_btn1->get_value());
  Serial.print("  btn2:");
  Serial.print(usr_btn2->get_value());
  Serial.print("  pot:");
  Serial.println(analogRead(USER_POT_PIN)); //TODO 
  Serial.println(""); 
}

/*****************************************************************
 **************************** main.c *****************************
 ****************************************************************/
// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  thisRobot = new Robot();
 thisRobot->teleop();
 //thisRobot->clean_window();
/*
  state = new Vnh5019(EXTENSION_MOTOR_INA_PIN,EXTENSION_MOTOR_INB_PIN,EXTENSION_MOTOR_PWM_PIN,EXTENSION_MOTOR_CS_PIN);
  state->set(128,REVERSE);
//    ExtensionSystem extension_system = new ExtensionSystem(EXTENSION_MOTOR_INA_PIN,RIGHT_GRIPPER_INB_PIN,RIGHT_GRIPPER_PWM_PIN,RIGHT_GRIPPER_CS_PIN);
  // initialize serial communication at 9600 bits per second:
  */
}
// the loop routine runs over and over again forever:
void loop() {
  thisRobot->reportState();
  //Serial.println(String(analogRead(A4)));
 
  delay(20);        // delay in between reads for stability
}

