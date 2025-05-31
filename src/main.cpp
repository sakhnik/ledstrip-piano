#include "Secrets.h"
#include "Mapping.h"
#include "Player.h"
#include "Music.h"
#include <WiFi.h>
#include <ESPmDNS.h>
#ifdef ENABLE_OTA
#include <ArduinoOTA.h>
#endif

Mapping mapping;
Polka p;
Menuet m;
Player player(m, mapping);

constexpr const auto LED_PIN = GPIO_NUM_8;

void setup()
{
    setCpuFrequencyMhz(80);

    MDNS.begin(Secrets::HOSTNAME);
    WiFi.setHostname(Secrets::HOSTNAME);
    WiFi.mode(WIFI_STA);
    WiFi.setAutoReconnect(true);
    WiFi.begin(Secrets::WIFI_SSID, Secrets::WIFI_PASS);

    pinMode(LED_PIN, OUTPUT);

#ifdef ENABLE_OTA
    ArduinoOTA.setHostname(Secrets::HOSTNAME);
    ArduinoOTA.begin();
#endif

    player.Setup();
}

void loop()
{
#ifdef ENABLE_OTA
    ArduinoOTA.handle();
#endif

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

            printf("wifi=%d\n", wifiStatus);
        }
    } else {
        if (!connectionReported) {
            connectionReported = true;
            digitalWrite(LED_PIN, LOW);
            auto ip = WiFi.localIP();
            printf("Connected to Wifi: %s\n", ip.toString().c_str());
        }
    }
}
