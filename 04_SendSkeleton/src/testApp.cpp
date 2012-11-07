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


	sender.setup("localhost", 12345);
}

//--------------------------------------------------------------
void testApp::update(){
	kinect.update();

	if(kinect.isFrameNew())
	{
		video.loadData( kinect.getVideoPixels() );

		kinect.getSkeletonPoints(skeletonPoints);

		for(int i=0; i<kinect::nui::SkeletonFrame::SKELETON_COUNT; i++)
		{
			if( skeletonPoints[i][0].z >= 0)
			{
				ofxOscMessage m;
				m.setAddress("/skeleton");
				m.addIntArg( i );

				for(int j=0; j<kinect::nui::SkeletonData::POSITION_COUNT; j++)
				{
					m.addFloatArg( skeletonPoints[i][j].x );
					m.addFloatArg( skeletonPoints[i][j].y );
					m.addFloatArg( skeletonPoints[i][j].z );
				}

				sender.sendMessage(m);
			}
		}
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(100, 100, 100);
	
	video.draw(0, 0, 1024, 768);

	ofPushMatrix();
	ofScale(1024/320.f, 768/240.f);
	for(int i=0; i<kinect::nui::SkeletonFrame::SKELETON_COUNT; i++)
	{
		drawSkeleton( skeletonPoints[i] );
	}
	ofPopMatrix();
}


void testApp::drawSkeleton(const ofPoint* src)
{
	ofPolyline pLine;
	ofPushStyle();
	ofSetColor(255);
	ofNoFill();
	ofSetLineWidth(4);
	// HEAD
	pLine.clear();
	pLine.addVertex(src[NUI_SKELETON_POSITION_HIP_CENTER].x, src[NUI_SKELETON_POSITION_HIP_CENTER].y);
	pLine.addVertex(src[NUI_SKELETON_POSITION_SPINE].x, src[NUI_SKELETON_POSITION_SPINE].y);
	pLine.addVertex(src[NUI_SKELETON_POSITION_SHOULDER_CENTER].x, src[NUI_SKELETON_POSITION_SHOULDER_CENTER].y);
	pLine.addVertex(src[NUI_SKELETON_POSITION_HEAD].x, src[NUI_SKELETON_POSITION_HEAD].y);
	pLine.draw();
	
	// BODY_LEFT
	pLine.clear();
	pLine.addVertex(src[NUI_SKELETON_POSITION_SHOULDER_CENTER].x, src[NUI_SKELETON_POSITION_SHOULDER_CENTER].y);
	pLine.addVertex(src[NUI_SKELETON_POSITION_SHOULDER_LEFT].x, src[NUI_SKELETON_POSITION_SHOULDER_LEFT].y);
	pLine.addVertex(src[NUI_SKELETON_POSITION_ELBOW_LEFT].x, src[NUI_SKELETON_POSITION_ELBOW_LEFT].y);
	pLine.addVertex(src[NUI_SKELETON_POSITION_WRIST_LEFT].x, src[NUI_SKELETON_POSITION_WRIST_LEFT].y);
	pLine.addVertex(src[NUI_SKELETON_POSITION_HAND_LEFT].x, src[NUI_SKELETON_POSITION_HAND_LEFT].y);
	pLine.draw();

	// BODY_RIGHT
	pLine.clear();
	pLine.addVertex(src[NUI_SKELETON_POSITION_SHOULDER_CENTER].x, src[NUI_SKELETON_POSITION_SHOULDER_CENTER].y);
	pLine.addVertex(src[NUI_SKELETON_POSITION_SHOULDER_RIGHT].x, src[NUI_SKELETON_POSITION_SHOULDER_RIGHT].y);
	pLine.addVertex(src[NUI_SKELETON_POSITION_ELBOW_RIGHT].x, src[NUI_SKELETON_POSITION_ELBOW_RIGHT].y);
	pLine.addVertex(src[NUI_SKELETON_POSITION_WRIST_RIGHT].x, src[NUI_SKELETON_POSITION_WRIST_RIGHT].y);
	pLine.addVertex(src[NUI_SKELETON_POSITION_HAND_RIGHT].x, src[NUI_SKELETON_POSITION_HAND_RIGHT].y);
	pLine.draw();

	// LEG_LEFT
	pLine.clear();
	pLine.addVertex(src[NUI_SKELETON_POSITION_HIP_CENTER].x, src[NUI_SKELETON_POSITION_HIP_CENTER].y);
	pLine.addVertex(src[NUI_SKELETON_POSITION_HIP_LEFT].x, src[NUI_SKELETON_POSITION_HIP_LEFT].y);
	pLine.addVertex(src[NUI_SKELETON_POSITION_KNEE_LEFT].x, src[NUI_SKELETON_POSITION_KNEE_LEFT].y);
	pLine.addVertex(src[NUI_SKELETON_POSITION_ANKLE_LEFT].x, src[NUI_SKELETON_POSITION_ANKLE_LEFT].y);
	pLine.addVertex(src[NUI_SKELETON_POSITION_FOOT_LEFT].x, src[NUI_SKELETON_POSITION_FOOT_LEFT].y);
	pLine.draw();

	// LEG_RIGHT
	pLine.clear();
	pLine.addVertex(src[NUI_SKELETON_POSITION_HIP_CENTER].x, src[NUI_SKELETON_POSITION_HIP_CENTER].y);
	pLine.addVertex(src[NUI_SKELETON_POSITION_HIP_RIGHT].x, src[NUI_SKELETON_POSITION_HIP_RIGHT].y);
	pLine.addVertex(src[NUI_SKELETON_POSITION_KNEE_RIGHT].x, src[NUI_SKELETON_POSITION_KNEE_RIGHT].y);
	pLine.addVertex(src[NUI_SKELETON_POSITION_ANKLE_RIGHT].x, src[NUI_SKELETON_POSITION_ANKLE_RIGHT].y);
	pLine.addVertex(src[NUI_SKELETON_POSITION_FOOT_RIGHT].x, src[NUI_SKELETON_POSITION_FOOT_RIGHT].y);
	pLine.draw();

	ofSetColor(0, 0, 255);
	ofSetLineWidth(0);
	ofFill();
	for(int i = 0; i < NUI_SKELETON_POSITION_COUNT; ++i){
		ofCircle(src[i].x, src[i].y, 5);
	}
	ofPopStyle();
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