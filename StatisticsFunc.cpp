//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <limits>

//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING

#include <iostream>

using namespace std;

bool statistics(const float dataset[], const int size,
                float& min, float& avg, float& max,
	        float& popSD, float& smplSD, float& mdn);

float minimum(const float dataset[], const int size);
float average(const float dataset[], const int size);
float maximum(const float dataset[], const int size);
float popStdDev(const float dataset[], const int size);
float smplStdDev(const float dataset[], const int size);
float median(const float dataset[], const int size);
#endif

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  

bool statistics(const float dataset[], const int size,
	   float& min, float& avg, float& max,
	   float& popSD, float& smplSD, float& mdn) {
    
    float data[size];
    
    for (int i=0;i<size;i++){
        data[i]=dataset[i];
    }
    
    int n = sizeof(data);
    int m = sizeof(float);
    int z = n/m;
    
    if (size<z){
        return 0;
    }
    
    if (size<=0){
        return 0;
    }
    
    if (size>z){
        return 0;
    }
    
    if (size==z && size!=0 ){
        min=minimum(dataset,size);
        max=maximum(dataset,size);
        avg = average(dataset,size);
        mdn = median(dataset,size);
        popSD = popStdDev(dataset,size);
        smplSD = smplStdDev(dataset,size);
        return 1;
    }
    
}

float minimum(const float dataset[], const int size) {
    float minf = FLT_MAX;
    for (int i=0;i<size;i++){
        if(dataset[i]<minf){
            minf=dataset[i];
        }
    }
    return minf;
}

float average(const float dataset[], const int size) {
    float sum=0;
    float avgf;
    for (int i=0;i<size;i++){
        sum=sum+dataset[i];
    }
    avgf=sum/size;
    return avgf;
}

float maximum(const float dataset[], const int size) {
    float maxf = -FLT_MAX;
    for (int i=0;i<size;i++){
        if(dataset[i]>maxf){
            maxf=dataset[i];
        }
    }
    return maxf;
}

float popStdDev(const float dataset[], const int size) {
    float squaresum = 0;
    float pd;
    float avg3 = average(dataset, size);
    for (int i=0;i<size;i++){
        squaresum = squaresum + pow(dataset[i]-avg3,2);
    }
    pd = sqrt(1/((float)size)*squaresum);
    return pd;
}

float smplStdDev(const float dataset[], const int size) {
    float squaresum2 = 0;
    float sd;
    float avg4 = average(dataset, size);
    for (int i=0;i<size;i++){
        squaresum2 = squaresum2 + pow(dataset[i]-avg4,2);
    }
    
    if (size==1){
    
        return std::numeric_limits<int>::max();
    
    }else{
        
        sd = sqrt(1/((float)size-1)*squaresum2);
        return sd;
    }
}

float median(const float dataset[], const int size) {
    float temp;

    int middle=size/2;
    float med;
    float data[size];
    
    for (int i=0;i<size;i++){
        data[i]=dataset[i];
    }
    
    for (int i=0;i<size;i++){
        for (int j=0;j<(size-i-1);j++){
            if (data[j+1]<data[j]){
                temp=data[j];
                data[j]=data[j+1];
                data[j+1]=temp;
            }
        }
    }
    
    if (size%2 == 0){
        med = (data[middle-1]+data[middle])/2;
    } else {
        med = data[middle];
    }
    return med;
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

int main(const int argc, const char* const argv[]) {
  int size = 5;
  float dataset[] = {1,2,3,4,5};
  float min;
  float avg;
  float max;
  float popStDev;
  float smplStDev;
  float median;

  if (statistics(dataset, size, min, avg, max, popStDev, smplStDev, median)) {
    cout << "Minimum: " << min << endl
	 << "Average: " << avg << endl
	 << "Median:  " << median << endl
	 << "Maximum: " << max << endl
	 << "Population Standard Deviation: " << popStDev << endl
	 << "Sample Standard Deviation:     " << smplStDev << endl;
  }
  else
    cout << "Error: unable to compute statistics" << endl;

  return 0;
}

#endif
