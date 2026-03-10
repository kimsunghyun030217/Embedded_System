volatile byte command = 0;
volatile byte data = 0;
const int pinLM35 = 1;
byte val = 0;

void setup () {
  Serial.begin(9600);
 pinMode(MISO, OUTPUT);
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
    data = val * 5 * 100 / 1024.0;
    SPDR = data;
    break;
 }
}

void loop() { 
 val = analogRead(pinLM35);
 if (digitalRead(SS) == HIGH)
 command = 0;
}
