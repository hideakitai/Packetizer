#include "ofMain.h"
#include "Packetizer.h"

class ofApp : public ofBaseApp 
{
	ofSerial serial;
	stringstream info[2];
	Packetizer::Unpacker unpacker;

public:

	void setup()
	{
		ofSetVerticalSync(false);
		ofSetFrameRate(60);
		ofSetBackgroundColor(0);

//		serial.setup("/dev/tty.usbmodem3071691", 115200);
		serial.setup("/dev/tty.usbmodem1421", 115200);

		unpacker.subscribe(0xFF, [&](const uint8_t* data, uint8_t size) 
		{
			info[0].str("");
			info[0].clear();
			
			info[0] << "size : " << (int)size << endl;
			info[0] << "data : ";
			for (size_t i = 0; i < size; ++i) info[0] << (int)data[i] << " ";
			info[0] << endl;
			
			if (size != 10) cout << "error 0xFF " << (int)size << endl;
			if (size != 10) cout << "error 0xFF " << (int)data[3] << endl;
		});
		unpacker.subscribe(0xFE, [&](const uint8_t* data, uint8_t size)
 	    {
		    info[1].str("");
		    info[1].clear();
		   
		    info[1] << "size : " << (int)size << endl;
		    info[1] << "data : ";
		    for (size_t i = 0; i < size; ++i) info[1] << (int)data[i] << " ";
			info[1] << endl;
			
			if (size != 5) cout << "error 0xFE " << (int)size << endl;
			if (size != 5) cout << "error 0xFE " << (int)data[4] << endl;
	    });
	}

	void update()
	{
		Packetizer::Packer packer;
		packer.pack(0, 1, 2, ofGetFrameNum() % 256, 4, 5, 6, 7, 8, 9);
		serial.writeBytes(packer.data(), packer.size());
		
		packer.init(1);
		packer << 9 << 8 << 7 << 6 << ofGetFrameNum() % 256 << Packetizer::endp();
		serial.writeBytes(packer.data(), packer.size());
		
		while (const size_t size = serial.available())
		{
			uint8_t serial_buffer[size];
			serial.readBytes((unsigned char*)serial_buffer, size);
			unpacker.feed((uint8_t*)serial_buffer, size);
		}
	}

	void draw()
	{
		ofDrawBitmapString(ofToString(ofGetFrameRate()), 20, 20);
		ofDrawBitmapString(info[0].str(), 20, 40);
		ofDrawBitmapString(info[1].str(), 20, 120);
	}
};


int main( ){
	ofSetupOpenGL(360,270,OF_WINDOW);			// <-------- setup the GL context
	ofRunApp(new ofApp());
}
