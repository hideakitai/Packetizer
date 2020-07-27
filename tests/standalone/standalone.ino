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
        const auto& sd1 = Packetizer::decode(se1.data.data(), se1.data.size());
        assert(s_test1 == sd1.data);
    }
    {
        std::vector<uint8_t> s_test2 {0x00, 0x00};
        const auto& se2 = Packetizer::encode(s_test2.data(), s_test2.size());
        const auto& sd2 = Packetizer::decode(se2.data.data(), se2.data.size());
        assert(s_test2 == sd2.data);
    }
    {
        std::vector<uint8_t> s_test3 {0x11, 0x22, 0x00, 0x33};
        const auto& se3 = Packetizer::encode(s_test3.data(), s_test3.size());
        const auto& sd3 = Packetizer::decode(se3.data.data(), se3.data.size());
        assert(s_test3 == sd3.data);
    }
    {
        std::vector<uint8_t> s_test4 {0x11, 0x22, 0x33, 0x44};
        const auto& se4 = Packetizer::encode(s_test4.data(), s_test4.size());
        const auto& sd4 = Packetizer::decode(se4.data.data(), se4.data.size());
        assert(s_test4 == sd4.data);
    }
    {
        std::vector<uint8_t> s_test5 {0x11, 0x00, 0x00, 0x00};
        const auto& se5 = Packetizer::encode(s_test5.data(), s_test5.size());
        const auto& sd5 = Packetizer::decode(se5.data.data(), se5.data.size());
        assert(s_test5 == sd5.data);
    }
    {
        std::vector<uint8_t> s_test6;
        for (size_t i = 0; i < 254; ++i) s_test6.emplace_back(i + 1);
        const auto& se6 = Packetizer::encode(s_test6.data(), s_test6.size());
        const auto& sd6 = Packetizer::decode(se6.data.data(), se6.data.size());
        assert(s_test6 == sd6.data);
    }
    {
        std::vector<uint8_t> s_test7;
        for (size_t i = 0; i < 255; ++i) s_test7.emplace_back(i);
        const auto& se7 = Packetizer::encode(s_test7.data(), s_test7.size());
        const auto& sd7 = Packetizer::decode(se7.data.data(), se7.data.size());
        assert(s_test7 == sd7.data);
    }
    {
        std::vector<uint8_t> s_test8;
        for (size_t i = 0; i < 255; ++i) s_test8.emplace_back(i + 1);
        const auto& se8 = Packetizer::encode(s_test8.data(), s_test8.size());
        const auto& sd8 = Packetizer::decode(se8.data.data(), se8.data.size());
        assert(s_test8 == sd8.data);
    }
    {
        std::vector<uint8_t> s_test9;
        for (size_t i = 0; i < 255; ++i) s_test9.emplace_back(i + 2);
        const auto& se9 = Packetizer::encode(s_test9.data(), s_test9.size());
        const auto& sd9 = Packetizer::decode(se9.data.data(), se9.data.size());
        assert(s_test9 == sd9.data);
    }
    {
        std::vector<uint8_t> s_test10;
        for (size_t i = 0; i < 255; ++i) s_test10.emplace_back(i + 3);
        const auto& se10 = Packetizer::encode(s_test10.data(), s_test10.size());
        const auto& sd10 = Packetizer::decode(se10.data.data(), se10.data.size());
        assert(s_test10 == sd10.data);
    }
    {
        std::vector<uint8_t> s_test11;
        for (size_t i = 0; i < 512; ++i) s_test11.emplace_back(i);
        const auto& se11 = Packetizer::encode(s_test11.data(), s_test11.size());
        const auto& sd11 = Packetizer::decode(se11.data.data(), se11.data.size());
        assert(s_test11 == sd11.data);
    }
    {
        std::vector<uint8_t> s_test12;
        for (size_t i = 0; i < 512; ++i) s_test12.emplace_back(i + 1);
        const auto& se12 = Packetizer::encode(s_test12.data(), s_test12.size());
        const auto& sd12 = Packetizer::decode(se12.data.data(), se12.data.size());
        assert(s_test12 == sd12.data);
    }
    {
        std::vector<uint8_t> s_test13;
        for (size_t i = 0; i < 512; ++i) s_test13.emplace_back(i + 2);
        const auto& se13 = Packetizer::encode(s_test13.data(), s_test13.size());
        const auto& sd13 = Packetizer::decode(se13.data.data(), se13.data.size());
        assert(s_test13 == sd13.data);
    }
    {
        std::vector<uint8_t> s_test14;
        for (size_t i = 0; i < 512; ++i) s_test14.emplace_back(i + 3);
        const auto& se14 = Packetizer::encode(s_test14.data(), s_test14.size());
        const auto& sd14 = Packetizer::decode(se14.data.data(), se14.data.size());
        assert(s_test14 == sd14.data);
    }

    // slip
    {
        std::vector<uint8_t> s_test1 {0x00};
        const auto& se1 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test1.data(), s_test1.size());
        const auto& sd1 = Packetizer::decode<Packetizer::encoding::SLIP>(se1.data.data(), se1.data.size());
        assert(s_test1 == sd1.data);
    }
    {
        std::vector<uint8_t> s_test2 {0x00, 0x00};
        const auto& se2 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test2.data(), s_test2.size());
        const auto& sd2 = Packetizer::decode<Packetizer::encoding::SLIP>(se2.data.data(), se2.data.size());
        assert(s_test2 == sd2.data);
    }
    {
        std::vector<uint8_t> s_test3 {0x11, 0x22, 0x00, 0x33};
        const auto& se3 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test3.data(), s_test3.size());
        const auto& sd3 = Packetizer::decode<Packetizer::encoding::SLIP>(se3.data.data(), se3.data.size());
        assert(s_test3 == sd3.data);
    }
    {
        std::vector<uint8_t> s_test4 {0x11, 0x22, 0x33, 0x44};
        const auto& se4 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test4.data(), s_test4.size());
        const auto& sd4 = Packetizer::decode<Packetizer::encoding::SLIP>(se4.data.data(), se4.data.size());
        assert(s_test4 == sd4.data);
    }
    {
        std::vector<uint8_t> s_test5 {0x11, 0x00, 0x00, 0x00};
        const auto& se5 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test5.data(), s_test5.size());
        const auto& sd5 = Packetizer::decode<Packetizer::encoding::SLIP>(se5.data.data(), se5.data.size());
        assert(s_test5 == sd5.data);
    }
    {
        std::vector<uint8_t> s_test6;
        for (size_t i = 0; i < 254; ++i) s_test6.emplace_back(i + 1);
        const auto& se6 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test6.data(), s_test6.size());
        const auto& sd6 = Packetizer::decode<Packetizer::encoding::SLIP>(se6.data.data(), se6.data.size());
        assert(s_test6 == sd6.data);
    }
    {
        std::vector<uint8_t> s_test7;
        for (size_t i = 0; i < 255; ++i) s_test7.emplace_back(i);
        const auto& se7 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test7.data(), s_test7.size());
        const auto& sd7 = Packetizer::decode<Packetizer::encoding::SLIP>(se7.data.data(), se7.data.size());
        assert(s_test7 == sd7.data);
    }
    {
        std::vector<uint8_t> s_test8;
        for (size_t i = 0; i < 255; ++i) s_test8.emplace_back(i + 1);
        const auto& se8 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test8.data(), s_test8.size());
        const auto& sd8 = Packetizer::decode<Packetizer::encoding::SLIP>(se8.data.data(), se8.data.size());
        assert(s_test8 == sd8.data);
    }
    {
        std::vector<uint8_t> s_test9;
        for (size_t i = 0; i < 255; ++i) s_test9.emplace_back(i + 2);
        const auto& se9 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test9.data(), s_test9.size());
        const auto& sd9 = Packetizer::decode<Packetizer::encoding::SLIP>(se9.data.data(), se9.data.size());
        assert(s_test9 == sd9.data);
    }
    {
        std::vector<uint8_t> s_test10;
        for (size_t i = 0; i < 255; ++i) s_test10.emplace_back(i + 3);
        const auto& se10 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test10.data(), s_test10.size());
        const auto& sd10 = Packetizer::decode<Packetizer::encoding::SLIP>(se10.data.data(), se10.data.size());
        assert(s_test10 == sd10.data);
    }
    {
        std::vector<uint8_t> s_test11;
        for (size_t i = 0; i < 512; ++i) s_test11.emplace_back(i);
        const auto& se11 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test11.data(), s_test11.size());
        const auto& sd11 = Packetizer::decode<Packetizer::encoding::SLIP>(se11.data.data(), se11.data.size());
        assert(s_test11 == sd11.data);
    }
    {
        std::vector<uint8_t> s_test12;
        for (size_t i = 0; i < 512; ++i) s_test12.emplace_back(i + 1);
        const auto& se12 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test12.data(), s_test12.size());
        const auto& sd12 = Packetizer::decode<Packetizer::encoding::SLIP>(se12.data.data(), se12.data.size());
        assert(s_test12 == sd12.data);
    }
    {
        std::vector<uint8_t> s_test13;
        for (size_t i = 0; i < 512; ++i) s_test13.emplace_back(i + 2);
        const auto& se13 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test13.data(), s_test13.size());
        const auto& sd13 = Packetizer::decode<Packetizer::encoding::SLIP>(se13.data.data(), se13.data.size());
        assert(s_test13 == sd13.data);
    }
    {
        std::vector<uint8_t> s_test14;
        for (size_t i = 0; i < 512; ++i) s_test14.emplace_back(i + 3);
        const auto& se14 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test14.data(), s_test14.size());
        const auto& sd14 = Packetizer::decode<Packetizer::encoding::SLIP>(se14.data.data(), se14.data.size());
        assert(s_test14 == sd14.data);
    }

    // index + no crc ----------------------------------------------------
    // cobs
    {
        std::vector<uint8_t> s_test1 {0x00};
        const auto& se1 = Packetizer::encode(0xCC, s_test1.data(), s_test1.size());
        const auto& sd1 = Packetizer::decode(se1.data.data(), se1.data.size(), true, false);
        assert(s_test1 == sd1.data);
        assert(0xCC == sd1.index);
    }
    {
        std::vector<uint8_t> s_test2 {0x00, 0x00};
        const auto& se2 = Packetizer::encode(0xCC, s_test2.data(), s_test2.size());
        const auto& sd2 = Packetizer::decode(se2.data.data(), se2.data.size(), true, false);
        assert(s_test2 == sd2.data);
        assert(0xCC == sd2.index);
    }
    {
        std::vector<uint8_t> s_test3 {0x11, 0x22, 0x00, 0x33};
        const auto& se3 = Packetizer::encode(0xCC, s_test3.data(), s_test3.size());
        const auto& sd3 = Packetizer::decode(se3.data.data(), se3.data.size(), true, false);
        assert(s_test3 == sd3.data);
        assert(0xCC == sd3.index);
    }
    {
        std::vector<uint8_t> s_test4 {0x11, 0x22, 0x33, 0x44};
        const auto& se4 = Packetizer::encode(0xCC, s_test4.data(), s_test4.size());
        const auto& sd4 = Packetizer::decode(se4.data.data(), se4.data.size(), true, false);
        assert(s_test4 == sd4.data);
        assert(0xCC == sd4.index);
    }
    {
        std::vector<uint8_t> s_test5 {0x11, 0x00, 0x00, 0x00};
        const auto& se5 = Packetizer::encode(0xCC, s_test5.data(), s_test5.size());
        const auto& sd5 = Packetizer::decode(se5.data.data(), se5.data.size(), true, false);
        assert(s_test5 == sd5.data);
        assert(0xCC == sd5.index);
    }
    {
        std::vector<uint8_t> s_test6;
        for (size_t i = 0; i < 254; ++i) s_test6.emplace_back(i + 1);
        const auto& se6 = Packetizer::encode(0xCC, s_test6.data(), s_test6.size());
        const auto& sd6 = Packetizer::decode(se6.data.data(), se6.data.size(), true, false);
        assert(s_test6 == sd6.data);
        assert(0xCC == sd6.index);
    }
    {
        std::vector<uint8_t> s_test7;
        for (size_t i = 0; i < 255; ++i) s_test7.emplace_back(i);
        const auto& se7 = Packetizer::encode(0xCC, s_test7.data(), s_test7.size());
        const auto& sd7 = Packetizer::decode(se7.data.data(), se7.data.size(), true, false);
        assert(s_test7 == sd7.data);
        assert(0xCC == sd7.index);
    }
    {
        std::vector<uint8_t> s_test8;
        for (size_t i = 0; i < 255; ++i) s_test8.emplace_back(i + 1);
        const auto& se8 = Packetizer::encode(0xCC, s_test8.data(), s_test8.size());
        const auto& sd8 = Packetizer::decode(se8.data.data(), se8.data.size(), true, false);
        assert(s_test8 == sd8.data);
        assert(0xCC == sd8.index);
    }
    {
        std::vector<uint8_t> s_test9;
        for (size_t i = 0; i < 255; ++i) s_test9.emplace_back(i + 2);
        const auto& se9 = Packetizer::encode(0xCC, s_test9.data(), s_test9.size());
        const auto& sd9 = Packetizer::decode(se9.data.data(), se9.data.size(), true, false);
        assert(s_test9 == sd9.data);
        assert(0xCC == sd9.index);
    }
    {
        std::vector<uint8_t> s_test10;
        for (size_t i = 0; i < 255; ++i) s_test10.emplace_back(i + 3);
        const auto& se10 = Packetizer::encode(0xCC, s_test10.data(), s_test10.size());
        const auto& sd10 = Packetizer::decode(se10.data.data(), se10.data.size(), true, false);
        assert(s_test10 == sd10.data);
        assert(0xCC == sd10.index);
    }
    {
        std::vector<uint8_t> s_test11;
        for (size_t i = 0; i < 512; ++i) s_test11.emplace_back(i);
        const auto& se11 = Packetizer::encode(0xCC, s_test11.data(), s_test11.size());
        const auto& sd11 = Packetizer::decode(se11.data.data(), se11.data.size(), true, false);
        assert(s_test11 == sd11.data);
        assert(0xCC == sd11.index);
    }
    {
        std::vector<uint8_t> s_test12;
        for (size_t i = 0; i < 512; ++i) s_test12.emplace_back(i + 1);
        const auto& se12 = Packetizer::encode(0xCC, s_test12.data(), s_test12.size());
        const auto& sd12 = Packetizer::decode(se12.data.data(), se12.data.size(), true, false);
        assert(s_test12 == sd12.data);
        assert(0xCC == sd12.index);
    }
    {
        std::vector<uint8_t> s_test13;
        for (size_t i = 0; i < 512; ++i) s_test13.emplace_back(i + 2);
        const auto& se13 = Packetizer::encode(0xCC, s_test13.data(), s_test13.size());
        const auto& sd13 = Packetizer::decode(se13.data.data(), se13.data.size(), true, false);
        assert(s_test13 == sd13.data);
        assert(0xCC == sd13.index);
    }
    {
        std::vector<uint8_t> s_test14;
        for (size_t i = 0; i < 512; ++i) s_test14.emplace_back(i + 3);
        const auto& se14 = Packetizer::encode(0xCC, s_test14.data(), s_test14.size());
        const auto& sd14 = Packetizer::decode(se14.data.data(), se14.data.size(), true, false);
        assert(s_test14 == sd14.data);
        assert(0xCC == sd14.index);
    }

    // slip
    {
        std::vector<uint8_t> s_test1 {0x00};
        const auto& se1 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test1.data(), s_test1.size());
        const auto& sd1= Packetizer::decode<Packetizer::encoding::SLIP>(se1.data.data(), se1.data.size(), true, false);
        assert(s_test1 == sd1.data);
        assert(0xCC == sd1.index);
    }
    {
        std::vector<uint8_t> s_test2 {0x00, 0x00};
        const auto& se2 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test2.data(), s_test2.size());
        const auto& sd2= Packetizer::decode<Packetizer::encoding::SLIP>(se2.data.data(), se2.data.size(), true, false);
        assert(s_test2 == sd2.data);
        assert(0xCC == sd2.index);
    }
    {
        std::vector<uint8_t> s_test3 {0x11, 0x22, 0x00, 0x33};
        const auto& se3 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test3.data(), s_test3.size());
        const auto& sd3= Packetizer::decode<Packetizer::encoding::SLIP>(se3.data.data(), se3.data.size(), true, false);
        assert(s_test3 == sd3.data);
        assert(0xCC == sd3.index);
    }
    {
        std::vector<uint8_t> s_test4 {0x11, 0x22, 0x33, 0x44};
        const auto& se4 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test4.data(), s_test4.size());
        const auto& sd4= Packetizer::decode<Packetizer::encoding::SLIP>(se4.data.data(), se4.data.size(), true, false);
        assert(s_test4 == sd4.data);
        assert(0xCC == sd4.index);
    }
    {
        std::vector<uint8_t> s_test5 {0x11, 0x00, 0x00, 0x00};
        const auto& se5 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test5.data(), s_test5.size());
        const auto& sd5= Packetizer::decode<Packetizer::encoding::SLIP>(se5.data.data(), se5.data.size(), true, false);
        assert(s_test5 == sd5.data);
        assert(0xCC == sd5.index);
    }
    {
        std::vector<uint8_t> s_test6;
        for (size_t i = 0; i < 254; ++i) s_test6.emplace_back(i + 1);
        const auto& se6 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test6.data(), s_test6.size());
        const auto& sd6= Packetizer::decode<Packetizer::encoding::SLIP>(se6.data.data(), se6.data.size(), true, false);
        assert(s_test6 == sd6.data);
        assert(0xCC == sd6.index);
    }
    {
        std::vector<uint8_t> s_test7;
        for (size_t i = 0; i < 255; ++i) s_test7.emplace_back(i);
        const auto& se7 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test7.data(), s_test7.size());
        const auto& sd7= Packetizer::decode<Packetizer::encoding::SLIP>(se7.data.data(), se7.data.size(), true, false);
        assert(s_test7 == sd7.data);
        assert(0xCC == sd7.index);
    }
    {
        std::vector<uint8_t> s_test8;
        for (size_t i = 0; i < 255; ++i) s_test8.emplace_back(i + 1);
        const auto& se8 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test8.data(), s_test8.size());
        const auto& sd8= Packetizer::decode<Packetizer::encoding::SLIP>(se8.data.data(), se8.data.size(), true, false);
        assert(s_test8 == sd8.data);
        assert(0xCC == sd8.index);
    }
    {
        std::vector<uint8_t> s_test9;
        for (size_t i = 0; i < 255; ++i) s_test9.emplace_back(i + 2);
        const auto& se9 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test9.data(), s_test9.size());
        const auto& sd9= Packetizer::decode<Packetizer::encoding::SLIP>(se9.data.data(), se9.data.size(), true, false);
        assert(s_test9 == sd9.data);
        assert(0xCC == sd9.index);
    }
    {
        std::vector<uint8_t> s_test10;
        for (size_t i = 0; i < 255; ++i) s_test10.emplace_back(i + 3);
        const auto& se10 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test10.data(), s_test10.size());
        const auto& sd10 = Packetizer::decode<Packetizer::encoding::SLIP>(se10.data.data(), se10.data.size(), true, false);
        assert(s_test10 == sd10.data);
        assert(0xCC == sd10.index);
    }
    {
        std::vector<uint8_t> s_test11;
        for (size_t i = 0; i < 512; ++i) s_test11.emplace_back(i);
        const auto& se11 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test11.data(), s_test11.size());
        const auto& sd11 = Packetizer::decode<Packetizer::encoding::SLIP>(se11.data.data(), se11.data.size(), true, false);
        assert(s_test11 == sd11.data);
        assert(0xCC == sd11.index);
    }
    {
        std::vector<uint8_t> s_test12;
        for (size_t i = 0; i < 512; ++i) s_test12.emplace_back(i + 1);
        const auto& se12 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test12.data(), s_test12.size());
        const auto& sd12 = Packetizer::decode<Packetizer::encoding::SLIP>(se12.data.data(), se12.data.size(), true, false);
        assert(s_test12 == sd12.data);
        assert(0xCC == sd12.index);
    }
    {
        std::vector<uint8_t> s_test13;
        for (size_t i = 0; i < 512; ++i) s_test13.emplace_back(i + 2);
        const auto& se13 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test13.data(), s_test13.size());
        const auto& sd13 = Packetizer::decode<Packetizer::encoding::SLIP>(se13.data.data(), se13.data.size(), true, false);
        assert(s_test13 == sd13.data);
        assert(0xCC == sd13.index);
    }
    {
        std::vector<uint8_t> s_test14;
        for (size_t i = 0; i < 512; ++i) s_test14.emplace_back(i + 3);
        const auto& se14 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test14.data(), s_test14.size());
        const auto& sd14 = Packetizer::decode<Packetizer::encoding::SLIP>(se14.data.data(), se14.data.size(), true, false);
        assert(s_test14 == sd14.data);
        assert(0xCC == sd14.index);
    }

    // no index + crc ----------------------------------------------------
    // cobs
    {
        std::vector<uint8_t> s_test1 {0x00};
        const auto& se1 = Packetizer::encode(s_test1.data(), s_test1.size(), true);
        const auto& sd1 = Packetizer::decode(se1.data.data(), se1.data.size(), true);
        assert(s_test1 == sd1.data);
    }
    {
        std::vector<uint8_t> s_test2 {0x00, 0x00};
        const auto& se2 = Packetizer::encode(s_test2.data(), s_test2.size(), true);
        const auto& sd2 = Packetizer::decode(se2.data.data(), se2.data.size(), true);
        assert(s_test2 == sd2.data);
    }
    {
        std::vector<uint8_t> s_test3 {0x11, 0x22, 0x00, 0x33};
        const auto& se3 = Packetizer::encode(s_test3.data(), s_test3.size(), true);
        const auto& sd3 = Packetizer::decode(se3.data.data(), se3.data.size(), true);
        assert(s_test3 == sd3.data);
    }
    {
        std::vector<uint8_t> s_test4 {0x11, 0x22, 0x33, 0x44};
        const auto& se4 = Packetizer::encode(s_test4.data(), s_test4.size(), true);
        const auto& sd4 = Packetizer::decode(se4.data.data(), se4.data.size(), true);
        assert(s_test4 == sd4.data);
    }
    {
        std::vector<uint8_t> s_test5 {0x11, 0x00, 0x00, 0x00};
        const auto& se5 = Packetizer::encode(s_test5.data(), s_test5.size(), true);
        const auto& sd5 = Packetizer::decode(se5.data.data(), se5.data.size(), true);
        assert(s_test5 == sd5.data);
    }
    {
        std::vector<uint8_t> s_test6;
        for (size_t i = 0; i < 254; ++i) s_test6.emplace_back(i + 1);
        const auto& se6 = Packetizer::encode(s_test6.data(), s_test6.size(), true);
        const auto& sd6 = Packetizer::decode(se6.data.data(), se6.data.size(), true);
        assert(s_test6 == sd6.data);
    }
    {
        std::vector<uint8_t> s_test7;
        for (size_t i = 0; i < 255; ++i) s_test7.emplace_back(i);
        const auto& se7 = Packetizer::encode(s_test7.data(), s_test7.size(), true);
        const auto& sd7 = Packetizer::decode(se7.data.data(), se7.data.size(), true);
        assert(s_test7 == sd7.data);
    }
    {
        std::vector<uint8_t> s_test8;
        for (size_t i = 0; i < 255; ++i) s_test8.emplace_back(i + 1);
        const auto& se8 = Packetizer::encode(s_test8.data(), s_test8.size(), true);
        const auto& sd8 = Packetizer::decode(se8.data.data(), se8.data.size(), true);
        assert(s_test8 == sd8.data);
    }
    {
        std::vector<uint8_t> s_test9;
        for (size_t i = 0; i < 255; ++i) s_test9.emplace_back(i + 2);
        const auto& se9 = Packetizer::encode(s_test9.data(), s_test9.size(), true);
        const auto& sd9 = Packetizer::decode(se9.data.data(), se9.data.size(), true);
        assert(s_test9 == sd9.data);
    }
    {
        std::vector<uint8_t> s_test10;
        for (size_t i = 0; i < 255; ++i) s_test10.emplace_back(i + 3);
        const auto& se10 = Packetizer::encode(s_test10.data(), s_test10.size(), true);
        const auto& sd10 = Packetizer::decode(se10.data.data(), se10.data.size(), true);
        assert(s_test10 == sd10.data);
    }
    {
        std::vector<uint8_t> s_test11;
        for (size_t i = 0; i < 512; ++i) s_test11.emplace_back(i);
        const auto& se11 = Packetizer::encode(s_test11.data(), s_test11.size(), true);
        const auto& sd11 = Packetizer::decode(se11.data.data(), se11.data.size(), true);
        assert(s_test11 == sd11.data);
    }
    {
        std::vector<uint8_t> s_test12;
        for (size_t i = 0; i < 512; ++i) s_test12.emplace_back(i + 1);
        const auto& se12 = Packetizer::encode(s_test12.data(), s_test12.size(), true);
        const auto& sd12 = Packetizer::decode(se12.data.data(), se12.data.size(), true);
        assert(s_test12 == sd12.data);
    }
    {
        std::vector<uint8_t> s_test13;
        for (size_t i = 0; i < 512; ++i) s_test13.emplace_back(i + 2);
        const auto& se13 = Packetizer::encode(s_test13.data(), s_test13.size(), true);
        const auto& sd13 = Packetizer::decode(se13.data.data(), se13.data.size(), true);
        assert(s_test13 == sd13.data);
    }
    {
        std::vector<uint8_t> s_test14;
        for (size_t i = 0; i < 512; ++i) s_test14.emplace_back(i + 3);
        const auto& se14 = Packetizer::encode(s_test14.data(), s_test14.size(), true);
        const auto& sd14 = Packetizer::decode(se14.data.data(), se14.data.size(), true);
        assert(s_test14 == sd14.data);
    }

    // slip
    {
        std::vector<uint8_t> s_test1 {0x00};
        const auto& se1 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test1.data(), s_test1.size(), true);
        const auto& sd1 = Packetizer::decode<Packetizer::encoding::SLIP>(se1.data.data(), se1.data.size(), true);
        assert(s_test1 == sd1.data);
    }
    {
        std::vector<uint8_t> s_test2 {0x00, 0x00};
        const auto& se2 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test2.data(), s_test2.size(), true);
        const auto& sd2 = Packetizer::decode<Packetizer::encoding::SLIP>(se2.data.data(), se2.data.size(), true);
        assert(s_test2 == sd2.data);
    }
    {
        std::vector<uint8_t> s_test3 {0x11, 0x22, 0x00, 0x33};
        const auto& se3 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test3.data(), s_test3.size(), true);
        const auto& sd3 = Packetizer::decode<Packetizer::encoding::SLIP>(se3.data.data(), se3.data.size(), true);
        assert(s_test3 == sd3.data);
    }
    {
        std::vector<uint8_t> s_test4 {0x11, 0x22, 0x33, 0x44};
        const auto& se4 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test4.data(), s_test4.size(), true);
        const auto& sd4 = Packetizer::decode<Packetizer::encoding::SLIP>(se4.data.data(), se4.data.size(), true);
        assert(s_test4 == sd4.data);
    }
    {
        std::vector<uint8_t> s_test5 {0x11, 0x00, 0x00, 0x00};
        const auto& se5 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test5.data(), s_test5.size(), true);
        const auto& sd5 = Packetizer::decode<Packetizer::encoding::SLIP>(se5.data.data(), se5.data.size(), true);
        assert(s_test5 == sd5.data);
    }
    {
        std::vector<uint8_t> s_test6;
        for (size_t i = 0; i < 254; ++i) s_test6.emplace_back(i + 1);
        const auto& se6 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test6.data(), s_test6.size(), true);
        const auto& sd6 = Packetizer::decode<Packetizer::encoding::SLIP>(se6.data.data(), se6.data.size(), true);
        assert(s_test6 == sd6.data);
    }
    {
        std::vector<uint8_t> s_test7;
        for (size_t i = 0; i < 255; ++i) s_test7.emplace_back(i);
        const auto& se7 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test7.data(), s_test7.size(), true);
        const auto& sd7 = Packetizer::decode<Packetizer::encoding::SLIP>(se7.data.data(), se7.data.size(), true);
        assert(s_test7 == sd7.data);
    }
    {
        std::vector<uint8_t> s_test8;
        for (size_t i = 0; i < 255; ++i) s_test8.emplace_back(i + 1);
        const auto& se8 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test8.data(), s_test8.size(), true);
        const auto& sd8 = Packetizer::decode<Packetizer::encoding::SLIP>(se8.data.data(), se8.data.size(), true);
        assert(s_test8 == sd8.data);
    }
    {
        std::vector<uint8_t> s_test9;
        for (size_t i = 0; i < 255; ++i) s_test9.emplace_back(i + 2);
        const auto& se9 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test9.data(), s_test9.size(), true);
        const auto& sd9 = Packetizer::decode<Packetizer::encoding::SLIP>(se9.data.data(), se9.data.size(), true);
        assert(s_test9 == sd9.data);
    }
    {
        std::vector<uint8_t> s_test10;
        for (size_t i = 0; i < 255; ++i) s_test10.emplace_back(i + 3);
        const auto& se10 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test10.data(), s_test10.size(), true);
        const auto& sd10 = Packetizer::decode<Packetizer::encoding::SLIP>(se10.data.data(), se10.data.size(), true);
        assert(s_test10 == sd10.data);
    }
    {
        std::vector<uint8_t> s_test11;
        for (size_t i = 0; i < 512; ++i) s_test11.emplace_back(i);
        const auto& se11 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test11.data(), s_test11.size(), true);
        const auto& sd11 = Packetizer::decode<Packetizer::encoding::SLIP>(se11.data.data(), se11.data.size(), true);
        assert(s_test11 == sd11.data);
    }
    {
        std::vector<uint8_t> s_test12;
        for (size_t i = 0; i < 512; ++i) s_test12.emplace_back(i + 1);
        const auto& se12 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test12.data(), s_test12.size(), true);
        const auto& sd12 = Packetizer::decode<Packetizer::encoding::SLIP>(se12.data.data(), se12.data.size(), true);
        assert(s_test12 == sd12.data);
    }
    {
        std::vector<uint8_t> s_test13;
        for (size_t i = 0; i < 512; ++i) s_test13.emplace_back(i + 2);
        const auto& se13 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test13.data(), s_test13.size(), true);
        const auto& sd13 = Packetizer::decode<Packetizer::encoding::SLIP>(se13.data.data(), se13.data.size(), true);
        assert(s_test13 == sd13.data);
    }
    {
        std::vector<uint8_t> s_test14;
        for (size_t i = 0; i < 512; ++i) s_test14.emplace_back(i + 3);
        const auto& se14 = Packetizer::encode<Packetizer::encoding::SLIP>(s_test14.data(), s_test14.size(), true);
        const auto& sd14 = Packetizer::decode<Packetizer::encoding::SLIP>(se14.data.data(), se14.data.size(), true);
        assert(s_test14 == sd14.data);
    }

    // index + crc ----------------------------------------------------
    // cobs
    {
        std::vector<uint8_t> s_test1 {0x00};
        const auto& se1 = Packetizer::encode(0xCC, s_test1.data(), s_test1.size(), true);
        const auto& sd1 = Packetizer::decode(se1.data.data(), se1.data.size(), true, true);
        assert(s_test1 == sd1.data);
        assert(0xCC == sd1.index);
    }
    {
        std::vector<uint8_t> s_test2 {0x00, 0x00};
        const auto& se2 = Packetizer::encode(0xCC, s_test2.data(), s_test2.size(), true);
        const auto& sd2 = Packetizer::decode(se2.data.data(), se2.data.size(), true, true);
        assert(s_test2 == sd2.data);
        assert(0xCC == sd2.index);
    }
    {
        std::vector<uint8_t> s_test3 {0x11, 0x22, 0x00, 0x33};
        const auto& se3 = Packetizer::encode(0xCC, s_test3.data(), s_test3.size(), true);
        const auto& sd3 = Packetizer::decode(se3.data.data(), se3.data.size(), true, true);
        assert(s_test3 == sd3.data);
        assert(0xCC == sd3.index);
    }
    {
        std::vector<uint8_t> s_test4 {0x11, 0x22, 0x33, 0x44};
        const auto& se4 = Packetizer::encode(0xCC, s_test4.data(), s_test4.size(), true);
        const auto& sd4 = Packetizer::decode(se4.data.data(), se4.data.size(), true, true);
        assert(s_test4 == sd4.data);
        assert(0xCC == sd4.index);
    }
    {
        std::vector<uint8_t> s_test5 {0x11, 0x00, 0x00, 0x00};
        const auto& se5 = Packetizer::encode(0xCC, s_test5.data(), s_test5.size(), true);
        const auto& sd5 = Packetizer::decode(se5.data.data(), se5.data.size(), true, true);
        assert(s_test5 == sd5.data);
        assert(0xCC == sd5.index);
    }
    {
        std::vector<uint8_t> s_test6;
        for (size_t i = 0; i < 254; ++i) s_test6.emplace_back(i + 1);
        const auto& se6 = Packetizer::encode(0xCC, s_test6.data(), s_test6.size(), true);
        const auto& sd6 = Packetizer::decode(se6.data.data(), se6.data.size(), true, true);
        assert(s_test6 == sd6.data);
        assert(0xCC == sd6.index);
    }
    {
        std::vector<uint8_t> s_test7;
        for (size_t i = 0; i < 255; ++i) s_test7.emplace_back(i);
        const auto& se7 = Packetizer::encode(0xCC, s_test7.data(), s_test7.size(), true);
        const auto& sd7 = Packetizer::decode(se7.data.data(), se7.data.size(), true, true);
        assert(s_test7 == sd7.data);
        assert(0xCC == sd7.index);
    }
    {
        std::vector<uint8_t> s_test8;
        for (size_t i = 0; i < 255; ++i) s_test8.emplace_back(i + 1);
        const auto& se8 = Packetizer::encode(0xCC, s_test8.data(), s_test8.size(), true);
        const auto& sd8 = Packetizer::decode(se8.data.data(), se8.data.size(), true, true);
        assert(s_test8 == sd8.data);
        assert(0xCC == sd8.index);
    }
    {
        std::vector<uint8_t> s_test9;
        for (size_t i = 0; i < 255; ++i) s_test9.emplace_back(i + 2);
        const auto& se9 = Packetizer::encode(0xCC, s_test9.data(), s_test9.size(), true);
        const auto& sd9 = Packetizer::decode(se9.data.data(), se9.data.size(), true, true);
        assert(s_test9 == sd9.data);
        assert(0xCC == sd9.index);
    }
    {
        std::vector<uint8_t> s_test10;
        for (size_t i = 0; i < 255; ++i) s_test10.emplace_back(i + 3);
        const auto& se10 = Packetizer::encode(0xCC, s_test10.data(), s_test10.size(), true);
        const auto& sd10 = Packetizer::decode(se10.data.data(), se10.data.size(), true, true);
        assert(s_test10 == sd10.data);
        assert(0xCC == sd10.index);
    }
    {
        std::vector<uint8_t> s_test11;
        for (size_t i = 0; i < 512; ++i) s_test11.emplace_back(i);
        const auto& se11 = Packetizer::encode(0xCC, s_test11.data(), s_test11.size(), true);
        const auto& sd11 = Packetizer::decode(se11.data.data(), se11.data.size(), true, true);
        assert(s_test11 == sd11.data);
        assert(0xCC == sd11.index);
    }
    {
        std::vector<uint8_t> s_test12;
        for (size_t i = 0; i < 512; ++i) s_test12.emplace_back(i + 1);
        const auto& se12 = Packetizer::encode(0xCC, s_test12.data(), s_test12.size(), true);
        const auto& sd12 = Packetizer::decode(se12.data.data(), se12.data.size(), true, true);
        assert(s_test12 == sd12.data);
        assert(0xCC == sd12.index);
    }
    {
        std::vector<uint8_t> s_test13;
        for (size_t i = 0; i < 512; ++i) s_test13.emplace_back(i + 2);
        const auto& se13 = Packetizer::encode(0xCC, s_test13.data(), s_test13.size(), true);
        const auto& sd13 = Packetizer::decode(se13.data.data(), se13.data.size(), true, true);
        assert(s_test13 == sd13.data);
        assert(0xCC == sd13.index);
    }
    {
        std::vector<uint8_t> s_test14;
        for (size_t i = 0; i < 512; ++i) s_test14.emplace_back(i + 3);
        const auto& se14 = Packetizer::encode(0xCC, s_test14.data(), s_test14.size(), true);
        const auto& sd14 = Packetizer::decode(se14.data.data(), se14.data.size(), true, true);
        assert(s_test14 == sd14.data);
        assert(0xCC == sd14.index);
    }

    // slip
    {
        std::vector<uint8_t> s_test1 {0x00};
        const auto& se1 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test1.data(), s_test1.size(), true);
        const auto& sd1 = Packetizer::decode<Packetizer::encoding::SLIP>(se1.data.data(), se1.data.size(), true, true);
        assert(s_test1 == sd1.data);
        assert(0xCC == sd1.index);
    }
    {
        std::vector<uint8_t> s_test2 {0x00, 0x00};
        const auto& se2 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test2.data(), s_test2.size(), true);
        const auto& sd2 = Packetizer::decode<Packetizer::encoding::SLIP>(se2.data.data(), se2.data.size(), true, true);
        assert(s_test2 == sd2.data);
        assert(0xCC == sd2.index);
    }
    {
        std::vector<uint8_t> s_test3 {0x11, 0x22, 0x00, 0x33};
        const auto& se3 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test3.data(), s_test3.size(), true);
        const auto& sd3 = Packetizer::decode<Packetizer::encoding::SLIP>(se3.data.data(), se3.data.size(), true, true);
        assert(s_test3 == sd3.data);
        assert(0xCC == sd3.index);
    }
    {
        std::vector<uint8_t> s_test4 {0x11, 0x22, 0x33, 0x44};
        const auto& se4 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test4.data(), s_test4.size(), true);
        const auto& sd4 = Packetizer::decode<Packetizer::encoding::SLIP>(se4.data.data(), se4.data.size(), true, true);
        assert(s_test4 == sd4.data);
        assert(0xCC == sd4.index);
    }
    {
        std::vector<uint8_t> s_test5 {0x11, 0x00, 0x00, 0x00};
        const auto& se5 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test5.data(), s_test5.size(), true);
        const auto& sd5 = Packetizer::decode<Packetizer::encoding::SLIP>(se5.data.data(), se5.data.size(), true, true);
        assert(s_test5 == sd5.data);
        assert(0xCC == sd5.index);
    }
    {
        std::vector<uint8_t> s_test6;
        for (size_t i = 0; i < 254; ++i) s_test6.emplace_back(i + 1);
        const auto& se6 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test6.data(), s_test6.size(), true);
        const auto& sd6 = Packetizer::decode<Packetizer::encoding::SLIP>(se6.data.data(), se6.data.size(), true, true);
        assert(s_test6 == sd6.data);
        assert(0xCC == sd6.index);
    }
    {
        std::vector<uint8_t> s_test7;
        for (size_t i = 0; i < 255; ++i) s_test7.emplace_back(i);
        const auto& se7 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test7.data(), s_test7.size(), true);
        const auto& sd7 = Packetizer::decode<Packetizer::encoding::SLIP>(se7.data.data(), se7.data.size(), true, true);
        assert(s_test7 == sd7.data);
        assert(0xCC == sd7.index);
    }
    {
        std::vector<uint8_t> s_test8;
        for (size_t i = 0; i < 255; ++i) s_test8.emplace_back(i + 1);
        const auto& se8 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test8.data(), s_test8.size(), true);
        const auto& sd8 = Packetizer::decode<Packetizer::encoding::SLIP>(se8.data.data(), se8.data.size(), true, true);
        assert(s_test8 == sd8.data);
        assert(0xCC == sd8.index);
    }
    {
        std::vector<uint8_t> s_test9;
        for (size_t i = 0; i < 255; ++i) s_test9.emplace_back(i + 2);
        const auto& se9 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test9.data(), s_test9.size(), true);
        const auto& sd9 = Packetizer::decode<Packetizer::encoding::SLIP>(se9.data.data(), se9.data.size(), true, true);
        assert(s_test9 == sd9.data);
        assert(0xCC == sd9.index);
    }
    {
        std::vector<uint8_t> s_test10;
        for (size_t i = 0; i < 255; ++i) s_test10.emplace_back(i + 3);
        const auto& se10 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test10.data(), s_test10.size(), true);
        const auto& sd10 = Packetizer::decode<Packetizer::encoding::SLIP>(se10.data.data(), se10.data.size(), true, true);
        assert(s_test10 == sd10.data);
        assert(0xCC == sd10.index);
    }
    {
        std::vector<uint8_t> s_test11;
        for (size_t i = 0; i < 512; ++i) s_test11.emplace_back(i);
        const auto& se11 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test11.data(), s_test11.size(), true);
        const auto& sd11 = Packetizer::decode<Packetizer::encoding::SLIP>(se11.data.data(), se11.data.size(), true, true);
        assert(s_test11 == sd11.data);
        assert(0xCC == sd11.index);
    }
    {
        std::vector<uint8_t> s_test12;
        for (size_t i = 0; i < 512; ++i) s_test12.emplace_back(i + 1);
        const auto& se12 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test12.data(), s_test12.size(), true);
        const auto& sd12 = Packetizer::decode<Packetizer::encoding::SLIP>(se12.data.data(), se12.data.size(), true, true);
        assert(s_test12 == sd12.data);
        assert(0xCC == sd12.index);
    }
    {
        std::vector<uint8_t> s_test13;
        for (size_t i = 0; i < 512; ++i) s_test13.emplace_back(i + 2);
        const auto& se13 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test13.data(), s_test13.size(), true);
        const auto& sd13 = Packetizer::decode<Packetizer::encoding::SLIP>(se13.data.data(), se13.data.size(), true, true);
        assert(s_test13 == sd13.data);
        assert(0xCC == sd13.index);
    }
    {
        std::vector<uint8_t> s_test14;
        for (size_t i = 0; i < 512; ++i) s_test14.emplace_back(i + 3);
        const auto& se14 = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, s_test14.data(), s_test14.size(), true);
        const auto& sd14 = Packetizer::decode<Packetizer::encoding::SLIP>(se14.data.data(), se14.data.size(), true, true);
        assert(s_test14 == sd14.data);
        assert(0xCC == sd14.index);
    }

    // callback w/ no index + no crc ----------------------------------------------------
    // cobs
    {
        bool b_success {false};
        std::vector<uint8_t> vs;
        for (size_t i = 0; i < 254; ++i) vs.emplace_back(i + 1);

        Packetizer::reset();
        Packetizer::encode_option(false);
        Packetizer::decode_option(false, false);

        const auto& p = Packetizer::encode(vs.data(), vs.size());

        Packetizer::subscribe([&](const uint8_t* data, const size_t size)
        {
            std::vector<uint8_t> rs;
            for (size_t i = 0; i < size; ++i) rs.emplace_back(data[i]);
            b_success = (vs == rs);
        });
        Packetizer::feed(p.data.data(), p.data.size());
        assert(b_success);
        Packetizer::unsubscribe();
    }
    // slip
    {
        bool b_success {false};
        std::vector<uint8_t> vs;
        for (size_t i = 0; i < 254; ++i) vs.emplace_back(i + 1);

        Packetizer::reset<Packetizer::encoding::SLIP>();
        Packetizer::encode_option<Packetizer::encoding::SLIP>(false);
        Packetizer::decode_option<Packetizer::encoding::SLIP>(false, false);

        const auto& p = Packetizer::encode<Packetizer::encoding::SLIP>(vs.data(), vs.size());

        Packetizer::subscribe<Packetizer::encoding::SLIP>([&](const uint8_t* data, const size_t size)
        {
            std::vector<uint8_t> rs;
            for (size_t i = 0; i < size; ++i) rs.emplace_back(data[i]);
            b_success = (vs == rs);
        });
        Packetizer::feed<Packetizer::encoding::SLIP>(p.data.data(), p.data.size());
        assert(b_success);
        Packetizer::unsubscribe<Packetizer::encoding::SLIP>();
    }

    // callback w/ no index + crc ----------------------------------------------------
    // cobs
    {
        bool b_success {false};
        std::vector<uint8_t> vs;
        for (size_t i = 0; i < 254; ++i) vs.emplace_back(i + 1);

        Packetizer::reset();
        Packetizer::encode_option(true);
        Packetizer::decode_option(false, true);

        const auto& p = Packetizer::encode(vs.data(), vs.size(), true);

        Packetizer::subscribe([&](const uint8_t* data, const size_t size)
        {
            std::vector<uint8_t> rs;
            for (size_t i = 0; i < size; ++i) rs.emplace_back(data[i]);
            b_success = (vs == rs);
        });
        Packetizer::feed(p.data.data(), p.data.size());
        assert(b_success);
        Packetizer::unsubscribe();
    }
    // slip
    {
        bool b_success {false};
        std::vector<uint8_t> vs;
        for (size_t i = 0; i < 254; ++i) vs.emplace_back(i + 1);

        Packetizer::reset<Packetizer::encoding::SLIP>();
        Packetizer::encode_option<Packetizer::encoding::SLIP>(true);
        Packetizer::decode_option<Packetizer::encoding::SLIP>(false, true);

        const auto& p = Packetizer::encode<Packetizer::encoding::SLIP>(vs.data(), vs.size(), true);

        Packetizer::subscribe<Packetizer::encoding::SLIP>([&](const uint8_t* data, const size_t size)
        {
            std::vector<uint8_t> rs;
            for (size_t i = 0; i < size; ++i) rs.emplace_back(data[i]);
            b_success = (vs == rs);
        });
        Packetizer::feed<Packetizer::encoding::SLIP>(p.data.data(), p.data.size());
        assert(b_success);
        Packetizer::unsubscribe<Packetizer::encoding::SLIP>();
    }

    // callback w/ index + no crc ----------------------------------------------------
    // cobs
    {
        bool b_success {false};
        std::vector<uint8_t> vs;
        for (size_t i = 0; i < 254; ++i) vs.emplace_back(i + 1);

        Packetizer::reset();
        Packetizer::encode_option(false);
        Packetizer::decode_option(true, false);

        const auto& p = Packetizer::encode(0xCC, vs.data(), vs.size());

        Packetizer::subscribe(0xCC, [&](const uint8_t* data, const size_t size)
        {
            std::vector<uint8_t> rs;
            for (size_t i = 0; i < size; ++i) rs.emplace_back(data[i]);
            b_success = (vs == rs);
        });
        Packetizer::feed(p.data.data(), p.data.size());
        assert(b_success);
        Packetizer::unsubscribe(0xCC);
    }
    // slip
    {
        bool b_success {false};
        std::vector<uint8_t> vs;
        for (size_t i = 0; i < 254; ++i) vs.emplace_back(i + 1);

        Packetizer::reset<Packetizer::encoding::SLIP>();
        Packetizer::encode_option<Packetizer::encoding::SLIP>(false);
        Packetizer::decode_option<Packetizer::encoding::SLIP>(true, false);

        const auto& p = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, vs.data(), vs.size());

        Packetizer::subscribe<Packetizer::encoding::SLIP>(0xCC, [&](const uint8_t* data, const size_t size)
        {
            std::vector<uint8_t> rs;
            for (size_t i = 0; i < size; ++i) rs.emplace_back(data[i]);
            b_success = (vs == rs);
        });
        Packetizer::feed<Packetizer::encoding::SLIP>(p.data.data(), p.data.size());
        assert(b_success);
        Packetizer::unsubscribe<Packetizer::encoding::SLIP>(0xCC);
    }

    // callback w/ index + crc ----------------------------------------------------
    // cobs
    {
        bool b_success {false};
        std::vector<uint8_t> vs;
        for (size_t i = 0; i < 254; ++i) vs.emplace_back(i + 1);

        Packetizer::reset();
        Packetizer::encode_option(true);
        Packetizer::decode_option(true, true);

        const auto& p = Packetizer::encode(0xCC, vs.data(), vs.size(), true);

        Packetizer::subscribe(0xCC, [&](const uint8_t* data, const size_t size)
        {
            std::vector<uint8_t> rs;
            for (size_t i = 0; i < size; ++i) rs.emplace_back(data[i]);
            b_success = (vs == rs);
        });
        Packetizer::feed(p.data.data(), p.data.size());
        assert(b_success);
        Packetizer::unsubscribe(0xCC);
    }
    // slip
    {
        bool b_success {false};
        std::vector<uint8_t> vs;
        for (size_t i = 0; i < 254; ++i) vs.emplace_back(i + 1);

        Packetizer::reset<Packetizer::encoding::SLIP>();
        Packetizer::encode_option<Packetizer::encoding::SLIP>(true);
        Packetizer::decode_option<Packetizer::encoding::SLIP>(true, true);

        const auto& p = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, vs.data(), vs.size(), true);

        Packetizer::subscribe<Packetizer::encoding::SLIP>(0xCC, [&](const uint8_t* data, const size_t size)
        {
            std::vector<uint8_t> rs;
            for (size_t i = 0; i < size; ++i) rs.emplace_back(data[i]);
            b_success = (vs == rs);
        });
        Packetizer::feed<Packetizer::encoding::SLIP>(p.data.data(), p.data.size());
        assert(b_success);
        Packetizer::unsubscribe<Packetizer::encoding::SLIP>(0xCC);
    }


    // callback w/ no index + no crc ----------------------------------------------------
    // cobs
    {
        bool b_success {false};
        std::vector<uint8_t> vs;
        for (size_t i = 0; i < 254; ++i) vs.emplace_back(i + 1);

        Packetizer::reset();
        Packetizer::encode_option(false);
        Packetizer::decode_option(false, false);

        const auto& p = Packetizer::encode(vs.data(), vs.size());

        Packetizer::subscribe([&](const uint8_t* data, const size_t size)
        {
            std::vector<uint8_t> rs;
            for (size_t i = 0; i < size; ++i) rs.emplace_back(data[i]);
            b_success = (vs == rs);
        });
        Packetizer::feed(p.data.data(), p.data.size());
        assert(b_success);
        Packetizer::unsubscribe();
    }
    // slip
    {
        bool b_success {false};
        std::vector<uint8_t> vs;
        for (size_t i = 0; i < 254; ++i) vs.emplace_back(i + 1);

        Packetizer::reset<Packetizer::encoding::SLIP>();
        Packetizer::encode_option<Packetizer::encoding::SLIP>(false);
        Packetizer::decode_option<Packetizer::encoding::SLIP>(false, false);

        const auto& p = Packetizer::encode<Packetizer::encoding::SLIP>(vs.data(), vs.size());

        Packetizer::subscribe<Packetizer::encoding::SLIP>([&](const uint8_t* data, const size_t size)
        {
            std::vector<uint8_t> rs;
            for (size_t i = 0; i < size; ++i) rs.emplace_back(data[i]);
            b_success = (vs == rs);
        });
        Packetizer::feed<Packetizer::encoding::SLIP>(p.data.data(), p.data.size());
        assert(b_success);
        Packetizer::unsubscribe<Packetizer::encoding::SLIP>();
    }

    // callback w/ no index + crc ----------------------------------------------------
    // cobs
    {
        bool b_success {false};
        std::vector<uint8_t> vs;
        for (size_t i = 0; i < 254; ++i) vs.emplace_back(i + 1);

        Packetizer::reset();
        Packetizer::encode_option(true);
        Packetizer::decode_option(false, true);

        const auto& p = Packetizer::encode(vs.data(), vs.size(), true);

        Packetizer::subscribe([&](const uint8_t* data, const size_t size)
        {
            std::vector<uint8_t> rs;
            for (size_t i = 0; i < size; ++i) rs.emplace_back(data[i]);
            b_success = (vs == rs);
        });
        Packetizer::feed(p.data.data(), p.data.size());
        assert(b_success);
        Packetizer::unsubscribe();
    }
    // slip
    {
        bool b_success {false};
        std::vector<uint8_t> vs;
        for (size_t i = 0; i < 254; ++i) vs.emplace_back(i + 1);

        Packetizer::reset<Packetizer::encoding::SLIP>();
        Packetizer::encode_option<Packetizer::encoding::SLIP>(true);
        Packetizer::decode_option<Packetizer::encoding::SLIP>(false, true);

        const auto& p = Packetizer::encode<Packetizer::encoding::SLIP>(vs.data(), vs.size(), true);

        Packetizer::subscribe<Packetizer::encoding::SLIP>([&](const uint8_t* data, const size_t size)
        {
            std::vector<uint8_t> rs;
            for (size_t i = 0; i < size; ++i) rs.emplace_back(data[i]);
            b_success = (vs == rs);
        });
        Packetizer::feed<Packetizer::encoding::SLIP>(p.data.data(), p.data.size());
        assert(b_success);
        Packetizer::unsubscribe<Packetizer::encoding::SLIP>();
    }

    // callback w/ index + no crc ----------------------------------------------------
    // cobs
    {
        bool b_success {false};
        std::vector<uint8_t> vs;
        for (size_t i = 0; i < 254; ++i) vs.emplace_back(i + 1);

        Packetizer::reset();
        Packetizer::encode_option(false);
        Packetizer::decode_option(true, false);

        const auto& p = Packetizer::encode(0xCC, vs.data(), vs.size());

        Packetizer::subscribe(0xCC, [&](const uint8_t* data, const size_t size)
        {
            std::vector<uint8_t> rs;
            for (size_t i = 0; i < size; ++i) rs.emplace_back(data[i]);
            b_success = (vs == rs);
        });
        Packetizer::feed(p.data.data(), p.data.size());
        assert(b_success);
        Packetizer::unsubscribe(0xCC);
    }
    // slip
    {
        bool b_success {false};
        std::vector<uint8_t> vs;
        for (size_t i = 0; i < 254; ++i) vs.emplace_back(i + 1);

        Packetizer::reset<Packetizer::encoding::SLIP>();
        Packetizer::encode_option<Packetizer::encoding::SLIP>(false);
        Packetizer::decode_option<Packetizer::encoding::SLIP>(true, false);

        const auto& p = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, vs.data(), vs.size());

        Packetizer::subscribe<Packetizer::encoding::SLIP>(0xCC, [&](const uint8_t* data, const size_t size)
        {
            std::vector<uint8_t> rs;
            for (size_t i = 0; i < size; ++i) rs.emplace_back(data[i]);
            b_success = (vs == rs);
        });
        Packetizer::feed<Packetizer::encoding::SLIP>(p.data.data(), p.data.size());
        assert(b_success);
        Packetizer::unsubscribe<Packetizer::encoding::SLIP>(0xCC);
    }

    // callback w/ index + crc ----------------------------------------------------
    // cobs
    {
        bool b_success {false};
        std::vector<uint8_t> vs;
        for (size_t i = 0; i < 254; ++i) vs.emplace_back(i + 1);

        Packetizer::reset();
        Packetizer::encode_option(true);
        Packetizer::decode_option(true, true);

        const auto& p = Packetizer::encode(0xCC, vs.data(), vs.size(), true);

        Packetizer::subscribe(0xCC, [&](const uint8_t* data, const size_t size)
        {
            std::vector<uint8_t> rs;
            for (size_t i = 0; i < size; ++i) rs.emplace_back(data[i]);
            b_success = (vs == rs);
        });
        Packetizer::feed(p.data.data(), p.data.size());
        assert(b_success);
        Packetizer::unsubscribe(0xCC);
    }
    // slip
    {
        bool b_success {false};
        std::vector<uint8_t> vs;
        for (size_t i = 0; i < 254; ++i) vs.emplace_back(i + 1);

        Packetizer::reset<Packetizer::encoding::SLIP>();
        Packetizer::encode_option<Packetizer::encoding::SLIP>(true);
        Packetizer::decode_option<Packetizer::encoding::SLIP>(true, true);

        const auto& p = Packetizer::encode<Packetizer::encoding::SLIP>(0xCC, vs.data(), vs.size(), true);

        Packetizer::subscribe<Packetizer::encoding::SLIP>(0xCC, [&](const uint8_t* data, const size_t size)
        {
            std::vector<uint8_t> rs;
            for (size_t i = 0; i < size; ++i) rs.emplace_back(data[i]);
            b_success = (vs == rs);
        });
        Packetizer::feed<Packetizer::encoding::SLIP>(p.data.data(), p.data.size());
        assert(b_success);
        Packetizer::unsubscribe<Packetizer::encoding::SLIP>(0xCC);
    }

    Serial.println("test finished");
}

void loop()
{
}

