#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // save default style
    defaultStyle = ofGetStyle();
    
    ofBackground(0);
    ofSetBackgroundAuto(false);
    currentDrawStyleId = 0;
    
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    fbo.begin();
    ofClear(0);
    ofClearAlpha();
    fbo.end();
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
            ofSetColor(0, 0, 0, 20);
            ofFill();
            ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
            ofSetColor(255);
            ofDrawCircle(pos, 42);
        }
            break;
        case 1: // BLACK out properly
        {
            // Fade out overall alpha
            glEnable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_ONE);
            glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
            float fClearOpacity = 0.04f;
            ofSetColor(255*fClearOpacity, 255*fClearOpacity);
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
        case 2: // fade out properly with alpha channel
        {
            ofClear(0);
            fbo.begin();
            
            glEnable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_ONE);
            glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
            
            float fClearOpacity = 0.04f;
            ofSetColor(0, 255*fClearOpacity);
            ofFill();
            ofDrawRectangle(0,0, ofGetWidth(), ofGetHeight());
            
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
    ofDrawRectangle(0,0, ofGetWidth(), 50);
    ofNoFill();
    ofSetColor(255, 255);
    ofDrawBitmapString(ofToString(currentDrawStyleId) + " This region is completely black for comparison with erased bg", 10, 30);
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
