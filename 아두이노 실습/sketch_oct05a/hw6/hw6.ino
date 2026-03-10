const int pinBuzzer = 2;
int state = 0;
const int pinButtonk0 = 3;
const int pinButtonk1 = 4;
const int pinButtonk2 = 5;
const int pinButtonk3 = 6;
const int pinButtonk4 = 7;
const int pinButtonk5 = 8;
const int pinButtonk6 = 9;
const int pinButtonk7 = 10;
void setup() { 
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinButtonk0,INPUT);
  pinMode(pinButtonk1,INPUT);
  pinMode(pinButtonk2,INPUT);
  pinMode(pinButtonk3,INPUT);
  pinMode(pinButtonk4,INPUT);
  pinMode(pinButtonk5,INPUT);
  pinMode(pinButtonk6,INPUT);
  pinMode(pinButtonk7,INPUT);
}

void loop() {
   if (digitalRead(pinButtonk0)==HIGH) {
      tone(pinBuzzer, 262); delay(100); 
    } else if (digitalRead(pinButtonk1)==HIGH) {
      tone(pinBuzzer, 294); delay(100); 
    }
    else if (digitalRead(pinButtonk2)==HIGH) {
      tone(pinBuzzer, 330); delay(100); 
    }
    else if (digitalRead(pinButtonk3)==HIGH) {
      tone(pinBuzzer, 349); delay(100); 
    }
    else if (digitalRead(pinButtonk4)==HIGH) {
      tone(pinBuzzer, 392); delay(100); 
    }
    else if (digitalRead(pinButtonk5)==HIGH) {
      tone(pinBuzzer, 440); delay(100); 
    }
    else if (digitalRead(pinButtonk6)==HIGH) {
      tone(pinBuzzer, 494); delay(100); 
    }
  else if (digitalRead(pinButtonk7)==HIGH) {
      tone(pinBuzzer, 523); delay(100); 
    }
    else
    noTone(pinBuzzer);
}
