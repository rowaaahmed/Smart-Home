int input1 = 4;
int input2 = 3;
int enable = 5;
int up = 6;
int down = 11;
int trig = 8;
int echo = 9;
int floorheight = 11;
long ultrasonic();

void setup() {
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);
  pinMode(enable, OUTPUT);
  pinMode(up, INPUT);
  pinMode(down, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  analogWrite(enable,10);
  Serial.begin(9600);
}

void loop() {
  //int up1 = digitalRead(up);
  Serial.println(digitalRead(up));
  //int down1 = digitalRead(down);
  Serial.println(digitalRead(down));
  long distance = ultrasonic();

  if (digitalRead(up) == LOW) {
    while (distance < floorheight) {
      
      digitalWrite(input1, HIGH);
      digitalWrite(input2, LOW);
      distance = ultrasonic();
      delay(200);
    }
    digitalWrite(input1, LOW);
  }
  if (digitalRead(down) == LOW) {
    while (distance > 3) {
      
      digitalWrite(input1, LOW);
      digitalWrite(input2, HIGH);
      distance = ultrasonic();
      delay(200);
    }
    digitalWrite(input2, LOW);
  }
}
long ultrasonic() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(2);
  digitalWrite(trig, LOW);
  long time = pulseIn(echo, HIGH);
  long distance = time * 0.034 / 2;
  Serial.print("distance=");
  Serial.println(distance);
  delay(20);
  return distance;
}