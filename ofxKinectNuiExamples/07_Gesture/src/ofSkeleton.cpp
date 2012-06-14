
#include "ofSkeleton.h"

bool ofSkeleton::bDrawVelocity = true;

// -------------------------------------------
ofSkeleton::ofSkeleton(void)
{
	lastUpdated = 0;
}

// -------------------------------------------
float ofSkeleton::age()
{
	return ofGetElapsedTimef() - lastUpdated;
}

// -------------------------------------------
void ofSkeleton::addFrame( ofSkeletonFrame& _frame )
{
	float t = ofGetElapsedTimef()-lastUpdated;

	// Velocity = d / t
	for(int i=0; i<kinect::nui::SkeletonData::POSITION_COUNT; i++)
	{
		float dist = ofDist(_frame.joints[i].x, _frame.joints[i].y, frame.joints[i].x, frame.joints[i].y );
		velocity[i] = dist / t;
	}

	frame = _frame;

	wave.add( frame, velocity );

	lastUpdated = ofGetElapsedTimef();
}


// --------------------------------------------
void ofSkeleton::draw()
{
	frame.draw();

	if(bDrawVelocity)
	{
		ofSetColor(255);
		for(int i=0; i<kinect::nui::SkeletonData::POSITION_COUNT; i++)
		{
			ofDrawBitmapString(ofToString(velocity[i], 2), frame.joints[i]);
		}
	}
}