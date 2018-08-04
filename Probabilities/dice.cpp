#include <iostream>
#include <iomanip>
extern "C" {
    #include <stdlib.h>
    #include <time.h>
}

using namespace std;

int Dice();
void RollDice(int times);
void RollTwoDice(int times);
void Lowhigh(int times, int sebtimes);

int Dice() {
    int min = 1, max = 6;
    int random = min + rand() / (RAND_MAX / (max - min + 1) + 1);
    return random;
}

void RollDice(int times){
    float howoften[] = {0,0,0,0,0,0};
    for (int i=0;i<times;i++){
        switch(Dice()){
            case 1:
                howoften[0]++;
                break;
            case 2:
                howoften[1]++;
                break;
            case 3:
                howoften[2]++;
                break;
            case 4:
                howoften[3]++;
                break;
            case 5:
                howoften[4]++;
                break;
            case 6:
                howoften[5]++;
                break;
        }
    }
    for (int i=0;i<6;i++){
        howoften[i]=howoften[i]/times;
        cout << (i+1) << ": (" << howoften[i] << ")" << endl;
    }
}

void RollTwoDice(int times){
    float howoften[] = {0,0,0,0,0,0,0,0,0,0,0};
    for (int i=0;i<times;i++){
        switch(Dice()+Dice()){
            case 2:
                howoften[0]++;
                break;
            case 3:
                howoften[1]++;
                break;
            case 4:
                howoften[2]++;
                break;
            case 5:
                howoften[3]++;
                break;
            case 6:
                howoften[4]++;
                break;
            case 7:
                howoften[5]++;
                break;
            case 8:
                howoften[6]++;
                break;
            case 9:
                howoften[7]++;
                break;
            case 10:
                howoften[8]++;
                break;
            case 11:
                howoften[9]++;
                break;
            case 12:
                howoften[10]++;
                break;
        }
    }
    for (int i=0;i<=7;i++){
        howoften[i]=howoften[i]/times;
        cout << (i+2) << ":  (" << howoften[i] << ")" << endl;
    }
    for (int i=8;i<=10;i++){
        howoften[i]=howoften[i]/times;
        cout << (i+2) << ": (" << howoften[i] << ")" << endl;
    }
}

void Lowhigh(int times, int subtimes){
    float split[2];
    float equal=0;
    for (int i=0;i<times;i++){
        split[0]=0;
        split[1]=0;
        for (int i=0;i<subtimes;i++){
            switch(Dice()){
                case 1:
                    split[0]++;
                    break;
                case 2:
                    split[0]++;
                    break;
                case 3:
                    split[0]++;
                    break;
                case 4:
                    split[1]++;
                    break;
                case 5:
                    split[1]++;
                    break;
                case 6:
                    split[1]++;
                    break;
            }
        }
        if (split[0]==split[1]){
            equal++;
        }
    }
    float result = equal/float(times);
    cout << "The fraction of times the number of high rolls is equal to the number of low rolls: " << result << endl;
}

int main(){
    srand((unsigned int)time(NULL));
    cout << endl;
    cout << "-----------------------------------" << endl;
    cout << endl;
    cout << "Question 1:" << endl;
    cout << endl;
    cout << "Roll the dice 10 times: " << endl;
    cout << setprecision(1) << fixed;
    RollDice(10);
    cout << endl;
    cout << "Roll the dice 1000 times: " << endl;
    cout << setprecision(3) << fixed;
    RollDice(1000);
    cout << endl;
    cout << "Roll the dice 100000 times: " << endl;
    cout << setprecision(5) << fixed;
    RollDice(100000);
    cout << endl;
    cout << "-----------------------------------" << endl;
    cout << endl;
    cout << "Question 2:" << endl;
    cout << endl;
    cout << "Low and High split:" << endl;
    Lowhigh(10000,100);
    cout << endl;
    cout << "-----------------------------------" << endl;
    cout << endl;
    cout << "Question 3:" << endl;
    cout << endl;
    cout << "Roll two dice 100000 times: " << endl;
    cout << setprecision(5) << fixed;
    RollTwoDice(100000);
    cout << endl;
    cout << "-----------------------------------" << endl;
    cout << endl;
    return 0;
}
