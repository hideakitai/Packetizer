#pragma once
#ifndef HT_SERIAL_PACKETIZER
#define HT_SERIAL_PACKETIZER

#ifdef ARDUINO
#include <Arduino.h>
#endif

#if defined(ARDUINO) || defined(OF_VERSION_MAJOR)
#define PACKETIZER_ENABLE_STREAM
#if defined(ESP_PLATFORM) || defined(ESP8266) || defined(ARDUINO_AVR_UNO_WIFI_REV2) || defined(ARDUINO_SAMD_MKRWIFI1010) || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_NANO_33_IOT)
#define PACKETIZER_ENABLE_WIFI
#endif
#if defined(ESP_PLATFORM) || defined(ESP8266) || !defined(ARTNET_ENABLE_WIFI)
#define PACKETIZER_ENABLE_ETHER
#endif
#endif

#if defined(PACKETIZER_ENABLE_ETHER) || defined(PACKETIZER_ENABLE_WIFI)
#define PACKETIZER_ENABLE_NETWORK
#include <UDP.h>
#include <Client.h>
#endif

#include "Packetizer/util/ArxTypeTraits/ArxTypeTraits.h"
#include "Packetizer/util/ArxContainer/ArxContainer.h"
#include "Packetizer/util/ArxSmartPtr/ArxSmartPtr.h"
#include "Packetizer/Types.h"
#include "Packetizer/Encoding.h"
#include "Packetizer/Encoder.h"
#include "Packetizer/Decoder.h"

namespace Packetizer = ht::serial::packetizer;

#endif  // HT_SERIAL_PACKETIZER
