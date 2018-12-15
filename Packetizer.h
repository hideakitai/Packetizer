#pragma once

#include "Packetizer/Common.h"
#ifdef __AVR__
#include "Packetizer/avr/Packer.h"
#include "Packetizer/avr/Unpacker.h"
#else
#include "Packetizer/Packer.h"
#include "Packetizer/Unpacker.h"
#endif

#ifdef TEENSYDUINO
extern "C"
{
    int _write() { return -1; }
}
namespace std
{
    void __throw_bad_alloc() { Serial.println("Unable to allocate memory"); }
    void __throw_length_error(char const* e) { Serial.print("Length Error :"); Serial.println(e); }
}
#endif
