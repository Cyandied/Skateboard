#include <ESP32Servo.h>
Servo myservo;
int pos = 0;
#define VRX_PIN 35
#define VRY_PIN 34
#define MOTOR 33

int xValue = 0;
int yValue = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(VRX_PIN, INPUT);
  pinMode(VRY_PIN, INPUT);
  myservo.attach(MOTOR);
  myservo.write(pos);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
    xValue = analogRead(VRX_PIN);
    yValue = analogRead(VRY_PIN);

    pos = map(yValue,0,4095,0,180);

    myservo.write(pos);

    

  Serial.print("x = ");
  Serial.print(xValue);
  Serial.print(", y = ");
  Serial.print(yValue);
  Serial.println("");
  delay(1500);
}
