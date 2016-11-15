#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // load port & ip
    try{
        loadFromXML();
    }
    catch(std::exception const& e){
        errorMessage = e.what();
    }
    
    if(loadOK){
        
        sender.setup(destinationIP,destinationPort);
        
        gui.setup("BlobSimulator");
        gui.setShape(30, 30, 320, 100);
        gui.add(sendBlobs.setup("Send data ", false));
        gui.add(desiredFramerate.setup("FrameRate",20,1,60));
        gui.add(blobSize.setup("BlobSize",0,0,100));
        
        prevFrameRate = desiredFramerate;
        
        ofSetFrameRate(desiredFramerate);
    }

}


void ofApp::loadFromXML() {
    
    loadOK = true;
    
    if (XML.loadFile("appConfig.xml")) {
        
        ofLogNotice("appConfig.xml loaded!");
        
        int numSettingsTags = XML.getNumTags("settings");
        if (numSettingsTags > 0) {
            
            XML.pushTag("settings", numSettingsTags - 1);
            //Blob OSC Sender
            int numOSCSenderTags = XML.getNumTags("OSCSenderSettings");
            
            if(numOSCSenderTags==0){
                loadOK = false;
                throw std::runtime_error(std::string("No OSC configuration found! Please configure the OSC sender and restart application."));
            }
            
            if (numOSCSenderTags > 0) {
                string ip = XML.getAttribute("OSCSenderSettings", "ip", "127.0.0.1", 0);
                int port = ofToInt(XML.getAttribute("OSCSenderSettings", "port", "6000", 0));
                
                this->destinationIP = ip;
                this->destinationPort = port;
            }
            
            XML.popTag();
        }
        
    }
    else {
        loadOK = false;
        throw std::runtime_error(std::string("XML not found! Please create the appConfig.xml."));
    }
}


//--------------------------------------------------------------
void ofApp::update(){
    if(loadOK){
        // sending biggest blob info
        if (this->sendBlobs) {
            this->sendData();
        }
        if(this->prevFrameRate!=desiredFramerate){
            ofSetFrameRate(this->desiredFramerate);
            this->prevFrameRate = this->desiredFramerate;
        }
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor::white, ofColor::gray);
    
    ofSetHexColor(0xffffff);
    
    if(loadOK){
        this->gui.draw();
    }
    else{
        ofDrawBitmapString(errorMessage, 20, 20);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::sendData() {
    
    // sending
    ofxOscMessage m;
    m.setAddress("/blob");
    m.addInt32Arg(0);
    float nomaX = (float) ofGetMouseX() / (float) ofGetWidth();
    float nomaY = (float) ofGetMouseY() / (float) ofGetHeight();
    m.addFloatArg(nomaX);
    m.addFloatArg(nomaY);
    float normaSize = this->blobSize/100.0f;
    m.addFloatArg(normaSize);
    sender.sendMessage(m);
}

