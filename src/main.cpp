#include "Secrets.h"
#include "Mapping.h"
#include "Player.h"
#include "Music.h"
#include <WiFi.h>
#include <ESPmDNS.h>
#include <ArduinoOTA.h>

Mapping mapping;
Polka p;
Menuet m;
Player player(m, mapping);

constexpr const auto LED_PIN = GPIO_NUM_8;

void setup()
{
    setCpuFrequencyMhz(80);

    Serial.begin(115200);
    while (!Serial) {
    }

    MDNS.begin(Secrets::HOSTNAME);
    WiFi.setHostname(Secrets::HOSTNAME);
    WiFi.mode(WIFI_STA);
    WiFi.setAutoReconnect(true);
    WiFi.begin(Secrets::WIFI_SSID, Secrets::WIFI_PASS);

    pinMode(LED_PIN, OUTPUT);

    ArduinoOTA.setHostname(Secrets::HOSTNAME);
    ArduinoOTA.begin();

    player.Setup();
}

void loop()
{
    ArduinoOTA.handle();

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

            Serial.print(F("wifi="));
            Serial.println(wifiStatus);
        }
    } else {
        if (!connectionReported) {
            connectionReported = true;
            digitalWrite(LED_PIN, LOW);
            auto ip = WiFi.localIP();
            Serial.print("Connected to WiFi: ");
            Serial.println(ip.toString().c_str());
        }
    }
}
