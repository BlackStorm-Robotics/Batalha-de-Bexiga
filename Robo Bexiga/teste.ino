#define IN1 25
#define IN2 33
#define IN3 14
#define IN4 27

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);
  Serial.println("Loading...");

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  delay(2000);
  Serial.println("Start");

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Running...");
  delay(1000);
}
