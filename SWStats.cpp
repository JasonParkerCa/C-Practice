#include <iostream>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <iomanip>
using namespace std;

int main (const int argc, const char*const argv[])
{
    
    if (argc<3) {
        cerr << "Error: Insufficient arguments; expecting 2 command-line arguments." << endl;
        return -1;
    }
    
    int n = argc - 2;
    int wz = atoi(argv[1]);


    if (wz > n || wz == 1) {
        cerr << "Warning: The number of input is smaller than the window size or the window size is one." << endl;
    }
    
    if (wz<1) {
        cerr << "Error: Unable to compute statistics over data set because the window size must be a positive integer." << endl;
        return -1;
    }else{
        float sample[n];
        float min = FLT_MAX;
        float max = -FLT_MAX;
        float average;
        float sum = 0;
        for (int i=0;i<n;i++)
        {
            sample[i]=atof(argv[i+2]);
        }
        
        cout << "Window Size: " << wz << endl;
        cout << "Sample   Value  SWMinimum SWAverage SWMaximum" << endl;
        
        if (n <= wz) {
            for (int i=0;i<n;i++){
                
                if (sample[i]<min){
                    min = sample[i];
                }
                
                if (sample[i]>max){
                    max = sample[i];
                }
                
                sum = sum + sample[i];
                average = sum / (i+1);
                
                cout << setw(6) << left << i+1 << setw(8) << right << sample[i] << setw(11) << right << min << setw(10) << right << average << setw(10) << right << max << endl;
            }
            return -1;
        }
        
        if (n > wz) {
            for (int i=0;i<wz;i++){
                
                if (sample[i]<min){
                    min = sample[i];
                }
                
                if (sample[i]>max){
                    max = sample[i];
                }
                
                sum = sum + sample[i];
                average = sum / (i+1);
                
                cout << setw(6) << left << i+1 << setw(8) << right << sample[i] << setw(11) << right << min << setw(10) << right << average << setw(10) << right << max << endl;
            }
            
            for (int i=wz;i<n;i++){
                
                min = FLT_MAX;
                max = -FLT_MAX;
                sum = 0;

                for (int k=i+1-wz;k<=i;k++)
                {
                    if (sample[k]<min){
                        min = sample[k];
                    }
                    
                    if (sample[k]>max){
                        max = sample[k];
                    }
                
                    sum = sum + sample[k];
                }
                
                average = sum / wz;
                
                cout << setw(6) << left << i+1 << setw(8) << right << sample[i] << setw(11) << right << min << setw(10) << right << average << setw(10) << right << max << endl;
            }
        
        }
    }
    
    return 0;
}
