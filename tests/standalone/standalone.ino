#define TEST_NO_SERIAL

#include <Packetizer.h>
#include <cassert>

void callback(const uint8_t* data, const size_t size)
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
    delay(2000);

    Serial.println("test start");

    // no index + no crc ----------------------------------------------------
    // cobs
    {
        std::vector<uint8_t> s_test1 {0x00};
        const auto& se1 = Packetizer::encode(s_test1.data(), s_test1.size());
        const auto& sd1 = Packetizer::decode(se1.data(), se1.size());
        assert(s_test1 == sd1);
    }
    {
        std::vector<uint8_t> s_test2 {0x00, 0x00};
        const auto& se2 = Packetizer::encode(s_test2.data(), s_test2.size());
        const auto& sd2 = Packetizer::decode(se2.data(), se2.size());
        assert(s_test2 == sd2);
    }
    {
        std::vector<uint8_t> s_test3 {0x11, 0x22, 0x00, 0x33};
        const auto& se3 = Packetizer::encode(s_test3.data(), s_test3.size());
        const auto& sd3 = Packetizer::decode(se3.data(), se3.size());
        assert(s_test3 == sd3);
    }
    {
        std::vector<uint8_t> s_test4 {0x11, 0x22, 0x33, 0x44};
        const auto& se4 = Packetizer::encode(s_test4.data(), s_test4.size());
        const auto& sd4 = Packetizer::decode(se4.data(), se4.size());
        assert(s_test4 == sd4);
    }
    {
        std::vector<uint8_t> s_test5 {0x11, 0x00, 0x00, 0x00};
        const auto& se5 = Packetizer::encode(s_test5.data(), s_test5.size());
        const auto& sd5 = Packetizer::decode(se5.data(), se5.size());
        assert(s_test5 == sd5);
    }
    {
        std::vector<uint8_t> s_test6;
        for (size_t i = 0; i < 254; ++i) s_test6.emplace_back(i + 1);
        const auto& se6 = Packetizer::encode(s_test6.data(), s_test6.size());
        const auto& sd6 = Packetizer::decode(se6.data(), se6.size());
        assert(s_test6 == sd6);
    }
    {
        std::vector<uint8_t> s_test7;
        for (size_t i = 0; i < 255; ++i) s_test7.emplace_back(i);
        const auto& se7 = Packetizer::encode(s_test7.data(), s_test7.size());
        const auto& sd7 = Packetizer::decode(se7.data(), se7.size());
        assert(s_test7 == sd7);
    }
    {
        std::vector<uint8_t> s_test8;
        for (size_t i = 0; i < 255; ++i) s_test8.emplace_back(i + 1);
        const auto& se8 = Packetizer::encode(s_test8.data(), s_test8.size());
        const auto& sd8 = Packetizer::decode(se8.data(), se8.size());
        assert(s_test8 == sd8);
    }
    {
        std::vector<uint8_t> s_test9;
        for (size_t i = 0; i < 255; ++i) s_test9.emplace_back(i + 2);
        const auto& se9 = Packetizer::encode(s_test9.data(), s_test9.size());
        const auto& sd9 = Packetizer::decode(se9.data(), se9.size());
        assert(s_test9 == sd9);
    }
    {
        std::vector<uint8_t> s_test10;
        for (size_t i = 0; i < 255; ++i) s_test10.emplace_back(i + 3);
        const auto& se10 = Packetizer::encode(s_test10.data(), s_test10.size());
        const auto& sd10 = Packetizer::decode(se10.data(), se10.size());
        assert(s_test10 == sd10);
    }
    {
        std::vector<uint8_t> s_test11;
        for (size_t i = 0; i < 512; ++i) s_test11.emplace_back(i);
        const auto& se11 = Packetizer::encode(s_test11.data(), s_test11.size());
        const auto& sd11 = Packetizer::decode(se11.data(), se11.size());
        assert(s_test11 == sd11);
    }
    {
        std::vector<uint8_t> s_test12;
        for (size_t i = 0; i < 512; ++i) s_test12.emplace_back(i + 1);
        const auto& se12 = Packetizer::encode(s_test12.data(), s_test12.size());
        const auto& sd12 = Packetizer::decode(se12.data(), se12.size());
        assert(s_test12 == sd12);
    }
    {
        std::vector<uint8_t> s_test13;
        for (size_t i = 0; i < 512; ++i) s_test13.emplace_back(i + 2);
        const auto& se13 = Packetizer::encode(s_test13.data(), s_test13.size());
        const auto& sd13 = Packetizer::decode(se13.data(), se13.size());
        assert(s_test13 == sd13);
    }
    {
        std::vector<uint8_t> s_test14;
        for (size_t i = 0; i < 512; ++i) s_test14.emplace_back(i + 3);
        const auto& se14 = Packetizer::encode(s_test14.data(), s_test14.size());
        const auto& sd14 = Packetizer::decode(se14.data(), se14.size());
        assert(s_test14 == sd14);
    }

    // slip
    {
        std::vector<uint8_t> s_test1 {0x00};
        const auto& se1 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test1.data(), s_test1.size());
        const auto& sd1 = Packetizer::decode<Packetizer::encoding::SLIP>(se1.data(), se1.size());
        assert(s_test1 == sd1);
    }
    {
        std::vector<uint8_t> s_test2 {0x00, 0x00};
        const auto& se2 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test2.data(), s_test2.size());
        const auto& sd2 = Packetizer::decode<Packetizer::encoding::SLIP>(se2.data(), se2.size());
        assert(s_test2 == sd2);
    }
    {
        std::vector<uint8_t> s_test3 {0x11, 0x22, 0x00, 0x33};
        const auto& se3 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test3.data(), s_test3.size());
        const auto& sd3 = Packetizer::decode<Packetizer::encoding::SLIP>(se3.data(), se3.size());
        assert(s_test3 == sd3);
    }
    {
        std::vector<uint8_t> s_test4 {0x11, 0x22, 0x33, 0x44};
        const auto& se4 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test4.data(), s_test4.size());
        const auto& sd4 = Packetizer::decode<Packetizer::encoding::SLIP>(se4.data(), se4.size());
        assert(s_test4 == sd4);
    }
    {
        std::vector<uint8_t> s_test5 {0x11, 0x00, 0x00, 0x00};
        const auto& se5 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test5.data(), s_test5.size());
        const auto& sd5 = Packetizer::decode<Packetizer::encoding::SLIP>(se5.data(), se5.size());
        assert(s_test5 == sd5);
    }
    {
        std::vector<uint8_t> s_test6;
        for (size_t i = 0; i < 254; ++i) s_test6.emplace_back(i + 1);
        const auto& se6 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test6.data(), s_test6.size());
        const auto& sd6 = Packetizer::decode<Packetizer::encoding::SLIP>(se6.data(), se6.size());
        assert(s_test6 == sd6);
    }
    {
        std::vector<uint8_t> s_test7;
        for (size_t i = 0; i < 255; ++i) s_test7.emplace_back(i);
        const auto& se7 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test7.data(), s_test7.size());
        const auto& sd7 = Packetizer::decode<Packetizer::encoding::SLIP>(se7.data(), se7.size());
        assert(s_test7 == sd7);
    }
    {
        std::vector<uint8_t> s_test8;
        for (size_t i = 0; i < 255; ++i) s_test8.emplace_back(i + 1);
        const auto& se8 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test8.data(), s_test8.size());
        const auto& sd8 = Packetizer::decode<Packetizer::encoding::SLIP>(se8.data(), se8.size());
        assert(s_test8 == sd8);
    }
    {
        std::vector<uint8_t> s_test9;
        for (size_t i = 0; i < 255; ++i) s_test9.emplace_back(i + 2);
        const auto& se9 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test9.data(), s_test9.size());
        const auto& sd9 = Packetizer::decode<Packetizer::encoding::SLIP>(se9.data(), se9.size());
        assert(s_test9 == sd9);
    }
    {
        std::vector<uint8_t> s_test10;
        for (size_t i = 0; i < 255; ++i) s_test10.emplace_back(i + 3);
        const auto& se10 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test10.data(), s_test10.size());
        const auto& sd10 = Packetizer::decode<Packetizer::encoding::SLIP>(se10.data(), se10.size());
        assert(s_test10 == sd10);
    }
    {
        std::vector<uint8_t> s_test11;
        for (size_t i = 0; i < 512; ++i) s_test11.emplace_back(i);
        const auto& se11 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test11.data(), s_test11.size());
        const auto& sd11 = Packetizer::decode<Packetizer::encoding::SLIP>(se11.data(), se11.size());
        assert(s_test11 == sd11);
    }
    {
        std::vector<uint8_t> s_test12;
        for (size_t i = 0; i < 512; ++i) s_test12.emplace_back(i + 1);
        const auto& se12 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test12.data(), s_test12.size());
        const auto& sd12 = Packetizer::decode<Packetizer::encoding::SLIP>(se12.data(), se12.size());
        assert(s_test12 == sd12);
    }
    {
        std::vector<uint8_t> s_test13;
        for (size_t i = 0; i < 512; ++i) s_test13.emplace_back(i + 2);
        const auto& se13 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test13.data(), s_test13.size());
        const auto& sd13 = Packetizer::decode<Packetizer::encoding::SLIP>(se13.data(), se13.size());
        assert(s_test13 == sd13);
    }
    {
        std::vector<uint8_t> s_test14;
        for (size_t i = 0; i < 512; ++i) s_test14.emplace_back(i + 3);
        const auto& se14 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test14.data(), s_test14.size());
        const auto& sd14 = Packetizer::decode<Packetizer::encoding::SLIP>(se14.data(), se14.size());
        assert(s_test14 == sd14);
    }

    // index + no crc ----------------------------------------------------
    // cobs
    {
        std::vector<uint8_t> s_test1 {0x00};
        const auto& se1 = Packetizer::encode(0xCC, s_test1.data(), s_test1.size());
        auto decoder = Packetizer::decode(se1.data(), se1.size(), true, false);
        assert(s_test1 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test2 {0x00, 0x00};
        const auto& se2 = Packetizer::encode(0xCC, s_test2.data(), s_test2.size());
        auto decoder = Packetizer::decode(se2.data(), se2.size(), true, false);
        assert(s_test2 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test3 {0x11, 0x22, 0x00, 0x33};
        const auto& se3 = Packetizer::encode(0xCC, s_test3.data(), s_test3.size());
        auto decoder = Packetizer::decode(se3.data(), se3.size(), true, false);
        assert(s_test3 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test4 {0x11, 0x22, 0x33, 0x44};
        const auto& se4 = Packetizer::encode(0xCC, s_test4.data(), s_test4.size());
        auto decoder = Packetizer::decode(se4.data(), se4.size(), true, false);
        assert(s_test4 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test5 {0x11, 0x00, 0x00, 0x00};
        const auto& se5 = Packetizer::encode(0xCC, s_test5.data(), s_test5.size());
        auto decoder = Packetizer::decode(se5.data(), se5.size(), true, false);
        assert(s_test5 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test6;
        for (size_t i = 0; i < 254; ++i) s_test6.emplace_back(i + 1);
        const auto& se6 = Packetizer::encode(0xCC, s_test6.data(), s_test6.size());
        auto decoder = Packetizer::decode(se6.data(), se6.size(), true, false);
        assert(s_test6 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test7;
        for (size_t i = 0; i < 255; ++i) s_test7.emplace_back(i);
        const auto& se7 = Packetizer::encode(0xCC, s_test7.data(), s_test7.size());
        auto decoder = Packetizer::decode(se7.data(), se7.size(), true, false);
        assert(s_test7 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test8;
        for (size_t i = 0; i < 255; ++i) s_test8.emplace_back(i + 1);
        const auto& se8 = Packetizer::encode(0xCC, s_test8.data(), s_test8.size());
        auto decoder = Packetizer::decode(se8.data(), se8.size(), true, false);
        assert(s_test8 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test9;
        for (size_t i = 0; i < 255; ++i) s_test9.emplace_back(i + 2);
        const auto& se9 = Packetizer::encode(0xCC, s_test9.data(), s_test9.size());
        auto decoder = Packetizer::decode(se9.data(), se9.size(), true, false);
        assert(s_test9 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test10;
        for (size_t i = 0; i < 255; ++i) s_test10.emplace_back(i + 3);
        const auto& se10 = Packetizer::encode(0xCC, s_test10.data(), s_test10.size());
        auto decoder = Packetizer::decode(se10.data(), se10.size(), true, false);
        assert(s_test10 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test11;
        for (size_t i = 0; i < 512; ++i) s_test11.emplace_back(i);
        const auto& se11 = Packetizer::encode(0xCC, s_test11.data(), s_test11.size());
        auto decoder = Packetizer::decode(se11.data(), se11.size(), true, false);
        assert(s_test11 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test12;
        for (size_t i = 0; i < 512; ++i) s_test12.emplace_back(i + 1);
        const auto& se12 = Packetizer::encode(0xCC, s_test12.data(), s_test12.size());
        auto decoder = Packetizer::decode(se12.data(), se12.size(), true, false);
        assert(s_test12 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test13;
        for (size_t i = 0; i < 512; ++i) s_test13.emplace_back(i + 2);
        const auto& se13 = Packetizer::encode(0xCC, s_test13.data(), s_test13.size());
        auto decoder = Packetizer::decode(se13.data(), se13.size(), true, false);
        assert(s_test13 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test14;
        for (size_t i = 0; i < 512; ++i) s_test14.emplace_back(i + 3);
        const auto& se14 = Packetizer::encode(0xCC, s_test14.data(), s_test14.size());
        auto decoder = Packetizer::decode(se14.data(), se14.size(), true, false);
        assert(s_test14 == decoder->packet());
        assert(0xCC == decoder->index());
    }

    // slip
    {
        std::vector<uint8_t> s_test1 {0x00};
        const auto& se1 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test1.data(), s_test1.size());
        auto decoder = Packetizer::decode<Packetizer::encoding::SLIP>(se1.data(), se1.size(), true, false);
        assert(s_test1 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test2 {0x00, 0x00};
        const auto& se2 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test2.data(), s_test2.size());
        auto decoder = Packetizer::decode<Packetizer::encoding::SLIP>(se2.data(), se2.size(), true, false);
        assert(s_test2 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test3 {0x11, 0x22, 0x00, 0x33};
        const auto& se3 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test3.data(), s_test3.size());
        auto decoder = Packetizer::decode<Packetizer::encoding::SLIP>(se3.data(), se3.size(), true, false);
        assert(s_test3 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test4 {0x11, 0x22, 0x33, 0x44};
        const auto& se4 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test4.data(), s_test4.size());
        auto decoder = Packetizer::decode<Packetizer::encoding::SLIP>(se4.data(), se4.size(), true, false);
        assert(s_test4 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test5 {0x11, 0x00, 0x00, 0x00};
        const auto& se5 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test5.data(), s_test5.size());
        auto decoder = Packetizer::decode<Packetizer::encoding::SLIP>(se5.data(), se5.size(), true, false);
        assert(s_test5 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test6;
        for (size_t i = 0; i < 254; ++i) s_test6.emplace_back(i + 1);
        const auto& se6 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test6.data(), s_test6.size());
        auto decoder = Packetizer::decode<Packetizer::encoding::SLIP>(se6.data(), se6.size(), true, false);
        assert(s_test6 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test7;
        for (size_t i = 0; i < 255; ++i) s_test7.emplace_back(i);
        const auto& se7 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test7.data(), s_test7.size());
        auto decoder = Packetizer::decode<Packetizer::encoding::SLIP>(se7.data(), se7.size(), true, false);
        assert(s_test7 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test8;
        for (size_t i = 0; i < 255; ++i) s_test8.emplace_back(i + 1);
        const auto& se8 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test8.data(), s_test8.size());
        auto decoder = Packetizer::decode<Packetizer::encoding::SLIP>(se8.data(), se8.size(), true, false);
        assert(s_test8 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test9;
        for (size_t i = 0; i < 255; ++i) s_test9.emplace_back(i + 2);
        const auto& se9 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test9.data(), s_test9.size());
        auto decoder = Packetizer::decode<Packetizer::encoding::SLIP>(se9.data(), se9.size(), true, false);
        assert(s_test9 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test10;
        for (size_t i = 0; i < 255; ++i) s_test10.emplace_back(i + 3);
        const auto& se10 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test10.data(), s_test10.size());
        auto decoder = Packetizer::decode<Packetizer::encoding::SLIP>(se10.data(), se10.size(), true, false);
        assert(s_test10 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test11;
        for (size_t i = 0; i < 512; ++i) s_test11.emplace_back(i);
        const auto& se11 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test11.data(), s_test11.size());
        auto decoder = Packetizer::decode<Packetizer::encoding::SLIP>(se11.data(), se11.size(), true, false);
        assert(s_test11 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test12;
        for (size_t i = 0; i < 512; ++i) s_test12.emplace_back(i + 1);
        const auto& se12 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test12.data(), s_test12.size());
        auto decoder = Packetizer::decode<Packetizer::encoding::SLIP>(se12.data(), se12.size(), true, false);
        assert(s_test12 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test13;
        for (size_t i = 0; i < 512; ++i) s_test13.emplace_back(i + 2);
        const auto& se13 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test13.data(), s_test13.size());
        auto decoder = Packetizer::decode<Packetizer::encoding::SLIP>(se13.data(), se13.size(), true, false);
        assert(s_test13 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test14;
        for (size_t i = 0; i < 512; ++i) s_test14.emplace_back(i + 3);
        const auto& se14 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test14.data(), s_test14.size());
        auto decoder = Packetizer::decode<Packetizer::encoding::SLIP>(se14.data(), se14.size(), true, false);
        assert(s_test14 == decoder->packet());
        assert(0xCC == decoder->index());
    }

    // no index + crc ----------------------------------------------------
    // cobs
    {
        std::vector<uint8_t> s_test1 {0x00};
        const auto& se1 = Packetizer::encode(s_test1.data(), s_test1.size(), true);
        const auto& sd1 = Packetizer::decode(se1.data(), se1.size(), true);
        assert(s_test1 == sd1);
    }
    {
        std::vector<uint8_t> s_test2 {0x00, 0x00};
        const auto& se2 = Packetizer::encode(s_test2.data(), s_test2.size(), true);
        const auto& sd2 = Packetizer::decode(se2.data(), se2.size(), true);
        assert(s_test2 == sd2);
    }
    {
        std::vector<uint8_t> s_test3 {0x11, 0x22, 0x00, 0x33};
        const auto& se3 = Packetizer::encode(s_test3.data(), s_test3.size(), true);
        const auto& sd3 = Packetizer::decode(se3.data(), se3.size(), true);
        assert(s_test3 == sd3);
    }
    {
        std::vector<uint8_t> s_test4 {0x11, 0x22, 0x33, 0x44};
        const auto& se4 = Packetizer::encode(s_test4.data(), s_test4.size(), true);
        const auto& sd4 = Packetizer::decode(se4.data(), se4.size(), true);
        assert(s_test4 == sd4);
    }
    {
        std::vector<uint8_t> s_test5 {0x11, 0x00, 0x00, 0x00};
        const auto& se5 = Packetizer::encode(s_test5.data(), s_test5.size(), true);
        const auto& sd5 = Packetizer::decode(se5.data(), se5.size(), true);
        assert(s_test5 == sd5);
    }
    {
        std::vector<uint8_t> s_test6;
        for (size_t i = 0; i < 254; ++i) s_test6.emplace_back(i + 1);
        const auto& se6 = Packetizer::encode(s_test6.data(), s_test6.size(), true);
        const auto& sd6 = Packetizer::decode(se6.data(), se6.size(), true);
        assert(s_test6 == sd6);
    }
    {
        std::vector<uint8_t> s_test7;
        for (size_t i = 0; i < 255; ++i) s_test7.emplace_back(i);
        const auto& se7 = Packetizer::encode(s_test7.data(), s_test7.size(), true);
        const auto& sd7 = Packetizer::decode(se7.data(), se7.size(), true);
        assert(s_test7 == sd7);
    }
    {
        std::vector<uint8_t> s_test8;
        for (size_t i = 0; i < 255; ++i) s_test8.emplace_back(i + 1);
        const auto& se8 = Packetizer::encode(s_test8.data(), s_test8.size(), true);
        const auto& sd8 = Packetizer::decode(se8.data(), se8.size(), true);
        assert(s_test8 == sd8);
    }
    {
        std::vector<uint8_t> s_test9;
        for (size_t i = 0; i < 255; ++i) s_test9.emplace_back(i + 2);
        const auto& se9 = Packetizer::encode(s_test9.data(), s_test9.size(), true);
        const auto& sd9 = Packetizer::decode(se9.data(), se9.size(), true);
        assert(s_test9 == sd9);
    }
    {
        std::vector<uint8_t> s_test10;
        for (size_t i = 0; i < 255; ++i) s_test10.emplace_back(i + 3);
        const auto& se10 = Packetizer::encode(s_test10.data(), s_test10.size(), true);
        const auto& sd10 = Packetizer::decode(se10.data(), se10.size(), true);
        assert(s_test10 == sd10);
    }
    {
        std::vector<uint8_t> s_test11;
        for (size_t i = 0; i < 512; ++i) s_test11.emplace_back(i);
        const auto& se11 = Packetizer::encode(s_test11.data(), s_test11.size(), true);
        const auto& sd11 = Packetizer::decode(se11.data(), se11.size(), true);
        assert(s_test11 == sd11);
    }
    {
        std::vector<uint8_t> s_test12;
        for (size_t i = 0; i < 512; ++i) s_test12.emplace_back(i + 1);
        const auto& se12 = Packetizer::encode(s_test12.data(), s_test12.size(), true);
        const auto& sd12 = Packetizer::decode(se12.data(), se12.size(), true);
        assert(s_test12 == sd12);
    }
    {
        std::vector<uint8_t> s_test13;
        for (size_t i = 0; i < 512; ++i) s_test13.emplace_back(i + 2);
        const auto& se13 = Packetizer::encode(s_test13.data(), s_test13.size(), true);
        const auto& sd13 = Packetizer::decode(se13.data(), se13.size(), true);
        assert(s_test13 == sd13);
    }
    {
        std::vector<uint8_t> s_test14;
        for (size_t i = 0; i < 512; ++i) s_test14.emplace_back(i + 3);
        const auto& se14 = Packetizer::encode(s_test14.data(), s_test14.size(), true);
        const auto& sd14 = Packetizer::decode(se14.data(), se14.size(), true);
        assert(s_test14 == sd14);
    }

    // slip
    {
        std::vector<uint8_t> s_test1 {0x00};
        const auto& se1 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test1.data(), s_test1.size(), true);
        const auto& sd1 = Packetizer::decode<Packetizer::encoding::SLIP>(se1.data(), se1.size(), true);
        assert(s_test1 == sd1);
    }
    {
        std::vector<uint8_t> s_test2 {0x00, 0x00};
        const auto& se2 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test2.data(), s_test2.size(), true);
        const auto& sd2 = Packetizer::decode<Packetizer::encoding::SLIP>(se2.data(), se2.size(), true);
        assert(s_test2 == sd2);
    }
    {
        std::vector<uint8_t> s_test3 {0x11, 0x22, 0x00, 0x33};
        const auto& se3 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test3.data(), s_test3.size(), true);
        const auto& sd3 = Packetizer::decode<Packetizer::encoding::SLIP>(se3.data(), se3.size(), true);
        assert(s_test3 == sd3);
    }
    {
        std::vector<uint8_t> s_test4 {0x11, 0x22, 0x33, 0x44};
        const auto& se4 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test4.data(), s_test4.size(), true);
        const auto& sd4 = Packetizer::decode<Packetizer::encoding::SLIP>(se4.data(), se4.size(), true);
        assert(s_test4 == sd4);
    }
    {
        std::vector<uint8_t> s_test5 {0x11, 0x00, 0x00, 0x00};
        const auto& se5 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test5.data(), s_test5.size(), true);
        const auto& sd5 = Packetizer::decode<Packetizer::encoding::SLIP>(se5.data(), se5.size(), true);
        assert(s_test5 == sd5);
    }
    {
        std::vector<uint8_t> s_test6;
        for (size_t i = 0; i < 254; ++i) s_test6.emplace_back(i + 1);
        const auto& se6 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test6.data(), s_test6.size(), true);
        const auto& sd6 = Packetizer::decode<Packetizer::encoding::SLIP>(se6.data(), se6.size(), true);
        assert(s_test6 == sd6);
    }
    {
        std::vector<uint8_t> s_test7;
        for (size_t i = 0; i < 255; ++i) s_test7.emplace_back(i);
        const auto& se7 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test7.data(), s_test7.size(), true);
        const auto& sd7 = Packetizer::decode<Packetizer::encoding::SLIP>(se7.data(), se7.size(), true);
        assert(s_test7 == sd7);
    }
    {
        std::vector<uint8_t> s_test8;
        for (size_t i = 0; i < 255; ++i) s_test8.emplace_back(i + 1);
        const auto& se8 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test8.data(), s_test8.size(), true);
        const auto& sd8 = Packetizer::decode<Packetizer::encoding::SLIP>(se8.data(), se8.size(), true);
        assert(s_test8 == sd8);
    }
    {
        std::vector<uint8_t> s_test9;
        for (size_t i = 0; i < 255; ++i) s_test9.emplace_back(i + 2);
        const auto& se9 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test9.data(), s_test9.size(), true);
        const auto& sd9 = Packetizer::decode<Packetizer::encoding::SLIP>(se9.data(), se9.size(), true);
        assert(s_test9 == sd9);
    }
    {
        std::vector<uint8_t> s_test10;
        for (size_t i = 0; i < 255; ++i) s_test10.emplace_back(i + 3);
        const auto& se10 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test10.data(), s_test10.size(), true);
        const auto& sd10 = Packetizer::decode<Packetizer::encoding::SLIP>(se10.data(), se10.size(), true);
        assert(s_test10 == sd10);
    }
    {
        std::vector<uint8_t> s_test11;
        for (size_t i = 0; i < 512; ++i) s_test11.emplace_back(i);
        const auto& se11 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test11.data(), s_test11.size(), true);
        const auto& sd11 = Packetizer::decode<Packetizer::encoding::SLIP>(se11.data(), se11.size(), true);
        assert(s_test11 == sd11);
    }
    {
        std::vector<uint8_t> s_test12;
        for (size_t i = 0; i < 512; ++i) s_test12.emplace_back(i + 1);
        const auto& se12 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test12.data(), s_test12.size(), true);
        const auto& sd12 = Packetizer::decode<Packetizer::encoding::SLIP>(se12.data(), se12.size(), true);
        assert(s_test12 == sd12);
    }
    {
        std::vector<uint8_t> s_test13;
        for (size_t i = 0; i < 512; ++i) s_test13.emplace_back(i + 2);
        const auto& se13 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test13.data(), s_test13.size(), true);
        const auto& sd13 = Packetizer::decode<Packetizer::encoding::SLIP>(se13.data(), se13.size(), true);
        assert(s_test13 == sd13);
    }
    {
        std::vector<uint8_t> s_test14;
        for (size_t i = 0; i < 512; ++i) s_test14.emplace_back(i + 3);
        const auto& se14 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test14.data(), s_test14.size(), true);
        const auto& sd14 = Packetizer::decode<Packetizer::encoding::SLIP>(se14.data(), se14.size(), true);
        assert(s_test14 == sd14);
    }

    // index + crc ----------------------------------------------------
    // cobs
    {
        std::vector<uint8_t> s_test1 {0x00};
        const auto& se1 = Packetizer::encode(0xCC, s_test1.data(), s_test1.size(), true);
        auto decoder = Packetizer::decode(se1.data(), se1.size(), true, true);
        assert(s_test1 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test2 {0x00, 0x00};
        const auto& se2 = Packetizer::encode(0xCC, s_test2.data(), s_test2.size(), true);
        auto decoder = Packetizer::decode(se2.data(), se2.size(), true, true);
        assert(s_test2 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test3 {0x11, 0x22, 0x00, 0x33};
        const auto& se3 = Packetizer::encode(0xCC, s_test3.data(), s_test3.size(), true);
        auto decoder = Packetizer::decode(se3.data(), se3.size(), true, true);
        assert(s_test3 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test4 {0x11, 0x22, 0x33, 0x44};
        const auto& se4 = Packetizer::encode(0xCC, s_test4.data(), s_test4.size(), true);
        auto decoder = Packetizer::decode(se4.data(), se4.size(), true, true);
        assert(s_test4 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test5 {0x11, 0x00, 0x00, 0x00};
        const auto& se5 = Packetizer::encode(0xCC, s_test5.data(), s_test5.size(), true);
        auto decoder = Packetizer::decode(se5.data(), se5.size(), true, true);
        assert(s_test5 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test6;
        for (size_t i = 0; i < 254; ++i) s_test6.emplace_back(i + 1);
        const auto& se6 = Packetizer::encode(0xCC, s_test6.data(), s_test6.size(), true);
        auto decoder = Packetizer::decode(se6.data(), se6.size(), true, true);
        assert(s_test6 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test7;
        for (size_t i = 0; i < 255; ++i) s_test7.emplace_back(i);
        const auto& se7 = Packetizer::encode(0xCC, s_test7.data(), s_test7.size(), true);
        auto decoder = Packetizer::decode(se7.data(), se7.size(), true, true);
        assert(s_test7 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test8;
        for (size_t i = 0; i < 255; ++i) s_test8.emplace_back(i + 1);
        const auto& se8 = Packetizer::encode(0xCC, s_test8.data(), s_test8.size(), true);
        auto decoder = Packetizer::decode(se8.data(), se8.size(), true, true);
        assert(s_test8 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test9;
        for (size_t i = 0; i < 255; ++i) s_test9.emplace_back(i + 2);
        const auto& se9 = Packetizer::encode(0xCC, s_test9.data(), s_test9.size(), true);
        auto decoder = Packetizer::decode(se9.data(), se9.size(), true, true);
        assert(s_test9 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test10;
        for (size_t i = 0; i < 255; ++i) s_test10.emplace_back(i + 3);
        const auto& se10 = Packetizer::encode(0xCC, s_test10.data(), s_test10.size(), true);
        auto decoder = Packetizer::decode(se10.data(), se10.size(), true, true);
        assert(s_test10 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test11;
        for (size_t i = 0; i < 512; ++i) s_test11.emplace_back(i);
        const auto& se11 = Packetizer::encode(0xCC, s_test11.data(), s_test11.size(), true);
        auto decoder = Packetizer::decode(se11.data(), se11.size(), true, true);
        assert(s_test11 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test12;
        for (size_t i = 0; i < 512; ++i) s_test12.emplace_back(i + 1);
        const auto& se12 = Packetizer::encode(0xCC, s_test12.data(), s_test12.size(), true);
        auto decoder = Packetizer::decode(se12.data(), se12.size(), true, true);
        assert(s_test12 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test13;
        for (size_t i = 0; i < 512; ++i) s_test13.emplace_back(i + 2);
        const auto& se13 = Packetizer::encode(0xCC, s_test13.data(), s_test13.size(), true);
        auto decoder = Packetizer::decode(se13.data(), se13.size(), true, true);
        assert(s_test13 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test14;
        for (size_t i = 0; i < 512; ++i) s_test14.emplace_back(i + 3);
        const auto& se14 = Packetizer::encode(0xCC, s_test14.data(), s_test14.size(), true);
        auto decoder = Packetizer::decode(se14.data(), se14.size(), true, true);
        assert(s_test14 == decoder->packet());
        assert(0xCC == decoder->index());
    }

    // slip
    {
        std::vector<uint8_t> s_test1 {0x00};
        const auto& se1 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test1.data(), s_test1.size(), true);
        auto decoder = Packetizer::decode<Packetizer::encoding::SLIP>(se1.data(), se1.size(), true, true);
        assert(s_test1 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test2 {0x00, 0x00};
        const auto& se2 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test2.data(), s_test2.size(), true);
        auto decoder = Packetizer::decode<Packetizer::encoding::SLIP>(se2.data(), se2.size(), true, true);
        assert(s_test2 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test3 {0x11, 0x22, 0x00, 0x33};
        const auto& se3 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test3.data(), s_test3.size(), true);
        auto decoder = Packetizer::decode<Packetizer::encoding::SLIP>(se3.data(), se3.size(), true, true);
        assert(s_test3 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test4 {0x11, 0x22, 0x33, 0x44};
        const auto& se4 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test4.data(), s_test4.size(), true);
        auto decoder = Packetizer::decode<Packetizer::encoding::SLIP>(se4.data(), se4.size(), true, true);
        assert(s_test4 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test5 {0x11, 0x00, 0x00, 0x00};
        const auto& se5 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test5.data(), s_test5.size(), true);
        auto decoder = Packetizer::decode<Packetizer::encoding::SLIP>(se5.data(), se5.size(), true, true);
        assert(s_test5 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test6;
        for (size_t i = 0; i < 254; ++i) s_test6.emplace_back(i + 1);
        const auto& se6 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test6.data(), s_test6.size(), true);
        auto decoder = Packetizer::decode<Packetizer::encoding::SLIP>(se6.data(), se6.size(), true, true);
        assert(s_test6 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test7;
        for (size_t i = 0; i < 255; ++i) s_test7.emplace_back(i);
        const auto& se7 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test7.data(), s_test7.size(), true);
        auto decoder = Packetizer::decode<Packetizer::encoding::SLIP>(se7.data(), se7.size(), true, true);
        assert(s_test7 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test8;
        for (size_t i = 0; i < 255; ++i) s_test8.emplace_back(i + 1);
        const auto& se8 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test8.data(), s_test8.size(), true);
        auto decoder = Packetizer::decode<Packetizer::encoding::SLIP>(se8.data(), se8.size(), true, true);
        assert(s_test8 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test9;
        for (size_t i = 0; i < 255; ++i) s_test9.emplace_back(i + 2);
        const auto& se9 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test9.data(), s_test9.size(), true);
        auto decoder = Packetizer::decode<Packetizer::encoding::SLIP>(se9.data(), se9.size(), true, true);
        assert(s_test9 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test10;
        for (size_t i = 0; i < 255; ++i) s_test10.emplace_back(i + 3);
        const auto& se10 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test10.data(), s_test10.size(), true);
        auto decoder = Packetizer::decode<Packetizer::encoding::SLIP>(se10.data(), se10.size(), true, true);
        assert(s_test10 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test11;
        for (size_t i = 0; i < 512; ++i) s_test11.emplace_back(i);
        const auto& se11 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test11.data(), s_test11.size(), true);
        auto decoder = Packetizer::decode<Packetizer::encoding::SLIP>(se11.data(), se11.size(), true, true);
        assert(s_test11 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test12;
        for (size_t i = 0; i < 512; ++i) s_test12.emplace_back(i + 1);
        const auto& se12 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test12.data(), s_test12.size(), true);
        auto decoder = Packetizer::decode<Packetizer::encoding::SLIP>(se12.data(), se12.size(), true, true);
        assert(s_test12 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test13;
        for (size_t i = 0; i < 512; ++i) s_test13.emplace_back(i + 2);
        const auto& se13 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test13.data(), s_test13.size(), true);
        auto decoder = Packetizer::decode<Packetizer::encoding::SLIP>(se13.data(), se13.size(), true, true);
        assert(s_test13 == decoder->packet());
        assert(0xCC == decoder->index());
    }
    {
        std::vector<uint8_t> s_test14;
        for (size_t i = 0; i < 512; ++i) s_test14.emplace_back(i + 3);
        const auto& se14 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test14.data(), s_test14.size(), true);
        auto decoder = Packetizer::decode<Packetizer::encoding::SLIP>(se14.data(), se14.size(), true, true);
        assert(s_test14 == decoder->packet());
        assert(0xCC == decoder->index());
    }

    // callback w/ no index + no crc ----------------------------------------------------
    // cobs
    {
        bool b_success {false};
        std::vector<uint8_t> vs;
        for (size_t i = 0; i < 254; ++i) vs.emplace_back(i + 1);
        const auto& p = Packetizer::encode(vs.data(), vs.size());
        Packetizer::options(false, false);
        Packetizer::subscribe([&](const uint8_t* data, const size_t size)
        {
            std::vector<uint8_t> rs;
            for (size_t i = 0; i < size; ++i) rs.emplace_back(data[i]);
            b_success = (vs == rs);
        });
        Packetizer::feed(p.data(), p.size());
        assert(b_success);
        Packetizer::unsubscribe();
    }
    // slip
    {
        bool b_success {false};
        std::vector<uint8_t> vs;
        for (size_t i = 0; i < 254; ++i) vs.emplace_back(i + 1);
        const auto& p = Packetizer::encode<Packetizer::encoding::SLIP>(vs.data(), vs.size());
        Packetizer::options<Packetizer::encoding::SLIP>(false, false);
        Packetizer::subscribe<Packetizer::encoding::SLIP>([&](const uint8_t* data, const size_t size)
        {
            std::vector<uint8_t> rs;
            for (size_t i = 0; i < size; ++i) rs.emplace_back(data[i]);
            b_success = (vs == rs);
        });
        Packetizer::feed<Packetizer::encoding::SLIP>(p.data(), p.size());
        assert(b_success);
        Packetizer::unsubscribe<Packetizer::encoding::SLIP>();
    }

    // callback w/ no index + crc ----------------------------------------------------
    // cobs
    {
        bool b_success {false};
        std::vector<uint8_t> vs;
        for (size_t i = 0; i < 254; ++i) vs.emplace_back(i + 1);
        const auto& p = Packetizer::encode(vs.data(), vs.size(), true);
        Packetizer::options(false, true);
        Packetizer::subscribe([&](const uint8_t* data, const size_t size)
        {
            std::vector<uint8_t> rs;
            for (size_t i = 0; i < size; ++i) rs.emplace_back(data[i]);
            b_success = (vs == rs);
        });
        Packetizer::feed(p.data(), p.size());
        assert(b_success);
        Packetizer::unsubscribe();
    }
    // slip
    {
        bool b_success {false};
        std::vector<uint8_t> vs;
        for (size_t i = 0; i < 254; ++i) vs.emplace_back(i + 1);
        const auto& p = Packetizer::encode<Packetizer::encoding::SLIP>(vs.data(), vs.size(), true);
        Packetizer::options<Packetizer::encoding::SLIP>(false, true);
        Packetizer::subscribe<Packetizer::encoding::SLIP>([&](const uint8_t* data, const size_t size)
        {
            std::vector<uint8_t> rs;
            for (size_t i = 0; i < size; ++i) rs.emplace_back(data[i]);
            b_success = (vs == rs);
        });
        Packetizer::feed<Packetizer::encoding::SLIP>(p.data(), p.size());
        assert(b_success);
        Packetizer::unsubscribe<Packetizer::encoding::SLIP>();
    }

    // callback w/ index + no crc ----------------------------------------------------
    // cobs
    {
        bool b_success {false};
        std::vector<uint8_t> vs;
        for (size_t i = 0; i < 254; ++i) vs.emplace_back(i + 1);
        const auto& p = Packetizer::encode(0xCC, vs.data(), vs.size());
        Packetizer::options(true, false);
        Packetizer::subscribe(0xCC, [&](const uint8_t* data, const size_t size)
        {
            std::vector<uint8_t> rs;
            for (size_t i = 0; i < size; ++i) rs.emplace_back(data[i]);
            b_success = (vs == rs);
        });
        Packetizer::feed(p.data(), p.size());
        assert(b_success);
        Packetizer::unsubscribe(0xCC);
    }
    // slip
    {
        bool b_success {false};
        std::vector<uint8_t> vs;
        for (size_t i = 0; i < 254; ++i) vs.emplace_back(i + 1);
        const auto& p = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, vs.data(), vs.size());
        Packetizer::options<Packetizer::encoding::SLIP>(true, false);
        Packetizer::subscribe<Packetizer::encoding::SLIP>(0xCC, [&](const uint8_t* data, const size_t size)
        {
            std::vector<uint8_t> rs;
            for (size_t i = 0; i < size; ++i) rs.emplace_back(data[i]);
            b_success = (vs == rs);
        });
        Packetizer::feed<Packetizer::encoding::SLIP>(p.data(), p.size());
        assert(b_success);
        Packetizer::unsubscribe<Packetizer::encoding::SLIP>(0xCC);
    }

    // callback w/ index + crc ----------------------------------------------------
    // cobs
    {
        bool b_success {false};
        std::vector<uint8_t> vs;
        for (size_t i = 0; i < 254; ++i) vs.emplace_back(i + 1);
        const auto& p = Packetizer::encode(0xCC, vs.data(), vs.size(), true);
        Packetizer::options(true, true);
        Packetizer::subscribe(0xCC, [&](const uint8_t* data, const size_t size)
        {
            std::vector<uint8_t> rs;
            for (size_t i = 0; i < size; ++i) rs.emplace_back(data[i]);
            b_success = (vs == rs);
        });
        Packetizer::feed(p.data(), p.size());
        assert(b_success);
        Packetizer::unsubscribe(0xCC);
    }
    // slip
    {
        bool b_success {false};
        std::vector<uint8_t> vs;
        for (size_t i = 0; i < 254; ++i) vs.emplace_back(i + 1);
        const auto& p = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, vs.data(), vs.size(), true);
        Packetizer::options<Packetizer::encoding::SLIP>(true, true);
        Packetizer::subscribe<Packetizer::encoding::SLIP>(0xCC, [&](const uint8_t* data, const size_t size)
        {
            std::vector<uint8_t> rs;
            for (size_t i = 0; i < size; ++i) rs.emplace_back(data[i]);
            b_success = (vs == rs);
        });
        Packetizer::feed<Packetizer::encoding::SLIP>(p.data(), p.size());
        assert(b_success);
        Packetizer::unsubscribe<Packetizer::encoding::SLIP>(0xCC);
    }


    // callback w/ no index + no crc ----------------------------------------------------
    // cobs
    Packetizer::global_options(false, false);
    {
        bool b_success {false};
        std::vector<uint8_t> vs;
        for (size_t i = 0; i < 254; ++i) vs.emplace_back(i + 1);
        const auto& p = Packetizer::encode(vs.data(), vs.size());
        Packetizer::subscribe([&](const uint8_t* data, const size_t size)
        {
            std::vector<uint8_t> rs;
            for (size_t i = 0; i < size; ++i) rs.emplace_back(data[i]);
            b_success = (vs == rs);
        });
        Packetizer::feed(p.data(), p.size());
        assert(b_success);
        Packetizer::unsubscribe();
    }
    // slip
    Packetizer::global_options<Packetizer::encoding::SLIP>(false, false);
    {
        bool b_success {false};
        std::vector<uint8_t> vs;
        for (size_t i = 0; i < 254; ++i) vs.emplace_back(i + 1);
        const auto& p = Packetizer::encode<Packetizer::encoding::SLIP>(vs.data(), vs.size());
        Packetizer::subscribe<Packetizer::encoding::SLIP>([&](const uint8_t* data, const size_t size)
        {
            std::vector<uint8_t> rs;
            for (size_t i = 0; i < size; ++i) rs.emplace_back(data[i]);
            b_success = (vs == rs);
        });
        Packetizer::feed<Packetizer::encoding::SLIP>(p.data(), p.size());
        assert(b_success);
        Packetizer::unsubscribe<Packetizer::encoding::SLIP>();
    }

    // callback w/ no index + crc ----------------------------------------------------
    // cobs
    Packetizer::global_options(false, true);
    {
        bool b_success {false};
        std::vector<uint8_t> vs;
        for (size_t i = 0; i < 254; ++i) vs.emplace_back(i + 1);
        const auto& p = Packetizer::encode(vs.data(), vs.size(), true);
        Packetizer::subscribe([&](const uint8_t* data, const size_t size)
        {
            std::vector<uint8_t> rs;
            for (size_t i = 0; i < size; ++i) rs.emplace_back(data[i]);
            b_success = (vs == rs);
        });
        Packetizer::feed(p.data(), p.size());
        assert(b_success);
        Packetizer::unsubscribe();
    }
    // slip
    Packetizer::global_options<Packetizer::encoding::SLIP>(false, true);
    {
        bool b_success {false};
        std::vector<uint8_t> vs;
        for (size_t i = 0; i < 254; ++i) vs.emplace_back(i + 1);
        const auto& p = Packetizer::encode<Packetizer::encoding::SLIP>(vs.data(), vs.size(), true);
        Packetizer::subscribe<Packetizer::encoding::SLIP>([&](const uint8_t* data, const size_t size)
        {
            std::vector<uint8_t> rs;
            for (size_t i = 0; i < size; ++i) rs.emplace_back(data[i]);
            b_success = (vs == rs);
        });
        Packetizer::feed<Packetizer::encoding::SLIP>(p.data(), p.size());
        assert(b_success);
        Packetizer::unsubscribe<Packetizer::encoding::SLIP>();
    }

    // callback w/ index + no crc ----------------------------------------------------
    // cobs
    Packetizer::global_options(true, false);
    {
        bool b_success {false};
        std::vector<uint8_t> vs;
        for (size_t i = 0; i < 254; ++i) vs.emplace_back(i + 1);
        const auto& p = Packetizer::encode(0xCC, vs.data(), vs.size());
        Packetizer::options(true, false);
        Packetizer::subscribe(0xCC, [&](const uint8_t* data, const size_t size)
        {
            std::vector<uint8_t> rs;
            for (size_t i = 0; i < size; ++i) rs.emplace_back(data[i]);
            b_success = (vs == rs);
        });
        Packetizer::feed(p.data(), p.size());
        assert(b_success);
        Packetizer::unsubscribe(0xCC);
    }
    // slip
    Packetizer::global_options<Packetizer::encoding::SLIP>(true, false);
    {
        bool b_success {false};
        std::vector<uint8_t> vs;
        for (size_t i = 0; i < 254; ++i) vs.emplace_back(i + 1);
        const auto& p = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, vs.data(), vs.size());
        Packetizer::options<Packetizer::encoding::SLIP>(true, false);
        Packetizer::subscribe<Packetizer::encoding::SLIP>(0xCC, [&](const uint8_t* data, const size_t size)
        {
            std::vector<uint8_t> rs;
            for (size_t i = 0; i < size; ++i) rs.emplace_back(data[i]);
            b_success = (vs == rs);
        });
        Packetizer::feed<Packetizer::encoding::SLIP>(p.data(), p.size());
        assert(b_success);
        Packetizer::unsubscribe<Packetizer::encoding::SLIP>(0xCC);
    }

    // callback w/ index + crc ----------------------------------------------------
    // cobs
    Packetizer::global_options(true, true);
    {
        bool b_success {false};
        std::vector<uint8_t> vs;
        for (size_t i = 0; i < 254; ++i) vs.emplace_back(i + 1);
        const auto& p = Packetizer::encode(0xCC, vs.data(), vs.size(), true);
        Packetizer::options(true, true);
        Packetizer::subscribe(0xCC, [&](const uint8_t* data, const size_t size)
        {
            std::vector<uint8_t> rs;
            for (size_t i = 0; i < size; ++i) rs.emplace_back(data[i]);
            b_success = (vs == rs);
        });
        Packetizer::feed(p.data(), p.size());
        assert(b_success);
        Packetizer::unsubscribe(0xCC);
    }
    // slip
    Packetizer::global_options<Packetizer::encoding::SLIP>(true, true);
    {
        bool b_success {false};
        std::vector<uint8_t> vs;
        for (size_t i = 0; i < 254; ++i) vs.emplace_back(i + 1);
        const auto& p = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, vs.data(), vs.size(), true);
        Packetizer::options<Packetizer::encoding::SLIP>(true, true);
        Packetizer::subscribe<Packetizer::encoding::SLIP>(0xCC, [&](const uint8_t* data, const size_t size)
        {
            std::vector<uint8_t> rs;
            for (size_t i = 0; i < size; ++i) rs.emplace_back(data[i]);
            b_success = (vs == rs);
        });
        Packetizer::feed<Packetizer::encoding::SLIP>(p.data(), p.size());
        assert(b_success);
        Packetizer::unsubscribe<Packetizer::encoding::SLIP>(0xCC);
    }

    Serial.println("test finished");
}

void loop()
{
}

