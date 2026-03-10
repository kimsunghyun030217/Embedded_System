const int led_RED=13;
const int led_YELLOW=13;
const int ledGREEN=13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
pinMode(led_RED,OUTPUT);
pinMode(led_YELLOW,OUTPUT);
pinMode(led_GREEN,OUTPUT);
}

void loop(){
  digitalWrite(led_RED,HIGH);
  delay(1000);
  digitalWrite(led_RED,LOW);
  
  digitalWrite(led_YELLOW,HIGH);
  delay(1000);
  digitalWrite(led_YELLOW,LOW);
  
  digitalWrite(led_GREEN,HIGH);
  delay(1000);
  digitalWrite(led_GREEN,LOW);
  }
