#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    
    // save the current style
    defaultStyle = ofGetStyle();
    
    ofSetBackgroundAuto(false);
    currentDrawStyleId = 0;
    
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    fbo.begin();
    ofClear(0);
    ofClearAlpha();
    fbo.end();
    
    // GUI
    gui.setup();
    gui.setPosition(10, 80);
    gui.add(guiColor.set("color", ofColor(5, 5, 5, 10), ofColor(0, 0),ofColor(20, 20)));
    gui.loadFromFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::update(){
    pos.x++;
    if (pos.x > ofGetWidth()) pos.x = 0;
    pos.y++;
    if(pos.y > ofGetHeight()) pos.y = 0;
}

//--------------------------------------------------------------
void ofApp::draw(){
    switch (currentDrawStyleId) {
        case 0: // draw fade with OF_BLENDMODE_ALPHA, you can see trails which means the white circle does't completely black out.
            
        {
            ofEnableBlendMode(OF_BLENDMODE_ALPHA);
            ofSetColor(guiColor);
            ofFill();
            ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
            ofSetColor(255);
            ofDrawCircle(pos, 42);
        }
            break;
        case 1: // fade out properly without fbo
        {
            // Fade out overall alpha
            glEnable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_ONE);
            glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
            ofSetColor(guiColor);
            ofFill();
            ofDrawRectangle(0,0, ofGetWidth(), ofGetHeight());
            
            // restores normal draw mode
            glDisable(GL_BLEND);
            glBlendEquation(GL_FUNC_ADD);
            glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);
            
            // draw moving circle
            ofSetColor(255);
            ofDrawCircle(pos, 42);
        }
            break;
        case 2: // fade out properly with fbo
        {
            ofClear(0);
            fbo.begin();
            
            glEnable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_ONE);
            glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
            
            ofSetColor(guiColor);
            ofFill();
            ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
            
            glDisable(GL_BLEND);
            glBlendEquation(GL_FUNC_ADD);
            glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);
            
            ofSetColor(255);
            ofDrawCircle(pos, 42);
            
            fbo.end();
            fbo.draw(0,0);
        }
            break;
        default:
            break;
    }
    
    // restore default style
    ofSetStyle(defaultStyle);
    
    // Draw background comparison zone
    ofSetColor(0);
    ofDrawRectangle(0, 0, ofGetWidth(), 80);
    ofSetColor(255);
    ofDrawLine(0, 80, ofGetWidth(), 80);
    ofNoFill();
    ofSetColor(255, 255);
    
    string currentDrawStyle;
    switch (currentDrawStyleId) {
        case 0:
            currentDrawStyle = "This makes trails";
            break;
        case 1:
            currentDrawStyle = "Fade out properly without fbo";
            break;
        case 2:
            currentDrawStyle = "Fade out properly with fbo";
            break;
        default:
            break;
    }
    
    ofDrawBitmapString(ofToString(currentDrawStyleId) + ": " + currentDrawStyle +
                       "\nThis region is completely black for comparison with erased bg" +
                       "\npress any key to change the refreshing style", 10, 30);
    
    // GUI
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    currentDrawStyleId = (currentDrawStyleId+1) % DRAW_STYLE_NUMBER;
    
    // restore default style
    ofSetStyle(defaultStyle);
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
