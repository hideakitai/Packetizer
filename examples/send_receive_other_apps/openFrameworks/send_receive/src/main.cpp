//#define PACKETIZER_SET_DEFAULT_ENCODING_SLIP
//#define PACKETIZER_USE_CRC_AS_DEFAULT

#include "ofMain.h"
#include "ofxPacketizer.h"

class ofApp : public ofBaseApp
{
    ofSerial serial;
    stringstream decoder_info;
    string modem {"/dev/tty.usbmodem1423201"}; // <= change to your own board

public:

    void setup()
    {
        ofSetVerticalSync(false);
        ofSetFrameRate(60);
        ofSetBackgroundColor(0);

        serial.setup(modem, 115200);

        Packetizer::subscribe(serial,
            [&](const uint8_t* data, const uint8_t size)
            {
                decoder_info << "packet has come!" << endl << endl;
                decoder_info << std::dec;
                decoder_info << "size : " << (int)size << endl;
                decoder_info << "data : ";
                for (size_t i = 0; i < size; ++i) decoder_info << (int)data[i] << " ";
                decoder_info << endl;
            }
        );
    }

    void update()
    {
        std::vector<uint8_t> v {0, 1, 2, (uint8_t)(ofGetFrameNum() % 256), 4, 5, 6, 7, 8, 9};
        Packetizer::send(serial, v.data(), v.size());

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
    ofSetupOpenGL(360, 270, OF_WINDOW);
    ofRunApp(new ofApp());
}

