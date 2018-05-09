#include <iostream>
#include <stdlib.h>
#include <float.h>
#include <math.h>
using namespace std;

int main (const int argc, const char*const argv[])
{
    if (argc<2){
        cerr << "Error: Unable to compute statistics over data set because at least one number is required." <<  endl;
        return -1;
    }
    
    float N[argc-1], sum, average, max, min, pd, sd, squaresum, n;
    n = argc -1;
    sum=0;
    squaresum = 0;
    max = -FLT_MAX;
    min = FLT_MAX;
    
    for (int i=0;i<n;i++){
        N[i] = atof(argv[i+1]);
        sum = sum + N[i];
        if (N[i]<min){
            min = N[i];
        }
        if (N[i]>max){
            max = N[i];
        }
    }
    average = sum/(n);
    
    for (int i=0;i<n;i++){
        squaresum = squaresum + pow((N[i]-average),2);
    }
    
    pd = sqrt(1/(n)*squaresum);
    sd = sqrt(1/(n-1)*squaresum);
    
    
    
    cout << "Number of floating-point numbers: " << n << endl;
    cout << "Minimum floating-point number: " << min << endl;
    cout << "Average floating-point number: " << average << endl;
    cout << "Maximum floating-point number: " << max << endl;
    cout << "Population standard deviation: " << pd << endl;
    if (n==1)
    {
        cout << "Sample standard deviation: " << "infinity" << endl;
    }else{
        cout << "Sample standard deviation: " << sd << endl;
    }
    
    return 0;
}
