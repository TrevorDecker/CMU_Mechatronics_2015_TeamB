#include <SPI.h>

/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
const int led = 13;
const int chipSelectPin = 10;
uint8_t result1, result2, result3;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  
  Serial.begin(9600);

  // start the SPI library:
  SPI.begin();
  pinMode(chipSelectPin, OUTPUT);
  digitalWrite(chipSelectPin, HIGH);
}

void print_reg(uint8_t reg_num) {
  digitalWrite(chipSelectPin, LOW);
  SPI.transfer(reg_num | 0x20);
  digitalWrite(chipSelectPin, HIGH);
  delay(10);
  digitalWrite(chipSelectPin, LOW);
  result1 = SPI.transfer(0x00);
  digitalWrite(chipSelectPin, HIGH);
  delay(10);
  digitalWrite(chipSelectPin, LOW);
  result2 = SPI.transfer(0x00);
  digitalWrite(chipSelectPin, HIGH);
  delay(10);
  digitalWrite(chipSelectPin, LOW);
  result3 = SPI.transfer(0x00);
  digitalWrite(chipSelectPin, HIGH);
  delay(10);
  
  Serial.print(reg_num, HEX);
  Serial.print(": ");
  Serial.print(result1, HEX);
  Serial.print(" ");
  Serial.print(result2, HEX);
  Serial.print(" ");
  Serial.println(result3, HEX);
}

// the loop routine runs over and over again forever:
void loop() {
  for(int i = 0; i < 0x1A; i++) {
    // scan through the chip registers
    print_reg(i);
  }
  
  digitalWrite(chipSelectPin, LOW);
  SPI.transfer(0x40);
  digitalWrite(chipSelectPin, HIGH);
  delay(10);
  digitalWrite(chipSelectPin, LOW);
  result1 = SPI.transfer(0x00);
  digitalWrite(chipSelectPin, HIGH);
  delay(10);
  digitalWrite(chipSelectPin, LOW);
  result2 = SPI.transfer(0xFF);
  digitalWrite(chipSelectPin, HIGH);
  delay(10);
  digitalWrite(chipSelectPin, LOW);
  result3 = SPI.transfer(0xFF);
  digitalWrite(chipSelectPin, HIGH);
  delay(3000);
  
  digitalWrite(chipSelectPin, LOW);
  SPI.transfer(0x41);
  digitalWrite(chipSelectPin, HIGH);
  delay(10);
  digitalWrite(chipSelectPin, LOW);
  result1 = SPI.transfer(0x00);
  digitalWrite(chipSelectPin, HIGH);
  delay(10);
  digitalWrite(chipSelectPin, LOW);
  result2 = SPI.transfer(0xFF);
  digitalWrite(chipSelectPin, HIGH);
  delay(10);
  digitalWrite(chipSelectPin, LOW);
  result3 = SPI.transfer(0xFF);
  digitalWrite(chipSelectPin, HIGH);
  delay(3000);
  
}
