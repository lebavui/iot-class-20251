#include <Wire.h>
#include <Adafruit_AHTX0.h>

// Create an instance of the AHT10 sensor
Adafruit_AHTX0 aht;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  Serial.println("AHT10 Sensor Example");

  // Initialize I2C communication
  if (!aht.begin()) {
    Serial.println("Failed to find AHT10 sensor! Check wiring.");
    while (1);
  }
  Serial.println("AHT10 sensor initialized.");
}

void loop() {
  // Read temperature and humidity from the sensor
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp); // Populate the event objects

  // Print temperature and humidity to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity.relative_humidity);
  Serial.println(" %");

  // Delay between readings
  delay(2000);
}