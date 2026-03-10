#include <SPI.h>

void setup() {
  SPI.begin();
  pinMode(SS, OUTPUT);
  digitalWrite(SS, HIGH); 
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  }

  
void loop() {
  digitalWrite(SS, LOW);
  const char *p = "Hello, Slave!\n";
  for (int i = 0; i < strlen(p); i++) { 
    SPI.transfer(p[i]); 
    }
    
    digitalWrite(SS, HIGH);
    delay(1000);
    }
