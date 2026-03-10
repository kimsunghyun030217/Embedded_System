const int pinPIRM = 2;
int val = 0;
void setup() {
pinMode(pinPIRM, INPUT);
Serial.begin(9600);
}
void loop() {
val = digitalRead(pinPIRM);
Serial.println(val);
delay(100);
}
