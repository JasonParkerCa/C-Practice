#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <iomanip>
using namespace std;

int main (const int argc, const char*const argv[])
{
    if (argc<4){
        cerr << "Unable to compute statistics over data set because at least one number is required." << endl;
        return -1;
    }

    float min, max, value, EWMA, premin, premax, mincount, maxcount, preEWMA;
    min=FLT_MAX;
    premin=FLT_MAX;
    max=-FLT_MAX;
    premax=-FLT_MAX;
    mincount = 1;
    maxcount = 1;
    
    float a = atof(argv[1]);
    float age = atof (argv[2]);
    
    if (age<=0){
        cerr << "Unable to compute statistics over data set because the age limit must be positive." << endl;
        return -1;
    }
    
    if (a<0 || a>1){
        cerr << "Unable to compute statistics over data set because the first argument must be betwwen 0 and 1." << endl;
        return -1;
    
    }else{

        cout << "Sample   Value  Minimum  EWMA  Maximum" << endl;
        for (int i=3; i<argc; i++){
            value = atof(argv[i]);
            if (value<min){
                min=atof(argv[i]);
            }
            mincount+= (min==premin) ? 1 : 0;
            premin = min;
            
            if (value>max){
                max=atof(argv[i]);
            }
            maxcount+= (max==premax) ? 1 : 0;
            premax = max;
            
            value = atof(argv[i]);
            
            if (i==3){
                EWMA = value;
                preEWMA = EWMA;
                cout << setw(2) << left << i-2 << "        " << setw(4) << left <<value << "  " <<setw(4) << left << min << "   " << setw(7) << left << EWMA << "    " <<setw(4) << left << max << endl;
            } else {
                if (mincount > age ){
                    min = value;
                    premin = value;
                    mincount=1;
                }
                if (maxcount > age ){
                    max = value;
                    premax = value;
                    maxcount=1;
                }
                EWMA =a*value+(1-a)*preEWMA;
                cout << setw(2) << left << i-2 << "        " << setw(4) << left <<value << "  " <<setw(4) << left << min << "   " << setw(7) << left << EWMA << "    " <<setw(4) << left << max << endl;
                preEWMA = EWMA;
            }
        }
    }
    return 0;
}
