//
//  Flock.hpp
//  boidsLine
//
//  Created by 川上皓大 on 2018/02/19.
//

#ifndef Flock_hpp
#define Flock_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Boid.hpp"

class Flock{
    
    vector<Boid> boids;
    int numBoid;       
    
public:
    
    Flock(){};
    Flock(int _numBoid);
    
    void display();
    void update(float sepVal, float aliVal, float cohVal);
};

#endif /* Flock_hpp */
