/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-one-to-many-esp32-esp8266/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/
#include <Stepper.h>
#include <esp_now.h>
#include <WiFi.h>
const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
#define IN1 16
#define IN2 22
#define IN3 21
#define IN4 17
Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);


//Structure example to receive data
//Must match the sender structure
typedef struct test_struct {
  int power;
} test_struct;

//Create a struct_message called myData
test_struct myData;

//callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Status: ");
  Serial.println(myData.power);
    if ( 70 < myData.power ){
      myStepper.step(stepsPerRevolution);
    } else if (myData.power < 60){
      myStepper.step(-stepsPerRevolution);
    }
  
}
 
void setup() {
  //Initialize Serial Monitor
  Serial.begin(115200);

  myStepper.setSpeed(10);
  
  //Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  //Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {

}
