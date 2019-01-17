"use strict";

const maxApi = require('max-api');
const packetizer = require('./packetizer/packetizer.js');

maxApi.addHandler('index', i => { packetizer.index(i); });

maxApi.addHandler('encode', (...args) =>
{
    maxApi.outlet(packetizer.encode(args));
});

maxApi.addHandler('decode', (...args) =>
{
    packetizer.feed(args);
    if (packetizer.available())
    {
        maxApi.outlet(packetizer.decode());
    }
});
