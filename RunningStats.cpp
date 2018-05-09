#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

using namespace std;

int main (const int argc, const char*const argv[])
{
    float min, max, average, sum, value;
    min=FLT_MAX;
    max=-FLT_MAX;
    sum=0;

    if (argc<2){
        cerr << "Error: Insufficient arguments; expecting at leat one number." << endl;
        return -1;
    }else{
        cout << "Sample   Value  Minimum  Average  Maximum" << endl;
        for (int a=1; a<argc; a++){
            sum = sum + atof(argv[a]);
            if (atof(argv[a])<min){
                min=atof(argv[a]);
            }
            if (atof(argv[a])>max){
                max=atof(argv[a]);
            }
            average = sum/a;
            value = atof(argv[a]);
            cout << a << "        " << value << "   " << min << "   " << average << "   " << max << endl;
        }
    }
    return 0;
}
