const int pinLED =13;
const int pinButton =2;


void setup() {
  // put your setup code here, to run once:
  pinMode(pinLED, OUTPUT);
  pinMode(pinButton, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  if(digitalRead(pinButton) ==HIGH)
    digitalWrite(pinLED, HIGH);
  else
    digitalWrite(pinLED, LOW);

}
