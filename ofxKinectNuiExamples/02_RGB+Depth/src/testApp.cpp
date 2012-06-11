/******************************************************************/
/**
 * @file	testApp.cpp
 * @brief	Example for ofxKinectNui addon
 * @note
 * @todo
 * @bug	
 *
 * @author	sadmb
 * @date	Oct. 28, 2011
 */
/******************************************************************/
#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {

	ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetFrameRate(60);
	ofSetVerticalSync(true);


	ofxKinectNui::InitSetting initSetting;
	initSetting.grabVideo = true;
	initSetting.grabDepth = true;
	initSetting.grabAudio = false;
	initSetting.grabLabel = true;
	initSetting.grabSkeleton = false;
	initSetting.grabCalibratedVideo = true;
	initSetting.grabLabelCv = true;
	kinect.init(initSetting);
	kinect.open(false);

	kinect.addKinectListener(this, &testApp::kinectPlugged, &testApp::kinectUnplugged);

	angle = kinect.getCurrentAngle();
	bPlugged = kinect.isConnected();
	nearClipping = kinect.getNearClippingDistance();
	farClipping = kinect.getFarClippingDistance();

	calibratedVideo.allocate(320, 240, GL_RGB);
	depth.allocate(320, 240, GL_RGB);
	labels.allocate(320, 240, GL_RGBA);
	video.allocate(kinect.getVideoResolutionWidth(), kinect.getVideoResolutionHeight(), GL_RGB);
}

//--------------------------------------------------------------
void testApp::update() {
	kinect.update();

	if(kinect.isFrameNew())
	{
		// Load the pixels from the Kinect into the textures we made
		calibratedVideo.loadData(kinect.getCalibratedVideoPixels());
		depth.loadData( kinect.getDepthPixels() );
		labels.loadData( kinect.getLabelPixels() );
		video.loadData( kinect.getVideoPixels() );
	}
}

//--------------------------------------------------------------
void testApp::draw() {
	ofBackground(100, 100, 100);

	ofPushMatrix();
	drawCalibratedTexture();	// draw calibrated images coodinates to depth images
	ofPopMatrix();	
}

//--------------------------------------------------------------
void testApp::drawCalibratedTexture(){
	int offsetX = -400;
	int offsetY = -300;
	glTranslatef(512, 386, 0);

	for(int y = 0; y < 240; y++)
	{
		for(int x = 0; x < 320; x++)
		{
			float distance = kinect.getDistanceAt(x, y);
			if(distance > 500 && distance < 1500){
				glPushMatrix();
				float radius = (1500 - distance);
				ofSetColor(kinect.getCalibratedColorAt(x, y));
				ofRotateY(mRotationY);
				ofRotateX(mRotationX);
				glTranslatef(x * 2.5 + offsetX, y * 2.5 + offsetY, radius);
				ofBox(5);
				glPopMatrix();
			}else{
				glPushMatrix();
				ofSetColor(kinect.getCalibratedColorAt(x, y));
				ofRotateY(mRotationY);
				ofRotateX(mRotationX);
				ofRect(x * 2.5 + offsetX, y * 2.5 + offsetY, 5, 5);
				glPopMatrix();
			}
		}
	}
}


//--------------------------------------------------------------
void testApp::exit() {

	kinect.setAngle(0);
	kinect.close();
	kinect.removeKinectListener(this);

}

//--------------------------------------------------------------
void testApp::keyPressed (int key) {
	switch(key){
	case 'v': // draw video only
	
	case OF_KEY_UP: // up the kinect angle
		angle++;
		if(angle > 27){
			angle = 27;
		}
		kinect.setAngle(angle);
		break;
	case OF_KEY_DOWN: // down the kinect angle
		angle--;
		if(angle < -27){
			angle = -27;
		}
		kinect.setAngle(angle);
		break;
	
	}
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y) {
	mRotationY = (x - 512) / 5;
	mRotationX = (384 - y) / 5;
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
}

//--------------------------------------------------------------
void testApp::kinectPlugged(){
	bPlugged = true;
}

//--------------------------------------------------------------
void testApp::kinectUnplugged(){
	bPlugged = false;
}
