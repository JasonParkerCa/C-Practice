//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
// You are allowed float.h

#include <math.h>
#include <float.h>

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

bool stringToFloat(const char input[], float& value);

//////////////////////////////////////////////////////////////
//
// Your code here ...

bool stringToFloat(const char input[], float& value) {
    int i=0;
    int point = 0;
    int eposition =0 ;
    bool ifpoint=false;
    bool ife=false;
    float ten=0;
    float decimal=0;
    float ec=0;
    int sized=0;
    int numberofe = 0;
    int numberofdot = 0;
    
    for (int i=0;input[i];i++){
        if (input[i]=='e'||input[i]=='E'){
            eposition=i;
            numberofe++;
            ife=true;
        }
        if (input[i]=='.'){
            numberofdot++;
        }
    }
    
    if (numberofe>1 || numberofdot>1){
        return 0;
    }
    
    
    while (input[i]){
        if ((input[i]<'0'||input[i]>'9')&&input[i]!='.'&&input[i]!='+'&&input[i]!='-'&&input[i]!='e'&&input[i]!='E'){
            return 0;
        }
        
        if (i!=0 && i!=eposition+1 && (input[i]=='+'||input[i]=='-') ){
            return 0;
        }
        
        if (input[i]=='.'){
            point=i;
            ifpoint=true;
        }
        i++;
    }
    
    
    if (ifpoint){
        if (input[point+1]<'0'||input[point+1]>'9'){
            return 0;
        }
    }
    
    if (eposition){
        
        if ((input[eposition+2]<'0'||input[eposition+2]>'9')&&(input[eposition+1]=='+'||input[eposition+1]=='-')) {
            return 0;
        }
        
        if ((input[eposition+1]<'0'||input[eposition+1]>'9')&&(input[eposition+1]!='+'&&input[eposition+1]!='-')) {
            return 0;
        }
        
    }
    
    if (ife==true && eposition==0){
        return 0;
    }
    
    value=0;
    
    if (!ifpoint){
        i=0;
        while (input[i] && (input[i]!='e'&&input[i]!='E')){
            if(input[i]>='0' && input[i]<='9'){
                value=value*(float)10+(input[i]-'0');
            }
            i++;
        }
        
        if (eposition){
            i=eposition+1;
            while (input[i]){
                if(input[i]>='0' && input[i]<='9'){
                    ec=ec*(float)10+(input[i]-'0');
                }
                i++;
            }
            
            if (input[eposition+1]=='+'){
                ec=ec;
            }
            if (input[eposition+1]=='-'){
                ec=(-1)*ec;
            }
        }
        
        value=value*pow(10, ec);
        
        if (input[0]=='+'){
            value=value;
        }
        if (input[0]=='-'){
            value=(-1)*value;
        }
        
    } else {
        i=0;
        while (input[i]!='.'){
            if(input[i]>='0' && input[i]<='9'){
                ten = ten*(float)10+(input[i]-'0');
            }
            i++;
        }
        
        i=point+1;
        while(input[i] && (input[i]!='e'&&input[i]!='E')){
            if(input[i]>='0' && input[i]<='9'){
                decimal = decimal*(float)10+(input[i]-'0');
                sized++;
            }
            i++;
        }
        decimal=decimal/(pow(10, sized));
        value=ten+decimal;
        
        if (eposition){
            i=eposition+1;
            while (input[i]){
                if(input[i]>='0' && input[i]<='9'){
                    ec=ec*10+(input[i]-'0');
                }
                i++;
            }
            
            if (input[eposition+1]=='+'){
                ec=ec;
            }
            if (input[eposition+1]=='-'){
                ec=(-1)*ec;
            }
        }
        
        value=value*pow(10, ec);
        
        if (input[0]=='+'){
            value=value;
        }
        if (input[0]=='-'){
            value=(-1)*value;
        }
        
    }
    
    
    
    
    
    if (value==FLT_MAX || value==FLT_MIN){
        return 0;
    }
    
    return 1;
    
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
    float argv1;
    
    if (argc < 2) {
        cerr << "Error: Usage: " << argv[0] << " <float>" << endl;
        return -1;
    }
    
    if (stringToFloat(argv[1],argv1))
        cout << "argv[1] is a float with value: " << argv1 <<endl;
    else
        cout << "argv[1] is not a float. argv[1]: " <<argv[1] << endl;
    return 0;
}

#endif
