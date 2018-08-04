#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>
using namespace std;

struct link {
    string temp;
    link* next;
};

string* makeArray(int arraysize, link* link){
    string* temp = new string[arraysize];
    for (int i=0;i<arraysize;i++){
        temp[i]=link->temp;
        link=link->next;
    }
    return temp;
}

int** doubleArray(int A, int B){
    int** temp;
    temp = new int*[A];
    for (int i=0;i<A;i++){
        temp[i] = new int[B];
    }
    return temp;
}

class Tuple {
public:
    int _numElement;
    int* _pData;
    Tuple();
    Tuple operator+(int number);
    void operator=(const Tuple& p);
    bool operator==(const Tuple& p);
    int size() const;
    void print();
};

Tuple:: Tuple(){
    _numElement=0;
    _pData=NULL;
}

Tuple Tuple::operator+(int number){
    Tuple temp;
    temp._pData=new int[_numElement+1];
    for (int i=0;i<_numElement;i++){
        temp._pData[i]=_pData[i];
    }
    temp._pData[_numElement]=number;
    temp._numElement=_numElement+1;
    return temp;
}

void Tuple::operator=(const Tuple& p){
    _numElement=p._numElement;
    _pData=new int[_numElement];
    for (int i=0;i<_numElement;i++){
        _pData[i]=p._pData[i];
    }
}

bool Tuple::operator==(const Tuple& p){
    if (_numElement!=p._numElement){
        return false;
    }
    for (int i=0;i<_numElement;i++){
        if (_pData[i]!=p._pData[i]){
            return false;
        }
    }
    return true;
}

int Tuple::size() const{
    return _numElement;
}

void Tuple::print(){
    if (_numElement==0){
        cout << "<> ";
    } else {
        for (int i=0;i<_numElement-1;i++){
            cout << _pData[i] << ",";
        }
        cout << _pData[_numElement-1];
    }
}

class Set {
public:
    void print();
    Set();
    Set(const int numElements, const Tuple Tuples[]);
    ~Set();
    int    _numElements;
    int    _tupleArraySize;
    Tuple* _pTuples;
};

void Set:: print(){
    for (int i=0;i<_numElements;i++){
        _pTuples[i].print();
    }
}

Set::Set() {
    _pTuples = NULL;
    _numElements = 0;
}

Set::Set(const int numElements, const Tuple tuples[]) {
    if (numElements<0){
        _numElements=-1;
    } else if (tuples==NULL){
        _numElements=0;
    } else {
        _numElements = numElements;
        if (numElements>0) {
            Tuple* temp = new Tuple[numElements];
            int* sizeoftuple = new int[numElements];
            for (int i=0;i<numElements;i++){
                temp[i] = tuples[i];
                sizeoftuple[i] = tuples[i].size();
            }
            for (int i=0;i<numElements-1;i++){
                if (temp[i].size()==sizeoftuple[i]){
                    for (int j=i+1;j<numElements;j++){
                        if (temp[i]==temp[j]){
                            temp[j]=temp[j]+0;
                        }
                    }
                }
            }
            int realsize = 0;
            Tuple* realTuples = new Tuple[numElements];
            for (int i=0;i<numElements;i++){
                if(temp[i].size()==sizeoftuple[i]){
                    realTuples[realsize]=temp[i];
                    realsize++;
                }
            }
            _numElements=realsize;
            _pTuples = new Tuple[realsize];
            for (int i=0;i<realsize;i++){
                _pTuples[i]=realTuples[i];
            }
        }
    }
}

Set::~Set() {
    if (_numElements>0){
        delete [] _pTuples;
    }
    _numElements=0;
}

int NumberofU;

class Social{
public:
    Social();
    Social(int numberofAandB);
    Social(const Social &s);
    Social(int numberofA, int numberofB, int** relation, int numberofRelation);
    ~Social();
    Social RE();
    Social RS();
    Social Composition(Social& s);
    Social Inverse();
    Social Square();
    Social operator+(const Social &s);
    Social operator-(const Social &s);
    void operator=(const Social &s);
    void print();
    int nSetA, nSetB;
    bool** R;
};

Social Social::RE(){
    Social temp;
    temp.nSetA=nSetA;
    temp.nSetB=nSetB;
    temp.R = R;
    for (int i=0;i<temp.nSetA;i++){
        if (i<NumberofU){
            temp.R[i][i]=true;
        }
    }
    return temp;
}

Social Social::RS(){
    Social temp;
    temp.nSetA=nSetA;
    temp.nSetB=nSetB;
    temp.R = R;
    for (int i=0;i<temp.nSetA;i++){
        for (int j=0;j<nSetB;j++){
            if (R[i][j]==true){
                temp.R[j][i]=true;
            }
        }
    }
    return temp;
}

Social Social::Composition(Social& s){
    Social temp;
    temp.nSetA=nSetA;
    temp.nSetB=nSetB;
    temp.R = new bool*[nSetA];
    for (int i=0;i<temp.nSetA;i++){
        temp.R[i] = new bool[temp.nSetB];
        for (int j=0;j<temp.nSetB;j++){
            temp.R[i][j]=false;
        }
    }
    for (int i=0;i<temp.nSetA;i++){
        for (int j=0;j<temp.nSetB;j++){
            if (s.R[i][j]==true){
                for (int z=0;z<nSetB;z++){
                    if (R[j][z]==true){
                        temp.R[i][z]=true;
                    }
                }
            }
        }
    }
    return temp;
}

Social Social::Inverse(){
    Social temp;
    temp.nSetA=nSetA;
    temp.nSetB=nSetB;
    temp.R = new bool*[nSetA];
    for (int i=0;i<temp.nSetA;i++){
        temp.R[i] = new bool[temp.nSetB];
        for (int j=0;j<temp.nSetB;j++){
            temp.R[i][j]=false;
        }
    }
    for (int i=0;i<temp.nSetA;i++){
        for (int j=0;j<temp.nSetB;j++){
            if (R[i][j]==true){
                temp.R[j][i]=true;
            }
        }
    }
    return temp;
}

Social Social::Square(){
    Social temp;
    temp.nSetA=nSetA;
    temp.nSetB=nSetB;
    temp.R = R;
    for (int i=0;i<temp.nSetA;i++){
        for (int j=0;j<temp.nSetB;j++){
            temp.R[j][i]=true;
        }
    }
    return temp;
}

Social Social::operator+(const Social &s){
    Social temp;
    temp.nSetA=nSetA;
    temp.nSetB=nSetB;
    temp.R = new bool*[nSetA];
    for (int i=0;i<temp.nSetA;i++){
        temp.R[i] = new bool[temp.nSetB];
        for (int j=0;j<temp.nSetB;j++){
            if (s.R[i][j]==true||R[i][j]==true){
                temp.R[i][j]=true;
            }
        }
    }
    return temp;
}

Social Social::operator-(const Social &s){
    Social temp;
    temp.nSetA=nSetA;
    temp.nSetB=nSetB;
    temp.R = R;
    for (int i=0;i<temp.nSetA;i++){
        for (int j=0;j<temp.nSetB;j++){
            if (s.R[i][j]){
                temp.R[i][j]=false;
            }
        }
    }
    return temp;
}

void Social::operator=(const Social &s){
    nSetA=s.nSetA;
    nSetB=s.nSetB;
    R = new bool*[nSetA];
    for (int i=0;i<nSetA;i++){
        R[i] = new bool [nSetB];
        for (int j=0;j<nSetB;j++){
            R[i][j]=s.R[i][j];
        }
    }
}

void Social::print() {
    for (int i=0;i<nSetA;i++){
        for (int j=0;j<nSetB;j++){
            if (R[i][j]==true){
                cout << "{" << i+1 << "," << j+1 << "} ";
            }
        }
    }
    cout << endl;
}

Social::Social(){
    R = NULL;
    nSetA=nSetB=0;
}

Social::Social(int numberofAandB){
    nSetA=nSetB=numberofAandB;
    R = new bool* [nSetA];
    for (int i=0;i<nSetA;i++){
        R[i] = new bool [nSetB];
        for (int j=0;j<nSetB;j++){
            R[i][j]=false;
        }
    }
}

Social::Social(const Social &s){
    nSetA=s.nSetA;
    nSetB=s.nSetB;
    R = new bool*[nSetA];
    for (int i=0;i<nSetA;i++){
        R[i] = new bool [nSetB];
        for (int j=0;j<nSetB;j++){
            R[i][j]=s.R[i][j];
        }
    }
}

Social::Social(int numberofA, int numberofB, int** relation, int numberofRelation){
    nSetA=numberofA;
    nSetB=numberofB;
    R = new bool*[numberofA];
    for (int i=0;i<numberofA;i++){
        R[i] = new bool [numberofB];
        for (int j=0;j<numberofB;j++){
            R[i][j]=false;
        }
    }
    for (int i=0;i<numberofRelation;i++){
        R[relation[i][0]-1][relation[i][1]-1]=true;
    }
}

Social::~Social(){
    nSetA=nSetB=0;
}

Social F,W,L,U;

void getData(){   
    int valueofU = 0, valueofC = 0, valueofF = 0, valueofW = 0, valueofL = 0;
    link* FLink = new link;
    link* head;
    head=FLink;
    string temp;
    getline(cin,temp);
    getline(cin,temp);
    valueofU=stoi(temp);
    Social UT = Social(valueofU);
    U=UT;
    NumberofU=valueofU;
    getline(cin,temp);
    getline(cin,temp);
    valueofC=stoi(temp);
    getline(cin,temp);
    int index=0, middle=0;
    char convert[20];
    string tempnumber;
    getline(cin,temp);
    while (temp!="#W"){
        index++;
        FLink->temp=temp;
        getline(cin,temp);
        if (temp!="#W"){
            FLink->next=new link;
            FLink=FLink->next;
        } else {
            FLink->next=NULL;
        }
    }
    FLink=head;
    valueofF=index;
    string* Farray=makeArray(valueofF,FLink);
    int** FP = doubleArray(valueofF, 2);
    for (int i=0;i<valueofF;i++){
        tempnumber="";
        strcpy(convert, Farray[i].c_str());
        for (int j=0;convert[j]!=' ';j++){
            tempnumber+=convert[j];
            middle=j+1;
        }
        FP[i][0]=stoi(tempnumber);
        tempnumber="";
        for (int j=middle+1;convert[j]!='\0';j++){
            tempnumber+=convert[j];
        }
        FP[i][1]=stoi(tempnumber);
    }
    link* WLink = new link;
    head=WLink;
    index=0;
    getline(cin,temp);
    while (temp!="#L"){
        index++;
        WLink->temp=temp;
        getline(cin,temp);
        if (temp!="#L"){
            WLink->next=new link;
            WLink=WLink->next;
        } else {
            WLink->next=NULL;
        }
    }
    WLink=head;
    valueofW=index;
    string* Warray=makeArray(valueofW,WLink);
    int** WP = doubleArray(valueofW, 2);
    for (int i=0;i<valueofW;i++){
        tempnumber="";
        strcpy(convert, Warray[i].c_str());
        for (int j=0;convert[j]!=' ';j++){
            tempnumber+=convert[j];
            middle=j+1;
        }
        WP[i][0]=stoi(tempnumber);
        tempnumber="";
        for (int j=middle+1;convert[j]!='\0';j++){
            tempnumber+=convert[j];
        }
        WP[i][1]=stoi(tempnumber);
    }
    link* LLink = new link;
    head=LLink;
    index=0;
    while (getline(cin,temp)){
        index++;
        LLink->temp=temp;
        if (cin){
            LLink->next=new link;
            LLink=LLink->next;
        } else {
            LLink->next=NULL;
        }
    }
    LLink=head;
    valueofL=index;
    string* Larray=makeArray(valueofL,LLink);
    int** LP = doubleArray(valueofL, 2);
    for (int i=0;i<valueofL;i++){
        tempnumber="";
        strcpy(convert, Larray[i].c_str());
        for (int j=0;convert[j]!=' ';j++){
            tempnumber+=convert[j];
            middle=j+1;
        }
        LP[i][0]=stoi(tempnumber);
        tempnumber="";
        for (int j=middle+1;convert[j]!='\0';j++){
            tempnumber+=convert[j];
        }
        LP[i][1]=stoi(tempnumber);
    }
    if (valueofU>=valueofC){
        valueofC=valueofU;
    } else {
        valueofU=valueofC;
    }
    Social FT = Social(valueofU,valueofU,FP,valueofF);
    Social WT = Social(valueofU,valueofC,WP,valueofW);
    Social LT = Social(valueofU,valueofC,LP,valueofL);

    F=FT;
    W=WT;
    L=LT;
}

int** makeBinary(){
    int numberofPowerset, temp;
    numberofPowerset=pow(2,NumberofU);
    int** BV = new int* [numberofPowerset];
    for (int i=0;i<numberofPowerset;i++){
        temp=i;
        BV[i] = new int [NumberofU];
        for (int j=NumberofU-1;j>=0;j--){
            BV[i][j]=temp%2;
            temp/=2;
        }
    }
    return BV;
}

int** makePowerSet(){
    int numberofPowerset;
    int** BV = makeBinary();
    numberofPowerset=pow(2,NumberofU);
    int** powerSet = new int* [numberofPowerset];
    for (int i=0;i<numberofPowerset;i++){
        powerSet[i] = new int [NumberofU];
        for (int j=0;j<NumberofU;j++){
            if (BV[i][j]==1){
                powerSet[i][j]=j+1;
            } else {
                powerSet[i][j]=0;
            }
        }
    }
    return powerSet;
}

void Result(Social D){
    int numberofPowerset;
    numberofPowerset=pow(2,NumberofU);
    int** PowerSet = makePowerSet();
    
    int numberofRelation=0;
    for (int i=0;i<D.nSetA;i++){
        for (int j=0;j<D.nSetB;j++){
            if (D.R[i][j]==true){
                numberofRelation++;
            }
        }
    }
    int** DArray = doubleArray(numberofRelation, 2);
    int index=0;
    for (int i=0;i<D.nSetA;i++){
        for (int j=0;j<D.nSetB;j++){
            if (D.R[i][j]==true){
                DArray[index][0]=i+1;
                DArray[index][1]=j+1;
                index++;
            }
        }
    }
    
    Tuple Delement[numberofPowerset];
    index=0;
    for (int i=0;i<numberofPowerset;i++){
        for (int j=0;j<NumberofU;j++){
            if (PowerSet[i][j]!=0){
                Delement[index]=Delement[index]+PowerSet[i][j];
            }
        }
        index++;
    }
    
    Set DSet = Set(numberofPowerset,Delement);
    
    Tuple** Dpair = new Tuple*[numberofPowerset*numberofPowerset];
    for (int i=0;i<numberofPowerset*numberofPowerset;i++){
        Dpair[i] = new Tuple[3];
    }
    
    index=0;
    for (int i=0;i<numberofPowerset;i++){
        for (int j=0;j<numberofPowerset;j++){
            Dpair[index][0]=DSet._pTuples[i];
            Dpair[index][1]=DSet._pTuples[j];
            Dpair[index][2]=Dpair[index][2]+1;
            index++;
        }
    }
    
    bool TFA;
    
    for (int i=0;i<numberofPowerset*numberofPowerset;i++){
        TFA=false;
        for (int j=0;j<Dpair[i][0]._numElement;j++){
            for (int z=0;z<Dpair[i][1]._numElement;z++){
                for (int h=0;h<numberofRelation;h++){
                    if (Dpair[i][0]._pData[j]==DArray[h][0]&&Dpair[i][1]._pData[z]==DArray[h][1]){
                        TFA=true;
                        break;
                    } else {
                        TFA=false;
                    }
                }
                if (TFA==false){
                    Dpair[i][2]._pData[0]=0;
                }
            }
        }
        if (Dpair[i][0]._numElement==0||Dpair[i][1]._numElement==0){
            Dpair[i][2]._pData[0]=0;
        }
    }
    
    for (int i=0;i<numberofPowerset*numberofPowerset;i++){
        if (Dpair[i][2]._pData[0]==1){
            cout << "{";
            Dpair[i][0].print();
            cout << "} {";
            Dpair[i][1].print();
            cout << "}" << endl;
        }
    }
}


int main (){
    
    getData();

    Social Fr;
    Fr = F.RE();
    Social Frs;
    Frs = Fr.RS();
    Social Lfw;
    Lfw = L+(W.Composition(Frs));
    Social Win;
    Win = W.Inverse();
    Social S;
    S = Win.Composition(Lfw);
    Social Us;
    Us = U.Square();
    Social D;
    D = Us-S;
    
    cout << endl;
    Result(D);  
    cout << endl;

    return 0;
}
