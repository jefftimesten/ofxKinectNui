#pragma once
#include "ofMain.h"
#include "ofSkeletonFrame.h"

class Particle : public ofVec3f {
public:
	ofColor color;
	float born, age, radius;
};


class ofSkeleton {
public:

	ofSkeleton();
	float age();
	void addFrame( ofSkeletonFrame& _frame );
	void draw(float x, float y, float w, float h, float d);
	void update();

protected:

	float lastUpdated;
	float velocity[kinect::nui::SkeletonData::POSITION_COUNT];
	ofPoint direction[kinect::nui::SkeletonData::POSITION_COUNT];
	ofSkeletonFrame frame;
	vector<Particle> particles;
};


