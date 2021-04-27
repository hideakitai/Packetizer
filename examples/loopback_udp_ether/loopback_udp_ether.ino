#define PACKETIZER_USE_INDEX_AS_DEFAULT

// #define PACKETIZER_SET_DEFAULT_ENCODING_SLIP
#define PACKETIZER_USE_CRC_AS_DEFAULT

#include <Packetizer.h>

uint8_t msg_index = 0x12;

// Ethernet stuff
uint8_t mac[] = {0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45};
const IPAddress ip(192, 168, 1, 201);
// Ethernet with useful options
// const IPAddress dns (192, 168, 0, 1);
// const IPAddress gateway (192, 168, 0, 1);
// const IPAddress subnet (255, 255, 255, 0);

const char* host = "192.168.0.17";
const int port = 54321;

EthernetUDP client;

void setup() {
    Serial.begin(115200);
    delay(2000);

    // Ethernet stuff
    Ethernet.begin(mac, ip);
    // Ethernet with useful options
    // Ethernet.begin(mac, ip, dns, gateway, subnet); // full
    // Ethernet.setRetransmissionCount(4); // default: 8[times]
    // Ethernet.setRetransmissionTimeout(50); // default: 200[ms]

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
