const maxApi = require('max-api');
const crc = require('./crc.js');

const START_BYTE  = 0x7D;
const FINISH_BYTE = 0x7E;
const ESCAPE_BYTE = 0x7F;
const ESCAPE_MASK = 0x20;

let packet = [];
let b_processing = false;

function decodePacket()
{
    let crc_received = packet[packet.length - 1];
    if (packet[packet.length - 2] === ESCAPE_BYTE) // before CRC byte can be ESCAPE_BYTE only if CRC is escaped
    {
        crc_received ^= ESCAPE_MASK;
        packet.splice(packet.length - 2, 2);
    }
    else
    {
        packet.pop();
    }

    let crc8 = crc.crc8(packet);
    if (crc8 === crc_received)
    {
        packet.forEach((v, i) => {
            if (v === ESCAPE_BYTE) packet.splice(i, 2, packet[i + 1] ^ ESCAPE_MASK);
        });
        packet.shift();
        maxApi.outlet(packet);
    }
    packet = [];
    b_processing = false;
}

maxApi.addHandler('data', (...args) =>
{
    args.forEach(d => {
        if (!b_processing)
        {
            if (d === START_BYTE)
            {
                packet = [];
                b_processing = true;
                packet.push(d);
            }
        }
        else
        {
            if (d === FINISH_BYTE) decodePacket();
            else                   packet.push(d);
        }
    });
});

