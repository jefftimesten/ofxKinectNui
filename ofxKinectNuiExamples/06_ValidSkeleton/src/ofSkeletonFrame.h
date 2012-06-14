
#pragma once
#include "ofMain.h"
#include "ofxKinectNui.h"

/**
Jeff Crouse - June 14, 2012

This class represents a single set of "joints" (ofPoints) for a single skeleton
It is basically just a wrapper around an array of ofPoints, but it's useful to 
be able to run tests on them and analyze them with respect to eachother.
*/

class ofSkeletonFrame
{
public:
	ofSkeletonFrame(void);

	void draw();
	float getAngleABC(  int _a, int _b, int _c );
	bool isValid();

	ofPoint joints[kinect::nui::SkeletonData::POSITION_COUNT];
	float lastValid;

	static float maxValidArea;
	static float minValidArea;
	static float minValidHeight;
};

