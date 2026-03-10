 const int led_red_pwm = 11;
 const int led_yellow_pwm = 10;
 const int led_green_pwm = 9;
 int fdir = 0; //꺼진지 안꺼진지 상태
 int fade = 0; //밝기
 int flag = 0; //다음걸로 넘어가는거
 int currentLED = 0; //뒤로 돌아가는거
 unsigned long l1,l2;


void setup() {
  // put your setup code here, to run once:
  l1=0;
}

void loop() {
  // put your main code here, to run repeatedly:
  l2 = millis();
 if (currentLED == 0) { // 빨간색 LED 페이딩
    if (l2 - l1 >= 40) {
      l1 = l2;
      if (!fdir) {
        fade += 5;
        if (fade >= 255) {
          fade = 255;
          fdir = 1;
        }
      } else {
        fade -= 5;
        if (fade <= 0) {
          fade = 0;
          fdir = 0;
          currentLED = 1; // 초록색 LED로 이동
          flag = 0;
        }
      }
      analogWrite(led_red_pwm, fade);
    }
  }
  if (currentLED == 1) { // 초록색 LED 페이딩
    if (l2 - l1 >= 40) {
      l1 = l2;
      if (!fdir) {
        fade += 5;
        if (fade >= 255) {
          fade = 255;
          fdir = 1;
        }
      } else {
        fade -= 5;
        if (fade <= 0) {
          fade = 0;
          fdir = 0;
          if(flag == 0)
          currentLED = 2; // 노란색 LED로 이동
          else
            currentLED = 0; //빨간색 LED로 이동
        }
      }
      analogWrite(led_yellow_pwm, fade);
    }
  } 
  if (currentLED == 2) {
    if (l2 - l1 >= 40) {
      l1 = l2;
      if (!fdir) {
        fade += 5;
        if (fade >= 255) {
          fade = 255;
          fdir = 1;
        }
      } else {
        fade -= 5;
        if (fade <= 0) {
          fade = 0;
          fdir = 0;
          flag = 1;
          currentLED = 1; // 빨간색 LED로 이동 (반복)
        }
      }
      analogWrite(led_green_pwm, fade);
    }
  }

} 
