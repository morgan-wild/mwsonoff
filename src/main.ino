#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "pinsRF.h"
#include "settings.h"

ESP8266WebServer _webServer(WEB_SERVER_PORT);

void setup()
{

    // --------------------------------------------------------------
    // Initialize GPIO

        pinMode(PIN_BUTTON, INPUT);
        pinMode(PIN_RELAY, OUTPUT);
        pinMode(PIN_LED_GREEN, OUTPUT);

    // --------------------------------------------------------------
    // Initialize Serial

        Serial.begin(115200);

        delay(10);

        Serial.println("Started");

    // --------------------------------------------------------------
    // Initialize Wifi

        WiFi.hostname(WIFI_DEVICE_NAME);

        #ifdef WIFI_DEVICE_STATIC_IP
        WiFi.config(WIFI_DEVICE_STATIC_IP, 
                    WIFI_DEVICE_STATIC_SUBNET,
                    WIFI_DEVICE_STATIC_GATEWAY, 
                    WIFI_DEVICE_STATIC_DNS);
        #endif

        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

        checkAndWaitWifiConnection();


    // --------------------------------------------------------------
    // Initialize Web server

        _webServer.on("/", HTTP_GET, []() {
            
            _webServer.send(200, "text/plain", String(digitalRead(PIN_RELAY) ? "ON" : "OFF"));
        });

        _webServer.on("/toggle", HTTP_POST, []() {

            digitalWrite(PIN_RELAY, !digitalRead(PIN_RELAY));

            _webServer.send(200, "text/plain", String(digitalRead(PIN_RELAY) ? "ON" : "OFF"));
        });

        _webServer.on("/on", HTTP_POST, []() {

            digitalWrite(PIN_RELAY, HIGH);

            _webServer.send(200, "text/plain", "ON");
        });

        _webServer.on("/off", HTTP_POST, []() {

            digitalWrite(PIN_RELAY, LOW);

            _webServer.send(200, "text/plain", "OFF");
        });

        _webServer.begin();

}

void loop()
{
    checkAndWaitWifiConnection();

    _webServer.handleClient();

    if (digitalRead(PIN_BUTTON) == BUTTON_PRESSED) {
    
        digitalWrite(PIN_RELAY, !digitalRead(PIN_RELAY));

        Serial.println("Toggle by button");

        // Prevent blink if the button stays pressed :)
        while (digitalRead(PIN_BUTTON) == BUTTON_PRESSED) {
            delay(10);
        }
    }

    delay(100);
}

void checkAndWaitWifiConnection() {

    if (WiFi.status() == WL_CONNECTED) {
        return;
    }

    Serial.print("Connecting");

    do {
        delay(500);

        Serial.print(".");

        digitalWrite(PIN_LED_GREEN, !digitalRead(PIN_LED_GREEN));
    }
    while (WiFi.status() != WL_CONNECTED);

    Serial.println();
    Serial.println("Connected (using ip address " + WiFi.localIP().toString() + ")");

    digitalWrite(PIN_LED_GREEN, HIGH);
}