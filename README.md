# Packetizer
binary data packer / unpacker


## Feature

- pack / unpack binary arrays to simple packet protocol
- simple packet check option using header / escape sequence / crc8
- mainly developed and checked for Arduino
- checked on Arduino, openFrameworks, Max7
- this repo is based on the work in [MsgPacketizer](https://github.com/hideakitai/MsgPacketizer) and [ArduinoOSC](https://github.com/hideakitai/ArduinoOSC)

## Packet Protocol

- 1 byte header
- 1 byte index
- N byte data (arbitrary binary arrays)
- 1 byte crc8 (for received data check)
- 1 byte footer

1 byte index can be used to identify the type of packet, or as you like.
All of the bytes (excluding header and footer) can be escaped and whole packet size can be increased.


## Dependencies

None



## Note

You can use this library by copying Packetizer.h to anywhere and `#include "Packetizer.h"`.
If you want to use projectGenerator of openFrameworks, rename directory to ```ofxPacketizer```.


## Usage


### Typical Usage

#### pack & write

``` c++
Packetizer::Packer packer;
packer.pack(1, 2, 3); // you can pack variable sized arguments
Serial.write(packer.data(), packer.size());
```

#### read & unpack

``` c++
Packetizer::Unacker unpacker;

void callback(const uint8_t* data, uint8_t size) { // do something here }

void setup()
{
    uint8_t index = 0x80; // function is automatically called if the index of received packet is 0x80

    // add callback as lambda
    unpacker.subscribe(index, [](const uint8_t* data, uint8_t size)
    {
        // do something here
    });

    // you can also add callback like this
    unpacker.subscribe(0x01, callback);
}

void loop()
{
    while (const int size = Serial.available())
    {
        uint8_t data[size];
        Serial.readBytes((char*)data, size);
        unpacker.feed(data, size);
    }
}
```

### details of pack & write

There are three ways to pack data.

#### 1. variable size arguments

Packetizer can pack variable sized arguments.

``` c++
Packetizer::Packer packer;
packer.pack(1, 2, 3); // you can pack variable sized arguments
Serial.write(packer.data(), packer.size());
```

Index can be set in constructer.

``` c++
Packetizer::Packer packer(10); // you can set index in constructor (default is 0x00)
packer.pack(11, 12, 13, 14, 15);
Serial.write(packer.data(), packer.size());
```

If you want to re-use Packer instance, please call init() before you pack() data.

``` c++
// 1st use
Packetizer::Packer packer;
packer.pack(31, 32);
Serial.write(packer.data(), packer.size());

// 2nd use
packer.init(); // please call init() if you re-use Packer instance
packer.pack(41, 42, 43);
Serial.write(packer.data(), packer.size());

// 3rd use
packer.init(50); // you can set index by init() (default is 0x00)
packer.pack(51, 52, 53, 54);
Serial.write(packer.data(), packer.size());
```


#### 2. insertion operator

You can pack data using insertion operator. If you finish packing, please use Packer::endp().

``` c++
Packetizer::Packer packer;
packer << 1 << 2;                  // add bytes like this
packer << 3;                       // you can add any bytes
packer << 4 << Packetizer::endp(); // finally you should add Packer::endp
Serial.write(packer.data(), packer.size());
```

If you re-use Packer instance, please use init() before you pack().

``` c++
// 1st use
Packetizer::Packer packer;
packer << 1 << 2 << 3 << 4 << Packetizer::endp();
Serial.write(packer.data(), packer.size());

// 2nd use
packer.init();
packer << 11 << 12 << 13 << Packer::endp;
Serial.write(packer.data(), packer.size());

// 3rd use
packer.init(20); // you can set index by init() (default is 0x00)
packer << 21 << 22 << 23 << Packer::endp;
Serial.write(packer.data(), packer.size());
```

#### 3. pointer to array and size (used in previous versions)

``` c++
Packetizer::Packer packer;
uint8_t test_array[5] = {0x7C, 0x7D, 0x7E, 0x7F, 0x80};

packer.pack(test_array, sizeof(test_array)); // default index = 0x00
Serial.write(packer.data(), packer.size());

packer.pack(test_array, sizeof(test_array), 0x01); // you can change index number
Serial.write(packer.data(), packer.size());
```


### Memory Management (for AVR Boards)

For AVR boards like Arduino Uno, you can manage required packet data size and buffering queue size.
Default packet data size is 32 byte, and buffering queue size is 2.
So internally `Packetizer::Packer` and `Packetizer::Unpacker` is defined as:

``` c++
using Packer = Packer_<64>;
using Unpacker = Unpacker_<2, 64>;
```

If you want to use them in larger or smaller data / queue size, define instances like:

``` c++
Packetzier::Packer_<128> packer; // you can send 128 byte data
Packetzier::Unpacker_<4, 128> packer; // you can receive 128 byte data and buffer 4 packets
```

Also you can manage the number of callback stacks (only for Unpacker).

``` c++
Packetzier::Unpacker_<4, 128, 16> packer; // 3rd argument is it. default is 8
```


### Memory Management (for NON-AVR Boards)

For NON-AVR boards like ARM processors, you can manage only packet buffering queue size.
Let me suppose that you add callbacks and you don't have other unpack method (like manually get data and `pop()` packets in `loop()`).
In such case, if you receive unexpected `index` data in many times, packet queue becomes too large and memory shortage occurs.
So internally we limit the packet queue size only you have callbacks.
If you receive correct `index` data, the packet will be handled in a moment.
This is defined as:

``` c++
using Unpacker = Unpacker_<4>;
```

So you can store 4 packet data by default.
You can manage queue size as follows.

``` c++
Packetzier::Unpacker_<16> packer;
```

## License

MIT