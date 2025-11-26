#include <WiFi.h>
#include <WebServer.h>

WebServer server(80);

const int LED = 2;

bool ledState = false;

void sendHtml() {
  String response = R"(
    <!DOCTYPE html><html>
      <head>
        <title>ESP32 Web Server Demo</title>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <style>
          html { font-family: sans-serif; text-align: center; }
          body { display: inline-flex; flex-direction: column; }
          h1 { margin-bottom: 1.2em; }
          div { display: grid; grid-template-columns: 1fr 1fr; grid-template-rows: auto auto; grid-auto-flow: column; grid-gap: 1em; }
          .btn { background-color: #5B5; border: none; color: #fff; padding: 0.5em 1em;
                 font-size: 2em; text-decoration: none }
          .btn.OFF { background-color: #333; }
        </style>
      </head>
            
      <body>
        <h1>ESP32 Web Server</h1>

        <div>
          <a href="/toggle" class="btn LED_TEXT">LED_TEXT</a>
        </div>
      </body>
    </html>
  )";
  response.replace("LED_TEXT", ledState ? "ON" : "OFF");
  server.send(200, "text/html", response);
}

void setup(void) {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

  WiFi.softAP("ESP32_IoT_Class", "12345678");
  Serial.print("AP mode started. IP address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", sendHtml);

  server.on("/toggle", []() {
    ledState = !ledState;
    digitalWrite(LED, ledState);
    
    sendHtml();
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  delay(2);
}
