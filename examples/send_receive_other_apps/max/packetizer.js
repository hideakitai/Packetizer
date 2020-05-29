"use strict";
const maxApi = require('max-api');
const cobs = require('cobs');
const slip = require('node-slip');
const crc = require('crc');

let b_index = false;
let b_crc = false;
let index = 0;
let encoding = "cobs";

maxApi.addHandler('encoding', s => { encoding = (s == "cobs") ? "cobs" : ((s === "slip") ? "slip" : "cobs"); });
maxApi.addHandler('verifying', b => { b_crc = b; });
maxApi.addHandler('indexing', b => { b_index = b; });
maxApi.addHandler('index', i => { index = i % 256; });


function encode_cobs(args)
{
    let arr = Array.from(cobs.encode(Buffer.from(args)));
    arr.push(0)
    maxApi.outlet(arr);
}

function encode_slip(args)
{
    let arr = Array.from(slip.generator(Buffer.from(args)));
    maxApi.outlet(arr);
}

maxApi.addHandler('encode', (...args) =>
{
    if (b_crc)
    {
        args.push(crc.crc8(Buffer.from(args)));
    }
    if (b_index)
    {
        args.unshift(index);
    }

    if (encoding === "cobs")
    {
        encode_cobs(args);
    }
    else
    {
        encode_slip(args);
    }
});


let packet = [];

function decode_cobs(args)
{
    args.forEach((v) =>
    {
        if (v === 0)
        {
            if (packet.length > 2)
            {
                const buffer = cobs.decode(Buffer.from(packet));
                if (b_crc)
                {
                    const crc_recv = buffer[buffer.length - 1];
                    const crc_calc = crc.crc8(buffer.slice(b_index ? 1 : 0, buffer.length - 1));
                    if (crc_recv === crc_calc)
                    {
                        maxApi.outlet(Array.from(buffer.slice(0, buffer.length - 1)));
                    }
                    else
                    {
                        maxApi.post("[COBS] crc not matched: recv = " + crc_recv + ", calc = " + crc_calc, "error");
                    }
                }
                else
                {
                    maxApi.outlet(Array.from(buffer.slice(0, buffer.length)));
                }
            }
            packet = [];
        }
        else
        {
            packet.push(v);
        }
    });
}

let receiver =
{
    data: function(buffer)
    {
        if (b_crc)
        {
            const crc_recv = buffer[buffer.length - 1];
            const crc_calc = crc.crc8(buffer.slice(b_index ? 1 : 0, buffer.length - 1));
            if (crc_recv === crc_calc)
            {
                maxApi.outlet(Array.from(buffer.slice(0, buffer.length - 1)));
            }
            else
            {
                maxApi.post("[SLIP] crc not matched: recv = " + crc_recv + ", calc = " + crc_calc, "error");
            }
        }
        else
        {
            maxApi.outlet(Array.from(buffer.slice(0, buffer.length)));
        }
    },
    framing: function(buffer)
    {
        maxApi.post("[SLIP] framing error: " + buffer.toString('hex').toUpperCase(), "error");
    },
    escape: function(buffer)
    {
        maxApi.post("[SLIP] escape error: " + buffer.toString('hex').toUpperCase(), "error");
    }
};

const SLIP_END = 0xC0;
const parser = new slip.parser(receiver);
function decode_slip(args)
{
    args.forEach((v) =>
    {
        packet.push(v);
        if (v === SLIP_END)
        {
            if (packet.length > 2)
            {
                parser.write(Buffer.from(packet));
                packet = [];
            }
        }
    });
}

maxApi.addHandler('decode', (...args) =>
{
    if (encoding === "cobs")
    {
        decode_cobs(args);
    }
    else
    {
        decode_slip(args);
    }
});


