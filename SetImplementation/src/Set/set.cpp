#include "tuple.h"
#include "set.h"
#include "invariant.h"
#include <iostream>
#include <limits.h>   // needed for INT_MIN
using namespace std;

// Set up an error set to be returned as necessary
const Set emptySet(0,(int*)0);
const Set errorSet(-1,(int*)0);

bool Set::isEmpty() const {
    return _numElements == 0;
}

bool Set::isError() const {
    bool isRepeat = false;
    if (_numElements<0){
        isRepeat=true;
    } else {
        for (int i=0;i<_numElements-1;i++){
            for (int j=i+1;j<_numElements;j++){
                if (_pTuples[i]==_pTuples[j]){
                    isRepeat = true;
                }
            }
        }
    }
    return isRepeat;
}

int Set::cardinality() const {
    if (this->isError()==true){
        return -1;
    }
    return _numElements;
}

Set Set::union_(const Set& s) const {
    if (_numElements==0 && s._numElements==0){
        return emptySet;
    }
    if (s.isError()==true||this->isError()==true){
        return errorSet;
    }
    Set s2 = this->intersection(s);
    int size = _numElements+s._numElements;
    int realsize = 0;
    Tuple* tuples = new Tuple[size];
    for (int i=0;i<s2._numElements;i++){
        tuples[realsize]=s2._pTuples[i];
        realsize++;
    }
    bool isRepeat;
    for (int i=0;i<_numElements;i++){
        isRepeat=false;
        for (int j=0;j<s2._numElements;j++){
            if (_pTuples[i]==tuples[j]){
                isRepeat=true;
            }
        }
        if (!isRepeat) {
            tuples[realsize]=_pTuples[i];
            realsize++;
        }
    }
    for (int i=0;i<s._numElements;i++){
        isRepeat=false;
        for (int j=0;j<s2._numElements;j++){
            if (_pTuples[i]==tuples[j]){
                isRepeat=true;
            }
        }
        if (!isRepeat) {
            tuples[realsize]=s._pTuples[i];
            realsize++;
        }
    }
    Set copy(realsize,tuples);
    return copy;
}

Set Set::intersection(const Set& s) const {
    if (_numElements==0 || s._numElements==0){
        return emptySet;
    }
    if (s.isError()==true||this->isError()==true){
        return errorSet;
    }
    int size;
    if (_numElements>=s._numElements){
        size=s._numElements;
    } else {
        size=_numElements;
    }
    Tuple* tuples = new Tuple[size];
    int realsize = 0;
    for (int i=0;i<_numElements;i++){
        for (int j=0;j<s._numElements;j++){
            if (_pTuples[i]==s._pTuples[j]){
                tuples[realsize]=_pTuples[i];
                realsize++;
            }
        }
    }
    Set copy(realsize,tuples);
    return copy;
}

Set Set::difference(const Set& s) const {
    if (_numElements==0){
        return emptySet;
    }
    if (s.isError()==true||this->isError()==true){
        return errorSet;
    }
    if (s._numElements==0){
        Set orig(_numElements,_pTuples);
        return orig;
    }
    Tuple* tuples = new Tuple[_numElements];
    int realsize = 0;
    bool isRepeat;
    for (int i=0;i<_numElements;i++){
        isRepeat=false;
        for (int j=0;j<s._numElements;j++){
            if (_pTuples[i]==s._pTuples[j]){
                isRepeat=true;
            }
        }
        if (!isRepeat){
            tuples[realsize]=_pTuples[i];
            realsize++;
        }
    }
    if (realsize==0){
        return emptySet;
    } else {
        Set copy(realsize,tuples);
        return copy;
    }
}

Set Set::select(predicate* p) const {
    if (this->isError()==true){
        return errorSet;
    }
    Tuple* tuples = new Tuple[_numElements];
    int realsize = 0;
    for (int i=0;i<_numElements;i++){
        if (p(_pTuples[i])){
            tuples[realsize]=_pTuples[i];
            realsize++;
        }
    }
    Set copy(realsize,tuples);
    return copy;
}

Set Set::project(const int numItems, const int items[]) const {
    if (this->isError()==true){
        return errorSet;
    }
    int size=0;
    Tuple* tuples = new Tuple[_numElements];
    Tuple curr;
    Tuple* setTuples = new Tuple[_numElements];
    for (int i=0;i<_numElements;i++){
        curr=_pTuples[i].project(numItems,items);
        if (!curr.isError() && !curr.isEmpty()){
            tuples[size] = curr;
            size++;
        }
    }
    for (int i=0;i<size-1;i++){
        if (tuples[i].size()==numItems){
            for (int j=i+1;j<size;j++){
                if (tuples[i]==tuples[j]){
                    tuples[j]=tuples[j]+0;
                }
            }
        }
    }
    int realsize = 0;
    for (int i=0;i<size;i++){
        if(tuples[i].size()==numItems){
            setTuples[realsize]=tuples[i];
            realsize++;
        }
    }
    Set copy(realsize,setTuples);
    return copy;
}

Set Set::cartesian(const Set& s) const {
    if (s.isError()==true||this->isError()==true){
        return errorSet;
    }
    if (_numElements>0 && s._numElements>0){
        int size = _numElements*s._numElements;
        Tuple* tuples = new Tuple[size];
        int first=0,second=0,index=0;
        while (first<_numElements){
            while (second<s._numElements){
                tuples[index]=_pTuples[first];
                tuples[index]=tuples[index]+s._pTuples[second];
                second++;
                index++;
            }
            second=0;
            first++;
        }
        Set copy(size,tuples);
        return copy;
    } else {
        return emptySet;
    }
}

void Set::operator=(const Set& s) {
    _numElements = s._numElements;
    if (_numElements>0){
        _pTuples = new Tuple[_numElements];
        for (int i=0;i<_numElements;i++){
            _pTuples[i]=s._pTuples[i];
        }
    }
}

Set Set::operator()(const int item) const {
    if (item>_numElements || item<=0 || this->isError()==true) {
        return errorSet;
    }
    Tuple* copyTuple = new Tuple;
    copyTuple[0] = _pTuples[item-1];
    Set copy(1,copyTuple);
    return copy;
}

Set::Set() {
    _pTuples = NULL;
    _numElements = 0;
}

Set::Set(const Set& s) {
    _numElements = s._numElements;
    if (_numElements>0){
        _pTuples = new Tuple[_numElements];
        for (int i=0;i<_numElements;i++){
            _pTuples[i]=s._pTuples[i];
        }
    }
}

Set::Set(const int numElements, const int data[]) {
    if (numElements<0){
        _numElements=-1;
    } else if (data==NULL){
        _numElements=0;
    } else {
        _numElements=numElements;
        if (numElements>0) {
            Tuple* temp = new Tuple[numElements];
            for (int i=0;i<numElements;i++){
                temp[i] = data[i];
            }
            for (int i=0;i<numElements-1;i++){
                if (temp[i].size()==1){
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
                if(temp[i].size()==1){
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

std::ostream& operator<<(std::ostream& os, const Set& s) {
    if (s.isError()){
        os << "{ERROR SET}";
        return os;
    } else {
        if (s.isEmpty()) {
            os << "{}";
            return os;
        } else {
            os << "{" << s._pTuples[0];
            for (int i = 1; i < s._numElements; ++i)
                os << "," << s._pTuples[i];
            os << "}";
            return os;
        }
    }
}
