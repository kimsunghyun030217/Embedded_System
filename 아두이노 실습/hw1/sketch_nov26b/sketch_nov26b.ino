#include <SoftwareSerial.h>

SoftwareSerial mySerial(4, 5);  // RX, TX

const int pinLM35 = 2; // LM35 센서 연결 핀
const int lightSensor = A1; // 조도 센서 연결 핀
int val = 0;
float temperature = 0;
int lightValue = 0;

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // LM35 온도 센서 값 읽기
  val = analogRead(pinLM35);
  temperature = val * 5 * 100 / 1024.0;
  
  // 조도 센서 값 읽기
  lightValue = analogRead(lightSensor);

  // 값을 시리얼로 전송
  mySerial.print("T:");
  mySerial.print(temperature);
  mySerial.print(",L:");
  mySerial.println(lightValue);

  delay(500);  // 1초 딜레이
}
