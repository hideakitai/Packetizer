#pragma once
#ifndef HT_SERIAL_PACKETIZER
#define HT_SERIAL_PACKETIZER

#if defined(ARDUINO_ARCH_AVR)\
 || defined(ARDUINO_ARCH_MEGAAVR)\
 || defined(ARDUINO_ARCH_SAMD)\
 || defined(ARDUINO_spresense_ast)
#define PACKETIZER_DISABLE_STL
#endif

#ifdef PACKETIZER_DISABLE_STL

#include "util/RingBuffer.h"

#else

#include <vector>
#include <deque>
#include <map>
#include <functional>

#endif // PACKETIZER_DISABLE_STL

#include "util/TeensyDirtySTLErrorSolution.h"
#include "util/CRCx/CRCx.h"

namespace ht {
namespace serial {
namespace packetizer {

    static constexpr uint8_t INDEX_OFFSET_INDEX = 1;
    static constexpr uint8_t INDEX_OFFSET_DATA = 2;
    static constexpr uint8_t INDEX_OFFSET_CRC_ESCAPE_FROM_END = 2;
    static constexpr uint8_t N_HEADER_SIZE = 2;
    static constexpr uint8_t N_FOOTER_SIZE = 1; // footer is not bufferred
    static constexpr uint8_t N_HEADER_FOOTER_SIZE = N_HEADER_SIZE + N_FOOTER_SIZE;

    struct endp {}; // for end of packet sign

#ifdef PACKETIZER_DISABLE_STL

    template <uint8_t N_PACKET_DATA_SIZE, uint8_t START_BYTE = 0xC1>
    class Encoder_
    {
        using Buffer = RingBuffer<uint8_t, N_PACKET_DATA_SIZE>;
        using EscapeBuffer = RingBuffer<uint8_t, N_PACKET_DATA_SIZE>;

#else

    template <uint8_t START_BYTE = 0xC1>
    class Encoder_
    {
        using Buffer = std::vector<uint8_t>;
        using EscapeBuffer = std::deque<uint8_t>;

#endif // PACKETIZER_DISABLE_STL

        static constexpr uint8_t FINISH_BYTE {START_BYTE + 1};
        static constexpr uint8_t ESCAPE_BYTE {START_BYTE + 2};
        static constexpr uint8_t ESCAPE_MASK {0x20};

        Buffer buffer;

    public:

        explicit Encoder_(const uint8_t idx = 0) { init(idx); }

        void init(const uint8_t index = 0)
        {
            buffer.clear();
            append((uint8_t)START_BYTE, false);
            append((uint8_t)index);
        }

        // ---------- pack w/ variadic arguments ----------

        template <typename ...Rest>
        void pack(const uint8_t first, Rest&& ...args)
        {
            append((uint8_t)first);
#ifdef PACKETIZER_DISABLE_STL
            pack(args...);
#else
            pack(std::forward<Rest>(args)...);
#endif
        }
        void pack()
        {
            footer();
        }

        // ---------- pack w/ data pointer and size ----------

        void pack(const uint8_t* const sbuf, const uint8_t size)
        {
            append((uint8_t*)sbuf, size);
            footer();
        }

        // ---------- pack w/ insertion operator ----------

        const endp& operator<< (const endp& e)
        {
            footer();
            return e; // dummy
        }
        Encoder_& operator<< (const uint8_t arg)
        {
            append(arg);
            return *this;
        }

        // get packing info
        const Buffer& packet() const { return buffer; }
        size_t size() const { return buffer.size(); }
        const uint8_t* data() const { return buffer.data(); }

    private:

        void append(const uint8_t* const data, const uint8_t size, const bool b_escape = true)
        {
            if (b_escape)
            {
                EscapeBuffer escapes;
                for (uint8_t i = 0; i < size; ++i)
                    if (is_escape_byte(data[i]))
                        escapes.push_back(i);

                if (escapes.empty())
                    for (uint8_t i = 0; i < size; ++i) buffer.push_back(data[i]);
                else
                {
                    size_t start = 0;
                    while (!escapes.empty())
                    {
                        const uint8_t& idx = escapes.front();
                        append(data + start, idx - start);
                        append(data[idx], true);
                        start = idx + 1;
                        escapes.pop_front();
                    }
                    if (start < size) append(data + start, size - start);
                }
            }
            else
                for (uint8_t i = 0; i < size; ++i) buffer.push_back(data[i]);
        }

        void append(const uint8_t data, const bool b_escape = true)
        {
            if (b_escape && is_escape_byte(data))
            {
                buffer.push_back((uint8_t)ESCAPE_BYTE);
                buffer.push_back((uint8_t)(data ^ ESCAPE_MASK));
            }
            else
                buffer.push_back(data);
        }

        void footer()
        {
            append(crcx::crc8(buffer.data(), buffer.size()));
            append(FINISH_BYTE, false);
        }

        bool is_escape_byte(const uint8_t d) const
        {
            return ((d == START_BYTE) || (d == ESCAPE_BYTE) || (d == FINISH_BYTE));
        }

    };


#ifdef PACKETIZER_DISABLE_STL

    template <uint8_t N_PACKET_QUEUE_SIZE, uint8_t N_PACKET_DATA_SIZE, uint8_t N_CALLBACK_SIZE = 8, uint8_t START_BYTE = 0xC1>
    class Decoder_
    {
        using Buffer = RingBuffer<uint8_t, N_PACKET_DATA_SIZE>;
        typedef void (*callback_t)(const uint8_t* data, const uint8_t size);
        typedef void (*cb_always_t)(const uint8_t index, const uint8_t* data, const uint8_t size);
        struct Map { uint8_t key; callback_t func; };
        using PacketQueue = RingBuffer<Buffer, N_PACKET_QUEUE_SIZE>;
        using CallbackMap = RingBuffer<Map, N_CALLBACK_SIZE>;

#else

    template <uint8_t N_PACKET_QUEUE_SIZE, uint8_t START_BYTE = 0xC1>
    class Decoder_
    {
        using Buffer = std::vector<uint8_t>;
        using callback_t = std::function<void(const uint8_t* data, const uint8_t size)>;
        using cb_always_t = std::function<void(const uint8_t index, const uint8_t* data, const uint8_t size)>;
        using PacketQueue = std::deque<Buffer>;
        using CallbackMap = std::map<uint8_t, callback_t>;

#endif // PACKETIZER_DISABLE_STL

        static constexpr uint8_t FINISH_BYTE {START_BYTE + 1};
        static constexpr uint8_t ESCAPE_BYTE {START_BYTE + 2};
        static constexpr uint8_t ESCAPE_MASK {0x20};

        Buffer buffer;
        PacketQueue packets;
        CallbackMap callbacks;
        cb_always_t callback_always;

        bool b_parsing {false};
        bool b_escape {false};

        uint32_t err_count {0};

        Stream* stream {nullptr};

    public:

        using CallbackType = callback_t;

        void attach(Stream& s) { stream = &s; }

        void subscribe(const uint8_t index, const callback_t& func)
        {
#ifdef PACKETIZER_DISABLE_STL
            callbacks.push_back(Map{index, func});
#else
            callbacks.emplace(std::make_pair(index, func));
#endif // PACKETIZER_DISABLE_STL
        }

        void subscribe(const cb_always_t& func)
        {
            callback_always = func;
        }

        void parse(bool b_exec_cb = true)
        {
            if (stream == nullptr) return;

            while (const int size = stream->available())
            {
                uint8_t data[size];
                stream->readBytes((char*)data, size);
                feed(data, size, b_exec_cb);
            }
        }

        void feed(const uint8_t* const data, const size_t size, bool b_exec_cb = true)
        {
            for (size_t i = 0; i < size; ++i) feed(data[i], b_exec_cb);
        }

        void feed(const uint8_t d, bool b_exec_cb = true)
        {
            if (d == START_BYTE)
            {
                reset();
                buffer.push_back(d);
                b_parsing = true;
            }
            else if (b_parsing)
            {
                if (d == FINISH_BYTE)
                    decode();
                else if (b_parsing)
                    buffer.push_back(d);
            }

            if (available() && b_exec_cb) callback();
        }

        void callback()
        {
            if (!callback_always && callbacks.empty()) return;

            while(available())
            {
                if (callback_always)
                    callback_always(index(), data(), size());

#ifdef PACKETIZER_DISABLE_STL
                for (auto& c : callbacks)
                {
                    if (c.key == index())
                    {
                        c.func(data(), size());
                        break;
                    }
                }
#else
                auto it = callbacks.find(index());
                if (it != callbacks.end()) it->second(data(), size());
#endif // PACKETIZER_DISABLE_STL
                pop();
            }
        }

        bool isParsing() const { return b_parsing; }
        size_t available() const { return packets.size(); }
        void pop() { packets.pop_front(); }
        void pop_back() { packets.pop_back(); }

        uint8_t index() const { return packets.front()[INDEX_OFFSET_INDEX]; }
        uint8_t size() const { return packets.front().size() - N_HEADER_FOOTER_SIZE; }
        uint8_t data(const uint8_t i) const { return data()[i]; }
        const uint8_t* data() const { return packets.front().data() + INDEX_OFFSET_DATA; }

        uint8_t index_back() const { return packets.back()[INDEX_OFFSET_INDEX]; }
        uint8_t size_back() const { return packets.back().size() - N_HEADER_FOOTER_SIZE; }
        uint8_t data_back(const uint8_t i) const { return data_back()[i]; }
        const uint8_t* data_back() const { return packets.back().data() + INDEX_OFFSET_DATA; }

        uint32_t errors() const { return err_count; }

    private:

        void decode()
        {
            if (isCrcMatched())
            {
                for (auto it = buffer.begin(); it != buffer.end(); ++it)
                {
                    if (*it == ESCAPE_BYTE)
                    {
                        it = buffer.erase(it);
                        *it = *it ^ ESCAPE_MASK;
                    }
                }
                packets.push_back(buffer);
            }
            else
                ++err_count;

            reset();

            if (N_PACKET_QUEUE_SIZE != 0)
                if (available() > N_PACKET_QUEUE_SIZE)
                    pop();
        }

        bool isCrcMatched()
        {
            uint8_t crc_received = buffer.back();
            uint8_t crc_offset_size = 1;
            if (*(buffer.end() - INDEX_OFFSET_CRC_ESCAPE_FROM_END) == ESCAPE_BYTE) // before CRC byte can be ESCAPE_BYTE only if CRC is escaped
            {
                crc_received ^= ESCAPE_MASK;
                crc_offset_size = 2;
            }

            uint8_t crc = crcx::crc8(buffer.data(), buffer.size() - crc_offset_size);
            return (crc == crc_received);
        }

        void reset()
        {
            buffer.clear();
            b_parsing = false;
        }
    };

#ifdef PACKETIZER_DISABLE_STL
    using Encoder = Encoder_<64>;
    using Decoder = Decoder_<2, 64>;
    using Packet = RingBuffer<uint8_t, 64>;
#else
    using Encoder = Encoder_<>;
    using Decoder = Decoder_<0>;
    using Packet = std::vector<uint8_t>;
#endif
    using CallbackType = Decoder::CallbackType;


    class PacketizeManager
    {
        PacketizeManager() {}
        PacketizeManager(const PacketizeManager&) = delete;
        PacketizeManager& operator=(const PacketizeManager&) = delete;

        Encoder encoder;

    public:

        static PacketizeManager& getInstance()
        {
            static PacketizeManager m;
            return m;
        }

        Encoder& getEncoder()
        {
            return encoder;
        }
    };

    const Packet& encode(const uint8_t index, const uint8_t* data, const uint8_t size)
    {
        auto& e = PacketizeManager::getInstance().getEncoder();
        e.init(index);
        e.pack(data, size);
        return e.packet();
    }

    template <typename ...Rest>
    const Packet& encode(const uint8_t index, const uint8_t first, Rest&& ...args)
    {
        auto& e = PacketizeManager::getInstance().getEncoder();
        e.init(index);

#ifdef PACKETIZER_DISABLE_STL
        return encode(e, first, args...);
#else
        return encode(e, first, std::forward<Rest>(args)...);
#endif
    }

    template <typename ...Rest>
    const Packet& encode(Encoder& p, const uint8_t first, Rest&& ...args)
    {
        p << first;

#ifdef PACKETIZER_DISABLE_STL
        return encode(p, args...);
#else
        return encode(p, std::forward<Rest>(args)...);
#endif
    }

    const Packet& encode(Encoder& p)
    {
        p << endp();
        return p.packet();
    }


    void send(Stream& stream, const uint8_t index, const uint8_t* data, const uint8_t size)
    {
        const auto& packet = encode(index, data, size);
        stream.write(packet.data(), packet.size());
    }

    template <typename ...Rest>
    void send(Stream& stream, const uint8_t index, const uint8_t first, Rest&& ...args)
    {
#ifdef PACKETIZER_DISABLE_STL
        const auto& packet = encode(index, first, args...);
#else
        const auto& packet = encode(index, first, std::forward<Rest>(args)...);
#endif
        stream.write(packet.data(), packet.size());
    }

} // packetizer
} // serial
} // ht

namespace Packetizer = ht::serial::packetizer;

#endif // HT_SERIAL_PACKETIZER
