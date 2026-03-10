const int pinLEDR = 8;
const int pinLEDG = 9;
const int pinLEDB = 10;
const int pinLEDR2 = 11; // 추가된 두 번째 RGB LED 핀
const int pinLEDG2 = 12; // 추가된 두 번째 RGB LED 핀
const int pinLEDB2 = 13; // 추가된 두 번째 RGB LED 핀

const int pinButtonRed = 2;
const int pinButtonGreen = 3;
const int pinButtonBlue = 4;
const int pinButtonRed2 = 5; // 추가된 두 번째 버튼 핀
const int pinButtonGreen2 = 6; // 추가된 두 번째 버튼 핀
const int pinButtonBlue2 = 7; // 추가된 두 번째 버튼 핀

boolean lastButtonRed = LOW;
boolean currentButtonRed = LOW;
boolean lastButtonGreen = LOW;
boolean currentButtonGreen = LOW;
boolean lastButtonBlue = LOW;
boolean currentButtonBlue = LOW;

boolean lastButtonRed2 = LOW;
boolean currentButtonRed2 = LOW;
boolean lastButtonGreen2 = LOW;
boolean currentButtonGreen2 = LOW;
boolean lastButtonBlue2 = LOW;
boolean currentButtonBlue2 = LOW;

boolean redLEDState = LOW;
boolean greenLEDState = LOW;
boolean blueLEDState = LOW;

boolean redLEDState2 = LOW;
boolean greenLEDState2 = LOW;
boolean blueLEDState2 = LOW;

void setup() {
  pinMode(pinLEDR, OUTPUT);
  pinMode(pinLEDG, OUTPUT);
  pinMode(pinLEDB, OUTPUT);
  pinMode(pinLEDR2, OUTPUT); // 추가된 두 번째 RGB LED 핀 설정
  pinMode(pinLEDG2, OUTPUT); // 추가된 두 번째 RGB LED 핀 설정
  pinMode(pinLEDB2, OUTPUT); // 추가된 두 번째 RGB LED 핀 설정
  pinMode(pinButtonRed, INPUT);
  pinMode(pinButtonGreen, INPUT);
  pinMode(pinButtonBlue, INPUT);
  pinMode(pinButtonRed2, INPUT); // 추가된 두 번째 버튼 핀 설정
  pinMode(pinButtonGreen2, INPUT); // 추가된 두 번째 버튼 핀 설정
  pinMode(pinButtonBlue2, INPUT); // 추가된 두 번째 버튼 핀 설정
}

boolean debounce(boolean last, int buttonPin) {
  boolean current = digitalRead(buttonPin);
  if (current != last) {
    delay(5);
    current = digitalRead(buttonPin);
  }
  return current;
}

void loop() {
  currentButtonRed = debounce(lastButtonRed, pinButtonRed);
  currentButtonGreen = debounce(lastButtonGreen, pinButtonGreen);
  currentButtonBlue = debounce(lastButtonBlue, pinButtonBlue);

  currentButtonRed2 = debounce(lastButtonRed2, pinButtonRed2);
  currentButtonGreen2 = debounce(lastButtonGreen2, pinButtonGreen2);
  currentButtonBlue2 = debounce(lastButtonBlue2, pinButtonBlue2);

  if (currentButtonRed == HIGH && lastButtonRed == LOW) {
    redLEDState = !redLEDState;
    digitalWrite(pinLEDR, redLEDState);
  }
  if (currentButtonGreen == HIGH && lastButtonGreen == LOW) {
    greenLEDState = !greenLEDState;
    digitalWrite(pinLEDG, greenLEDState);
  }
  if (currentButtonBlue == HIGH && lastButtonBlue == LOW) {
    blueLEDState = !blueLEDState;
    digitalWrite(pinLEDB, blueLEDState);
  }

  if (currentButtonRed2 == HIGH && lastButtonRed2 == LOW) {
    redLEDState2 = !redLEDState2;
    digitalWrite(pinLEDR2, redLEDState2);
  }
  if (currentButtonGreen2 == HIGH && lastButtonGreen2 == LOW) {
    greenLEDState2 = !greenLEDState2;
    digitalWrite(pinLEDG2, greenLEDState2);
  }
  if (currentButtonBlue2 == HIGH && lastButtonBlue2 == LOW) {
    blueLEDState2 = !blueLEDState2;
    digitalWrite(pinLEDB2, blueLEDState2);
  }

  lastButtonRed = currentButtonRed;
  lastButtonGreen = currentButtonGreen;
  lastButtonBlue = currentButtonBlue;
  lastButtonRed2 = currentButtonRed2;
  lastButtonGreen2 = currentButtonGreen2;
  lastButtonBlue2 = currentButtonBlue2;
}
