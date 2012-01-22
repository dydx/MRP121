/*
 TouchWheel.pde
 MPR121 WhellPad Example Code
 
 by:Waiman Zhao
 Mail:Binpower@foxmail.com
 created on: 11/2/14

      SDA -> A4
      SCL -> A5
      IRQ -> D2
*/
#include <Wire.h>
#include"mpr121.h"

int pin = 13;
volatile int state = LOW;
int key = 0;

void setup()
{ 
  Serial.begin(9600);
  Wire.begin(); 
  mpr121QuickConfig();
  delay(500);
  pinMode(pin, OUTPUT);
  attachInterrupt(0, blink, FALLING);
}

void loop()
{
  digitalWrite(pin, state);  
  if(state==HIGH){
    key=wheelKey();
    if(key>=0){
    Serial.print("wheelKey:\t");
    Serial.println(key,DEC); 
    }
    
    key=keypad();
    if(key>=0){
    Serial.print("keypad:\t");
    Serial.println(key,DEC); 
    }
    state = LOW;
  }
}

void blink()
{
  state =HIGH;
}

