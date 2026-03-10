const int LED = 7;
volatile byte command = 0;
volatile byte data = 0;

void setup() {
  pinMode(MISO, OUTPUT);
  pinMode(SS, INPUT);
  pinMode(LED, OUTPUT);
  SPCR |= _BV(SPE);
  SPCR &= ~_BV(MSTR);
  SPCR |= _BV(SPIE);
}

ISR(SPI_STC_vect) {
  byte c = SPDR;
  switch (command) {
    case 0:
      command = c;
      SPDR = 0;
      break;
    case 's':
      SPDR = data;
      break;
  }
}

void loop() {
  if (digitalRead(SS) == LOW) {
    if (command == 's') {
      int temperature = data;

      // 특정 온도 이상이면 LED를 켬
      if (temperature > 30) {
        digitalWrite(LED, HIGH);
      } else {
        digitalWrite(LED, LOW);
      }
    }
    command = 0;
  }
  delay(1000); // 원하는 주기로 반복
}
