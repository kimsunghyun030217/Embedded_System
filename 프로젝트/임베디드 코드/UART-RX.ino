/*
 * =====================================================
 *  UART-RX Arduino (시나리오 3 - 수신측)
 *  - UART: TX Arduino로부터 데이터 수신
 *  - SG-90 서보: 햇빛가리개 제어
 *  - LED: 가로등 제어
 *  - LCD I2C: 온습도 실시간 출력
 * =====================================================
 *
 * 핀 연결:
 *  RX          → D0  (TX Arduino TX에 연결)
 *  서보 PWM    → D9
 *  가로등 LED  → D5
 *  LCD SDA     → A4
 *  LCD SCL     → A5
 *
 * 조도 기준: 400 이상 → 햇빛가리개 ON / 400 미만 → 가로등 ON
 *
 * ※ 라이브러리: LiquidCrystal_I2C, Servo (기본 내장)
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define SERVO_PIN        9
#define LED_PIN          5
#define LIGHT_THRESHOLD  400
#define SERVO_OPEN       90
#define SERVO_CLOSE      0
#define LCD_UPDATE_MS    2000

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo sunShade;

String rxBuffer = "";
unsigned long lastLcdUpdate = 0;

int  lastLight = -1, lastTemperature = -1, lastHumidity = -1;
bool shadeOpen = false, ledOn = false;

void setup() {
  Serial.begin(9600);

  sunShade.attach(SERVO_PIN);
  sunShade.write(SERVO_CLOSE);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Waiting data...");
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      parseData(rxBuffer);
      rxBuffer = "";
    } else {
      rxBuffer += c;
    }
  }

  unsigned long now = millis();
  if (now - lastLcdUpdate >= LCD_UPDATE_MS && lastTemperature != -1) {
    lastLcdUpdate = now;
    updateLCD();
  }
}

void parseData(String data) {
  if (data.length() == 0) return;
  if (data.indexOf("L:-1") >= 0) return;  // 오류 패킷 무시

  int lIdx = data.indexOf("L:");
  int tIdx = data.indexOf(",T:");
  int hIdx = data.indexOf(",H:");
  if (lIdx < 0 || tIdx < 0 || hIdx < 0) return;

  lastLight       = data.substring(lIdx + 2, tIdx).toInt();
  lastTemperature = data.substring(tIdx + 3, hIdx).toInt();
  lastHumidity    = data.substring(hIdx + 3).toInt();

  controlDevices(lastLight);
}

void controlDevices(int lightVal) {
  if (lightVal >= LIGHT_THRESHOLD) {
    // 밝음: 햇빛가리개 펼침, 가로등 OFF
    if (!shadeOpen) { sunShade.write(SERVO_OPEN);  shadeOpen = true; }
    if (ledOn)      { digitalWrite(LED_PIN, LOW);  ledOn = false; }
  } else {
    // 어두움: 햇빛가리개 접음, 가로등 ON
    if (shadeOpen)  { sunShade.write(SERVO_CLOSE); shadeOpen = false; }
    if (!ledOn)     { digitalWrite(LED_PIN, HIGH); ledOn = true; }
  }
}

void updateLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp:  ");
  lcd.print(lastTemperature);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Humid: ");
  lcd.print(lastHumidity);
  lcd.print(" %");
}