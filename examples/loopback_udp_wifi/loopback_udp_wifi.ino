#define PACKETIZER_USE_INDEX_AS_DEFAULT

// #define PACKETIZER_SET_DEFAULT_ENCODING_SLIP
#define PACKETIZER_USE_CRC_AS_DEFAULT

#include <Packetizer.h>

uint8_t msg_index = 0x12;

// WiFi stuff
const char* ssid = "your-ssid";
const char* pwd = "your-password";
const IPAddress ip(192, 168, 0, 201);
const IPAddress gateway(192, 168, 0, 1);
const IPAddress subnet(255, 255, 255, 0);
const char* host = "192.168.0.17";
const int port = 54321;

WiFiUDP client;

void setup() {
    Serial.begin(115200);
    delay(2000);

    // WiFi stuff (no timeout setting for WiFi)
#ifdef ESP_PLATFORM
    WiFi.disconnect(true, true);  // disable wifi, erase ap info
    delay(1000);
    WiFi.mode(WIFI_STA);
#endif
    WiFi.begin(ssid, pwd);
    WiFi.config(ip, gateway, subnet);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.print("WiFi connected, IP = ");
    Serial.println(WiFi.localIP());

    // start client
    client.begin(port);

    Packetizer::subscribe(client, msg_index,
        [&](const uint8_t* data, const size_t size) {
            Serial.print("received data: ");
            for (size_t i = 0; i < size; ++i) {
                Serial.print(data[i]);
                Serial.print(" ");
            }
            Serial.println();
        });
}

void loop() {
    static uint32_t count = 0;
    static uint32_t prev_ms = millis();
    if (millis() > prev_ms + 1000) {
        uint32_t now = millis();
        uint8_t data[10];
        for (size_t i = 0; i < 10; ++i) {
            data[i] = count + i;
        }
        Packetizer::send(client, host, port, msg_index, data, 10);
        prev_ms = now;
        ++count;
    }

    Packetizer::parse();  // must be called to trigger callback
}
