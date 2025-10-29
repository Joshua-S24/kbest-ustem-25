#include <Gizmo.h>
#include <Servo.h>

Gizmo gizmo;

Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;

unsigned long myTime;
bool running = true;

void setup() {
  // put your setup code here, to run once:
  gizmo.begin();
  motor1.attach(GIZMO_MOTOR_1);
  motor2.attach(GIZMO_MOTOR_2);
  motor3.attach(GIZMO_MOTOR_3);
  motor4.attach(GIZMO_MOTOR_4);

  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  while (running){
    motor1.write(120);
    motor2.write(120);
    motor3.write(120);
    motor4.write(120);
    myTime = millis();
    if (myTime > 3000){
      running = false;
    }
  }
  
}
