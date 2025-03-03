#include <Servo.h>

int c = 1;
int sp = 0;
int lastButtonState1 = HIGH;
int lastButtonState2 = HIGH;
bool buttonReleased1 = false;
bool buttonReleased2 = false;
Servo myservo;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(A0, INPUT);
  myservo.attach(3);
}

void loop() {
  int buttonState1 = digitalRead(2);

  if (buttonState1 == LOW && lastButtonState1 == HIGH) {
    buttonReleased1 = false;  
  }

  if (buttonState1 == HIGH && lastButtonState1 == LOW && !buttonReleased1) {
    c++;
    buttonReleased1 = true;  
    delay(200);
  }

  int buttonState2 = digitalRead(4);

  if (buttonState2 == LOW && lastButtonState2 == HIGH) {  
    buttonReleased2 = false;
  }

  if (buttonState2 == HIGH && lastButtonState2 == LOW && !buttonReleased2) {
    c--;
    buttonReleased2 = true;
    delay(200);
  }

  if (c < 1) c = 3;
  if (c > 3) c = 1;

  digitalWrite(13, (c == 1) ? HIGH : LOW);
  digitalWrite(12, (c == 2) ? HIGH : LOW);
  digitalWrite(11, (c == 3) ? HIGH : LOW);

  lastButtonState1 = buttonState1;
  lastButtonState2 = buttonState2;

  //sp = map(c, 1, 3, 0, 180); Управление на сервото с бутони
  sp = map(analogRead(A0), 0, 1023, 0, 180);
  myservo.write(sp);

  delay(100);
}
