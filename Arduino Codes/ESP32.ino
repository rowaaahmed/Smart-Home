#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL2xGVVPtOa"
#define BLYNK_TEMPLATE_NAME "Test"
#define BLYNK_AUTH_TOKEN "BUO-1dpSDUzTOOlm5MJj50PVQLwMNCof"


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Zaid";  //add netwrk name
char pass[] = "zaid1230";   //add network password

int Buzzer = 21;
int SW = 32;
int Laser = 13;
int LDR = 35;
int flag = 0;

int red = 19;
int Buzzer2 = 16;
int sensor = 34;
int Value = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(Buzzer, OUTPUT);
  pinMode(LDR, INPUT); 
  pinMode(Laser, OUTPUT);
  pinMode(SW, INPUT);

  pinMode(red, OUTPUT);
  pinMode(Buzzer2, OUTPUT);
  digitalWrite(red, LOW);
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();

  
  digitalWrite(Buzzer2, LOW);
  Value = analogRead(sensor);
  Serial.print("Smoke= ");
  Serial.println(Value);
  //Value = map(Value, 350, 450, 0, 100);

  if (digitalRead(Laser)){
    delay(300);
    int LDRStatus = analogRead(LDR);
    Serial.print("LDR= ");
    Serial.println(LDRStatus);


    if (LDRStatus <=100|| flag==1) {
      flag = 1;
      digitalWrite(Buzzer, HIGH);
      Blynk.logEvent("laser_security");
      tone(Buzzer,15000);             
      delay(100);
      noTone(Buzzer);
    }
    else {
      digitalWrite(Buzzer, LOW);
      flag==0;
   }
  }
  else{
    digitalWrite(Laser, LOW);
    digitalWrite(Buzzer, LOW);
    flag = 0;
  }
  
  if (Value >= 550) {

    digitalWrite(red, HIGH);
    Blynk.logEvent("smoke_sensor");
    tone(Buzzer2, 1000);
    delay(200);
    noTone(Buzzer2);
  } 

  else {
    digitalWrite(red, LOW);
  
  }
  delay(100);


}