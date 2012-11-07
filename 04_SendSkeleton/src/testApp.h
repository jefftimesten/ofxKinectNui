#pragma once

#include "ofxKinectNui.h"
#include "ofMain.h"
#include "ofxOsc.h"


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

		ofxKinectNui kinect;
		ofxOscSender sender;

		bool bPlugged;
		bool bUnplugged;
		
		unsigned short nearClipping;
		unsigned short farClipping;
		int angle;

		ofTexture video;
		const ofPoint* skeletonPoints[kinect::nui::SkeletonFrame::SKELETON_COUNT];
};
