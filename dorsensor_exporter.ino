#include <WiFi.h>
#include <WebServer.h>
#include "config.h"

int doorState;

WebServer httpServer(9000);

void handle_request() {
    doorState = digitalRead(DOOR_SENSOR_PIN); // read state
    Serial.println(doorState);
    
    String HTMLData = "door_status{label=\"front\"} " + String(doorState);
    httpServer.send(200, "text/html", HTMLData);
    
} 

void setup() {
    Serial.begin(9600);
    while (!Serial) {}
    Serial.println("Tring to connect to Wifi SSID: ");
    Serial.println(ssid);
  
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected successfully");
    Serial.print("Assigned IP: ");
    Serial.println(WiFi.localIP());

    pinMode(DOOR_SENSOR_PIN, INPUT_PULLUP); // set ESP32 pin to input pull-up mode
  
    httpServer.on("/", handle_request);
    httpServer.begin();
    Serial.println("HTTP server started");
    delay(100);
}

void loop() {
  httpServer.handleClient();
}
