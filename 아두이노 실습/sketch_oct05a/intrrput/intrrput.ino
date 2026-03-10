const byte pinLED = 13;
const byte pinINT = 2;
volatile byte state = LOW;

void setup() {
  // put your setup code here, to run once:
  pinMode(pinLED, OUTPUT);

  pinMode(pinINT, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pinINT), blink,CHANGE);
}

void loop() {
  // put you main code here, to run repeatedly:
  digitalWrite(pinLED, state);

}
void blink() { state =!state;}
