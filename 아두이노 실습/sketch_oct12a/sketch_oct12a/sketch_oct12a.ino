const int pinLM35 = 1;
const int RGBLEDR = 8;
const int RGBLEDG = 9;
const int RGBLEDB = 10;

int val = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(RGBLEDR, OUTPUT);
  pinMode(RGBLEDG, OUTPUT);
  pinMode(RGBLEDB, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(pinLM35);
  
  if((val*5*100/1024.0)>25){
    digitalWrite(RGBLEDR, HIGH);
    digitalWrite(RGBLEDG, LOW);
    digitalWrite(RGBLEDB, LOW);
  }
  else
     digitalWrite(RGBLEDB, HIGH);


}
