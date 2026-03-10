/*
 * =====================================================
 *  S1 Arduino - 신호등 LED 제어
 *  - SPI Slave: Master로부터 신호 명령 수신
 * =====================================================
 *
 * 핀 연결:
 *  SPI SS      → D10
 *  SPI MOSI    → D11
 *  SPI MISO    → D12
 *  SPI SCK     → D13
 *  RED LED     → D3
 *  YELLOW LED  → D4
 *  GREEN LED   → D5  (직진)
 *  LEFT LED    → D6  (좌회전)
 *  PEDESTRIAN  → D7  (횡단보도 녹색)
 */

#include <SPI.h>

#define LED_RED          3
#define LED_YELLOW       4
#define LED_GREEN        5
#define LED_LEFT         6
#define LED_PEDESTRIAN   7

#define CMD_GREEN_STRAIGHT   0x01
#define CMD_GREEN_LEFT       0x02
#define CMD_RED_BLINK        0x03
#define CMD_PEDESTRIAN_GREEN 0x04

volatile uint8_t receivedCmd = 0;
volatile bool    newCmd      = false;

bool blinkState   = false;
unsigned long lastBlink = 0;
#define BLINK_INTERVAL 500

void setup() {
  Serial.begin(9600);

  pinMode(LED_RED,        OUTPUT);
  pinMode(LED_YELLOW,     OUTPUT);
  pinMode(LED_GREEN,      OUTPUT);
  pinMode(LED_LEFT,       OUTPUT);
  pinMode(LED_PEDESTRIAN, OUTPUT);

  pinMode(MISO, OUTPUT);
  SPCR |= _BV(SPE);
  SPCR &= ~_BV(MSTR);
  SPCR |= _BV(SPIE);
  sei();

  setGreenStraight();
  Serial.println("[S1] 신호등 슬레이브 시작");
}

void loop() {
  if (newCmd) {
    newCmd = false;
    switch (receivedCmd) {
      case CMD_GREEN_STRAIGHT:   setGreenStraight();   break;
      case CMD_GREEN_LEFT:       setGreenLeft();        break;
      case CMD_RED_BLINK:        allOff();              break;
      case CMD_PEDESTRIAN_GREEN: setPedestrianGreen();  break;
    }
  }

  // 적색 점멸 처리
  if (receivedCmd == CMD_RED_BLINK) {
    unsigned long now = millis();
    if (now - lastBlink >= BLINK_INTERVAL) {
      lastBlink = now;
      blinkState = !blinkState;
      digitalWrite(LED_RED, blinkState ? HIGH : LOW);
    }
  }
}

ISR(SPI_STC_vect) {
  receivedCmd = SPDR;
  newCmd = true;
}

void allOff() {
  digitalWrite(LED_RED,        LOW);
  digitalWrite(LED_YELLOW,     LOW);
  digitalWrite(LED_GREEN,      LOW);
  digitalWrite(LED_LEFT,       LOW);
  digitalWrite(LED_PEDESTRIAN, LOW);
}

void setGreenStraight() {
  allOff();
  digitalWrite(LED_GREEN, HIGH);
}

void setGreenLeft() {
  allOff();
  digitalWrite(LED_LEFT, HIGH);
}

void setPedestrianGreen() {
  allOff();
  digitalWrite(LED_PEDESTRIAN, HIGH);
}