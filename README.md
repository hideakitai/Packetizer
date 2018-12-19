# Packetizer
binary data packer / unpacker


## Feature

- pack / unpack binary arrays to simple packet protocol
- simple packet check option using header / escape sequence / checksum / crc8 support
- mainly developed and checked for Arduino
- checked on Arduino, openFrameworks, Max7
- this repo is based on the work in [MsgPacketizer](https://github.com/hideakitai/MsgPacketizer) and [ArduinoOSC](https://github.com/hideakitai/ArduinoOSC)

## Packet Protocol

- 1 byte header
- 1 byte index
- 1 byte size ( = N)
- N byte data (arbitrary binary arrays)
- 1 byte footer (crc8, simple some, or none)

1 byte index can be used to identify the type of data, or as you like.

You can also choose the type of footer from None / Simple Sum / CRC8.



## Dependencies

None



## Note

If you want to use projectGenerator of openFrameworks, rename directory to ```ofxPacketizer```


## Usage

### pack & write

``` c++
Packetizer::Packer packer; // default packet checker is crc8
uint8_t test_array[5] = {0x7C, 0x7D, 0x7E, 0x7F, 0x80};

packer.pack(test_array, sizeof(test_array));
Serial.write(packer.data(), packer.size());
```

### read & unpack

``` c++
Packetizer::Unacker unpacker; // default packet checker is crc8

while (const int size = Serial.available())
{
    uint8_t data[size];
    Serial.readBytes((char*)data, size);

    unpacker.feed(data, size);

    while (unpacker.available())
    {
        Serial.print("index : ");
        Serial.println(unpacker.index());

        Serial.print("size  : ");
        Serial.println(unpacker.size());

        Serial.print("data : ");
        for (uint8_t i = 0; i < unpacker.size(); ++i)
        {
            Serial.print(unpacker.data()[i]);
            Serial.print(" ");
        }
        Serial.println();

        unpacker.pop();
    }
}
```

### Footer

set at constructor

```
Packetizer::Packet packer; // default = CRC8
Packetizer::Packer packer(Packetizer::Checker::None);
Packetizer::Packer packer(Packetizer::Checker::Sum);
Packetizer::Packer packer(Packetizer::Checker::CRC8);

Packetizer::Unpacker unpacker; // default = CRC8
Packetizer::Unpacker unpacker(Packetizer::Checker::None);
Packetizer::Unpacker unpacker(Packetizer::Checker::Sum);
Packetizer::Unpacker unpacker(Packetizer::Checker::CRC8);
```

or set after constructor

```c++
Packetizer::Packer::setCheckMode(Packetizer::Checker::None);
Packetizer::Packer::setCheckMode(Packetizer::Checker::Sum);
Packetizer::Packer::setCheckMode(Packetizer::Checker::CRC8); // default

Packetizer::Unpacker::setCheckMode(Packetizer::Checker::None);
Packetizer::Unpacker::setCheckMode(Packetizer::Checker::Sum);
Packetizer::Unpacker::setCheckMode(Packetizer::Checker::CRC8); // default
```

### Memory Management for AVR Boards

For AVR boards like Arduino Uno, you can manage required packet data size and buffering queue size.
Default packet data size is 32 byte, and buffering queue size is 2.
So internally `Packetizer::Packer` and `Packetizer::Unpacker` is defined as:

``` c++
using Packer = Packer_<32>;
using Unpacker = Unpacker_<2, 32>;
```

If you want to use them in larger or smaller data / queue size, define instances like:

``` c++
Packetzier::Packer_<128> packer; // you can send 128 byte data
Packetzier::Unpacker_<4, 128> packer; // you can receive 128 byte data and buffer 4 packets
```

There is no option for ARM boards (internally STL is used to buffer packets).


## License

MIT