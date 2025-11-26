#include <WiFi.h>
#include <HTTPClient.h>

#include <Wire.h>
#include <Adafruit_AHTX0.h>

// Create an instance of the AHT10 sensor
Adafruit_AHTX0 aht;

const char* ssid = "Honda Free Wifi 01";
const char* password = "";

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

  // Connect to Wi-Fi
  Serial.printf("Connecting to Wi-Fi: %s\n", ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to Wi-Fi!");
  
  pinMode(2, OUTPUT);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Gửi yêu cầu lấy trạng thái LED

    http.begin("http://192.168.2.69:1880/get_state");

    int httpCode = http.GET();

    if (httpCode > 0) {
      Serial.printf("Response code: %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println("Response body:");
        Serial.println(payload);

        if (payload.equals("{\"switch\":true}")) {
          digitalWrite(2, HIGH);
        } else {
          digitalWrite(2, LOW);
        }
      }
    } else {
      Serial.printf("Error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();

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

    // Gửi yêu cầu cập nhật nhiệt độ và độ ẩm
    char url[80];
    sprintf(url, "http://192.168.2.69:1880/get_to_send?temperature=%.1f&humidity=%.1f", temp.temperature, humidity.relative_humidity);

    http.begin(url);

    httpCode = http.GET();

    if (httpCode > 0) {
      Serial.printf("Response code: %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println("Response body:");
        Serial.println(payload);
      }
    } else {
      Serial.printf("Error: %s\n", http.errorToString(httpCode));
    }

    http.end();
  }

  delay(5000);
}