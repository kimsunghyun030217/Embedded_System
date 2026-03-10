#include <SoftwareSerial.h>

SoftwareSerial mySerial(4, 5); // RX, TX

unsigned long l1, l2, l3, l4;
unsigned long interval1 = 300;
unsigned long interval2 = 300;
const int pinLM35 = 2;
const int lightsenser = A1;
int val = 0;
float tem_val = 0;
int lightvalue = 0;

void setup() {
 Serial.begin(9600);
 mySerial.begin(9600);
 l1 = 0;
 l3 = 0;
}

void loop() {
  val = analogRead(pinLM35);
  l2 = millis();
  if (l2 - l1 >= interval1) {
    l1 = l2;
    // 조도센서 측정
    lightvalue = analogRead(lightsenser);
    Serial.print("Light : ");
    Serial.println(lightvalue);
    if (lightvalue < 400 ) {
      mySerial.write(lightvalue);
      delay(100);
    }
  }
  
  l4 = millis();
  if (l4 - l3 >= interval2) {
    l3 = l4;
    // 온도센서 측정
    Serial.print( "Temperature : ");
    tem_val = val * 5 * 100 / 1024.0;
    Serial.println(tem_val);
    mySerial.write(tem_val);
  }
}
