#pragma once
#include "ofMain.h"
#include "ofSkeletonFrame.h"


class WaveGesture {
public:
	WaveGesture() 
	{
		step=0;
		lastAdvance=0;
	}

	void add( ofSkeletonFrame& frame, float* velocity ) 
	{
		float secondsSinceLastAdvance = ofGetElapsedTimef()-lastAdvance;

		// To activate step 1: right hand velocity is positive
		if(step == 0)
		{
			if(velocity[NUI_SKELETON_POSITION_HAND_RIGHT] > 0)
			{
				advance( frame.joints[NUI_SKELETON_POSITION_HAND_RIGHT] );
			}
		}

		// Reset if: right hand velocity is negative
		// To activate step 2: we must be in step 1 for more than .5 seconds
		// In other words: right hand must move right for more than a half second
		if(step==1)
		{
			if(velocity[NUI_SKELETON_POSITION_HAND_RIGHT] < 0)
			{
				reset();
			} 
			else if( secondsSinceLastAdvance > .5 )
			{
				advance( frame.joints[NUI_SKELETON_POSITION_HAND_RIGHT] );
			}
		} 


		// If we don't advance again within a second, reset the gesture
		// To activate step 3: velocity must turn negative
		if(step==2)
		{
			if(secondsSinceLastAdvance < 1) 
			{
				reset();
			}

			if(velocity[NUI_SKELETON_POSITION_HAND_RIGHT] < 0)
			{
				advance( frame.joints[NUI_SKELETON_POSITION_HAND_RIGHT] );
			}
		}
	
		// If velocity turns positive, reset the gesture
		// If the hand moves left for a half second, 
		if(step==3)
		{
			if(velocity[NUI_SKELETON_POSITION_HAND_RIGHT] > 0) 
			{
				reset();
			} 
			else if( secondsSinceLastAdvance > .5 ) 
			{
				advance( frame.joints[NUI_SKELETON_POSITION_HAND_RIGHT] );
			}
		}

		// Win!
		if(step==4)
		{
			cout << "wave!" << endl;
			reset();
		}
	}

	void advance(ofPoint p)
	{
		step++;
		points.push_back( p );
		lastAdvance = ofGetElapsedTimef();
	}

	void reset()
	{
		step=0;
		points.clear();
	}

	void draw()
	{
		ofPushStyle();
		ofSetColor(255, 255, 0);
		for(int i=0; i<points.size(); i++)
			ofCircle(points[i], 4);
		ofPopStyle();
	}

	float lastAdvance;
	int step;
	vector<ofPoint> points;
};

class ofSkeleton {
public:

	ofSkeleton();
	float age();
	void addFrame( ofSkeletonFrame& _frame );
	void draw();

	static bool bDrawVelocity;

protected:

	WaveGesture wave;
	float lastUpdated;
	float velocity[kinect::nui::SkeletonData::POSITION_COUNT];
	ofSkeletonFrame frame;
};


