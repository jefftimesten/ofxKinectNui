#pragma once
#include "ofMain.h"
#include "ofSkeletonFrame.h"


class WaveGestureDetector {
public:

	WaveGestureDetector();
	void add( ofPoint* direction );
	bool isDone() { return step==4; }
	void reset();
	int trackingJoint;

protected:
	void advance();
	float lastAdvance;
	int step;
};