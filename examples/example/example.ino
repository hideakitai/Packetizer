#include "Packetizer.h"

Packetizer::Unpacker unpacker;

bool b_received_0 = false;
bool b_received_1 = false;

void setup()
{
    Serial.begin(115200);

    unpacker.subscribe(0, [](const uint8_t* data, uint8_t size)
    {
        // send back packet
        Packetizer::Packer packer(0xFF); // set index
        for (uint8_t i = 0; i < size; ++i) packer << data[i];
        packer << Packetizer::endp();
        Serial.write(packer.data(), packer.size());
    });

    unpacker.subscribe(1, [](const uint8_t* data, uint8_t size)
    {
        // send back packet
        Packetizer::Packer packer(0xFE); // set index
        for (uint8_t i = 0; i < size; ++i) packer << data[i];
        packer << Packetizer::endp();
        Serial.write(packer.data(), packer.size());
    });
}

void loop()
{
    // read packet
    while (const int size = Serial.available())
    {
        uint8_t data[size];
        Serial.readBytes((char*)data, size);
        unpacker.feed(data, size); // if index matches, callback is automatically called
    }
}
