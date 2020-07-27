#define PACKETIZER_USE_INDEX_AS_DEFAULT

#define PACKETIZER_SET_DEFAULT_ENCODING_SLIP
// #define PACKETIZER_USE_CRC_AS_DEFAULT

#include <Packetizer.h>

uint8_t recv_index = 0x12;
uint8_t send_index = 0x34;

void setup()
{
    Serial.begin(115200);
    delay(2000);

    // you can add callback depending on index value
    Packetizer::subscribe(Serial, recv_index,
        [](const uint8_t* data, const size_t size)
        {
            Packetizer::send(Serial, send_index, data, size); // send back packet
        }
    );

    // you can also add callback called every time packet comes
    Packetizer::subscribe(Serial,
        [](const uint8_t index, const uint8_t* data, const size_t size)
        {
            // create new packet which has same data (you can use same as std::vector)
            Packetizer::Packet packet;
            packet.index = index;
            for (size_t i = 0; i < size; ++i) packet.data.push_back(data[i]);

            // add error count
            auto decoder = Packetizer::getDecoderRef(Serial);
            packet.data.push_back((uint8_t)decoder->errors());

            // send back to same index
            Packetizer::send(Serial, packet.index, packet.data.data(), packet.data.size());

            // indicate by led
            static bool b = false;
            digitalWrite(13, b);
            b = !b;
        }
    );
}

void loop()
{
    Packetizer::parse();
}
