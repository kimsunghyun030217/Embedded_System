#include <SoftwareSerial.h>

SoftwareSerial soft(4, 5);

void setup() {
  Serial.begin(9600);
  soft.begin(9600);
}

void loop() {
  // 상대가 보낸 문자가 있는지 확인하고, 있다면 나의 시리얼 모니터에 출력
  while (soft.available()) {
    char receivedChar = soft.read();
    Serial.write(receivedChar);
  }

  // 내가 입력한 문자가 있는지 확인하고, 있다면 상대에게 전송 및 나의 시리얼 모니터에 출력
  while (Serial.available()) {
    char sendChar = Serial.read();
    soft.write(sendChar);
    Serial.write(sendChar);
  }
}
