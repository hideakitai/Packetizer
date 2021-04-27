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

#ifdef PACKETIZER_ENABLE_WIFI
#ifdef ESP_PLATFORM
#include <WiFi.h>
#include <WiFiUdp.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#elif defined(ARDUINO_AVR_UNO_WIFI_REV2) || defined(ARDUINO_SAMD_MKRWIFI1010) || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(ARDUINO_SAMD_NANO_33_IOT)
#include <SPI.h>
#include <WiFiNINA.h>
#include <WiFiUdp.h>
#elif defined(ARDUINO_SAMD_MKR1000)
#include <SPI.h>
#include <WiFi101.h>
#include <WiFiUdp.h>
#endif
#endif  // PACKETIZER_ENABLE_WIFI

#ifdef PACKETIZER_ENABLE_ETHER
#include <Ethernet.h>
#include <EthernetUdp.h>
#endif  // PACKETIZER_ENABLE_ETHER

#include "Packetizer/util/ArxTypeTraits/ArxTypeTraits.h"
#include "Packetizer/util/ArxContainer/ArxContainer.h"
#include "Packetizer/util/ArxSmartPtr/ArxSmartPtr.h"
#include "Packetizer/Types.h"
#include "Packetizer/Encoding.h"
#include "Packetizer/Encoder.h"
#include "Packetizer/Decoder.h"

namespace Packetizer = ht::serial::packetizer;

#endif  // HT_SERIAL_PACKETIZER
