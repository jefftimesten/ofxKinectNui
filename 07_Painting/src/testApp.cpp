#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
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


	// Step 5. Move the camera a bit
	cam.setPosition( ofGetWidth() / 2.0, (ofGetHeight()/2.0)-300, 1000 );
	cam.lookAt( ofVec3f(ofGetWidth() / 2.0, ofGetHeight()/2.0-50, 0)  );
	cam.setScale(1, -1, 1);

	depth = -1000;

	// Do we want to filter out invalid skeletons?
	bDoFiltering=true;
}

//--------------------------------------------------------------
void testApp::update(){
	
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
			if(skeletonPoints[i][0].z==-1) continue;

			// Make a ofSkeletonFrame object
			ofSkeletonFrame frame;

			// For each skeleton (i), loop through all of the ofPoints (j)
			// Remember, there are 20 (kinect::nui::SkeletonData::POSITION_COUNT) joints
			// Also, this time we are going to normalize the points
			// that is, put them on a scale of 0-1
			for(int j=0; j<kinect::nui::SkeletonData::POSITION_COUNT; j++)
			{
				frame.joints[j].x = ofMap(skeletonPoints[i][j].x, 0, kinect.getDepthResolutionWidth(), 0, 1);
				frame.joints[j].y = ofMap(skeletonPoints[i][j].y, 0, kinect.getDepthResolutionHeight(), 0, 1);
				frame.joints[j].z = ofMap(skeletonPoints[i][j].z, MIN_SKELETON_Z, MAX_SKELETON_Z, 0, 1); 
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

	for(int i=0; i<kinect::nui::SkeletonFrame::SKELETON_COUNT; i++)
	{
		skeletons[i].update();
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofBackground(100, 100, 100);

	cam.begin();  
    glEnable(GL_DEPTH_TEST);
    

	ofSetColor(0);
	ofNoFill();
	ofPushMatrix();
	ofScale(ofGetWidth(), ofGetHeight(), depth);
	ofTranslate(.5, .5, .5);
	ofBox(0, 0, 0, 1);
	ofPopMatrix(); 


	for(int i=0; i<kinect::nui::SkeletonFrame::SKELETON_COUNT; i++)
	{
		// Only draw the skeleton if it has been updated in the last 2 seconds.
		skeletons[i].draw(0, 0, ofGetWidth(), ofGetHeight(), depth);
	}

	glDisable(GL_DEPTH_TEST);
	cam.end();


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
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	switch(key){
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