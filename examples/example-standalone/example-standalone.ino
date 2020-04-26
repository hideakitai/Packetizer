#define TEST_NO_SERIAL

#include <Packetizer.h>

Packetizer::Encoder packer;
Packetizer::Decoder unpacker;

uint8_t test_array_0[3] = {0, 1, 2};
uint8_t test_array_1[5] = {0x7C, 0x7D, 0x7E, 0x7F, 0x80};
uint8_t test_array_2[8] = {210, 211, 222, 15, 126, 200, 31, 91};
uint8_t test_array_3[3] = {3, 4, 5};
uint8_t test_array_4[11] = {10, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
uint8_t test_array_5[11] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 125};

void callback(const uint8_t* data, uint8_t size)
{
    Serial.print("size  : ");
    Serial.println(size);

    Serial.print("data : ");
    for (uint8_t i = 0; i < size; ++i)
    {
        Serial.print(data[i], HEX);
        Serial.print(" ");
    }
    Serial.println();
}

void setup()
{
    Serial.begin(115200);
    delay(5000);

    // -----------------------------------------------------------------------

    Serial.println("test 1");
    Serial.println("---------- packing data ----------");
    Serial.print("data : ");
    for (uint8_t i = 0; i < sizeof(test_array_0); ++i)
    {
        Serial.print(test_array_0[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    packer.pack(test_array_0, sizeof(test_array_0));


    Serial.println("---------- packed data ----------");
    Serial.print("data : ");
    for (uint8_t i = 0; i < packer.size(); ++i)
    {
        Serial.print(packer.data()[i], HEX);
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
            Serial.print(unpacker.data()[i], HEX);
            Serial.print(" ");
        }
        Serial.println();

        unpacker.pop();
    }

    // -----------------------------------------------------------------------

    Serial.println();
    Serial.println("test 2");
    Serial.println("---------- packing data ----------");

    Serial.print("data : ");
    for (uint8_t i = 0; i < sizeof(test_array_1); ++i)
    {
        Serial.print(test_array_1[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    packer.init(1);
    packer.pack(test_array_1, sizeof(test_array_1));


    Serial.println("---------- packed data ----------");
    Serial.print("data : ");
    for (uint8_t i = 0; i < packer.size(); ++i)
    {
        Serial.print(packer.data()[i], HEX);
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
            Serial.print(unpacker.data()[i], HEX);
            Serial.print(" ");
        }
        Serial.println();

        unpacker.pop();
    }

    // -----------------------------------------------------------------------

    Serial.println();
    Serial.println("test 3");
    Serial.println("---------- packing data ----------");

    Serial.print("data : ");
    for (uint8_t i = 0; i < sizeof(test_array_2); ++i)
    {
        Serial.print(test_array_2[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    packer.init(2);
    packer.pack(test_array_2, sizeof(test_array_2));


    Serial.println("---------- packed data ----------");
    Serial.print("data : ");
    for (uint8_t i = 0; i < packer.size(); ++i)
    {
        Serial.print(packer.data()[i], HEX);
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
            Serial.print(unpacker.data()[i], HEX);
            Serial.print(" ");
        }
        Serial.println();

        unpacker.pop();
    }

    // -----------------------------------------------------------------------

    Serial.println();
    Serial.println("test 4");
    Serial.println("---------- packing data ----------");

    Serial.print("data : ");
    for (uint8_t i = 0; i < sizeof(test_array_3); ++i)
    {
        Serial.print(test_array_3[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    packer.init(3);
    packer.pack(test_array_3[0], test_array_3[1], test_array_3[2]);


    Serial.println("---------- packed data ----------");
    Serial.print("data : ");
    for (uint8_t i = 0; i < packer.size(); ++i)
    {
        Serial.print(packer.data()[i], HEX);
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
            Serial.print(unpacker.data()[i], HEX);
            Serial.print(" ");
        }
        Serial.println();

        unpacker.pop();
    }


    // -----------------------------------------------------------------------

    Serial.println();
    Serial.println("test 5");
    Serial.println("---------- packing data ----------");

    Serial.print("data : ");
    for (uint8_t i = 0; i < sizeof(test_array_4); ++i)
    {
        Serial.print(test_array_4[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    packer.init(0x7D);
    packer << test_array_4[0] << test_array_4[1] << test_array_4[2] << test_array_4[3] << test_array_4[4];
    packer << test_array_4[5] << test_array_4[6] << test_array_4[7];
    packer << test_array_4[8] << test_array_4[9] << test_array_4[10] << Packetizer::endp();


    Serial.println("---------- packed data ----------");
    Serial.print("data : ");
    for (uint8_t i = 0; i < packer.size(); ++i)
    {
        Serial.print(packer.data()[i], HEX);
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
            Serial.print(unpacker.data()[i], HEX);
            Serial.print(" ");
        }
        Serial.println();

        unpacker.pop();
    }

    // -----------------------------------------------------------------------

    Serial.println();
    Serial.println("test 6");
    Serial.println("---------- packing data ----------");

    Serial.print("data : ");
    for (uint8_t i = 0; i < sizeof(test_array_4); ++i)
    {
        Serial.print(test_array_4[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    packer.init(0x7E);
    packer << test_array_4[0] << test_array_4[1] << test_array_4[2] << test_array_4[3] << test_array_4[4];
    packer << test_array_4[5] << test_array_4[6] << test_array_4[7];
    packer << test_array_4[8] << test_array_4[9] << test_array_4[10] << Packetizer::endp();


    Serial.println("---------- packed data ----------");
    Serial.print("data : ");
    for (uint8_t i = 0; i < packer.size(); ++i)
    {
        Serial.print(packer.data()[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    unpacker.subscribe(0x7E,
        [](const uint8_t* data, const uint8_t size)
        {
            Serial.print("size  : ");
            Serial.println(size);

            Serial.print("data : ");
            for (uint8_t i = 0; i < size; ++i)
            {
                Serial.print(data[i], HEX);
                Serial.print(" ");
            }
            Serial.println();
        }
    );

    Serial.println("---------- unpacked results ----------");

    unpacker.feed(packer.data(), packer.size());


    // -----------------------------------------------------------------------

    Serial.println();
    Serial.println("test 7");
    Serial.println("---------- packing data ----------");

    Serial.print("data : ");
    for (uint8_t i = 0; i < sizeof(test_array_4); ++i)
    {
        Serial.print(test_array_4[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    packer.init(0x7F);
    packer << test_array_4[0] << test_array_4[1] << test_array_4[2] << test_array_4[3] << test_array_4[4];
    packer << test_array_4[5] << test_array_4[6] << test_array_4[7];
    packer << test_array_4[8] << test_array_4[9] << test_array_4[10] << Packetizer::endp();


    Serial.println("---------- packed data ----------");
    Serial.print("data : ");
    for (uint8_t i = 0; i < packer.size(); ++i)
    {
        Serial.print(packer.data()[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    unpacker.subscribe(0x7F, callback);

    Serial.println("---------- unpacked results ----------");

    unpacker.feed(packer.data(), packer.size());


    // -----------------------------------------------------------------------

    Serial.println();
    Serial.println("test 8");
    Serial.println("---------- packing data ----------");

    Serial.print("data : ");
    for (uint8_t i = 0; i < sizeof(test_array_4); ++i)
    {
        Serial.print(test_array_4[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    packer.init();
    packer << test_array_4[0] << test_array_4[1] << test_array_4[2] << test_array_4[3] << test_array_4[4];
    packer << test_array_4[5] << test_array_4[6] << test_array_4[7];
    packer << test_array_4[8] << test_array_4[9] << test_array_4[10] << Packetizer::endp();


    Serial.println("---------- packed data ----------");
    Serial.print("data : ");
    for (uint8_t i = 0; i < packer.size(); ++i)
    {
        Serial.print(packer.data()[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    unpacker.subscribe(0x00, callback);

    Serial.println("---------- unpacked results ----------");

    unpacker.feed(packer.data(), packer.size());


    // -----------------------------------------------------------------------

    Serial.println();
    Serial.println("test 9");
    Serial.println("---------- packing data ----------");

    Serial.print("data : ");
    for (uint8_t i = 0; i < sizeof(test_array_5); ++i)
    {
        Serial.print(test_array_5[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    packer.init();
    packer << test_array_5[0] << test_array_5[1] << test_array_5[2] << test_array_5[3] << test_array_5[4];
    packer << test_array_5[5] << test_array_5[6] << test_array_5[7];
    packer << test_array_5[8] << test_array_5[9] << test_array_5[10] << Packetizer::endp();


    Serial.println("---------- packed data ----------");
    Serial.print("data : ");
    for (uint8_t i = 0; i < packer.size(); ++i)
    {
        Serial.print(packer.data()[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    unpacker.subscribe(0x00, callback);

    Serial.println("---------- unpacked results ----------");

    unpacker.feed(packer.data(), packer.size());


    // -----------------------------------------------------------------------

    Serial.println();
    Serial.println("test 12");
    Serial.println("---------- packing data ----------");

    Serial.print("data : ");
    for (uint8_t i = 0; i < 10; ++i)
    {
        Serial.print(i, HEX);
        Serial.print(" ");
    }
    Serial.println();

    const auto& packet12 = Packetizer::encode(12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22);

    Serial.println("---------- packed data ----------");
    Serial.print("data : ");
    for (auto& p : packet12)
    {
        Serial.print(p, HEX);
        Serial.print(" ");
    }
    Serial.println();

    unpacker.subscribe([](const uint8_t index, const uint8_t* data, const uint8_t size)
    {
        Serial.print("index = ");
        Serial.print(index);
        Serial.print(", size = ");
        Serial.print(size);
        Serial.print(", data = ");
        for (uint8_t i = 0; i < size; ++i)
        {
            Serial.print(data[i], HEX);
            Serial.print(" ");
        }
        Serial.println();
    });

    Serial.println("---------- unpacked results ----------");

    unpacker.feed(packet12.data(), packet12.size());

    // -----------------------------------------------------------------------

    Serial.println();
    Serial.println("test 10");
    Serial.println("---------- packing data ----------");

    Serial.print("data : ");
    for (uint8_t i = 0; i < sizeof(test_array_5); ++i)
    {
        Serial.print(test_array_5[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    const auto& packet10 = Packetizer::encode(10, (const uint8_t*)test_array_5, sizeof(test_array_5));

    Serial.println("---------- packed data ----------");
    Serial.print("data : ");
    for (auto& p : packet10)
    {
        Serial.print(p, HEX);
        Serial.print(" ");
    }
    Serial.println();

    unpacker.subscribe(10, callback);

    Serial.println("---------- unpacked results ----------");

    unpacker.feed(packet10.data(), packet10.size());

    // -----------------------------------------------------------------------

    unpacker.unsubscribe();

    Serial.println();
    Serial.println("test 11");
    Serial.println("---------- packing data ----------");

    Serial.print("data : ");
    for (uint8_t i = 0; i < 10; ++i)
    {
        Serial.print(i, HEX);
        Serial.print(" ");
    }
    Serial.println();

    const auto& packet11 = Packetizer::encode(11, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
    // auto packet11 = Packetizer::encode(11, 0, 1);

    Serial.println("---------- packed data ----------");
    Serial.print("data : ");
    for (auto& p : packet11)
    {
        Serial.print(p, HEX);
        Serial.print(" ");
    }
    Serial.println();

    unpacker.subscribe(11, callback);

    Serial.println("---------- unpacked results ----------");

    unpacker.feed(packet11.data(), packet11.size());

}

void loop()
{
}
