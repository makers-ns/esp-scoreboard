#include <ButtonDebounce.h>

ButtonDebounce button1(D0, 250);
ButtonDebounce button2(D3, 250);
ButtonDebounce button3(2, 250);
void buttonChanged1(int state){
  Serial.println("1 Changed: " + String(state));
}
void buttonChanged2(int state){
  Serial.println("2 Changed: " + String(state));
}
void buttonChanged3(int state){
  Serial.println("3 Changed: " + String(state));
}
void setup() {
  Serial.begin(115200);
  button1.setCallback(buttonChanged1);
  button2.setCallback(buttonChanged2);
  button3.setCallback(buttonChanged3);
}

void loop() {
  //button1.update();
  //button2.update();
  button3.update();
}
