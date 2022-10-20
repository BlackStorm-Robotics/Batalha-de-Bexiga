#include <BTAddress.h>
#include <BTAdvertisedDevice.h>
#include <BTScan.h>
#include <BluetoothSerial.h>

#define IN1 25
#define IN2 33
#define IN3 14
#define IN4 27

BluetoothSerial SerialBT;

void setup() {
  // Put your setup code here, to run once:
  Serial.begin(9600);

  // Entradas ponte H
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  SerialBT.begin("ESP32 Bexiga"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  delay(2000);
  Serial.println("--- Start ---");
}

void loop() {

  if (SerialBT.available()) {
    Serial.println(SerialBT.read());
  }
  delay(20);
}