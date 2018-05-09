#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main (const int argc, const char* const argv[])
{

    if (argc<4) {
        cerr << "Error: Insufficient arguments; expecting 3 command-line arguments." << endl;
        return -1;
    }
    
    if (argc>4) {
        cerr << "Warning: Expecting three command-line arguments; received more; ignoring extraneous arguments."<< endl;
    }
   
    float v1, v2, d, Max_a, a, t, t2;
    v1 = atof(argv[1]);
    d = atof(argv[2]);
    Max_a = atof(argv[3]);
    a = (0-v1 * v1) / (2 * d);
    t = (0-v1) / a;
    
    if ( (v1 * d) < 0 || v1 == 0 || (v1 ==0 && d == 0) ) {
        
        cout << "There is no possibility of collision because ßthe car is at rest or moving at the opposite direction to the obstacle." << endl;
        return -1;
            
    } else {
        
        if (v1 < 0 && Max_a!=0)
        {
        
            if (a <= Max_a && d!=0)
            {
                
                cout << "Initial car velocity: "  << v1     << " m/s"   << endl;
                cout << "Distance to obstacle: "  << d      << " m"     << endl;
                cout << "Minimum deceleration: "  << a << " m/s/s" << endl;
                cout << "Maximum stopping time: " << t      << " s"     << endl;
                
            }else{
                
                v2 = -sqrt(v1 * v1 + 2 * Max_a * d);
                t2  = (v2 - v1) / Max_a;
                cout << "Crash will occur in " << t2 << " seconds at velocity "<< v2 << "m/s; deploying airbags." << endl;
            }
        }
            
        if (v1 > 0 && Max_a!=0)
        {
            
            if (a >= (-Max_a) && d!=0)
            {
                
                cout << "Initial car velocity: "  << v1     << " m/s"   << endl;
                cout << "Distance to obstacle: "  << d      << " m"     << endl;
                cout << "Minimum deceleration: "  << (-a) << " m/s/s" << endl;
                cout << "Maximum stopping time: " << t      << " s"     << endl;
                
            }else{
                
                v2 = sqrt(v1 * v1 + 2 * (-Max_a) * d);
                t2  = (v2 - v1) / (-Max_a);
                cout << "Crash will occur in " << t2 << " seconds at velocity "<< v2 << " m/s; deploying airbags." << endl;
            }
        }
        
        if (Max_a==0 && v1!=0)
        {
            cout << "Crash will occur in " << d/v1 << " seconds at velocity "<< v1 << " m/s; deploying airbags." << endl;
        }

    
    }
    return 0;
}
