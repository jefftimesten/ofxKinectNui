#pragma once

#include "ofMain.h"
#include "ofxKinectNui.h"
#include "ofxKinectNuiPlayer.h"
#include "ofxKinectNuiRecorder.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void drawSkeleton(const ofPoint* src);
		void exit();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void kinectPlugged();
		void kinectUnplugged();

		
		void startRecording();
		void stopRecording();
		void startPlayback();
		void stopPlayback();

		ofxKinectNui kinect;
		ofxKinectNuiPlayer kinectPlayer;
		ofxBase3DVideo* kinectSource;

		ofxKinectNuiRecorder kinectRecorder;
		
		bool bRecord;
		bool bPlayback;
		bool bPlugged;
		bool bUnplugged;
		
		unsigned short nearClipping;
		unsigned short farClipping;
		int angle;
	
		ofTexture labels;
		ofTexture depth;
		ofTexture video;
		ofTexture calibratedVideo;
		const ofPoint* skeletonPoints[kinect::nui::SkeletonFrame::SKELETON_COUNT];
};
