//
//  Boid.cpp
//  boidsLine
//
//  Created by Kota Kawakami on 2018/02/15.
//

#include "Boid.hpp"
#include "ofMain.h"

Boid::Boid(float x, float y, float z){
    
    acceleration = ofVec3f(0, 0, 0);
    
    velocity = ofVec3f(3.0, 3.0, 3.0);
    location = ofVec3f(x, y, z);
    
    maxSpeed = 55;
    maxForce = 0.1;
    
    lineCol = ofColor(ofRandom(255), ofRandom(255), ofRandom(255), 100);
}

void Boid::applyForce(ofVec3f force){
    
    acceleration += force;
}

ofVec2f Boid::seek(ofVec3f target){
    
    desired = target - location;
    
    desired.scale(maxSpeed);
    
    steer = desired - velocity;
    steer.limit(maxForce);
    
    return steer;
}

ofVec2f Boid::separate(vector<Boid> boids){
    
    float separationThreshold = 30;
    sum.set(0, 0, 0);
    int count = 0;
    
    for(vector<Boid>::iterator it = boids.begin(); it != boids.end(); ++it){
        
        float d = location.distance((*it).location);
        
        if ((d > 0) && (d < separationThreshold)) {
            
            diff = location - (*it).location;
            diff.normalize();
            diff /= d;
            sum  += diff;
            count++;
        }
    }
    
    if (count > 0) {
        
        sum /= count;
        sum.scale(maxSpeed);
        steer = sum - velocity;
        steer.limit(maxForce);
        
    }
    
    return steer;
}

ofVec2f Boid::align(vector<Boid> boids){
    
    float neighborDist = 10;
    int count          = 0;
    sum.set(0, 0, 0);
    
    for(vector<Boid>::iterator it = boids.begin(); it != boids.end(); ++it){
        
        float d = location.distance((*it).location);
        
        if((d > 0) && (d < neighborDist)){
            
            sum += (*it).velocity;
            count++;
        }
    }
    
    if(count > 0){
        
        sum /= count;
        sum.scale(maxSpeed);
        
        steer = sum - velocity;
        steer.limit(maxForce);
        
        return steer;
    
    } else {
     
        return ofVec3f(0, 0, 0);
    }
}

ofVec2f Boid::cohesion(vector<Boid> boids){
    
    float neighborDist = 80;
    int count          = 0;
    sum.set(0, 0, 0);
    
    for(vector<Boid>::iterator it = boids.begin(); it != boids.end(); ++it){
        
        float d = location.distance((*it).location);
        
        if((d > 0) && (d < neighborDist)){
            
            sum += (*it).location;
            count++;
        }
    }
    
    if(count > 0){
        
        sum /= count;
        
        return seek(sum);
    
    } else {
        
        return ofVec3f(0, 0, 0);
    }
}

void Boid::flock(vector<Boid> boids, float sepVal, float aliVal, float cohVal){
    
    ofVec3f sep = separate(boids);
    ofVec3f ali = align(boids);
    ofVec3f coh = cohesion(boids);
    
    sep *= sepVal;
    ali *= aliVal;
    coh *= cohVal;

    applyForce(sep);
    applyForce(ali);
    applyForce(coh);
}


void Boid::update(){
    
    float bounceDistance = 500;
    float bounceForce    = 0.5f;
    
    if(location.x < bounceDistance/2){

        applyForce(ofVec3f(bounceForce,0, 0));

    }else if(location.x > ofGetWidth()-bounceDistance/2){

        applyForce(ofVec3f(-bounceForce,0, 0));

    }

    if(location.y < bounceDistance/2){

        applyForce(ofVec3f(0, bounceForce, 0));

    }else if(location.y > ofGetHeight()-bounceDistance/2){

        applyForce(ofVec3f(0,-bounceForce, 0));

    }

    if(location.z < -bounceDistance/2){

        applyForce(ofVec3f(0, 0, bounceForce));

    }else if(location.z > bounceDistance/2){

        applyForce(ofVec3f(0, 0, -bounceForce));

    }
    
    velocity += acceleration;
    velocity.limit(maxSpeed);
    location += velocity;
    acceleration *= 0;
    
    history.push_back(location);

    if (history.size() > 100) {
        history.erase(history.begin());
    }
    
}

void Boid::display(vector<Boid> boids){
    
    ofBeginShape();
    ofNoFill();
    ofSetColor(lineCol);
    ofSetLineWidth(2);

    for (vector<ofVec3f>::iterator it = history.begin(); it != history.end(); ++it) {
        ofVertex((*it).x, (*it).y, (*it).z);
    }
    
    ofEndShape();
}
