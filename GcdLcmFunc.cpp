//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include <limits.h>

//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING

#include <iostream>

using namespace std;

int greatestCommonDenominator(const int, const int);
int leastCommonMultiple(const int, const int);
#endif

//////////////////////////////////////////////////////////////
//
// Your code here ...
//

int greatestCommonDenominator(const int a, const int b) {
    if (a<=0 || b<=0){
         return -1;
     }
    int r,ax,bx,gcdf;
    ax=a;
    bx=b;
    do
    {
        r = ax % bx;
        if (r==0){
            gcdf = bx;
        }
        ax = bx;
        bx = r;
        
    } while (r!=0);
    return gcdf;
}

int leastCommonMultiple (const int a, const int b) {
    if (a<=0 || b<=0){
        return -1;
    }
    if (a/greatestCommonDenominator(a,b)>INT_MAX/b){
        return -2;
    }
    int lcmf;
    lcmf = a/greatestCommonDenominator(a,b)*b;
    return lcmf;
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

  if (argc < 3) {
    cerr << "Error: Usage: " << argv[0] << "<num1> <num2>; exiting" << endl;
    return -1;
  }

  int gcd = greatestCommonDenominator(atoi(argv[1]),atoi(argv[2]));
  if (gcd < 0)
    cerr << "Unable to compute GCD(" << argv[1] << "," << argv[2] << ")" << endl;
  else
    cout << "GCD(" << argv[1] << "," << argv[2] << ") = " << gcd << endl;

  int lcm = leastCommonMultiple(atoi(argv[1]),atoi(argv[2]));
  if (lcm < 0)
    cerr << "Unable to compute LCM(" << argv[1] << "," << argv[2] << ")" << endl;
  else
    cout << "LCM(" << argv[1] << "," << argv[2] << ") = " << lcm << endl;


  return 0;
}

#endif
