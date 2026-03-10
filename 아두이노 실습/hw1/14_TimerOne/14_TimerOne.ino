#include <TimerOne.h>

void setup() {
 Serial.begin(115200);
 Timer1.initialize(1000);
 Timer1.attachInterrupt(timerISR);
}
void loop() {
 noInterrupts();
 Serial.print("(");
 Serial.println(")");
 interrupts();
 delay(10);
}
void timerISR() {
 Serial.println(" ]");
}
