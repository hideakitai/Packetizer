// #define PACKETIZER_SET_DEFAULT_ENCODING_SLIP
// #define PACKETIZER_USE_CRC_AS_DEFAULT

#include <Packetizer.h>

const uint8_t recv_index = 0x12;
const uint8_t send_index = 0x34;

void setup()
{
    Serial.begin(115200);
    delay(2000);

    Packetizer::subscribe(Serial,
        [&](const uint8_t* data, const size_t size)
        {
            Packetizer::send(Serial, data, size); // send back packet
        }
    );
}

void loop()
{
    Packetizer::parse();
}
