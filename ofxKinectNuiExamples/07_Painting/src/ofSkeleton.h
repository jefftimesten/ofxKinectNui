#pragma once
#include "ofMain.h"
#include "ofSkeletonFrame.h"

class Particle : public ofVec2f {
public:
	ofVec2f velocity;
	ofColor color;
	float radius;
};


class ofSkeleton {
public:

	ofSkeleton();
	float age();
	void addFrame( ofSkeletonFrame& _frame );
	void draw();
	void update();
	void addParticles( int num, ofPoint location, ofPoint direction, float velocity );
	static bool bDrawVelocity;

protected:

	float lastUpdated;
	float velocity[kinect::nui::SkeletonData::POSITION_COUNT];
	ofPoint direction[kinect::nui::SkeletonData::POSITION_COUNT];
	ofSkeletonFrame frame;
	vector<Particle> particles;
};


