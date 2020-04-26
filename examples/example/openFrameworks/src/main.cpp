#include "ofMain.h"
#include "Packetizer.h"

class ofApp : public ofBaseApp 
{
	ofSerial serial;
	stringstream decoder_info;
	Packetizer::Decoder decoder;
    string modem {"/dev/tty.usbserial-DN06ACVP"}; // <= change to your own board

public:

	void setup()
	{
		ofSetVerticalSync(false);
		ofSetFrameRate(60);
		ofSetBackgroundColor(0);

		serial.setup(modem, 115200);
        decoder.attach(serial);

        decoder.subscribe([&](const uint8_t index, const uint8_t* data, uint8_t size)
        {
            decoder_info << "packet has come! index = 0x" << std::hex << (int)index << endl;
        });
        
		decoder.subscribe(0x34, [&](const uint8_t* data, uint8_t size)
		{
            decoder_info << std::dec;
			decoder_info << "size : " << (int)size << endl;
			decoder_info << "data : ";
			for (size_t i = 0; i < size; ++i) decoder_info << (int)data[i] << " ";
			decoder_info << endl;
			
			if (size != 10) cout << "error 0xFF " << (int)size << endl;
			if (size != 10) cout << "error 0xFF " << (int)data[3] << endl;
		});
	}

	void update()
	{
        Packetizer::send(serial, 0x12, 0, 1, 2, ofGetFrameNum() % 256, 4, 5, 6, 7, 8, 9);

        decoder_info.str("");
        decoder_info.clear();
        
        decoder.parse();
	}

	void draw()
	{
		ofDrawBitmapString("FPS : " + ofToString(ofGetFrameRate()), 20, 20);
        
        const string& str = decoder_info.str();
        if (str.empty())
            ofDrawBitmapString("no response", 20, 40);
        else
            ofDrawBitmapString(str, 20, 40);
	}
};


int main( ){
	ofSetupOpenGL(360,270,OF_WINDOW);			// <-------- setup the GL context
	ofRunApp(new ofApp());
}
