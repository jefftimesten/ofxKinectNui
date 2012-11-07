#pragma once
#include "ofMain.h"
#include "ofxKinectNui.h"

/**
Jeff Crouse - June 14, 2012

This class represents a single set of "joints" (ofPoints) for a single skeleton
It is basically just a wrapper around an array of ofPoints, but it's useful to 
be able to run tests on them and analyze them with respect to eachother.

NOTE: This SkeletonFrame class assumes that values are normalized
*/


// From my experiments, these are the closest and furthest z values 
#define MIN_SKELETON_Z 2300
#define MAX_SKELETON_Z 35000

class ofSkeletonFrame
{
public:
	ofSkeletonFrame(void);

	void draw(float x, float y, float w, float h, float d);
	float getAngleABC(  int _a, int _b, int _c );
	bool isValid();

	ofPoint joints[kinect::nui::SkeletonData::POSITION_COUNT];
	
	static float maxValidArea;
	static float minValidArea;
	static float minValidHeight;
};

