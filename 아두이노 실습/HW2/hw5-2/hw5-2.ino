const int red = 8;
const int green = 9;
const int blue = 10;
const int pinTrig= 2; 
const int pinEcho= 4;
long T, L;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
}
 void loop() {
  digitalWrite(pinTrig, LOW); delayMicroseconds(2);
  digitalWrite(pinTrig, HIGH); delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  
  T = pulseIn(pinEcho, HIGH);
  L = T/58.82;
  
  if(L >= 0 && L <= 10){
  digitalWrite(red, HIGH);
  digitalWrite(green, LOW);
  digitalWrite(blue, LOW);}
  else if(L > 10 && L <= 15){
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
  digitalWrite(blue, LOW);}
  else if(L > 15 && L <= 30) {
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(blue, HIGH);}
  else {
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(blue, LOW);
  }  
  delay(100); 
}
