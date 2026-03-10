const int pinLED = 13;
volatile byte state = LOW;
 
void setup() {
 TIMSK2 = (TIMSK2 & B11111110) | 0x01;
 TCCR2B = (TCCR2B & B11111000) | 0x07;
 pinMode(pinLED, OUTPUT);
}
void loop() {
 digitalWrite(pinLED, state);
}
ISR(TIMER2_OVF_vect){
 state = !state;
}
