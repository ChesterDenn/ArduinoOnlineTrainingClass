

#include<SoftwareSerial.h>
#include <dht.h>

#define DHT22_PIN 8
#define ldr A0
#define lm35 A1
#define mq7aout A2
#define mq7dout 7
#define led1 2
#define led2 3
#define led3 4
#define led4 5
#define led5 6

dht DHT;
SoftwareSerial BlueTooth(11, 12);       //TXD11  RXD12

struct
{
  uint32_t total;
  uint32_t ok;
  uint32_t crc_error;
  uint32_t time_out;
  uint32_t connect;
  uint32_t ack_l;
  uint32_t ack_h;
  uint32_t unknown;
} stat = { 0, 0, 0, 0, 0, 0, 0, 0};


void setup() {
  Serial.begin(9600);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);


  Serial.println("Goodnight moon!");
  BlueTooth.begin(9600);
  
  delay(500);
}
void loop() {

  Serial.println("Loop Started");
  funReadSensor();
  delay(1000);

  if (BlueTooth.available()) {
    Serial.write(BlueTooth.read());
  }
  if (Serial.available() > 0)
  {
    int incomingByte = Serial.read();

  }
}

void funReadSensor()
{
  float temp;
  float temp1;
  float light;
  float humidity;
  float co;
  int colimit;

  //Serial.print("Reading Temp");
  temp = analogRead(lm35);
  temp = temp * 0.48828125;

  //Serial.print("Reading Light");
  light = analogRead(ldr);

  // co = analogRead(mq7aout);
  //delay(10);
  //co = analogRead(mq7aout);
  /*
    colimit = digitalRead(mq7dout);
    if (colimit == HIGH)
    {
      digitalWrite(led1, HIGH);
    }
    else
    {
      digitalWrite(led1, LOW);
    }
  */
  int chk = DHT.read22(DHT22_PIN);
  switch (chk)
  {
    case DHTLIB_OK:
      stat.ok++;
      Serial.println("OK,\t");
      break;
    case DHTLIB_ERROR_CHECKSUM:
      stat.crc_error++;
      Serial.println("Checksum error,\t");
      break;
    case DHTLIB_ERROR_TIMEOUT:
      stat.time_out++;
      Serial.println("Time out error,\t");
      break;
    case DHTLIB_ERROR_CONNECT:
      stat.connect++;
      Serial.println("Connect error,\t");
      break;
    case DHTLIB_ERROR_ACK_L:
      stat.ack_l++;
      Serial.println("Ack Low error,\t");
      break;
    case DHTLIB_ERROR_ACK_H:
      stat.ack_h++;
      Serial.println("Ack High error,\t");
      break;
    default:
      stat.unknown++;
      Serial.println("Unknown error,\t");
      break;
  }

  humidity = DHT.humidity;
  temp1 = DHT.temperature;
  Serial.print("Light");
  Serial.print(",\t");
  Serial.print(",\t");
  Serial.print("Temp(LM35)");
  Serial.print(",\t");
  Serial.print("Temp(DHT22)");
  Serial.print(",\t");
  Serial.println("Humidity");
  //Serial.print(",\t");
  //Serial.println("CO");
  Serial.print(light);
  Serial.print(",\t");
  Serial.print(",\t");
  Serial.print(temp);
  Serial.print(",\t");
  Serial.print(",\t");
  Serial.print(temp1);
  Serial.print(",\t");
  Serial.print(",\t");
  Serial.print(humidity);
  //Serial.print(",\t");
  //Serial.print(",\t");
  //Serial.println(co);
  Serial.println("");

  int L = light;
  int T = temp;
  int T1 = temp1;
  int H = humidity;
  //int CO = co;

  String l, t, t1, h, c;
  l = String(L);
  t = String(T);
  t1 = String(T1);
  h = String(H);
  //c = String(CO);


  Serial.print(L);
  Serial.print(",\t");
  Serial.print(",\t");
  Serial.print(T);
  Serial.print(",\t");
  Serial.print(",\t");
  Serial.print(T1);
  Serial.print(",\t");
  Serial.print(",\t");

  Serial.println(H);
  BlueTooth.println(l + '@' + t + '@' + t1 + '@' + h );
  Serial.println(l + '@' + t + '@' + t1 + '@' + h );




}

