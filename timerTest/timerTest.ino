#include <AsyncTimer.h>
#include <Gizmo.h>

Gizmo gizmo;

AsyncTimer t;

bool timerCounting = false;
void setup() {

  // put your setup code here, to run once:
  gizmo.begin();
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  t.handle();
  gizmo.refresh();
  if (gizmo.getButton(GIZMO_BUTTON_RT) && !timerCounting){
    pressButton();
  }

  if (timerCounting){
    Serial.println("time count");
  }
}

void pressButton(){
  timerCounting = true;
  t.setTimeout(timeout, 5000);
}

void timeout(){
  timerCounting = false;
  Serial.println("time stop");
}