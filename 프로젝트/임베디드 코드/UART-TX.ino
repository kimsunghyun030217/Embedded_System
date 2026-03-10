/*
 * =====================================================
 *  UART-TX Arduino (시나리오 3 - 송신측)
 *  - DHT11: 온습도 측정
 *  - DFR0026: 조도 측정
 *  - UART: 측정값 전송 "L:{조도},T:{온도},H:{습도}"
 * =====================================================
 *
 * 핀 연결:
 *  DHT11 DATA  → D4
 *  조도센서 AO → A0
 *  TX          → D1  (RX Arduino RX에 연결)
 *
 * ※ 라이브러리: DHT sensor library (Adafruit)
 */

#include <DHT.h>

#define DHT_PIN      4
#define DHT_TYPE     DHT11
#define LIGHT_PIN    A0
#define SEND_INTERVAL_MS  1000

DHT dht(DHT_PIN, DHT_TYPE);
unsigned long lastSend = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  delay(2000);  // 센서 안정화
}

void loop() {
  unsigned long now = millis();
  if (now - lastSend >= SEND_INTERVAL_MS) {
    lastSend = now;

    int lightVal      = analogRead(LIGHT_PIN);
    float humidity    = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("L:-1,T:-1,H:-1");
      return;
    }

    Serial.print("L:");
    Serial.print(lightVal);
    Serial.print(",T:");
    Serial.print((int)temperature);
    Serial.print(",H:");
    Serial.println((int)humidity);
  }
}