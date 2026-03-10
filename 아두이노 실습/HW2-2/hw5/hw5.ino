const int pinVibM= 3;
const int red = 8;
const int green = 9;
const int blue = 10;
byte count = 0;
void setup() {
  pinMode(pinVibM, INPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  attachInterrupt(1, countVib, FALLING);
}
void loop() {
  if(count != 0) {
    digitalWrite(red, HIGH);
    digitalWrite(green, HIGH);
    digitalWrite(blue, HIGH);
    delay(100);
    count = 0;
  } else{
    digitalWrite(red, LOW);
    digitalWrite(green, LOW);
    digitalWrite(blue, LOW);
    delay(100);
  }
}
void countVib() {
  count++;
}
