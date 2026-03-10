const byte pinLED = 13;
const byte pinINT = 7;
volatile byte state = LOW;
void setup() {
 PCICR |= _BV(2);
 PCMSK2 |= _BV(7);
 pinMode(pinINT, INPUT_PULLUP);
 pinMode(pinLED, OUTPUT);
}
void loop() {
 digitalWrite(pinLED, state);
}
ISR(PCINT2_vect) {
 state = !state;
}
