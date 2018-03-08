#define TEST_NO_SERIAL

#include "Packetizer.h"

Packetizer::Packer packer;
Packetizer::Unpacker unpacker;

uint8_t test_array_0[3] = {0, 1, 2};
uint8_t test_array_1[5] = {0x7C, 0x7D, 0x7E, 0x7F, 0x80};
uint8_t test_array_2[8] = {210, 211, 222, 15, 126, 200, 31, 91};

void setup()
{
    Serial.begin(115200);
    delay(5000);

    // set check mode if you need, defualt is CRC8
    // packer.setCheckMode(Packetizer::Checker::None);
    // unpacker.setCheckMode(Packetizer::Checker::None);
    // packer.setCheckMode(Packetizer::Checker::Sum);
    // unpacker.setCheckMode(Packetizer::Checker::Sum);
    // packer.setCheckMode(Packetizer::Checker::CRC8);
    // unpacker.setCheckMode(Packetizer::Checker::CRC8);

    Serial.println("test 1");
    Serial.println("---------- packing data ----------");
    Serial.print("data : ");
    for (uint8_t i = 0; i < sizeof(test_array_0); ++i)
    {
        Serial.print(test_array_0[i]);
        Serial.print(" ");
    }
    Serial.println();

    packer.pack(test_array_0, sizeof(test_array_0));


    Serial.println("---------- packed data ----------");
    Serial.print("data : ");
    for (uint8_t i = 0; i < packer.size(); ++i)
    {
        Serial.print(packer.data()[i]);
        Serial.print(" ");
    }
    Serial.println();


    Serial.println("---------- unpacked results ----------");

    unpacker.feed(packer.data(), packer.size());

    while (unpacker.available())
    {
        Serial.print("index : ");
        Serial.println(unpacker.index());

        Serial.print("size  : ");
        Serial.println(unpacker.size());

        Serial.print("data : ");
        for (uint8_t i = 0; i < unpacker.size(); ++i)
        {
            Serial.print(unpacker.data()[i]);
            Serial.print(" ");
        }
        Serial.println();

        unpacker.pop();
    }

    Serial.println();
    Serial.println("test 2");
    Serial.println("---------- packing data ----------");

    Serial.print("data : ");
    for (uint8_t i = 0; i < sizeof(test_array_1); ++i)
    {
        Serial.print(test_array_1[i]);
        Serial.print(" ");
    }
    Serial.println();

    packer.pack(test_array_1, sizeof(test_array_1));


    Serial.println("---------- packed data ----------");
    Serial.print("data : ");
    for (uint8_t i = 0; i < packer.size(); ++i)
    {
        Serial.print(packer.data()[i]);
        Serial.print(" ");
    }
    Serial.println();



    Serial.println("---------- unpacked results ----------");

    unpacker.feed(packer.data(), packer.size());

    while (unpacker.available())
    {
        Serial.print("index : ");
        Serial.println(unpacker.index());

        Serial.print("size  : ");
        Serial.println(unpacker.size());

        Serial.print("data : ");
        for (uint8_t i = 0; i < unpacker.size(); ++i)
        {
            Serial.print(unpacker.data()[i]);
            Serial.print(" ");
        }
        Serial.println();

        unpacker.pop();
    }

    Serial.println();
    Serial.println("test 3");
    Serial.println("---------- packing data ----------");

    Serial.print("data : ");
    for (uint8_t i = 0; i < sizeof(test_array_2); ++i)
    {
        Serial.print(test_array_2[i]);
        Serial.print(" ");
    }
    Serial.println();

    packer.pack(test_array_2, sizeof(test_array_2));


    Serial.println("---------- packed data ----------");
    Serial.print("data : ");
    for (uint8_t i = 0; i < packer.size(); ++i)
    {
        Serial.print(packer.data()[i]);
        Serial.print(" ");
    }
    Serial.println();


    Serial.println("---------- unpacked results ----------");

    unpacker.feed(packer.data(), packer.size());

    while (unpacker.available())
    {
        Serial.print("index : ");
        Serial.println(unpacker.index());

        Serial.print("size  : ");
        Serial.println(unpacker.size());

        Serial.print("data : ");
        for (uint8_t i = 0; i < unpacker.size(); ++i)
        {
            Serial.print(unpacker.data()[i]);
            Serial.print(" ");
        }
        Serial.println();

        unpacker.pop();
    }
}

void loop()
{
#ifndef TEST_NO_SERIAL
    while (const int size = Serial.available())
    {
        uint8_t data[size];
        Serial.readBytes((char*)data, size);
        unpacker.feed(data, size);

        while (unpacker.available())
        {
            switch(unpacker.index())
            {
                case 0:
                {
                    int id;
                    unpacker >> id;
                    // or
                    // int id = unpacker.deserialize<int>();

                    // return same message
                    packer.pack(id, unpacker.index());
                    break;
                }
                case 1:
                {
                    float time;
                    unpacker >> time;
                    // or
                    // float time = unpacker.deserialize<float>();

                    // return same message
                    packer.pack(time, unpacker.index());
                    break;
                }
                case 2:
                {
                    Message m;
                    unpacker >> m;
                    // or
                    // Message m = unpacker.deserialize<Message>();

                    // return same message
                    packer.pack(m, unpacker.index());
                    break;
                }
                default:
                {
                    break;
                }
            }
            Serial.write(packer.data(), packer.size());
            unpacker.pop();
        }
    }
#endif
}