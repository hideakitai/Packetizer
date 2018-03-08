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
Packetizer::Reader reader; // default = CRC8
Packetizer::Reader reader(Packetizer::Checker::None);
Packetizer::Reader reader(Packetizer::Checker::Sum);
Packetizer::Reader reader(Packetizer::Checker::CRC8);

Packetizer::Sender sender; // default = CRC8
Packetizer::Sender sender(Packetizer::Checker::None);
Packetizer::Sender sender(Packetizer::Checker::Sum);
Packetizer::Sender sender(Packetizer::Checker::CRC8);
```

or set after constructor

```c++
Packetizer::Reader::setCheckMode(Packetizer::Checker::None);
Packetizer::Reader::setCheckMode(Packetizer::Checker::Sum);
Packetizer::Reader::setCheckMode(Packetizer::Checker::CRC8); // default

Packetizer::Sender::setCheckMode(Packetizer::Checker::None);
Packetizer::Sender::setCheckMode(Packetizer::Checker::Sum);
Packetizer::Sender::setCheckMode(Packetizer::Checker::CRC8); // default
```


## License

MIT