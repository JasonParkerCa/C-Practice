//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include <limits>
#include <math.h>

//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//


#ifndef MARMOSET_TESTING
#include <iostream>
using namespace std;
#endif

#define NaN std::numeric_limits<float>::quiet_NaN()
#define isNaN(X) (X != X) // NaN is the only float that is not equal to itself

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove

bool hitTargetGivenAngle (const float h, const float m, const float theta,
                          const float d, const float step, const float k,
                          const float t, const float b, const float w, float& v);

float Calculation(const float h,const float d, const float m, float angle, float v, const float k, float time);

float BisectionHelper(const float h, const float m, const float theta,
                      const float d, const float step, const float k,
                      const float t, const float b, const float w,float v1, float v2, float percision,  float size);
float Bisection(const float h, const float m, const float theta,
                const float d, const float step, const float k,
                const float t, const float b, const float w,float v1, float v2, float percision, float size);


const float pi=3.1415926535897;


//////////////////////////////////////////////////////////////
//
// Your code here ...
//

float Calculation(const float h,const float d, const float m, float angle, float v, const float k, float time){
    float x=0;
    float y=0;
    angle=angle/180*pi;
    float vx=v*cos(angle);
    float vy=v*sin(angle);
    float ax=0,ay=0;
    int i=0;
    
    while (x<d && i<1000000){
        x+=vx*time;
        y+=vy*time;
        
        ax=k*v*v*cos(angle)/m;
        ay=k*v*v*sin(angle)/m+9.8;
        
        vx=vx - ax * time;
        vy=vy - ay * time;
        
        v=sqrt(vx*vx+vy*vy);
        angle=atan(vy/vx);
        i++;
    }
    return y;
}

float BisectionHelper(const float h, const float m, const float theta,
                      const float d, const float step, const float k,
                      const float t, const float b, const float w,float v1, float v2, float precision, float size){
    
    float y1, y2, midpoint, ymidpoint, interval;
    interval=v2-v1;
    midpoint=(v1+v2)/2;
    y1=Calculation(h,d,m,theta,v1,k,step)-t+h;
    y2=Calculation(h,d,m,theta,v2,k,step)-t+h;
    ymidpoint=Calculation(h,d,m,theta,midpoint,k,step)-t+h;
    
    if (fabs(y1)<=precision){
        return v1;
    }
    if (fabs(y2)<=precision){
        return v2;
    }
    if (fabs(midpoint)<=precision||interval<=size){
        return midpoint;
    }
    
    if ( y1*ymidpoint>0 ){
        return BisectionHelper(h, m, theta, d, step, k, t, b, w, midpoint,v2,precision,size);
    } else {
        return BisectionHelper(h, m, theta, d, step, k, t, b, w, v1,midpoint,precision,size);
    }
    
}

float Bisection(const float h, const float m, const float theta,
                const float d, const float step, const float k,
                const float t, const float b, const float w,float v1, float v2, float percision, float size){
    
    if (v1>=v2||percision<0||size<0){
        return NaN;
    }
    
    return BisectionHelper(h, m, theta, d, step, k, t, b, w, v1, v2, percision, size);
}

bool hitTargetGivenAngle (const float h, const float m, const float theta,
                          const float d, const float step, const float k,
                          const float t, const float b, const float w, float& v) {
    
    if (h<0||m<=0||d<0||b<0||w<0||step<=0||k<0||theta>=90||theta<0){
        return false;
    }
    
    
    float vmin, vmax, percision,size;
    vmin=1;
    vmax=200;
    percision=0.000001;
    size=0.00001;
    
    v=Bisection(h, m, theta, d, step, k, t, b, w, vmin, vmax, percision,size);
    
    return true;
    
}


#ifndef MARMOSET_TESTING
int main() {
    
    // Some test driver code here ....
    float h = 50;
    float d = 60;
    float b = 40;
    float t = 0;
    float w = 30;
    float m = 0.5;
    float step = 0.01;
    float k = 0;
    float theta = 68.81; // Angle in degrees;
    float v = 25;
    
    cout << endl << "Given angle: " << theta << endl;
    cout << "Target at (" << d << "," << t << ")" << endl;
    if (hitTargetGivenAngle (h, m, theta, d, step, k, t, b, w, v)) {
        cout << "required initial velocity: " << v << endl << endl;
    }
    else {
        cout << "cannot calculate the velocity" << endl << endl;
    }
    
    return 0;
}
#endif


