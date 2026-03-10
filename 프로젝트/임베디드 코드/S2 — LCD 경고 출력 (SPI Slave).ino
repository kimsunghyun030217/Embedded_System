/*
 * =====================================================
 *  S2 Arduino - LCD 경고 출력
 *  - SPI Slave: Master로부터 LCD 명령 수신
 *  - LCD 16x2 I2C
 * =====================================================
 *
 * 핀 연결:
 *  SPI SS    → D10
 *  SPI MOSI  → D11
 *  SPI MISO  → D12
 *  SPI SCK   → D13
 *  LCD SDA   → A4
 *  LCD SCL   → A5
 */

#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define CMD_LCD_NORMAL   0x10
#define CMD_LCD_WARNING  0x11

volatile uint8_t receivedCmd = 0;
volatile bool    newCmd      = false;

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  System Ready  ");

  pinMode(MISO, OUTPUT);
  SPCR |= _BV(SPE);
  SPCR &= ~_BV(MSTR);
  SPCR |= _BV(SPIE);
  sei();

  Serial.println("[S2] LCD 슬레이브 시작");
}

void loop() {
  if (newCmd) {
    newCmd = false;
    switch (receivedCmd) {
      case CMD_LCD_NORMAL:  lcdClear();   break;
      case CMD_LCD_WARNING: lcdWarning(); break;
    }
  }
}

ISR(SPI_STC_vect) {
  receivedCmd = SPDR;
  newCmd = true;
}

void lcdClear() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   Monitoring   ");
}

void lcdWarning() {
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("!! WARNING !!");
  lcd.setCursor(2, 1);
  lcd.print("무단횡단 경고!");
}