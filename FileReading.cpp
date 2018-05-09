//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <fstream>
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

int histogram(const char filename[], int histogram[10], 
              const int minAcceptableID, const int maxAcceptableID,
              int*& rejects);
int pow(int number, int times);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  
// Return -1 if you cannot compute the histogram for any
// reason;
// Return 0 if the histogram is correct and there are no
// rejections;
// Return the number of rejects if there are rejected
// records from the file
//

int pow(int number, int times){
    int result = 1;
    for (int i=1;i<=times;i++){
        result = result * number;
    }
    return result;
}



int histogram(const char filename[], int histogram[10],
              const int minAcceptableID, const int maxAcceptableID,
              int*& rejects) {
    int maxNumErrors = 100;
    int StudentID=0;
    int digit;
    int numberOfDigits = 0;
    int Grade=0;
    int index;
    int indexOfRejects=0;
    int i=0;
    int reject=0;
    const int max = 200;
    char data[max];
    int sign=1;
    rejects=new int[maxNumErrors];
    int numberOfRe = 0;
    
    std::ifstream in;
    in.open(filename);
    
    if (!in.is_open() || maxAcceptableID>INT_MAX || minAcceptableID<=0 || minAcceptableID>=maxAcceptableID || NULL==histogram){
        return -1;
    }
    
    bool done=false;
    int number =0;
    
    while (!in.eof()) {
        number++;
        in.getline(data,max);
    }
    
    
    int mark[number];
    
    in.close();
    in.open(filename);
    
    number=0;
    while (!done) {
        StudentID=0;
        Grade=0;
        sign=1;
        if (!in.getline(data,max)){
            if (in.eof()){
                done=true;
                break;
            }else{
                return -1;
            }
        }
        number++;
        i=0;
        numberOfDigits=0;
        while (data[i]!=','){
            if (data[i]>='0' && data[i]<='9'){
                numberOfDigits++;
            }
            if ((data[i]<'0' || data[i]>'9') && data[i]!=' ' && data[i]!='\t'){
                return -1;
            }
            i++;
        }
        
        index = 0;
        i=0;
        while (data[i]!=','){
            if (data[i]>='0' && data[i]<='9'){
                digit=data[i]-'0';
                StudentID=digit*pow(10, numberOfDigits-1-index)+StudentID;
                index++;
            }
            i++;
        }
        
        i=i+1;
        index=i;
        numberOfDigits=0;
        
        while (data[i]!=0){
            if (data[i]>='0' && data[i]<='9'){
                numberOfDigits++;
            }
            if ((data[i]<'0' || data[i]>'9') && data[i]!=' ' && data[i]!='\t' && data[i]!='-'){
                return -1;
            }
            i++;
        }
        
        i=index;
        index = 0;
        
        while (data[i]!=0){
            if (data[i]=='-'){
                sign=-1;
            }
            if (data[i]>='0' && data[i]<='9'){
                digit=data[i]-'0';
                Grade=digit*pow(10, numberOfDigits-1-index)+Grade;
                index++;
            }
            i++;
        }
        
        Grade=sign*Grade;
        
        if (StudentID<minAcceptableID || StudentID>maxAcceptableID || Grade<0 || Grade>100){
            reject++;
            rejects[indexOfRejects]=number;
            indexOfRejects++;
        } else {
            mark[numberOfRe]=Grade;
            numberOfRe++;
        }
    }
    
    
    for (int i=0;i<10;i++){
        histogram[i]=0;
    }
    
    for (int i=0;i<numberOfRe;i++){
        if (mark[i]!=100){
            histogram[mark[i]/10]++;
        }
        if (mark[i]==100){
            histogram[9]++;
        }
    }
    
    in.close();
    return reject;
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
  if (argc < 2) {

  }
  const int numBuckets = 10;
  const int bucketRange = 100/numBuckets;
  int  buckets[numBuckets];
  int* rejectedRecords;
  int retCode = histogram(argv[1], buckets, 22200000, 22299999, rejectedRecords);
  if (retCode < 0) {
      cout << "Unable to compute histogram." << endl;
  }
  else {
    for (int i = 0; i < numBuckets; ++i)
      if (i != numBuckets-1)
	cout << "Number [" << i*bucketRange << "," << (((i+1)*bucketRange)-1) << "]: " << buckets[i] << endl;
      else
	cout << "Number [" << i*bucketRange << "," << (((i+1)*bucketRange)) << "]: " << buckets[i] << endl;
    if (retCode > 0) {
      cout << "Number of rejected records: " << retCode << endl;
      cout << "Rejected records are:";
      for (int i = 0; i < retCode; ++i)
	cout << " " << rejectedRecords[i];
      cout << endl;
      delete[] rejectedRecords;
    }
  }

  return 0;
}

#endif
