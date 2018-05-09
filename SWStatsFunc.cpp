//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include <float.h>
#include <limits>
#include <math.h>

//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING

#include <iostream>

using namespace std;

int SWStats(const float dataset[], const int size,
            const int currentSample, const int windowSize,
            float& min, float& avg, float& max,
            float& smplSD, float& mdn);

int SWMinimum(const float dataset[], const int size,
              const int currentSample, const int windowSize,
              float& minimum);
int SWAverage(const float dataset[], const int size,
              const int currentSample, const int windowSize,
              float& average);
int SWMaximum(const float dataset[], const int size,
              const int currentSample, const int windowSize,
              float& maximum);
int SWSmplStdDev(const float dataset[], const int size,
                 const int currentSample, const int windowSize,
                 float& smplStdDev);
int SWMedian(const float dataset[], const int size,
             const int currentSample, const int windowSize,
             float& median);
#endif

//////////////////////////////////////////////////////////////
//
// Your code here ...
//

int SWStats(const float dataset[], const int size,
            const int currentSample, const int windowSize,
            float& min, float& avg, float& max,
            float& smplSD, float& mdn) {
    
    if (windowSize==1){
        return 1;
    }
    
    if (windowSize>=size){
        SWMinimum(dataset,size,currentSample,windowSize,min);
        SWAverage(dataset,size,currentSample,windowSize,avg);
        SWMaximum(dataset,size,currentSample,windowSize,max);
        SWMedian(dataset,size,currentSample,windowSize,mdn);
        SWSmplStdDev(dataset,size,currentSample,windowSize,smplSD);
        
        return 1;
    }
    
    if (windowSize==0){
        return -1;
    }
    
    if (windowSize<0){
        return -1;
    }
    
    if (windowSize<size && windowSize>1){
        SWMinimum(dataset,size,currentSample,windowSize,min);
        SWAverage(dataset,size,currentSample,windowSize,avg);
        SWMaximum(dataset,size,currentSample,windowSize,max);
        SWMedian(dataset,size,currentSample,windowSize,mdn);
        SWSmplStdDev(dataset,size,currentSample,windowSize,smplSD);
        return 0;
    }
    return 0;
}

int SWMinimum(const float dataset[], const int size,
              const int currentSample, const int windowSize,
              float& minimum) {
    
    minimum = FLT_MAX;
    
    if (currentSample<windowSize){
        for (int i=0;i<=currentSample;i++){
            
            if (dataset[i]<minimum){
                minimum = dataset[i];
            }
        }
    }
    
    if (currentSample>=windowSize){
        for (int k=currentSample+1-windowSize;k<=currentSample;k++)
        {
            if (dataset[k]<minimum){
                minimum = dataset[k];
            }
        }
    }
    return minimum;
}

int SWAverage(const float dataset[], const int size,
              const int currentSample, const int windowSize,
              float& average) {
    float sum=0;
    if (currentSample<windowSize){
        for (int i=0;i<=currentSample;i++){
            sum=sum+dataset[i];
        }
        sum=sum+(windowSize-currentSample-1)*dataset[0];
        average=sum/windowSize;
    }
    
    if (currentSample>=windowSize){
        for (int k=currentSample+1-windowSize;k<=currentSample;k++)
        {
            sum=sum+dataset[k];
        }
        average=sum/windowSize;
    }
    return average;
}

int SWMaximum(const float dataset[], const int size,
              const int currentSample, const int windowSize,
              float& maximum) {
    maximum = -FLT_MAX;
    
    if (currentSample<windowSize){
        for (int i=0;i<=currentSample;i++){
            
            if (dataset[i]>maximum){
                maximum = dataset[i];
            }
        }
    }
    
    if (currentSample>=windowSize){
        for (int k=currentSample+1-windowSize;k<=currentSample;k++)
        {
            if (dataset[k]>maximum){
                maximum = dataset[k];
            }
        }
    }
    return maximum;
}

int SWSmplStdDev(const float dataset[], const int size,
                 const int currentSample, const int windowSize,
                 float& smplStdDev) {
    
    float squaresum =0;
    float avgf;
    SWAverage(dataset,size,currentSample,windowSize,avgf);
    
    if (currentSample<windowSize){
        for (int i=0;i<=currentSample;i++){
            squaresum=squaresum+pow(dataset[i]-avgf,2);
        }
        squaresum=squaresum+(windowSize-currentSample-1)*pow(dataset[0]-avgf,2);
        
        smplStdDev = sqrt(1/((float)windowSize-1)*squaresum);
    }
    
    if (currentSample>=windowSize){
        for (int k=currentSample+1-windowSize;k<=currentSample;k++)
        {
            squaresum=squaresum+pow(dataset[k]-avgf,2);
        }
        smplStdDev = sqrt(1/((float)windowSize-1)*squaresum);
    }
    return smplStdDev;
}

int SWMedian(const float dataset[], const int size,
             const int currentSample, const int windowSize,
             float& median) {
    
    float temp;
    int middle;
    
    if (currentSample<windowSize){
        float data1[windowSize];
        for (int i=0;i<windowSize;i++){
            data1[i]= (i<=currentSample)? dataset[i]:dataset[0];
        }
        
        for (int i=0;i<windowSize;i++){
            for (int j=0;j<windowSize-i-1;j++){
                if (data1[j+1]<data1[j]){
                    temp=data1[j];
                    data1[j]=data1[j+1];
                    data1[j+1]=temp;
                }
            }
        }
        middle=(windowSize)/2;
        if (windowSize%2 ==0){
            median=(data1[middle-1]+data1[middle])/2;
        } else {
            median=data1[middle];
        }
    }
    
    
    if (currentSample>=windowSize){
        float data2[windowSize];
        int index=0;
        for (int i=currentSample+1-windowSize;i<=currentSample;i++){
            data2[index]=dataset[i];
            index++;
        }
        
        for (int i=0;i<windowSize;i++){
            for (int j=0;j<(windowSize-i-1);j++){
                if (data2[j+1]<data2[j]){
                    temp=data2[j];
                    data2[j]=data2[j+1];
                    data2[j+1]=temp;
                }
            }
        }
        middle=windowSize/2;
        if (windowSize%2 ==0){
            median=(data2[middle-1]+data2[middle])/2;
        } else {
            median=data2[middle];
        }
    }
    return median;
    
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
    int size = 4;
    float dataset[] = {17.6028, 10.9157, 16.7465, 16.9766};
    int windowSize = 5;
    int currentSample = 0;
    float min;
    float avg;
    float max;
    float smplSD;
    float median;
    
    cout << "Sample \t Minimum \t Average \t Maximum \t Medium \t Sample Standard Deviation" << endl;
    
    while (currentSample < size) {
        int retCode = SWStats(dataset, size, currentSample, windowSize, min, avg, max, smplSD, median);
        if (retCode >= 0) {
            cout << dataset[currentSample] << "\t " << min << "\t " << avg << "\t " << max << "\t " << median << "\t " << smplSD << endl;
            if (retCode > 0)
                cerr << "Warning: something weird happened, but we computed stats anyway ... YMMV" << endl;
        }
        else {
            cerr << "Error: unable to compute sliding-window statistics; exiting" << endl;
            return(-1);
        }
        ++currentSample;
    }
    return 0;
}

#endif
