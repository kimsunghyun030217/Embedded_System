/*
 * =====================================================
 *  Master Arduino
 *  - 초음파 센서(HC-SR04P): 차량 감지 (시나리오 1)
 *  - PIR 센서(HC-SR501):    무단횡단 감지 (시나리오 2)
 *  - SPI Master:            S1(신호등), S2(LCD) 제어
 * =====================================================
 *
 * 핀 연결:
 *  초음파 TRIG  → D6
 *  초음파 ECHO  → D7
 *  PIR OUT      → D2 (인터럽트 핀)
 *  SPI SS_S1    → D10 (S1 신호등 슬레이브 선택)
 *  SPI SS_S2    → D9  (S2 LCD 슬레이브 선택)
 *  SPI MOSI     → D11
 *  SPI MISO     → D12
 *  SPI SCK      → D13
 */

#include <SPI.h>

#define TRIG_PIN     6
#define ECHO_PIN     7
#define PIR_PIN      2

#define SS_S1        10
#define SS_S2        9

#define CMD_GREEN_STRAIGHT   0x01
#define CMD_GREEN_LEFT       0x02
#define CMD_RED_BLINK        0x03
#define CMD_PEDESTRIAN_GREEN 0x04
#define CMD_LCD_NORMAL       0x10
#define CMD_LCD_WARNING      0x11

#define VEHICLE_DETECT_CM    30
#define BLINK_DURATION_MS    5000
#define LEFT_SIGNAL_MS       5000

volatile bool pirDetected = false;

void pirISR();
long measureDistance();
void sendSPI(uint8_t ssPin, uint8_t command);
void scenario1_vehicleDetected();
void scenario2_pedestrianDetected();
void normalMode();

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(PIR_PIN), pirISR, RISING);

  pinMode(SS_S1, OUTPUT);
  pinMode(SS_S2, OUTPUT);
  digitalWrite(SS_S1, HIGH);
  digitalWrite(SS_S2, HIGH);

  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV16);

  normalMode();
  Serial.println("[Master] 시스템 시작 - 주도로 녹색 직진 신호");
}

void loop() {
  if (pirDetected) {
    pirDetected = false;
    Serial.println("[Master] PIR 감지! 시나리오 2 실행");
    scenario2_pedestrianDetected();
    normalMode();
    return;
  }

  long dist = measureDistance();
  Serial.print("[Master] 초음파 거리: ");
  Serial.print(dist);
  Serial.println(" cm");

  if (dist > 0 && dist < VEHICLE_DETECT_CM) {
    Serial.println("[Master] 차량 감지! 시나리오 1 실행");
    scenario1_vehicleDetected();
    normalMode();
  }

  delay(200);
}

void scenario1_vehicleDetected() {
  sendSPI(SS_S1, CMD_GREEN_LEFT);
  sendSPI(SS_S1, CMD_PEDESTRIAN_GREEN);
  delay(LEFT_SIGNAL_MS);
}

void scenario2_pedestrianDetected() {
  sendSPI(SS_S1, CMD_RED_BLINK);
  sendSPI(SS_S2, CMD_LCD_WARNING);
  delay(BLINK_DURATION_MS);
  sendSPI(SS_S2, CMD_LCD_NORMAL);
}

void normalMode() {
  sendSPI(SS_S1, CMD_GREEN_STRAIGHT);
  sendSPI(SS_S2, CMD_LCD_NORMAL);
  Serial.println("[Master] 정상 상태 복귀");
}

void sendSPI(uint8_t ssPin, uint8_t command) {
  digitalWrite(ssPin, LOW);
  delayMicroseconds(10);
  SPI.transfer(command);
  delayMicroseconds(10);
  digitalWrite(ssPin, HIGH);
  delay(10);
}

long measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) return -1;
  return duration * 0.034 / 2;
}

void pirISR() {
  pirDetected = true;
}