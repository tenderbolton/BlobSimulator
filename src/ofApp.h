#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxOsc.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void loadFromXML();
        void sendData();
            
        ofxOscSender sender;
        string destinationIP;
        int destinationPort;
    
        //Interface
        ofxPanel gui;
        ofxLabel texto;
        ofxToggle sendBlobs;
        ofxIntSlider desiredFramerate;
        ofxIntSlider blobSize;
    
        ofxXmlSettings XML;
        
        bool loadOK;
        string errorMessage;
        
        int prevFrameRate;

		
};
