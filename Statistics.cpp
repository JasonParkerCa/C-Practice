#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

using namespace std;

int main (const int argc, const char*const argv[])
{
    float min, max, average, sum;
    min=FLT_MAX;
    max=-FLT_MAX;
    sum=0;

    if (argc<2){
        cerr << "Unable to compute statistics over data set because at least one number is required." << endl;
        return -1;
    }else{
        for (int a=1; a<argc; a++){
            sum = sum + atof(argv[a]);
            if (atof(argv[a])<min){
                min=atof(argv[a]);
            }
            if (atof(argv[a])>max){
                max=atof(argv[a]);
            }
            average = sum/a;
        }
        cout <<"Number of floating-point numbers: "<<argc-1<<endl;
        cout <<"Minimum floating-point number: "<<min<<endl;
        cout <<"Average floating-point number: "<<average<<endl;
        cout <<"Maximum floating-point number: "<<max<<endl;
    }
    return 0;
}
