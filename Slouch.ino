#include <Wire.h>
#include "BMA250.h"

BMA250 accel;


int ttl = 200;
int freq = 1;

boolean singleOn = true;
boolean displaySerial = false;

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  accel.begin(BMA250_range_2g, BMA250_update_time_32ms);
}

void loop() {
  
  accel.read();
  //Print out the accelerometer data
  if (displaySerial) {
  Serial.print("x: ");
  Serial.print(accel.X);
  Serial.print(", y: ");
  Serial.print(accel.Y);
  Serial.print(", z:");
  Serial.print(accel.Z);
  Serial.print(",  t: ");   
  Serial.print(accel.rawTemp/2 + 24);
  Serial.println("degC");
  // z = 155 - 0
  }
  
  Level(round(accel.Z/10)+1);
  //delay(100);
  
}

void Level(int level) {
  if (level > 17) level = 17;
  for(int i=1;i<level;i++){
    LedOn(i);
    delay(freq);
  };
  
}

void LedOn(int ledNum) {
  if (singleOn){ 
    for(int i=5;i<10;i++){
      pinMode(i, INPUT);
      digitalWrite(i, LOW);
    };
  }
  if(ledNum<1 || ledNum>16) return;
  char highpin[16]={5,6,5,7,6,7,6,8,5,8,8,7,9,7,9,8};
  char lowpin[16]= {6,5,7,5,7,6,8,6,8,5,7,8,7,9,8,9};
  ledNum--;
  digitalWrite(highpin[ledNum],HIGH);
  digitalWrite(lowpin[ledNum],LOW);
  pinMode(highpin[ledNum],OUTPUT);
  pinMode(lowpin[ledNum],OUTPUT);
}

