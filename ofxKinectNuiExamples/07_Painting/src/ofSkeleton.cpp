 
#include "ofSkeleton.h"


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
		velocity[i] = ofDist(_frame.joints[i].x, _frame.joints[i].y, frame.joints[i].x, frame.joints[i].y ) / t;
		direction[i] = (frame.joints[i] - _frame.joints[i]).normalize();
	}

	frame = _frame;
	lastUpdated = ofGetElapsedTimef();


	if(velocity[NUI_SKELETON_POSITION_HAND_LEFT] > .1)
	{
		Particle p;
		p.color.set(255, 0, 0);
		p.set( frame.joints[NUI_SKELETON_POSITION_HAND_LEFT] );
		p.born = ofGetElapsedTimef();
		particles.push_back( p );
	}

	if(velocity[NUI_SKELETON_POSITION_HAND_RIGHT] > .1)
	{
		Particle p;
		p.color.set(0, 255, 0);
		p.set( frame.joints[NUI_SKELETON_POSITION_HAND_RIGHT] );
		p.born = ofGetElapsedTimef();
		particles.push_back( p );
	}

	if(velocity[NUI_SKELETON_POSITION_HEAD] > .1)
	{
		Particle p;
		p.color.set(0, 0, 255);
		p.set( frame.joints[NUI_SKELETON_POSITION_HEAD] );
		p.born = ofGetElapsedTimef();
		particles.push_back( p );
	}
}


// --------------------------------------------
void ofSkeleton::update()
{
	for(int i=0; i<particles.size(); i++)
	{
		float age = ofGetElapsedTimef() - particles[i].born;
		if(age < 5) 
		{
			particles[i].radius = sin((age/5.0) * PI) * 30.0;
		} 
		else 
		{
			particles.erase( particles.begin() + i );
		}
	}

}

// --------------------------------------------
void ofSkeleton::draw(float x, float y, float w, float h, float d)
{
	if(age() < 2)
		frame.draw(x, y, w, h, d);

	// Draw particles
	for(int i=0; i<particles.size(); i++)
	{
		ofSetColor(particles[i].color);
		ofPushMatrix();
		ofTranslate(particles[i].x*w, particles[i].y*h, particles[i].z*d);
		ofCircle(0, 0, particles[i].radius);
		ofPopMatrix();
	}
}