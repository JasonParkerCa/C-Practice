//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include <limits>

//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING



using namespace std;

float NthRoot(const float S, const int N, const float precision);
#endif

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  
// Return std::numeric_limits<float>::quiet_NaN() (comes from
// <limits.h>) if cannot compute the Nth root of S with
// precision.
//

float NthRoot(const float S, const int N, const float precision) {
    float Rn, xi, z, Rnt, n;
    n = float (N);
    
    if (S < 0 && N % 2 ==0 ) {
        return std::numeric_limits<float>::quiet_NaN();
    }
    
    if (n<2) {
        return std::numeric_limits<float>::quiet_NaN();
    }
    
    if (precision <=0 || precision>=1) {
        return std::numeric_limits<float>::quiet_NaN();
    }
    
    xi = 1;
    
    if (S==0){
        xi=0;
    }
    
    if (S!=0){
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
    }
    
    return xi;

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
  
  if (argc < 4) {
    cerr << "Error: Usage: " << argv[0] << " <number> <root> <precision>; exiting" << endl;
    return -1;
  }

  float root = NthRoot(atof(argv[1]),atoi(argv[2]),atof(argv[3]));
  if (isNaN(root))
    cerr << "Unable to compute " << argv[2] << "th root of " << argv[1] << " with precision " << argv[3] << endl;
  else
    cout << "Root(" << argv[1] << "," << argv[2] << ") = " << root << endl
	 << "(with precision " << argv[3] << ")" << endl; 

  return 0;
}

#endif
