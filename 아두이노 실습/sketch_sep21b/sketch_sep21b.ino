const int led_pwm =13;
unsigned long l3,l4;
unsigned long interval2 = 30;
int fDir=0;
int fade=0;
void setup() {
  // put your setup code here, to run once:

  l3=0;
}

void loop() {
  // put your main code here, to run repeatedly:
  l4=millis();

  if(l4-l3 >= interval2){
    l3=l4;

    if(!fDir){
      fade+=5;
      if(fade>=255){
        fade=255; fDir=1; }
    }else{
      fade-=5;
      if(fade<=0){
        fade=0; fDir=0;}
      }
      analogWrite(led_pwm, fade);
  }

}
