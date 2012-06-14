#include "WaveGestureDetector.h"

// ----------------------------------------------------
WaveGestureDetector::WaveGestureDetector() 
{
	step=0;
	lastAdvance=0;
	trackingJoint = NUI_SKELETON_POSITION_HAND_RIGHT;
}


// ----------------------------------------------------
void WaveGestureDetector::add(ofPoint* direction ) 
{
	float secondsSinceLastAdvance = ofGetElapsedTimef()-lastAdvance;


	// To activate step 1: right hand x direction is positive
	if(step == 0)
	{
		if(direction[trackingJoint].x > 0)
		{
			advance();
		}
	}

	// Reset if: right hand x direction is negative
	// To activate step 2: we must be in step 1 for more than .5 seconds
	// In other words: right hand must move right for more than a half second
	if(step==1)
	{
		if(direction[trackingJoint].x < 0)
		{
			reset();
		} 
		else if( secondsSinceLastAdvance > .3 )
		{
			advance();
		}
	} 


	// If we don't advance again within a second, reset the gesture
	// To activate step 3: x direction must turn negative
	if(step==2)
	{
		if(secondsSinceLastAdvance > 1) 
		{
			reset();
		}

		if(direction[trackingJoint].x < 0)
		{
			advance(  );
		}
	}
	
	// If x direction turns positive, reset the gesture
	// If the hand moves left for a half second, 
	if(step==3)
	{
		if(direction[trackingJoint].x > 0) 
		{
			reset();
		} 
		else if( secondsSinceLastAdvance > .5 ) 
		{
			advance();
		}
	}

	// Win!
	// But if the gesture isn't "manually" reset within 2 seconds, get rid of it.
	if(step==4)
	{
		if(secondsSinceLastAdvance > 2)
		{
			reset();
		}
	}
}


// ----------------------------------------------------
void WaveGestureDetector::advance()
{
	step++;
	if(trackingJoint==NUI_SKELETON_POSITION_HAND_RIGHT)
		cout << "advance: " << step << endl;
	lastAdvance = ofGetElapsedTimef();
}


// ----------------------------------------------------
void WaveGestureDetector::reset()
{
	step=0;
	if(trackingJoint==NUI_SKELETON_POSITION_HAND_RIGHT)
	cout << "reset" << endl;
}
