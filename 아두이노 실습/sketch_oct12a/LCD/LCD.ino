#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
int ledPin = 8;  // LED가 연결된 핀
int sensorPin = A0;  // 온도 센서가 연결된 아날로그 핀
float set = 29.0, cur;
byte degree[8]={
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
  B00000,
};

byte fan_off[8]={
  B00100,
  B00100,
  B00100,
  B11111,
  B00100,
  B00100,
  B00100,
  B00000,
};

byte fan_on[8]={
  B00100,
  B10101,
  B01110,
  B11111,
  B01110,
  B10101,
  B00100,
  B00000,
};

void setup() {
  lcd.begin(16, 2);
  lcd.createChar(0, degree);
  lcd.createChar(1, fan_off);
  lcd.createChar(2, fan_on);
  lcd.setCursor(0, 0); lcd.print("Set:");
  lcd.setCursor(10, 0); lcd.write((byte)0);
  lcd.setCursor(11, 0); lcd.print("C");
  lcd.setCursor(0, 1); lcd.print("Cur:");
  lcd.setCursor(10, 1); lcd.write((byte)0);
  lcd.setCursor(11, 1); lcd.print("C");

  pinMode(ledPin, OUTPUT); // LED 핀을 출력 모드로 설정
}

void loop() {
  cur = analogRead(sensorPin) * 0.48828125; // 아날로그 값을 온도로 변환
  lcd.setCursor(6, 0); lcd.print(set, 1);
  lcd.setCursor(6, 1); lcd.print(cur, 1);
  lcd.setCursor(15,1);

  if (cur > set) {
    lcd.write(2);
    digitalWrite(ledPin, HIGH); // LED 켜기
  }
  else {
    lcd.write(1);
    digitalWrite(ledPin, LOW); // LED 끄기
  }

  delay(500);
}
