#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
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
void testApp::update(){
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
void testApp::draw(){
	
	ofBackground(100, 100, 100);
	glEnable(GL_DEPTH_TEST);
	ofPushMatrix();

	// Center the image and rotate it around the vertical center of the screen
	ofTranslate((ofGetWidth()/2.0)-(640/2.0), 600);
	ofRotateX((mouseY - (ofGetHeight()/2) ) / 5.f);
	ofTranslate(0, -400);


	// Draw the interaction area
	ofSetColor(0);
	ofNoFill();
	ofPushMatrix();
	ofScale(640, 480, -1000);
	ofTranslate(.5, .5, .5);
	ofBox(0, 0, 0, 1);
	ofPopMatrix(); 


	// Loop through every x/y coordinate in the depth image
	for(int y=0; y<240; y++)
	{
		for(int x=0; x<320; x++)
		{
			float d = kinect.getDistanceAt(x, y);

			// The min and max distances (in mm) are 800 and 4000
			if(ofInRange(d, 800, 4000))
			{
				float z = ofMap( d, 800, 4000, 0, -1000, false);
				ofColor c = kinect.getCalibratedColorAt(x, y);

				ofPushMatrix();
				ofTranslate(x*2, y*2, z);
				ofSetColor( c );
				ofCircle(0, 0, 1);
				ofPopMatrix();
			}
		}
	}


	ofPopMatrix();	
	glDisable(GL_DEPTH_TEST);
}

//--------------------------------------------------------------
void testApp::exit() {

	kinect.setAngle(0);
	kinect.close();
	kinect.removeKinectListener(this);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	switch(key)
	{
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
void testApp::mouseMoved(int x, int y ){

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
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}


//--------------------------------------------------------------
void testApp::kinectPlugged(){
	bPlugged = true;
}

//--------------------------------------------------------------
void testApp::kinectUnplugged(){
	bPlugged = false;
}