const int redPin = 9;    // RED LED 연결 핀
const int greenPin = 10; // GREEN LED 연결 핀
const int bluePin = 11;  // BLUE LED 연결 핀

char serialInput; // 시리얼 입력을 저장할 변수

void setup() {
  Serial.begin(9600);

  // LED 핀을 출력으로 설정
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // LED 초기 상태: 꺼짐
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}

void loop() {
  if (Serial.available() > 0) {
    serialInput = Serial.read(); // 시리얼 입력 읽기

    // 키에 따라 RGB LED 제어
    switch (serialInput) {
      case 'r':
        toggleLED(redPin);
        break;
      case 'g':
        toggleLED(greenPin);
        break;
      case 'b':
        toggleLED(bluePin);
        break;
    }
  }
}

void toggleLED(int pin) {
  // 현재 LED 상태 읽기
  int currentState = digitalRead(pin);

  // LED 상태 변경
  if (currentState == HIGH) {
    digitalWrite(pin, LOW); // 켜져 있으면 끄기
  } else {
    digitalWrite(pin, HIGH); // 꺼져 있으면 켜기
  }
}
