#pragma once

namespace Packetizer
{
    enum class State { Start, Index, Size, Data, Checksum };
    enum class Checker { None, Sum, CRC8 };

    const uint8_t START_BYTE = 0x7E;
    const uint8_t ESCAPE_BYTE = 0x7D;
    const uint8_t ESCAPE_MASK = 0x20;
    const uint16_t ESCAPE_MARKER = 0xFFFF;
}

