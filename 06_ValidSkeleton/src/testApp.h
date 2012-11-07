#pragma once

#include "ofxKinectNui.h"
#include "ofMain.h"
#include "ofSkeleton.h"

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

		bool bPlugged;
		bool bUnplugged;
		bool bDoFiltering;

		unsigned short nearClipping;
		unsigned short farClipping;
		int angle;

		ofTexture video;
		ofSkeleton skeletons[kinect::nui::SkeletonFrame::SKELETON_COUNT];
};
