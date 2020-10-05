#define PACKETIZER_USE_INDEX_AS_DEFAULT

//#define PACKETIZER_SET_DEFAULT_ENCODING_SLIP
//#define PACKETIZER_USE_CRC_AS_DEFAULT

#include "ofMain.h"
#include "ofxPacketizer.h"

class ofApp : public ofBaseApp
{
    ofSerial serial;
    stringstream decoder_info;
    string modem {"/dev/tty.SLAB_USBtoUART"}; // <= change to your own board

    const uint8_t send_index = 0x12;
    const uint8_t recv_index = 0x34;

public:

    void setup()
    {
        ofSetVerticalSync(false);
        ofSetFrameRate(60);
        ofSetBackgroundColor(0);

        serial.setup(modem, 115200);

        Packetizer::subscribe(serial, [&](const uint8_t index, const uint8_t* data, const size_t size)
        {
            decoder_info << "packet has come! index = 0x" << std::hex << (int)index << endl;
            decoder_info << "idx  : " << std::hex << (int)index << endl;
            decoder_info << "size : " << std::dec << (int)size << endl;
            decoder_info << "data : ";
            for (size_t i = 0; i < size; ++i) decoder_info << (int)data[i] << " ";
            decoder_info << endl << endl;
        });

        Packetizer::subscribe(serial, recv_index, [&](const uint8_t* data, const size_t size)
        {
            decoder_info << "inside indexed callback!" << endl;
            decoder_info << "idx  : " << std::hex << (int)recv_index << endl;
            decoder_info << "size : " << std::dec << (int)size << endl;
            decoder_info << "data : ";
            for (size_t i = 0; i < size; ++i) decoder_info << (int)data[i] << " ";
            decoder_info << endl << endl;
        });
        
        Packetizer::subscribe(serial, send_index, [&](const uint8_t* data, const size_t size)
        {
            decoder_info << "inside error report callback!" << endl;
            decoder_info << "idx  : " << std::hex << (int)send_index << endl;
            decoder_info << "size : " << std::dec << (int)size << endl;
            decoder_info << "data : ";
            for (size_t i = 0; i < size; ++i) decoder_info << (int)data[i] << " ";
            decoder_info << endl;
            decoder_info << "errs : " << std::dec << (int)data[size - 1] << endl;
            decoder_info << endl << endl;
        });
    }

    void update()
    {
        std::vector<uint8_t> v {0, 1, 2, (uint8_t)(ofGetFrameNum() % 256), 4, 5, 6, 7, 8, 9};
        Packetizer::send(serial, send_index, v.data(), v.size());

        decoder_info.str("");
        decoder_info.clear();

        Packetizer::parse();
    }

    void draw()
    {
        ofDrawBitmapString("FPS : " + ofToString(ofGetFrameRate()), 20, 20);

        const string& str = decoder_info.str();
        if (str.empty())
            ofDrawBitmapString("no response", 20, 50);
        else
            ofDrawBitmapString(str, 20, 50);
    }
};


int main( )
{
    ofSetupOpenGL(360, 360, OF_WINDOW);
    ofRunApp(new ofApp());
}
