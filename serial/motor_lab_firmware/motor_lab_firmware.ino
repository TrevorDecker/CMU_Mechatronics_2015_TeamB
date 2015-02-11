#include <PID_v1.h>

#include <Encoder.h>

#include <Servo.h>

// hardware configuration
#define INPUT_POT A0
#define INPUT_RANGE A4
#define INPUT_BEND A1
#define INPUT_LIMIT 4
#define OUTPUT_DEBUG 13
#define OUTPUT_SERVO 9
#define OUTPUT_MOTOR_FORWARD 5
#define OUTPUT_MOTOR_BACKWARD 6
#define OUTPUT_STEPPER_STEP 7
#define OUTPUT_STEPPER_DIR 8
#define OUTPUT_STEPPER_EN 13
#define INPUT_ENCODER_A 2  //should be on an interrupt pin 
#define INPUT_ENCODER_B 3  //should be on an interrupt pin 
#define KDPP 1
#define KDPI 0
#define KDPD 0
#define KDVP 1
#define KDVI 0
#define KDVD 0

#define ENCODER_DT_MIN_MS 50
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
// sensor readings
unsigned int encoder_position = 0;
unsigned int encoder_position_old = 0;
double encoder_velocity = 0;
unsigned int pot_value = 0;
unsigned int range_value = 0;
unsigned int bend_value = 0;
uint8_t limit_value_old = 0;
uint8_t limit_value = 0;
// setpoints
unsigned int stepper_position = 0; //TODO should this be an unsigned int
unsigned int stepper_setpoint = 0;
uint8_t servo_setpoint = 0;
uint8_t motor_pwm_setpoint = 0;
uint8_t motor_pwm_direction = 0; // 0 = forwards
// program mode 0 = sensor, 1 = gui, velocity, 2 = gui, position, 3 = sensor, position
uint8_t program_mode = 0;
// other
byte index = 0;
char read_value[5];
unsigned int data_timer = 0;
uint8_t incomingByte = 0; // for incoming serial data
unsigned long time_old = 0;
unsigned long time_now = 0;
unsigned long time_dt = 0; // time between encoder updates
// PID
double pid_position_input;
double pid_position_output;
double pid_position_setpoint;
double pid_velocity_input;
double pid_velocity_output;
double pid_velocity_setpoint;

PID dc_position_PID(&pid_position_input,
                    &pid_position_output,
                    &pid_position_setpoint,
                    KDPP,KDPI,KDPD,DIRECT);
PID dc_velocity_PID(&pid_velocity_input,
                    &pid_velocity_output,
                    &pid_velocity_setpoint,
                    KDVP,KDVI,KDVD,DIRECT);
Servo servo;
Encoder kencoder(INPUT_ENCODER_A,INPUT_ENCODER_B);
struct FilterData bend_filter;
struct FilterData range_filter;



/*-------------------------------------------*/
/* Initializization code (run once via call from Arduino framework) */
void setup() {
  // establish direction of pins we are using to drive LEDs 
  pinMode(INPUT_POT, INPUT); 
  //pinMode(BendBefore, OUTPUT); 
  pinMode(INPUT_RANGE, INPUT);
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
  
  // filter setup
  filter_init(&range_filter);
  filter_init(&bend_filter);
  
  // PID setup
  dc_position_PID.SetOutputLimits(-255,255);
  
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
  /*
  Serial.print(pot_value);
  Serial.print(" ");
  Serial.print(range_value);
  Serial.print(" ");
  Serial.print(bend_value);
  Serial.print(" ");
  Serial.print(encoder_position);
  Serial.print(" ");
  Serial.print(encoder_velocity);
  Serial.print(" ");
  Serial.print(time_dt);
  Serial.print(" ");
  Serial.print(pid_position_input);
  Serial.print(" ");
  Serial.print(pid_position_output);
  Serial.print(" ");
  Serial.print(pid_position_setpoint);
  Serial.print(" ");
  Serial.print(program_mode);
  Serial.println();
  */
}


/* Main routine (called repeated by from the Arduino framework) */
void loop() {
  data_timer++;
  
  // read sensor data
  if(millis() - time_now > ENCODER_DT_MIN_MS) {
    // time
    time_old = time_now;
    time_now = millis();
    time_dt = time_now - time_old;
    // encoder update on slow cycle
    encoder_position_old = encoder_position;
    encoder_position = kencoder.read();
    encoder_velocity = ((double)(encoder_position - encoder_position_old))/((double)time_dt);
  }
  // analog sensors
  pot_value = analogRead(INPUT_POT);
  range_value = filter_add(&range_filter, analogRead(INPUT_RANGE));
  bend_value = filter_add(&bend_filter, analogRead(INPUT_BEND));
  limit_value_old = limit_value;
  limit_value = digitalRead(INPUT_LIMIT);

  //checks to see if data has been sent 
  if (Serial.available() > 0){
    char mode = 0;
       //read the incoming byte:
      incomingByte = Serial.read();
      Serial.println(incomingByte);
      switch (incomingByte){
       case 'S': 
         //servo mode 
         Serial.println("S MODE");
         index = 0;
         mode = 'S';
         break;
       case 'R':
         //reset
         Serial.println("R Mode");
         index = 0;
         mode = 'R';
         break;
       case 'P':
         //Position DC
         Serial.println("P Mode");
         index = 0;
         mode = 'P';
         break; 
       case 'V':
         //Velocity DC
         Serial.println("V Mode");
         index = 0;
         mode = 'V';
         break;
       case 'A':
        //Stepper position
         Serial.println("A Mode");
         index = 0;
         mode = 'A';
        break;
       default:
         Serial.print("default:");
         Serial.println(incomingByte);
        read_value[index] = incomingByte;
        index ++;
         int sum;
        if(index > 3){
          sum = atoi(read_value);
          Serial.print("top:");
          Serial.println(read_value);
          index = 0;
          //send data to the correct motor
         //TODO  
        }
     }
  }
  
  
  
  // change program mode, if necessary
  if(limit_value_old == 0 && limit_value == 1) {
    if(program_mode < 3) {
      program_mode++;
    } else {
      program_mode = 0;
    }
  }
  
  
  // determine proper control settings
  if(program_mode == 1) {
    // gui control velocity
    if(dc_velocity_PID.GetMode() == MANUAL) {
      dc_position_PID.SetMode(MANUAL);
      dc_velocity_PID.SetMode(AUTOMATIC);
    }
    // todo
  } else if (program_mode == 2) {
    // gui control position
    if(dc_position_PID.GetMode() == MANUAL) {
      dc_velocity_PID.SetMode(MANUAL);
      dc_position_PID.SetMode(AUTOMATIC);
    }
    // todo
  } else if (program_mode == 3) {
    // sensor control with motor position
    pid_position_input = encoder_position;
    pid_position_setpoint = (double)(pot_value);
    if(dc_position_PID.GetMode() == MANUAL) {
      dc_velocity_PID.SetMode(MANUAL);
      dc_position_PID.SetMode(AUTOMATIC);
    }
    dc_position_PID.Compute();
    
    // process output
    if(pid_position_output < 0) {
      motor_pwm_direction = 1;
    } else {
      motor_pwm_direction = 0;
    }
    
    motor_pwm_setpoint = (uint8_t)pid_position_output;
    
    stepper_setpoint = range_value; // 0-1024
    servo_setpoint = 45;
  } else {
    // user motor velocity pid
    pid_velocity_input = encoder_velocity * 512;
    pid_velocity_setpoint = (double)(pot_value/4);
    if(dc_velocity_PID.GetMode() == MANUAL) {
      dc_position_PID.SetMode(MANUAL);
      dc_velocity_PID.SetMode(AUTOMATIC);
    }
    dc_velocity_PID.Compute();
    motor_pwm_direction = 0; // forwards
    motor_pwm_setpoint = (uint8_t)pid_velocity_output;

    stepper_setpoint = range_value; // 0-1024
    servo_setpoint = 45;
  }
  
  // output settings
  // set servo
  servo.write(servo_setpoint);
  
  // set motor output based on pot value
  if (motor_pwm_setpoint < 16) {
    // have a dead-band for low values
    analogWrite(OUTPUT_MOTOR_FORWARD, 0);
    analogWrite(OUTPUT_MOTOR_BACKWARD, 0);
  } else if (motor_pwm_direction == 0) {
    // move forwards
    analogWrite(OUTPUT_MOTOR_FORWARD, motor_pwm_setpoint);
    analogWrite(OUTPUT_MOTOR_BACKWARD, 0);
  } else {
    analogWrite(OUTPUT_MOTOR_FORWARD, 0);
    analogWrite(OUTPUT_MOTOR_BACKWARD, motor_pwm_setpoint);
  }
  
  
  // set stepper motor to position based on bend sensor
  int stepper_position_error = stepper_setpoint - stepper_position;
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
  
  // output relevant data
  if (data_timer == 50) {
    data_timer = 0;
    output_serial_data();
  }
}

