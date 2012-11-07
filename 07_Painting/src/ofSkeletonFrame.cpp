#include "ofSkeletonFrame.h"

float ofSkeletonFrame::maxValidArea=1.5;
float ofSkeletonFrame::minValidArea=0.01;
float ofSkeletonFrame::minValidHeight=.2;


//--------------------------------------------------------------
ofSkeletonFrame::ofSkeletonFrame(void)
{
	joints[0].z = -1;
}


//--------------------------------------------------------------------------------
bool ofSkeletonFrame::isValid() 
{ 
	if(joints[0].z == -1)
		return false;

    ofPoint min(FLT_MAX, FLT_MAX);
    ofPoint max(0, 0);
    for(int i=0; i<NUI_SKELETON_POSITION_COUNT; i++)
    {        
        if(joints[i].x > max.x) max.x = joints[i].x;
        if(joints[i].y > max.y) max.y = joints[i].y;
        if(joints[i].x < min.x) min.x = joints[i].x;
        if(joints[i].y < min.y) min.y = joints[i].y;
    }
           
    ofRectangle boundingRect(min.x, min.y, max.x-min.x, max.y-min.y);
    float area = boundingRect.width * boundingRect.height;

    if(!ofInRange(area, minValidArea, maxValidArea)) {
        if(area!=0) ofLog(OF_LOG_VERBOSE, "Area ("+ofToString(area)+") not in range");
        return false;
    }
    
    // If the foot is higher than the head, we've got a fucked up skeleton
    if(joints[NUI_SKELETON_POSITION_FOOT_LEFT].y < joints[NUI_SKELETON_POSITION_HEAD].y) {
        ofLog(OF_LOG_VERBOSE, "not valid bcz foot is above head");
        return false;
    }
    
    if(getAngleABC(NUI_SKELETON_POSITION_HIP_CENTER, NUI_SKELETON_POSITION_SPINE, NUI_SKELETON_POSITION_SHOULDER_CENTER) > 10) {
        ofLog(OF_LOG_VERBOSE, "not valid bcz of hip->spine->shoulder angle");
        return false;
    }
    
    if(boundingRect.height < minValidHeight) { 
        ofLog(OF_LOG_VERBOSE, "Min height not met. Height="+ofToString(boundingRect.height));
        return false;
    }
    
    if(joints[NUI_SKELETON_POSITION_FOOT_RIGHT].y < joints[NUI_SKELETON_POSITION_HEAD].y) {
		ofLog(OF_LOG_VERBOSE, "Right foot is above head");
        return false;
    }
    
    if((joints[NUI_SKELETON_POSITION_KNEE_LEFT].y < joints[NUI_SKELETON_POSITION_SHOULDER_CENTER].y)) {
		ofLog(OF_LOG_VERBOSE, "Left knee is above shoulders");
        return false;
	}
    
    if((joints[NUI_SKELETON_POSITION_KNEE_RIGHT].y < joints[NUI_SKELETON_POSITION_SHOULDER_CENTER].y)) {
		ofLog(OF_LOG_VERBOSE, "Right knee is above shoulders");
        return false;
	}
    
	return true;
}


//----------------------------------------------------------
float ofSkeletonFrame::getAngleABC( int _a, int _b, int _c )
{    
	ofPoint a = joints[_a];
	ofPoint b = joints[_b];
	ofPoint c = joints[_c];

    ofPoint ba = (a-b).getNormalized();
    ofPoint bc = (c-b).getNormalized();
    float angle = acos( ba.dot(bc) );
    return angle;
}

//--------------------------------------------------------------
void ofSkeletonFrame::draw(float x, float y, float w, float h, float d)
{
	ofPushMatrix();
	ofTranslate(x, y);

	ofPolyline pLine;
	ofPushStyle();
	ofSetColor(255);
	ofNoFill();
	ofSetLineWidth(2);

	// HEAD
	pLine.clear();
	pLine.addVertex(joints[NUI_SKELETON_POSITION_HIP_CENTER].x*w, joints[NUI_SKELETON_POSITION_HIP_CENTER].y*h, joints[NUI_SKELETON_POSITION_HIP_CENTER].z*d);
	pLine.addVertex(joints[NUI_SKELETON_POSITION_SPINE].x*w, joints[NUI_SKELETON_POSITION_SPINE].y*h, joints[NUI_SKELETON_POSITION_SPINE].z*d);
	pLine.addVertex(joints[NUI_SKELETON_POSITION_SHOULDER_CENTER].x*w, joints[NUI_SKELETON_POSITION_SHOULDER_CENTER].y*h, joints[NUI_SKELETON_POSITION_SHOULDER_CENTER].z*d);
	pLine.addVertex(joints[NUI_SKELETON_POSITION_HEAD].x*w, joints[NUI_SKELETON_POSITION_HEAD].y*h, joints[NUI_SKELETON_POSITION_HEAD].z*d);
	pLine.draw();
	
	// BODY_LEFT
	pLine.clear();
	pLine.addVertex(joints[NUI_SKELETON_POSITION_SHOULDER_CENTER].x*w, joints[NUI_SKELETON_POSITION_SHOULDER_CENTER].y*h, joints[NUI_SKELETON_POSITION_SHOULDER_CENTER].z*d);
	pLine.addVertex(joints[NUI_SKELETON_POSITION_SHOULDER_LEFT].x*w, joints[NUI_SKELETON_POSITION_SHOULDER_LEFT].y*h, joints[NUI_SKELETON_POSITION_SHOULDER_LEFT].z*d);
	pLine.addVertex(joints[NUI_SKELETON_POSITION_ELBOW_LEFT].x*w, joints[NUI_SKELETON_POSITION_ELBOW_LEFT].y*h, joints[NUI_SKELETON_POSITION_ELBOW_LEFT].z*d);
	pLine.addVertex(joints[NUI_SKELETON_POSITION_WRIST_LEFT].x*w, joints[NUI_SKELETON_POSITION_WRIST_LEFT].y*h, joints[NUI_SKELETON_POSITION_WRIST_LEFT].z*d);
	pLine.addVertex(joints[NUI_SKELETON_POSITION_HAND_LEFT].x*w, joints[NUI_SKELETON_POSITION_HAND_LEFT].y*h, joints[NUI_SKELETON_POSITION_HAND_LEFT].z*d);
	pLine.draw();

	// BODY_RIGHT
	pLine.clear();
	pLine.addVertex(joints[NUI_SKELETON_POSITION_SHOULDER_CENTER].x*w, joints[NUI_SKELETON_POSITION_SHOULDER_CENTER].y*h, joints[NUI_SKELETON_POSITION_SHOULDER_CENTER].z*d);
	pLine.addVertex(joints[NUI_SKELETON_POSITION_SHOULDER_RIGHT].x*w, joints[NUI_SKELETON_POSITION_SHOULDER_RIGHT].y*h, joints[NUI_SKELETON_POSITION_SHOULDER_RIGHT].z*d);
	pLine.addVertex(joints[NUI_SKELETON_POSITION_ELBOW_RIGHT].x*w, joints[NUI_SKELETON_POSITION_ELBOW_RIGHT].y*h, joints[NUI_SKELETON_POSITION_ELBOW_RIGHT].z*d);
	pLine.addVertex(joints[NUI_SKELETON_POSITION_WRIST_RIGHT].x*w, joints[NUI_SKELETON_POSITION_WRIST_RIGHT].y*h, joints[NUI_SKELETON_POSITION_WRIST_RIGHT].z*d);
	pLine.addVertex(joints[NUI_SKELETON_POSITION_HAND_RIGHT].x*w, joints[NUI_SKELETON_POSITION_HAND_RIGHT].y*h, joints[NUI_SKELETON_POSITION_HAND_RIGHT].z*d);
	pLine.draw();

	// LEG_LEFT
	pLine.clear();
	pLine.addVertex(joints[NUI_SKELETON_POSITION_HIP_CENTER].x*w, joints[NUI_SKELETON_POSITION_HIP_CENTER].y*h, joints[NUI_SKELETON_POSITION_HIP_CENTER].z*d);
	pLine.addVertex(joints[NUI_SKELETON_POSITION_HIP_LEFT].x*w, joints[NUI_SKELETON_POSITION_HIP_LEFT].y*h, joints[NUI_SKELETON_POSITION_HIP_LEFT].z*d);
	pLine.addVertex(joints[NUI_SKELETON_POSITION_KNEE_LEFT].x*w, joints[NUI_SKELETON_POSITION_KNEE_LEFT].y*h, joints[NUI_SKELETON_POSITION_KNEE_LEFT].z*d);
	pLine.addVertex(joints[NUI_SKELETON_POSITION_ANKLE_LEFT].x*w, joints[NUI_SKELETON_POSITION_ANKLE_LEFT].y*h, joints[NUI_SKELETON_POSITION_ANKLE_LEFT].z*d);
	pLine.addVertex(joints[NUI_SKELETON_POSITION_FOOT_LEFT].x*w, joints[NUI_SKELETON_POSITION_FOOT_LEFT].y*h, joints[NUI_SKELETON_POSITION_FOOT_LEFT].z*d);
	pLine.draw();

	// LEG_RIGHT
	pLine.clear();
	pLine.addVertex(joints[NUI_SKELETON_POSITION_HIP_CENTER].x*w, joints[NUI_SKELETON_POSITION_HIP_CENTER].y*h, joints[NUI_SKELETON_POSITION_HIP_CENTER].z*d);
	pLine.addVertex(joints[NUI_SKELETON_POSITION_HIP_RIGHT].x*w, joints[NUI_SKELETON_POSITION_HIP_RIGHT].y*h, joints[NUI_SKELETON_POSITION_HIP_RIGHT].z*d);
	pLine.addVertex(joints[NUI_SKELETON_POSITION_KNEE_RIGHT].x*w, joints[NUI_SKELETON_POSITION_KNEE_RIGHT].y*h, joints[NUI_SKELETON_POSITION_KNEE_RIGHT].z*d);
	pLine.addVertex(joints[NUI_SKELETON_POSITION_ANKLE_RIGHT].x*w, joints[NUI_SKELETON_POSITION_ANKLE_RIGHT].y*h, joints[NUI_SKELETON_POSITION_ANKLE_RIGHT].z*d);
	pLine.addVertex(joints[NUI_SKELETON_POSITION_FOOT_RIGHT].x*w, joints[NUI_SKELETON_POSITION_FOOT_RIGHT].y*h, joints[NUI_SKELETON_POSITION_FOOT_RIGHT].z*d);
	pLine.draw();

	ofSetColor(0, 0, 255);
	ofSetLineWidth(0);
	ofFill();
	for(int i = 0; i < NUI_SKELETON_POSITION_COUNT; ++i){
		ofPushMatrix();
		ofTranslate(joints[i].x*w, joints[i].y*h, joints[i].z*d);
		ofCircle(0, 0, 5);
		ofPopMatrix();
	}


	ofPopStyle();
	ofPopMatrix();
}
