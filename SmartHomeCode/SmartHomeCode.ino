#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int trigPin = 5;
const int echoPin = 4;
const int lightsensPin = 0;
const int peepPin = 14;
const int ventPin = 12;
const int lightPin = 13;
long duration;
int distance;
int light;
float humi;
float temp;
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(lightsensPin, INPUT);
  pinMode(peepPin, OUTPUT);
  pinMode(ventPin, OUTPUT);
  pinMode(lightPin, OUTPUT);
  Serial.begin(9600);
  
  dht.begin();
}

void loop() {
  delay(distance * 15 + 50);
  //distance START
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  
  distance= duration*0.034/2;
  
  Serial.print("State: ");
  if(distance > 20){
    Serial.print("Safe ");
  } else {
    Serial.print("Movement ");
  }
  //distance END
  //humidity & temp START
  
  humi = dht.readHumidity();
  temp = dht.readTemperature();
  
  Serial.print(F("Humidity: "));
  Serial.print(humi);
  Serial.print(F("%  Temperature: "));
  Serial.print(temp);
  Serial.print(F("°C "));
  
  //humidity & temp END
  //lightsens START

  light = analogRead(lightsensPin);
  Serial.print("Light: ");
  Serial.println(light);
  
  //lightsens END 
  //peep START
  analogWrite(peepPin, 200);
  delay(40);
  analogWrite(peepPin, 0);

  //peep END
  //vent START
  
  if(temp > 28 || humi > 44){
    digitalWrite(ventPin, HIGH);
  } else {
    digitalWrite(ventPin, LOW);
  }
  //vent END

  if(light > 800 || distance < 20){
    digitalWrite(lightPin, HIGH);
  } else {
    digitalWrite(lightPin, LOW);
  }
  
}
