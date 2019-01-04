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
// copied from https://github.com/gcc-mirror/
namespace std
{
    void __throw_bad_alloc() { _GLIBCXX_THROW_OR_ABORT(bad_alloc()); }
    void __throw_length_error(const char* __s __attribute__((unused))) { _GLIBCXX_THROW_OR_ABORT(length_error(_(__s))); }
    void __throw_bad_function_call() { _GLIBCXX_THROW_OR_ABORT(bad_function_call()); }
    // void _Rb_tree_decrement(std::_Rb_tree_node_base* a) {}
    // void _Rb_tree_insert_and_rebalance(bool, std::_Rb_tree_node_base*, std::_Rb_tree_node_base*, std::_Rb_tree_node_base&) {}
}
#endif // TEENSYDUINO
#endif // PACKETIZER_H
