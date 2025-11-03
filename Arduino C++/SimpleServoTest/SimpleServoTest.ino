#include <Gizmo.h>
#include <Servo.h>


Gizmo gizmo;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

void setup() {
  // put your setup code here, to run once:
  gizmo.begin();
  servo1.attach(GIZMO_SERVO_1);
  servo2.attach(GIZMO_SERVO_2);
  servo3.attach(GIZMO_SERVO_3);
  servo4.attach(GIZMO_SERVO_4);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

  gizmo.refresh();

  if (gizmo.getButton(GIZMO_BUTTON_A)){
    fullServoWrite(90);
  }

  if (gizmo.getButton(GIZMO_BUTTON_X)){
    fullServoWrite(180);
  }

  if (gizmo.getButton(GIZMO_BUTTON_Y)){
    fullServoWrite(0);
  }

}

void fullServoWrite(int angle){
  servo1.write(angle);
  servo2.write(angle);
  servo3.write(angle);
  servo4.write(angle);
}
