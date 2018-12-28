const maxApi = require('max-api');
const crc = require('./crc.js');

const START_BYTE  = 0x7D;
const FINISH_BYTE = 0x7E;
const ESCAPE_BYTE = 0x7F;
const ESCAPE_MASK = 0x20;

let index = 0;

function isEscapeByte(arg) { return (arg >= START_BYTE) &&(arg <= ESCAPE_BYTE); }

maxApi.addHandler('index', (i) => { index = i; });

maxApi.addHandler('data', (...args) =>
{
    args.forEach((v, i) => {
        if (isEscapeByte(v)) {
            args.splice(i, 1, v ^ ESCAPE_MASK);
            args.splice(i, 0, ESCAPE_BYTE);
        }
    });

    if (isEscapeByte(index))
    {
        args.unshift(index ^ ESCAPE_MASK);
        args.unshift(ESCAPE_BYTE);
    }
    else
    {
        args.unshift(index);
    }
    args.unshift(START_BYTE);
    let crc8 = crc.crc8(args);
    if (isEscapeByte(crc8))
    {
        args.push(ESCAPE_BYTE);
        args.push(crc8 ^ ESCAPE_MASK);
    }
    else
    {
        args.push(crc8);
    }
    args.push(FINISH_BYTE);
    maxApi.outlet(args);
});
