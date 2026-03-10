const int pinTilt = 17;
const int LEDR = 8;
const int LEDG = 9;
const int LEDB = 10;

int val = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LEDR,OUTPUT);
  pinMode(LEDG,OUTPUT);
  pinMode(LEDB,OUTPUT);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:

  val = digitalRead(pinTilt);

  if(val==1){
    digitalWrite(LEDR,HIGH);
    digitalWrite(LEDG,HIGH);
    digitalWrite(LEDB,HIGH);
  }

  else
  digitalWrite(LEDR,LOW);
  digitalWrite(LEDG,LOW);
  digitalWrite(LEDB,LOW);
}
