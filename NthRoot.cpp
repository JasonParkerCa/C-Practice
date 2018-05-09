#include <iostream>
#include <stdlib.h>

using namespace std;

int main (const int argc, const char*const argv[])
{
    if (argc<4){
        cerr << "Error: Unable to compute Nth root because the program needs three command lines." << endl;
        return -1;
    }
    
    if (argc>4){
        cerr << "Warning: Expecting three command-line arguments; received more; ignoring extraneous arguments." << endl;
    }
    
    float S, Rn, xi, z, precision, Rnt, n;
    int root;
    S = atof(argv[1]);
    root = atoi(argv[2]);
    n = float (root);
    if (S < 0 && root % 2 ==0 ) {
        cerr << "Error: Unable to compute Nth root because negative numbvers have no even root." << endl;
        return -1;
    }
    
    if (n<2) {
        cerr << "Error: Unable to compute Nth root because root must be an integer which is bigger than two." << endl;
        return -1;
    }
    
    precision = atof(argv[3]);
    
    if (precision < 0) {
        cerr << "Error: Unable to compute Nth root because the precision must be positive." << endl;
        return -1;
    }

    xi = 1;

    do
    {
        Rn = 1;
        z=1;
        
        for (int k=1; k<=n-1; k++)
        {
        z = z*(1/xi);
        }
        
        xi = ((n-1)/n)*xi + (S/n)*z;
        
        for (int k=1;k<=n;k++)
        {
            Rn = Rn * xi;
        }
        
        if ((S-Rn)/S>=0){
            Rnt = (S-Rn)/S;
        } else {
            Rnt = (Rn-S)/S;
        }
    
    } while (Rnt > precision);

    cout << "Root(" << S << "," << n << ") = " << xi << endl;
    
    cout << "(With precision " << Rnt << ")" << endl;

}
