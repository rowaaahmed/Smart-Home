#include <Servo.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>

Servo servo;

 
#define SS_PIN 10
#define RST_PIN 9


MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
LiquidCrystal lcd(8, 7, 5, 4, 3, 2);
int contrast=0;

void setup() 
{
  lcd.begin(16, 2);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  pinMode(A0, OUTPUT);
  analogWrite(6,contrast);
  servo.attach(A0);
  Serial.begin(9600);

}
void loop() 
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Put your Card");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Door locked");
  delay(1000);
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return; 
  }

  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();

  content.toUpperCase();
  if (content.substring(1) == "B3 6E 92 4B" ) //change here the UID of the card/cards that you want to give access
  {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.clear();
    lcd.print("Door unlocked");
    servo.write(105);
    delay(600);
    servo.write(90);
    delay(1000);

    servo.write(75);
    delay(600);
    servo.write(90);
    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.print("Door locked");
    delay(1000);
   
  }
 
 else if (content.substring(1) == "CC 1B 1B 30")   {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.clear();
    lcd.print("Wrong Card");
    delay(3000);
    lcd.clear();
    lcd.print("Door locked");
    delay(1000);
   
  }
}