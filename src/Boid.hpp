//
//  Boid.hpp
//  boidsLine
//
//  Created by Kota Kawakami on 2018/02/15.
//

#ifndef Boid_hpp
#define Boid_hpp

#include <stdio.h>
#include "ofMain.h"

class Boid{
    
    ofVec3f location;        // 位置
    ofVec3f velocity;        // 速度
    ofVec3f acceleration;    // 加速度
    ofVec3f desired;         // 必要な速度
    ofVec3f steer;           // 操舵力(必要な速度 - 現在の速度)
    ofVec3f diff;            // 近いビークルから遠ざかる方向のベクトル
    ofVec3f sum;             // 隣接したボイドの合計ベクトル
  
    ofColor lineCol;
    
    vector<ofVec3f> history; // 軌跡
    
    float r;
    float maxForce;
    float maxSpeed;
    
    float sepVal;
    float aliVal;
    float cohVal;
    
public:
  
    Boid(){};
    Boid(float x, float y, float z);
   
    void update();
    void display(vector<Boid> boids);
    void applyForce(ofVec3f force);
    void flock(vector<Boid> boids, float sepVal, float aliVal, float cohVal);
   
    ofVec2f seek(ofVec3f target);
    ofVec2f separate(vector<Boid> boids);     // 群れのルール1: 分離
    ofVec2f align(vector<Boid> boids);        // 群れのルール2: 整列
    ofVec2f cohesion(vector<Boid> boids);     // 群れのルール3: 結合
};

#endif /* Boid_hpp */
