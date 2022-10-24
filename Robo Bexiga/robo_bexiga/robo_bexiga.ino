#include <BTAddress.h>
#include <BTAdvertisedDevice.h>
#include <BTScan.h>
#include <BluetoothSerial.h>

#define ENA 12
#define IN1 14
#define IN2 27

#define IN3 25
#define IN4 33
#define ENB 32

const bool FRENTE = true;
const bool TRAS = false;

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(9600);

  // Entradas ponte H
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);

  delay(2000);
  Serial.println("--- Start ---");

  SerialBT.begin("ESP32 Bexiga"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  Serial.println("Robozin deve ta funfando :D");
}

void loop() {

  if (SerialBT.available()) {
    char msg = SerialBT.read();
    //Serial.write(msg);
    //Serial.write("\n");

    // 0 = Stop, 1 = Go Forward, 2 = Go Backward, 3 = Rotate Right, 4 = Rotate Left, 5 = Turn Right Forward, 6 = Turn Left Forward, 7 = Turn Right Backward, 8 = turn Left Backward
    switch (msg) {
      case '0':
        Serial.println("Pare");
        Stop();
        break;
      case '1':
        Serial.println("Frente");
        Frente();
        break;
      case '2':
        Serial.println("Tras");
        Tras();
        break;
      case '3':
        Serial.println("Direita");
        RotateRight();
        break;
      case '4':
        Serial.println("Esquerda");
        RotateLeft();
        break;
      case '5':
        Serial.println("Frente Direita");
        Motores(255, 125, FRENTE);
        break;
      case '6':
        Serial.println("Fente Esquerda");
        Motores(125, 255, FRENTE);
        break;
      case '7':
        Serial.println("Tras Direita");
        Motores(255, 125, TRAS);
        break;
      case '8':
        Serial.println("Tras Esquerda");
        Motores(125, 255, TRAS);
        break;
    }
  }
}

void Motores(byte left, byte right, bool direction) {
  digitalWrite(IN1, direction);
  digitalWrite(IN2, !direction);
  digitalWrite(IN3, direction);
  digitalWrite(IN4, !direction);
  analogWrite(ENA, left);
  analogWrite(ENB, right);
}

void Frente() {
  Motores(255, 255, FRENTE);
}

void Tras() {
  Motores(255, 255, TRAS);
}

void Stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
}

void RotateRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
}

void RotateLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
}
