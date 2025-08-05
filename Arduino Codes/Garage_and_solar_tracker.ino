#include <IRremote.hpp>
#define IR_RECEIVE_PIN A0
#include <Servo.h>

Servo servo1;
int i = 62;
 #define LDR1 A1
#define LDR2 A2
#define error 10
int Spoint = 90; 
Servo servo2;
 
void setup() { 
  Serial.begin(9600);
  servo1.attach(9);
  servo1.write(62);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  servo2.attach(11);
  servo2.write(Spoint);
  delay(1000);
}
void loop() {
 if (IrReceiver.decode()) {
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    IrReceiver.resume();
    if(IrReceiver.decodedIRData.decodedRawData==0xAD52FF00){
      while (i>=22) {
      servo1.write(i);
      delay(50);
      i=i-2;
      }
    }
    if(IrReceiver.decodedIRData.decodedRawData==0xE718FF00){
      while (i<=62) {
      servo1.write(i);
      delay(50);
      i=i+2;
      }
    }
    
 }
  int ldr1 = analogRead(LDR1);
  int ldr2 = analogRead(LDR2);
  int value1 = abs(ldr1 - ldr2);
  int value2 = abs(ldr2 - ldr1);

  
  if (value1 <= error || value2 <= error) {
    
  } else {
    
    if (ldr1 > ldr2 && Spoint > 0) {
      Spoint = constrain(Spoint - 1, 0, 180); 
    }
    if (ldr1 < ldr2 && Spoint < 180) {
      Spoint = constrain(Spoint + 1, 0, 180); 
    }
  }
  
  servo2.write(Spoint); 
  delay(80); 
}