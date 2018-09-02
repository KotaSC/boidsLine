//
//  Flock.cpp
//  boidsLine
//
//  Created by 川上皓大 on 2018/02/19.
//

#include "Flock.hpp"
#include "ofApp.h"

Flock::Flock(int _numBoid){
    
    numBoid  = _numBoid;
   
    for (int i = 0; i < numBoid; i++) {
        
        Boid newBoid = Boid(ofGetWidth()/2, ofGetHeight()/2, ofRandom(-70, 70));
        boids.push_back(newBoid);
    }
}

void Flock::update(float sepVal, float aliVal, float cohVal){
    
    for(vector<Boid>::iterator it = boids.begin(); it != boids.end(); ++it){
        
        (*it).flock(boids, sepVal, aliVal, cohVal);
        (*it).update();
    }
}

void Flock::display(){
    
    for(vector<Boid>::iterator it = boids.begin(); it != boids.end(); ++it){
        
        (*it).display(boids);
    }
}

