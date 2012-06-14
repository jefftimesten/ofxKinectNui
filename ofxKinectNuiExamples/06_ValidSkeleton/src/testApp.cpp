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

	// Step 1: initialize the camera.  Tell it which functionality it should activate
	ofxKinectNui::InitSetting initSetting;
	initSetting.grabVideo = true;
	initSetting.grabDepth = true;
	initSetting.grabAudio = false;
	initSetting.grabLabel = true;
	initSetting.grabSkeleton = true;
	initSetting.grabCalibratedVideo = false;
	initSetting.grabLabelCv = false;
	initSetting.videoResolution = NUI_IMAGE_RESOLUTION_640x480;
	initSetting.depthResolution = NUI_IMAGE_RESOLUTION_320x240;
	kinect.init(initSetting);
	kinect.open(false);

	// Step 2:  If you want to be notified when the camera is plugged in or unplugged, use this
	kinect.addKinectListener(this, &testApp::kinectPlugged, &testApp::kinectUnplugged);

	// Step 3: Get some initial information about the state of the camera
	angle = kinect.getCurrentAngle();
	bPlugged = kinect.isConnected();
	nearClipping = kinect.getNearClippingDistance();
	farClipping = kinect.getFarClippingDistance();


	// Step 4: Initialze a texture for the video
	video.allocate(kinect.getVideoResolutionWidth(), kinect.getVideoResolutionHeight(), GL_RGB);


	// Do we want to filter out invalid skeletons?
	bDoFiltering=true;
}

//--------------------------------------------------------------
void testApp::update() {

	kinect.update();

	if(kinect.isFrameNew())
	{
		video.loadData( kinect.getVideoPixels() );

		// Get the skeleton points in a 2D array from the camera...
		const ofPoint* skeletonPoints[kinect::nui::SkeletonFrame::SKELETON_COUNT];
		kinect.getSkeletonPoints( skeletonPoints );


		// Loop through each skeleton
		for(int i=0; i<kinect::nui::SkeletonFrame::SKELETON_COUNT; i++)
		{
			// Make a ofSkeletonFrame object
			ofSkeletonFrame frame;

			// For each skeleton (i), loop through all of the ofPoints (j)
			// Remember, there are 20 (kinect::nui::SkeletonData::POSITION_COUNT) joints
			for(int j=0; j<kinect::nui::SkeletonData::POSITION_COUNT; j++)
			{
				frame.joints[j] = skeletonPoints[i][j];
			}

			// Once we've added all of the ofPoints to the ofSkeletonFrame object,
			// If the ofSkeletonFrame object is "valid", add it to the skeleton
			// Otherwise, we just ignore it completely
			if(frame.isValid() || !bDoFiltering)
			{
				skeletons[i].addFrame( frame );
			}
		}
	}
}

//--------------------------------------------------------------
void testApp::draw() {

	ofBackground(100, 100, 100);
	
	video.draw(0, 0);


	ofPushMatrix();
	ofScale(640/320.f, 480/240.f);
	for(int i=0; i<kinect::nui::SkeletonFrame::SKELETON_COUNT; i++)
	{
		// Only draw the skeleton if it has been updated in the last 2 seconds.
		if(skeletons[i].age() < 2)
			skeletons[i].frame.draw();
	}
	ofPopMatrix();


	ofSetColor(255);
	string message = (bDoFiltering) ? "Filtering: on" : "Filtering: off";
	ofDrawBitmapString(message, 10, ofGetHeight()-30);
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
	case 'f':
		bDoFiltering=!bDoFiltering;
		break;
	}
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y) {
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
