double Fahrenheit(double celsius) 
{
        return 1.8 * celsius + 32;
}   

double Kelvin(double celsius)
{
        return celsius + 273.15;
}    

double dewPoint(double celsius, double humidity)
{
        double A0= 373.15/(273.15 + celsius);
        double SUM = -7.90298 * (A0-1);
        SUM += 5.02808 * log10(A0);
        SUM += -1.3816e-7 * (pow(10, (11.344*(1-1/A0)))-1) ;
        SUM += 8.1328e-3 * (pow(10,(-3.49149*(A0-1)))-1) ;
        SUM += log10(1013.246);
        double VP = pow(10, SUM-3) * humidity;
        double T = log(VP/0.61078);   // temp var
        return (241.88 * T) / (17.558-T);
}

double dewPointFast(double celsius, double humidity)
{
        double a = 17.271;
        double b = 237.7;
        double temp = (a * celsius) / (b + celsius) + log(humidity/100);
        double Td = (b * temp) / (a - temp);
        return Td;
}

#include <dht11.h>
#include <SoftwareSerial.h>

#define DHT11PIN 2
dht11 DHT11;

SoftwareSerial mySerial(4, 5);  // RX, TX

const int lightSensor = A0; // 조도 센서 연결 핀
int lightValue = 0;

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  int chk = DHT11.read(DHT11PIN);
  
  Serial.print("Read sensor: ");
  switch (chk)
  {
    case DHTLIB_OK: 
                Serial.println("OK"); 
                break;
    case DHTLIB_ERROR_CHECKSUM: 
                Serial.println("Checksum error"); 
                break;
    case DHTLIB_ERROR_TIMEOUT: 
                Serial.println("Time out error"); 
                break;
    default: 
                Serial.println("Unknown error"); 
                break;
  }

  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);

  Serial.print("Temperature (oC): ");
  Serial.println((float)DHT11.temperature, 2);

  mySerial.print("T:");
  mySerial.print((float)DHT11.temperature);
  
  mySerial.print(",H:");
  mySerial.print((float)DHT11.humidity);
  
  
  // 조도 센서 값 읽기
  lightValue = analogRead(lightSensor);
  Serial.println(lightValue);
  mySerial.print(",L:");
  mySerial.println(lightValue);

  delay(1000);
}
