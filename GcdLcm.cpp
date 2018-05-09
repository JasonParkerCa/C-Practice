#include <iostream>
#include <stdlib.h>

using namespace std;

int main(const int argc, const char* const argv[]) {
    
    if (argc<3){
        cerr << "Error: Unable to compute GCD and/or LCM because the program needs two postive Integer numbers." << endl;
        return -1;
    }
    
    if (argc>3){
        cerr << "Warning: Expecting two command-line arguments; received more; ignoring extraneous arguments." << endl;
    }
    
    int a, b, r, ax, bx, GCD, LCM;
    a=atoi(argv[1]);
    b=atoi(argv[2]);
    ax = a;
    bx = b;
    
    if (a<=0 || b<=0){
        cerr << "Error: Unable to compute GCD and/or LCM because the program needs two postive Integer numbers." << endl;
        return -1;
    }
    
    do
    {
        r = ax % bx;
        if (r==0){
            GCD = bx;
        }
        ax = bx;
        bx = r;
        
    } while (r!=0);
    
    for (int i=1;;i++){
        if (i%a==0 && i%b==0){
            LCM =i;
            break;
        }
    }
    
    cout << "GCD(" << a <<"," << b << ") = " << GCD << endl;
    cout << "LCM(" << a <<"," << b << ") = " << LCM << endl;
    
    return 0;
}
