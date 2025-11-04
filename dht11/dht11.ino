#include "DHT.h"

#define DHT_PIN 4
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float temp = dht.readTemperature();
  float humid = dht.readHumidity();

  Serial.print("Nhiet do: ");
  Serial.println(temp);
  Serial.print("Do am: ");
  Serial.println(humid);

  Serial.println();
  delay(1000);
}
