//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include<math.h>
#include<limits.h>

//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING
#include <iostream>
using namespace std;
#endif

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove
// Replace "..." in bisectionHelper() with any parameter(s)
// you need to ensure termination when precision and
// minIntervalSize are too tightly specified.
//

bool stringToInt(const char input[], int& value);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//
// Return std::numeric_limits<float>::quiet_NaN() (comes from
// <limits>) if cannot compute the root for some reason
//

bool stringToInt(const char input[], int& value) {
    int i=0;
    while (input[i]){
        if (  ((input[i]!='+' && input[i]!='-') && (input[i]<'0' || input[i]>'9') && i==0) || ((input[i]<'0' || input[i]>'9') && i!=0)  ) {
            return 0;
        }
        i++;
    }
    
    value=0;
    i=0;
    
    int size=0;
    while (input[i]){
        size++;
        i++;
    }

    int number[size];
    
    if (input[0]=='+'||input[0]=='-'){
        for (int i=1;i<size;i++){
            number[i]=input[i]-'0';
        }
    } else {
        for (int i=0;i<size;i++){
            number[i]=input[i]-'0';
        }
    }
    
    
    if (input[0]=='+'||input[0]=='-'){
        for (int i=1;i<size;i++){
            value=number[i]*pow(10, size-i-1)+value;
        }
    } else {
        for (int i=0;i<size;i++){
            value=number[i]*pow(10, size-i-1)+value;
        }
    }
    
    
    if (input[0]=='+'){
        value=value;
    }
    if (input[0]=='-'){
        value=-value;
    }
    
    if (value==INT_MAX || value==INT_MIN){
        return 0;
    }
    
    
    return true;
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
    
    // Some test driver code here ....
    int argv1;
    
    if (argc < 2) {
        cerr << "Error: Usage: " << argv[0] << " <int>" << endl;
        return -1;
    }
    
    if (stringToInt(argv[1],argv1))
        cout << "argv[1] is an int with value: " << argv1 <<endl;
    else
        cout << "argv[1] is not an int." << endl;
    return 0;
}

#endif
