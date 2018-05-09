//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING
#include <iostream>
using namespace std;
#endif

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove
// Replace "..." in bisectionHelper() with any parameter(s)
// you need to ensure termination when precision and
// minIntervalSize are too tightly specified.
//

bool projectileDestination(const float h, const float v, const float m,
                           const float theta, const float d,
                           const float t, const float b, const float w,
                           float& destX, float& destY);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//
// Return std::numeric_limits<float>::quiet_NaN() (comes from
// <limits>) if cannot compute the root for some reason
//

bool projectileDestination(const float h, const float v, const float m,
                           const float theta, const float d,
                           const float t, const float b, const float w,
                           float& destX, float& destY) {
    
    if (theta<0 || theta>180 || w<0 || b<0 || h<0 || v<0 || m<=0){
        return 0;
    }
    
    
    float pi=3.1415926535897;
    float vx;
    float vy;
    float time;
    float xd;
    
    if (theta==90 || v==0){
        destX=0;
        destY=h;
        return 1;
    }
    
    if (theta>90 && theta <=180){
        vx=cos((180-theta)*pi/180)*v;
        vy=sin((180-theta)*pi/180)*v;
        time = ( (-1)*vy-sqrt(vy*vy-4*(-4.9)*h) ) / (-9.8);
        xd = vx*time;
        destX=(-1)*xd;
        destY=0;
        return 1;
    }
    
    if (theta>0 && theta<90){
        vx=cos(theta*pi/180)*v;
        vy=sin(theta*pi/180)*v;
        float timemax = ( (-1)*vy-sqrt(vy*vy-4*(-4.9)*h) ) / (-9.8);
        float vxmax = vx*timemax;
        time = ( (-1)*vy-sqrt(vy*vy-4*(-4.9)*(h-t)) ) / (-9.8);
        
        if (vxmax<=b){
            destX=vxmax;
            destY=0;
            return 1;
        }
        
        if (vxmax>b && time!=time){
            destX=b;
            time=b/vx;
            destY=h+vy*time-4.9*time*time;
            return 1;
        }
        
        if (time==time){
            
            if (vxmax>b && (vx*time) < b){
                destX = b;
                time = b/vx;
                destY = h+vy*time-4.9*time*time;
                return 1;
            }
            
            if (vxmax>b && (vx*time) >= b && (vx*time) <= b+w){
                destX=vx*time;
                destY=t;
                return 1;
            }
            
            if (vxmax>b && (vx*time > b+w)){
                destX=vxmax;
                destY=0;
                return 1;
            }
            
        }
    }
    
    return 1;
}

//////////////////////////////////////////////////////////////
//
// Test Driver
//
// Do not remove the #ifndef and its associated #endif
// This is required so that when you submit your code,
// this test driver will be ignored by Marmoset
//

#ifndef MARMOSET_TESTING

#define isNaN(X) (X != X)  // NaN is the only float that is not equal to itself

int main(const int argc, const char* const argv[]) {
    
    // Some test driver code here ....
    
    float h = 50;
    float v = 9.2;
    float m = 1;
    float theta = 45;        // Angle in degrees; will need to be converted by function
    float d = 100;
    float t = 1;
    float b = 5000000;
    float w = 20;
    
    float hitsAtX;
    float hitsAtY;
    
    if (projectileDestination(h,v,m,theta,d,t,b,w,hitsAtX,hitsAtY))
        cout << "Projectile hit at (" << hitsAtX << ", " << hitsAtY << ")" <<endl;
    else
        cout << "Unable to calculate where projectile hits." << endl;
    return 0;
}

#endif
