//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//
#include <limits.h>

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

int range(const int dataset[], const int size);
int mode(const int dataset[], const int size, int mode[]);
bool sort(int dataset[], const int size);
int selection(int dataset[], const int size, int i);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  Return -1 if there there are any problems with the dataset.
//

int range(const int dataset[], const int size){
    if (size<=1){
        return -1;
    }
    int min = INT_MAX;
    int max =-INT_MAX;
    for (int i=0;i<size;i++){
        if (min>dataset[i]){
            min=dataset[i];
        }
        if (max<dataset[i]){
            max=dataset[i];
        }
    }
    if ((max-min)>=0){
        return (max-min);
    }else{
        return -1;
    }
}
int mode(const int dataset[], const int size, int mode[]){
    int m[size][2];
    int n;
    for (int i=0;i<size;i++){
        n=0;
        m[i][0]=dataset[i];
        for (int j=0;j<size;j++){
            if (m[i][0]==dataset[j]){
                n++;
            }
        }
        m[i][1]=n;
    }
    
    for (int i=0;i<size-1;i++){
        for (int j=i+1;j<size;j++){
            if (m[i][0]==m[j][0]){
                m[j][1]=0;
            }
        }
    }
    
    int max=-INT_MAX;
    int x=0;
    
    for (int i=0;i<size;i++){
        if (max<m[i][1]){
            max=m[i][1];
        }
    }
    
    for (int i=0;i<size;i++){
        if (m[i][1]==max){
            mode[x]=m[i][0];
            x++;
        }
    }
    
    selection(mode,x,0);
    return x;
}

bool sort(int dataset[], const int size){
    selection(dataset, size, 0);
    return 1;
}

int selection(int dataset[], const int size, int i){
    if (i==size-1){
        return 0;
    } else {
        int min=i;
        int temp;
        for (int j=i+1;j<size;j++){
            if (dataset[min]>dataset[j]){
                min=j;
            }
        }
        temp=dataset[i];
        dataset[i]=dataset[min];
        dataset[min]=temp;
        
        return selection(dataset,size,i+1);
    }
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
  int data[] = {1,2,3,4,5};
  int size = 6;
  //change this to however many modes you expect to find
  int modeArray[100]={0};
  int rng = range(data, size);
  int modes = mode(data, size, modeArray);
    
  cout << "range: " << rng << " number of Modes: " << modes << " Modes are this: ";
  for(int i = 0; i<modes;i++){
  	cout<< modeArray[i];
  	if(i<modes-1){
  		cout << ", ";
  	}
  }
  cout<<endl;
  return 0;
}

#endif
