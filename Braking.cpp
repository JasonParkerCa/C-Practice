#include <iostream>
#include <stdlib.h>

using namespace std;

int main (const int argc, const char* const argv[])
{
    float velocity, distance, deceleration, time;
    velocity = atof(argv[1]);
    distance = atof(argv[2]);
    deceleration = (0-velocity*velocity)/(2*distance);
    time = (0-velocity)/deceleration;
    
    cout << "Initial car velocity: "  << argv[1]      << " m/s"   << endl;
    cout << "Distance to obstacle: "  << argv[2]      << " m"     << endl;
    cout << "Minimum deceleration: "  << deceleration << " m/s/s" << endl;
    cout << "Maximum stopping time: " << time         << " s"     << endl;


    return 0;
}
