// #define PACKETIZER_SET_DEFAULT_ENCODING_SLIP
// #define PACKETIZER_USE_CRC_AS_DEFAULT

#include <Packetizer.h>

auto decoder = Packetizer::getDecoderRef();

void setup()
{
    Serial.begin(115200);
    delay(2000);
}

void loop()
{
    while (const int size = Serial.available())
    {
        uint8_t data[size];
        Serial.readBytes((char*)data, size);
        decoder->feed(data, size);

        while (decoder->available())
        {
            Packetizer::send(Serial, decoder->data(), decoder->size());
            decoder->pop();
        }
    }
}
