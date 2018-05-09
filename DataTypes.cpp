#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

using namespace std;

int main (const int argc, const char* const argv[])
{
    int x;
    unsigned int y;
    int bits = sizeof(int)*8;
    x=atoi(argv[1]);
    y=x;
    int msb = x >> (bits-1)&1;
    int msb2 = y >> (bits-1)&1;

    cout << "The value of x is "   << x
         << "\nThe value of y is " << y
         << "\nThe most significant bit of x is " << msb
         << "\nThe most significant bit of y is " << msb2
         << endl;
    
    cout << "Type: \"signed char\"; Size: "            << sizeof(signed char)          << " bytes; Minumum value: " << SCHAR_MIN  << " ; Maximum value: " <<  SCHAR_MAX  << endl;
    cout << "Type: \"short int\"; Size: "              << sizeof(short int)            << " bytes; Minumum value: " <<  SHRT_MIN  << " ; Maximum value: " <<   SHRT_MAX  << endl;
    cout << "Type: \"int\"; Size: "                    << sizeof(int)                  << " bytes; Minumum value: " <<   INT_MIN  << " ; Maximum value: " <<    INT_MAX  << endl;
    cout << "Type: \"long int\"; Size: "               << sizeof(long int)             << " bytes; Minumum value: " <<  LONG_MIN  << " ; Maximum value: " <<   LONG_MAX  << endl;
    cout << "Type: \"long long int\"; Size: "          << sizeof(long long)            << " bytes; Minumum value: " << LLONG_MIN  << " ; Maximum value: " <<  LLONG_MAX  << endl;
    cout << "Type: \"unsigned char\"; Size: "          << sizeof(unsigned char)        << " bytes; Minumum value: " <<    "0"     << " ; Maximum value: " <<  UCHAR_MAX  << endl;
    cout << "Type: \"unsigned short int\"; Size: "     << sizeof(unsigned short int)   << " bytes; Minumum value: " <<    "0"     << " ; Maximum value: " <<  USHRT_MAX  << endl;
    cout << "Type: \"unsigned int\"; Size: "           << sizeof(unsigned int)         << " bytes; Minumum value: " <<    "0"     << " ; Maximum value: " <<   UINT_MAX  << endl;
    cout << "Type: \"unsigned long int\"; Size: "      << sizeof(unsigned long int)    << " bytes; Minumum value: " <<    "0"     << " ; Maximum value: " <<  ULONG_MAX  << endl;
    cout << "Type: \"unsigned long long int\"; Size: " << sizeof(unsigned long long)   << " bytes; Minumum value: " <<    "0"     << " ; Maximum value: " << ULLONG_MAX  << endl;
    cout << "Type: \"float\"; Size: "                  << sizeof(float)                << " bytes; Minumum value: " <<   FLT_MIN  << " ; Maximum value: " <<    FLT_MAX  << endl;
    cout << "Type: \"double\"; Size: "                 << sizeof(double)               << " bytes; Minumum value: " <<   DBL_MIN  << " ; Maximum value: " <<    DBL_MAX  << endl;
    cout << "Type: \"long double\"; Size: "            << sizeof(long double)          << " bytes; Minumum value: " <<  LDBL_MIN  << " ; Maximum value: " <<   LDBL_MAX  << endl;

    return 0;
}
