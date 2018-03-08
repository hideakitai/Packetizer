#pragma once

namespace CRC
{
    uint8_t getCRC8(const uint8_t *buff, size_t size)
    {
        uint8_t* p = (uint8_t*)buff;
        uint8_t result = 0xFF;

        for (result = 0 ; size != 0 ; size--)
        {
            result ^= *p++;

            for (size_t i = 0 ; i < 8; i++)
            {
                if (result & 0x80)
                {
                    result <<= 1; result ^= 0x85; // x8 + x7 + x2 + x0
                }
                else
                {
                    result <<= 1;
                }
            }
        }
        return result;
    }

    uint16_t getCRC16(const uint8_t* buff, size_t size)
    {
        uint8_t* data = (uint8_t*)buff;
        uint16_t result = 0xFFFF;

        for (size_t i = 0; i < size; ++i)
        {
            result ^= data[i];
            for (size_t j = 0; j < 8; ++j)
            {
                if (result & 0x01) result = (result >> 1) ^ 0xA001;
                else result >>= 1;
            }
        }
        return result;
    }
}
