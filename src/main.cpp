#include "Secrets.h"
#include "Mapping.h"
#include "Player.h"
#include "Music.h"
#include "esp32-hal-gpio.h"
#include <Arduino.h>
#include <WiFi.h>
#include <iostream>

Mapping mapping;
Polka p;
Menuet m;
Player player(m, mapping);

constexpr const auto LED_PIN = GPIO_NUM_8;

void setup()
{
    Serial.begin(115200);
    while (!Serial) {
    }

    WiFi.setHostname(Secrets::HOSTNAME);
    WiFi.mode(WIFI_STA);
    WiFi.setAutoReconnect(true);
    WiFi.begin(Secrets::WIFI_SSID, Secrets::WIFI_PASS);
    pinMode(LED_PIN, OUTPUT);

    player.Setup();
}

void loop()
{
    player.Tick();

    auto now = millis();
    static auto prevMillis = now;
    static bool connectionReported = false;

    auto wifiStatus = WiFi.status();
    if (wifiStatus != WL_CONNECTED) {
        connectionReported = false;
        if (now - prevMillis > 500) {
            prevMillis = now;
            static auto state = HIGH;
            state = HIGH - state;
            digitalWrite(LED_PIN, state);
            std::cout << "wifi=" << wifiStatus << std::endl;
        }
    } else {
        if (!connectionReported) {
            connectionReported = true;
            digitalWrite(LED_PIN, LOW);
            auto ip = WiFi.localIP();
            std::cout << "Connected to WiFi: " << ip.toString().c_str() << std::endl;
        }
    }
}
