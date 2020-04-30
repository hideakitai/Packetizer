#include <Packetizer.h>

Packetizer::Decoder decoder;

uint8_t recv_index = 0x12;
uint8_t send_index = 0x34;

void setup()
{
    Serial.begin(115200);

    decoder.subscribe(recv_index, [](const uint8_t* data, const uint8_t size)
    {
        Packetizer::send(Serial, send_index, data, size); // send back packet
    });
}

void loop()
{
    while (const int size = Serial.available())
    {
        uint8_t data[size];
        Serial.readBytes((char*)data, size);
        decoder.feed(data, size);
    }
}

