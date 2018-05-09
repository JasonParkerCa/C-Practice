//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include <math.h>
#include <float.h>

//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING
#include <iostream>
using namespace std;


// Sample function for which you need to find the root

float f(const float x) {
    return 3.2*x*x*x - 2.1*x - 23.0;
}

#endif

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove
// Replace "..." in bisectionHelper() with any parameter(s)
// you need to ensure termination when precision and
// minIntervalSize are too tightly specified.
//

float bisectionHelper(const float left, const float right,
                      const float precision, const float minIntervalSize, float Minimum);
float bisection(const float left, const float right,
                const float precision, const float minIntervalSize);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//
// Return std::numeric_limits<float>::quiet_NaN() (comes from
// <limits>) if cannot compute the root for some reason
//

float bisectionHelper(const float left, const float right,
                      const float precision, const float minIntervalSize, float Minimum){
    
    if (precision < Minimum || minIntervalSize < Minimum || (left>right) || (f(left)*f(right)>0)){
        return std::numeric_limits<float>::quiet_NaN();
    }
    
    if (left<(-FLT_MAX) || right>(FLT_MAX) || left>FLT_MAX || right<-(FLT_MAX) || isNaN(left) || isNaN(right) || isNaN(f(left)) || isNaN(f(right)) ) {
        return std::numeric_limits<float>::quiet_NaN();
    }
    
    float midpoint = ( left + right ) / 2;
    
    if (fabs(f(left))<=precision || f(left)==0){
        return left;
    }
    
    if (fabs(f(right))<=precision || f(right)==0){
        return right;
    }
    
    if (fabs(f(midpoint))<=precision || (right-left)<=minIntervalSize || f(midpoint)==0){
        return midpoint;
    }else{
        if (f(left)*f(midpoint) <= 0){
            return bisectionHelper(left,midpoint,precision,minIntervalSize,Minimum);
        } else {
            return bisectionHelper(midpoint,right,precision,minIntervalSize,Minimum);
        }
    }
}


float bisection(const float left, const float right,
                const float precision, const float minIntervalSize) {
    float min = FLT_MIN;
    return bisectionHelper(left, right, precision, minIntervalSize,min);
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

    return 0;
}

#endif
