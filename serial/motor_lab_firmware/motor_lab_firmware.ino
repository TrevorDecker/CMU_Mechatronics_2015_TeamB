#include <PID_v1.h>
#include <Encoder.h>
#include <Servo.h>

// hardware configuration
#define INPUT_POT A0
#define INPUT_BEND A4
#define INPUT_LIMIT 4
#define OUTPUT_DEBUG 13
#define OUTPUT_SERVO 5
#define OUTPUT_MOTOR_FORWARD 12
#define OUTPUT_MOTOR_BACKWARD 13
#define OUTPUT_STEPPER_STEP 7
#define OUTPUT_STEPPER_DIR 8
#define OUTPUT_STEPPER_EN 9
#define INPUT_ENCODER_A 2  //should be on an interrupt pin 
#define INPUT_ENCODER_B 3  //should be on an interrupt pin 
#define KSPP 1
#define KSPI 0
#define KSPD 0 
#define KSVP 1
#define KSVI 0
#define KSVD 0 
#define KSPP 1
#define KDPI 0
#define KDPD 0
#define KSVP 1
#define KDVI 0
#define KDVD 0

#define STEPPER_DELAY_US 2000
#define FILTER_SIZE 32

struct FilterData {
  unsigned int total;
  unsigned int index;
  unsigned int data[FILTER_SIZE];
};

// zero out all the filter parameters and data
void filter_init(struct FilterData *filter_data) {
  filter_data->total = 0;
  filter_data->index = 0;
  for(unsigned int i = 0; i < FILTER_SIZE; i++) {
    (filter_data->data)[i] = 0;
  }
}

// add 
unsigned int filter_add(struct FilterData *filter_data, unsigned int new_value) {
  filter_data->total -= filter_data->data[filter_data->index];
  (filter_data->data)[filter_data->index] = new_value;
  filter_data->total += new_value;
  
  filter_data->index++;
  if(filter_data->index >= FILTER_SIZE) {
    filter_data->index = 0;
  }
  
  return (filter_data->total)/FILTER_SIZE;
}


// global data
unsigned int PotVal=0;
unsigned int BendVal=0;
unsigned int LimitVal=0;
unsigned int stepper_position = 0; //TODO should this be an unsigned int 
int stepper_velocity = 0;
unsigned int data_timer = 0;
double DC_position = 0;
double old_DC_position = 0;
double DC_velocity = 0;
int DC_Speed = 0;    //Using fixed point for reduced space usage 
int incomingByte = 0; //for incoming serial data

//PID
double Input_stepper_position_PID;
double Input_stepper_velocity_PID;
double Input_dc_position_PID;
double Input_dc_velocity_PID;

double Output_stepper_position_PID;
double Output_stepper_velocity_PID;
double Output_dc_position_PID;
double Output_dc_velocity_PID;

double Setpoint_stepper_position_PID;
double Setpoint_stepper_velocity_PID;
double Setpoint_dc_position_PID;
double Setpoint_dc_velocity_PID;

//time between encoder updates 
double dt;

PID stepper_position_PID(&Input_stepper_position_PID,&Output_stepper_position_PID,&Setpoint_stepper_position_PID,KSPP,KSPI,KSPD,DIRECT);
PID stepper_velocity_PID(&Input_stepper_velocity_PID,&Output_stepper_velocity_PID,&Setpoint_stepper_velocity_PID,KSVP,KSVI,KSVD,DIRECT);
PID dc_position_PID(&Input_dc_position_PID,&Output_stepper_position_PID,&Setpoint_stepper_position_PID,KSPP,KDPI,KDPD,DIRECT);
PID dc_velocity_PID(&Input_dc_velocity_PID,&Output_stepper_velocity_PID,&Setpoint_stepper_velocity_PID,KSVP,KDVI,KDVD,DIRECT);
Servo servo;
Encoder kencoder(INPUT_ENCODER_A,INPUT_ENCODER_B);
struct FilterData bend_filter;



/*-------------------------------------------*/
/* Initializization code (run once via call from Arduino framework) */
void setup() {
  // establish direction of pins we are using to drive LEDs 
  pinMode(INPUT_POT, INPUT); 
  //pinMode(BendBefore, OUTPUT); 
  pinMode(INPUT_BEND, INPUT);
  pinMode(INPUT_LIMIT, INPUT_PULLUP);
  pinMode(OUTPUT_DEBUG, OUTPUT);
  
  // output setup
  servo.attach(OUTPUT_SERVO); // servo
  pinMode(OUTPUT_MOTOR_FORWARD, OUTPUT);
  analogWrite(OUTPUT_MOTOR_FORWARD, 0);
  pinMode(OUTPUT_MOTOR_BACKWARD, OUTPUT);
  digitalWrite(OUTPUT_MOTOR_BACKWARD, 0);
  pinMode(OUTPUT_STEPPER_STEP, OUTPUT);
  digitalWrite(OUTPUT_STEPPER_STEP, 0);
  pinMode(OUTPUT_STEPPER_DIR, OUTPUT);
  digitalWrite(OUTPUT_STEPPER_DIR, 0);
  pinMode(OUTPUT_STEPPER_EN, OUTPUT);
  digitalWrite(OUTPUT_STEPPER_EN, 1);
  
  filter_init(&bend_filter);

/*  Input = DC_position;
  Setpoint = INPUT_POT;
  myPID.SetMode(AUTOMATIC);
*/
  
  
  Serial.begin(9600);
}

void set_Stepper_to(int goal){
   //TODO 
}

void set_Stepper_velocity(double goal_velocity){
 //TODO 
}

void step() {
  // enable controller
  digitalWrite(OUTPUT_STEPPER_EN, 0);
  delayMicroseconds(STEPPER_DELAY_US/2);
  // pulse up
  digitalWrite(OUTPUT_STEPPER_STEP, HIGH);
  delayMicroseconds(10);
  // pulse down
  digitalWrite(OUTPUT_STEPPER_STEP, LOW);
  delayMicroseconds(STEPPER_DELAY_US/2);
  // disable controller
  digitalWrite(OUTPUT_STEPPER_EN, 1);
}

void output_serial_data() {
  Serial.print(PotVal);
  Serial.print(" ");
  Serial.print(BendVal);
  Serial.print(" ");
  Serial.print(LimitVal);
  long newEncoder = kencoder.read();
  Serial.print(" ");
  Serial.print(newEncoder);
  Serial.print(" ");
  Serial.print(incomingByte);
  Serial.println();
}

void noGUI(){
  
  // set servo position
  // use the limit switch to move between 2 set positions
  if (LimitVal == 1) {
    servo.write(45);
  } else {
    servo.write(135);
  }
//  analogWrite(OUTPUT_MOTOR_FORWARD,Output);
      
  // set motor output based on pot value
  if (PotVal < 16) {
    // have a dead-band for low values
    analogWrite(OUTPUT_MOTOR_FORWARD, 0);
//    analogWrite(OUTPUT_MOTOR_BACKWARD, 0);
  } else {
    // rescale output since analog values are 0-1023
    analogWrite(OUTPUT_MOTOR_FORWARD, PotVal/4);
//    analogWrite(OUTPUT_MOTOR_BACKWARD, 0);
  }

  
  // set stepper motor to position based on bend sensor
  int stepper_position_error = BendVal - stepper_position;
  if (stepper_position_error > 8) {
    // set direction
    digitalWrite(OUTPUT_STEPPER_DIR, HIGH);
    step();
    stepper_position++;
  } else if (stepper_position_error < -8) {
    digitalWrite(OUTPUT_STEPPER_DIR, LOW);
    step();
    stepper_position--;
  }
}


/* Main routine (called repeated by from the Arduino framework) */
void loop() {
  dt = 1; //TODO change this 
  old_DC_position = DC_position;
  DC_position = kencoder.read();
  DC_velocity = (DC_position - old_DC_position)/dt;
  PotVal = analogRead(INPUT_POT);
  BendVal = filter_add(&bend_filter, analogRead(INPUT_BEND));
  LimitVal = digitalRead(INPUT_LIMIT);

  data_timer++;
  if (data_timer > 50) {
    data_timer = 0;
    output_serial_data();
  }


  //checks to see if data has been sent 
  if (Serial.available() > 0){
       //read the incoming byte:
      incomingByte = Serial.read();
  }
  
  //8 bits

// incomingByte = 0 then use all sensors on the board
// incomingByte > 0 then use gui 
// incomingByte_firstbit = 0 then set position
// incomingByte_firstbit = 1 then set velocity
// incomingByte_secondbit = 0 then servo = low extreme  
// incomingByte_secondbit = 1 then servo = high extreme
// incomingByte_thridBit = 0 then modify steper motor
// incomingByte_thridBit = 1 then modify DC motor
// incomingByte_fourthbit = direction
// incomingByte_5 - 8 = 0001 = 0
// incomingByte_5 - 8 = 0001 = 1
// incomingByte_5 - 8 = 0010 = 2
// incomingByte_5 - 8 = 0011 = 3
// incomingByte_5 - 8 = 0100 = 4
// incomingByte_5 - 8 = 0101 = 5
// incomingByte_5 - 8 = 0110 = 6
// incomingByte_5 - 8 = 0111 = 7
// incomingByte_5 - 8 = 1000 = 8
// incomingByte_5 - 8 = 1001 = 9
// incomingByte_5 - 8 = 1010 = 10
// incomingByte_5 - 8 = 1011 = 11
// incomingByte_5 - 8 = 1100 = 12
// incomingByte_5 - 8 = 1101 = 13
// incomingByte_5 - 8 = 1110 = 14
// incomingByte_5 - 8 = 1111 = 15
if(incomingByte == 0){
  noGUI();
}else{
 boolean velocityMode = ((incomingByte >> 7) & B10000000) == 1;
 boolean servoHigh    = ((incomingByte >> 6) & B01000000) == 1; 
 boolean stepperMotor  = ((incomingByte >> 5) & B00100000) == 1;
 boolean dir          = ((incomingByte >> 4) & B00010000) == 1;
 unsigned int speed_  = (incomingByte        & B00001111);
 //puts sign on the speed of the motor
 int delta = speed_;
 if(dir == 1){
    delta = -delta;
 } 
 
 if(servoHigh){
   //set servo   
   servo.write(180);
 }else{
   //set servo low 
   servo.write(45);
 }
 
 double Input_stepper_position_PID;
double Input_stepper_velocity_PID;
double Input_dc_position_PID;
double Input_dc_velocity_PID;

double Output_stepper_position_PID;
double Output_stepper_velocity_PID;
double Output_dc_position_PID;
double Output_dc_velocity_PID;

double Setpoint_stepper_position_PID;
double Setpoint_stepper_velocity_PID;
double Setpoint_dc_position_PID;
double Setpoint_dc_velocity_PID;
 
  if(stepperMotor){
    if(velocityMode){
     //set steperMotor velocityMode
     Input_stepper_velocity_PID =  stepper_velocity;
     //TODO update setpoint
     stepper_velocity_PID.Compute();
     //todo send value  
     }else{
      //set steperMotor Position Mode     
      Input_stepper_position_PID = stepper_position;
      //TODO update setpoint
      stepper_position_PID.Compute();
      //TODO send value 
    }
  }else{
    if(velocityMode){
     //set DCMotor velocityMode
     Input_dc_velocity_PID = DC_velocity;
     //TODO update setpoint
     dc_velocity_PID.Compute();
     //TDOO send value 
    }else{
      //set DCMotor Position Mode
      Input_dc_position_PID = DC_position;
      //TODO update setpoint
      dc_position_PID.Compute();
      //TODO send value 
      
    }
  }
 
}
  


//delay(1);
//step();

}  // end loop()
