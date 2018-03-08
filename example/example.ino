#include "Packetizer.h"

Packetizer::Packer packer;
Packetizer::Unpacker unpacker;

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    while (const int size = Serial.available())
    {
        uint8_t data[size];
        Serial.readBytes((char*)data, size);
        unpacker.feed(data, size);

        while (unpacker.available())
        {
            // send back same message
            packer.pack(unpacker.data(), unpacker.size(), unpacker.index()); // index is option
            Serial.write(packer.data(), packer.size());

            unpacker.pop();
        }
    }
}
