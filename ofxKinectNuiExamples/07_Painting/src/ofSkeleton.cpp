
#include "ofSkeleton.h"

bool ofSkeleton::bDrawVelocity = false;

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
}


// --------------------------------------------
void ofSkeleton::addParticles( int num, ofPoint location, ofPoint direction, float velocity )
{
	ofColor c;
	for(int i=0; i<num; i++)
	{
		Particle p;
		p.color.setHsb(ofRandom(255), 255, 255);
		p.set( location );
		p.radius = ofRandom(2, 5);
		p.velocity = direction * (velocity * ofRandomf());
		particles.push_back( p );
	}
}

// --------------------------------------------
void ofSkeleton::update()
{
	for(int i=0; i<particles.size(); i++)
	{
		particles[i].velocity.y += .098;
		particles[i] += particles[i].velocity;
	}
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

	for(int i=0; i<particles.size(); i++)
	{
		ofSetColor(particles[i].color);
		ofCircle(particles[i], particles[i].radius);
	}
}