#pragma once

#include "../CRC.h"
#include "RingQueue.h"

namespace Packetizer
{
    template <uint8_t SEND_BUFFER_SIZE = 128>
    class Packer_
    {
    public:

        Packer_(Checker m = Checker::CRC8) : mode(m) {}
        ~Packer_() {}

        void setCheckMode(Checker m) { mode = m; }

		uint8_t* data() { return pack_buffer; }

        size_t size() { return count; }


        const uint8_t* pack(uint8_t* sbuf, uint8_t size, const uint8_t& index = 0)
        {
            memset(pack_buffer, 0, SEND_BUFFER_SIZE);
            count = 0;

            append((uint8_t)START_BYTE, false);
            append((uint8_t)index);
            append((uint8_t)size);
            append((uint8_t*)sbuf, size);

            if (mode == Checker::Sum)
            {
                uint8_t sum = (uint8_t)START_BYTE + index + (uint8_t)size;
                for (size_t i = 0; i < size; ++i) sum += (uint8_t)sbuf[i];
                append(sum);
            }
            else if (mode == Checker::CRC8)
            {
                append(CRC::getCRC8((uint8_t*)sbuf, size));
            }

            return data();
        }

    protected:

        void append(const uint8_t* const data, const size_t& size, bool isEscape = true)
        {
            if (isEscape)
            {
                RingQueue<uint16_t> escapes {SEND_BUFFER_SIZE};
                for (size_t i = 0; i < size; ++i)
                    if ((data[i] == START_BYTE) || (data[i] == ESCAPE_BYTE))
                        escapes.push(i);

                if (escapes.empty())
                {
                    for (size_t i = 0; i < size; ++i)
                    {
                        pack_buffer[count++] = data[i];
                    }
                }
                else
                {
                    size_t start = 0;
                    while (!escapes.empty())
                    {
                        const size_t& idx = escapes.front();
                        append(data + start, idx - start);
                        append(data[idx], true);
                        start = idx + 1;
                        escapes.pop();
                    }
                    if (start < size) append(data + start, size - start);
                }
            }
            else
            {
                for (size_t i = 0; i < size; ++i)
                {
                    pack_buffer[count++] = data[i];
                }
            }
        }


        void append(const uint8_t& data, bool isEscape = true)
        {
            if (isEscape && ((data == START_BYTE) || (data == ESCAPE_BYTE)))
            {
                pack_buffer[count++] = ESCAPE_BYTE;
                pack_buffer[count++] = (uint8_t)(data ^ ESCAPE_MASK);
            }
            else
            {
                pack_buffer[count++] = data;
            }
        }

    private:

        Checker mode;

        uint8_t pack_buffer[SEND_BUFFER_SIZE];
        size_t count;
    };

    using Packer = Packer_<128>;
}
