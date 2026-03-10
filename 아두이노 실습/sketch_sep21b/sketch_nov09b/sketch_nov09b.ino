#include <SoftwareSerial.h>

SoftwareSerial mySerial(4,5);
byte c;
void setup(){
  mySerial.begin(9600);
  Serial.begin(9600);
}

void loop(){
  if(mySerial.available()){
    c=mySerial.read();
 
    Serial.write(c);
    
  }
}
