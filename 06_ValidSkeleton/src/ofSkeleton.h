#pragma once
#include "ofMain.h"
#include "ofSkeletonFrame.h"

/**
Jeff Crouse - June 14, 2012

This is a very simple class that is meant to represent one of the 7 skeletons
that can be tracked by the Kinect camera.
*/


class ofSkeleton {
public:

	// -------------------------------------------
	ofSkeleton(void)
	{
		lastUpdated=0;
	}

	// -------------------------------------------
	float age()
	{
		return ofGetElapsedTimef() - lastUpdated;
	}

	// -------------------------------------------
	void addFrame( ofSkeletonFrame _frame )
	{
		frame = _frame;
		lastUpdated = ofGetElapsedTimef();
	}


	float lastUpdated;
	ofSkeletonFrame frame;
};
