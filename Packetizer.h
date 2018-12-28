#pragma once
#ifndef PACKETIZER_H
#define PACKETIZER_H

#include "Packetizer/Packetizer.h"

#ifdef TEENSYDUINO
extern "C"
{
    int _write() { return -1; }
}
// DIRTY for TEENSYDUINO compile...
namespace std
{
    void __throw_bad_alloc() { Serial.println("Unable to allocate memory"); }
    void __throw_length_error(char const* e) { Serial.print("Length Error :"); Serial.println(e); }
    void __throw_bad_function_call() {}
    // void _Rb_tree_decrement(std::_Rb_tree_node_base* a) {}
    // void _Rb_tree_insert_and_rebalance(bool, std::_Rb_tree_node_base*, std::_Rb_tree_node_base*, std::_Rb_tree_node_base&) {}
}
#endif // TEENSYDUINO
#endif // PACKETIZER_H
