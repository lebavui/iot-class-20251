void setup() {
  Serial.begin(9600);

}

void loop() {
  // Đọc dữ liệu digital chân 15 (1 hoặc 0)
  Serial.print(digitalRead(15));
  Serial.print("   ");
  // Đọc dữ liệu analog chân 2
  // Với ESP32 độ phân giải mặc định là 12 bit
  Serial.println(analogRead(2));
  delay(1000);
}
