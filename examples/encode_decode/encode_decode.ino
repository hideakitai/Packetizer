// #define PACKETIZER_USE_CRC_AS_DEFAULT
// #define PACKETIZER_SET_DEFAULT_ENCODING_SLIP

#include <Packetizer.h>

void setup() {
    Serial.begin(115200);
    delay(2000);

    {
        Packetizer::Packet p_in {0x00, {0x00}};
        const auto& p_buff = Packetizer::encode(p_in.data.data(), p_in.data.size());
        const auto& p_out = Packetizer::decode(p_buff.data.data(), p_buff.data.size());

        Serial.print("input   = ");
        for (const auto& p : p_in.data) {
            Serial.print(p, HEX);
            Serial.print(" ");
        }
        Serial.println();
        Serial.print("encoded = ");
        for (const auto& p : p_buff.data) {
            Serial.print(p, HEX);
            Serial.print(" ");
        }
        Serial.println();
        Serial.print("decoded = ");
        for (const auto& p : p_out.data) {
            Serial.print(p, HEX);
            Serial.print(" ");
        }
        Serial.println();

        if (p_in.data != p_out.data)
            Serial.println("test 1 failed!");
        else
            Serial.println("test 1 success!");
    }
    {
        Packetizer::Packet p_in {0x00, {0x00, 0x00}};
        const auto& p_buff = Packetizer::encode(p_in.data.data(), p_in.data.size());
        const auto& p_out = Packetizer::decode(p_buff.data.data(), p_buff.data.size());

        Serial.print("input   = ");
        for (const auto& p : p_in.data) {
            Serial.print(p, HEX);
            Serial.print(" ");
        }
        Serial.println();
        Serial.print("encoded = ");
        for (const auto& p : p_buff.data) {
            Serial.print(p, HEX);
            Serial.print(" ");
        }
        Serial.println();
        Serial.print("decoded = ");
        for (const auto& p : p_out.data) {
            Serial.print(p, HEX);
            Serial.print(" ");
        }
        Serial.println();

        if (p_in.data != p_out.data)
            Serial.println("test 2 failed!");
        else
            Serial.println("test 2 success!");
    }
    {
        Packetizer::Packet p_in {0x00, {0x11, 0x22, 0x00, 0x33}};
        const auto& p_buff = Packetizer::encode(p_in.data.data(), p_in.data.size());
        const auto& p_out = Packetizer::decode(p_buff.data.data(), p_buff.data.size());

        Serial.print("input   = ");
        for (const auto& p : p_in.data) {
            Serial.print(p, HEX);
            Serial.print(" ");
        }
        Serial.println();
        Serial.print("encoded = ");
        for (const auto& p : p_buff.data) {
            Serial.print(p, HEX);
            Serial.print(" ");
        }
        Serial.println();
        Serial.print("decoded = ");
        for (const auto& p : p_out.data) {
            Serial.print(p, HEX);
            Serial.print(" ");
        }
        Serial.println();

        if (p_in.data != p_out.data)
            Serial.println("test 3 failed!");
        else
            Serial.println("test 3 success!");
    }
    {
        Packetizer::Packet p_in {0x00, {0x11, 0x22, 0x33, 0x44}};
        const auto& p_buff = Packetizer::encode(p_in.data.data(), p_in.data.size());
        const auto& p_out = Packetizer::decode(p_buff.data.data(), p_buff.data.size());

        Serial.print("input   = ");
        for (const auto& p : p_in.data) {
            Serial.print(p, HEX);
            Serial.print(" ");
        }
        Serial.println();
        Serial.print("encoded = ");
        for (const auto& p : p_buff.data) {
            Serial.print(p, HEX);
            Serial.print(" ");
        }
        Serial.println();
        Serial.print("decoded = ");
        for (const auto& p : p_out.data) {
            Serial.print(p, HEX);
            Serial.print(" ");
        }
        Serial.println();

        if (p_in.data != p_out.data)
            Serial.println("test 4 failed!");
        else
            Serial.println("test 4 success!");
    }
    {
        Packetizer::Packet p_in {0x00, {0x11, 0x00, 0x00, 0x00}};
        const auto& p_buff = Packetizer::encode(p_in.data.data(), p_in.data.size());
        const auto& p_out = Packetizer::decode(p_buff.data.data(), p_buff.data.size());

        Serial.print("input   = ");
        for (const auto& p : p_in.data) {
            Serial.print(p, HEX);
            Serial.print(" ");
        }
        Serial.println();
        Serial.print("encoded = ");
        for (const auto& p : p_buff.data) {
            Serial.print(p, HEX);
            Serial.print(" ");
        }
        Serial.println();
        Serial.print("decoded = ");
        for (const auto& p : p_out.data) {
            Serial.print(p, HEX);
            Serial.print(" ");
        }
        Serial.println();

        if (p_in.data != p_out.data)
            Serial.println("test 5 failed!");
        else
            Serial.println("test 5 success!");
    }
    {
        Packetizer::Packet p_in {0x00, {0xC0, 0xC1, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE}};
        const auto& p_buff = Packetizer::encode(p_in.data.data(), p_in.data.size());
        const auto& p_out = Packetizer::decode(p_buff.data.data(), p_buff.data.size());

        Serial.print("input   = ");
        for (const auto& p : p_in.data) {
            Serial.print(p, HEX);
            Serial.print(" ");
        }
        Serial.println();
        Serial.print("encoded = ");
        for (const auto& p : p_buff.data) {
            Serial.print(p, HEX);
            Serial.print(" ");
        }
        Serial.println();
        Serial.print("decoded = ");
        for (const auto& p : p_out.data) {
            Serial.print(p, HEX);
            Serial.print(" ");
        }
        Serial.println();

        if (p_in.data != p_out.data)
            Serial.println("test 6 failed!");
        else
            Serial.println("test 6 success!");
    }
}

void loop() {
}
