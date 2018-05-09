//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <limits>

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
// #defines, enum, and function declarations; do not remove
//

#define isNaN(X) (X != X)  // NaN is the only float that is not equal to itself
#define NaN std::numeric_limits<float>::quiet_NaN() // (comes from <limits>)

enum sortType { ASCENDING, DESCENDING, UNKNOWN, UNSORTED };
bool isSorted(const float data[], const int currentDataItem, const sortType typeOfSort);
bool sorted(const float data[]);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//
//
bool isSorted(const float data[], const int currentDataItem, const sortType typeOfSort){
    if (currentDataItem==0){
        return true;
    }
    
    if (data[currentDataItem-1]-data[currentDataItem-1]!=0){
        return true;
    }
    
    switch (typeOfSort) {
        case ASCENDING:
            if (data[currentDataItem]<data[currentDataItem+1]){
                return isSorted(data, currentDataItem+1, ASCENDING);
            } else {
                return isSorted(data, currentDataItem, UNSORTED);
            }
            break;
        case DESCENDING:
            if (data[currentDataItem]>data[currentDataItem+1]){
                return isSorted(data, currentDataItem+1, DESCENDING);
            } else {
                return isSorted(data, currentDataItem, UNSORTED);
            }
            break;
        case UNKNOWN:
            if (data[currentDataItem]==data[currentDataItem+1]){
                return isSorted(data, currentDataItem+1, UNKNOWN);
            } else {
                return isSorted(data, currentDataItem, UNSORTED);
            }
            break;
        case UNSORTED:
            if (data[currentDataItem]==data[currentDataItem+1]){
                return isSorted(data, currentDataItem+1, UNKNOWN);
            }
            if (data[currentDataItem]<data[currentDataItem+1]){
                return isSorted(data, currentDataItem+1, ASCENDING);
            }
            if (data[currentDataItem]>data[currentDataItem+1]){
                return isSorted(data, currentDataItem+1, DESCENDING);
            }
            break;
    }
    return true;
}

bool sorted(const float data[]) {
    int i=0;
    int b=0;
    while (data[i]==data[i+1]){
        i++;
    }
    if (data[i]<data[i+1]){
        while (data[i+1]-data[i+1]==0){
            if (data[i]>data[i+1]){
                return false;
            }
            i++;
        }
    }
    if (data[i]>data[i+1]){
        while (data[i+1]-data[i+1]==0){
            if (data[i]<data[i+1]){
                return false;
            }
            i++;
        }
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

int main(const int argc, const char* const argv[]) {
    
    // Some test driver code here ....
    float data[] = {100, 100, NaN};
    
    if (sorted(data))
        cout << "Data is sorted" << endl;
    else
        cout << "Data is not sorted" << endl;
    
    return 0;
}

#endif

