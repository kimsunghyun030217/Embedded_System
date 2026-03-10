#include <Wire.h>
#define sv2 9
byte i = 0;
void setup() {
 Wire.begin(sv2);
 Wire.onReceive(receiveEvent);
 Serial.begin(9600);
}
void loop() {
 delay(100);
}
void receiveEvent(int howMany) {
 while (Wire.available() > 2) {
 char c = Wire.read();
 Serial.print(c);
 }
 int x = Wire.read();
 Serial.print(x);
 char c = Wire.read();
 Serial.print(c);
}
