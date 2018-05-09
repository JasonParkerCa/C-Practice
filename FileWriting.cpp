//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//
#include <fstream>
#include <limits.h>
#include <math.h>
//////////////////////////////////////////////////////////////
//
// local #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING
#include <iostream>
#endif

//////////////////////////////////////////////////////////////
//
// struct definitions
//

using namespace std;

#ifndef MARMOSET_TESTING
struct Student{
    int studentID;
    int grade;
};

struct Dataset{
    int numStudents;
    Student* students;
};

struct Rejects{
    int numRejects;
    int* rejects;
};

struct Mode{
    int numModes;
    int* modes;
};

struct Statistics{
    int   minimum;
    float average;
    int   maximum;
    float popStdDev;
    float smplStdDev;
    Mode  mode;
    int   histogram[10];
};
#endif

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove
//
int readCSV(const char filename[],const int minAcceptableID,
            const int maxAcceptableID,Dataset& data,
            Rejects& rejects);

int computeStatistics(Dataset& data, Statistics& stats);

int writeCSV(const char filename[], const Statistics& stats);

int selection(int* dataset, const int size, int i);

bool OK = true;

//////////////////////////////////////////////////////////////
//
// Function definitions. PLEASE USE HELPER FUNCTIONS
//


int selection(int* dataset, const int size, int i){
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


int readCSV(const char filename[],const int minAcceptableID,
            const int maxAcceptableID,Dataset& data,
            Rejects& rejects){
    
    if (filename==NULL){
        OK=false;
        return -1;
    }
    
    
    
    int lengthoffilename=0;
    bool extension=false;
    int lengthnew;
    int index;
    char* newfile1;
    char* newfile2;
    char* newfile3;
    
    for (int i=0;filename[i]!=0;i++){
        lengthoffilename++;
    }
    
    
    if (lengthoffilename<=4){
        lengthnew=lengthoffilename+4;
        newfile1=new char[lengthoffilename+4];
        for (int i=0;i<lengthoffilename;i++){
            newfile1[i]=filename[i];
        }
        newfile1[lengthnew-4]='.';
        newfile1[lengthnew-3]='c';
        newfile1[lengthnew-2]='s';
        newfile1[lengthnew-1]='v';
        index=1;
    } else {
        for (int i=0;filename[i+3]!=0;i++){
            if (filename[i]=='.'&&filename[i+1]=='c'&&filename[i+2]=='s'&&filename[i+3]=='v'){
                extension=true;
            }
        }
        if (extension){
            lengthnew=lengthoffilename+4;
            newfile2=new char[lengthnew];
            for (int i=0;i<lengthoffilename;i++){
                newfile2[i]=filename[i];
            }
            index=2;
        } else {
            lengthnew=lengthoffilename+4;
            newfile3=new char[lengthoffilename+4];
            for (int i=0;i<lengthoffilename;i++){
                newfile3[i]=filename[i];
            }
            newfile3[lengthnew-4]='.';
            newfile3[lengthnew-3]='c';
            newfile3[lengthnew-2]='s';
            newfile3[lengthnew-1]='v';
            index=3;
        }
    }
    
    char newfile[lengthnew];
    
    if (index==1){
        for (int i=0;i<lengthnew;i++){
            newfile[i]=newfile1[i];
        }
    }
    
    if (index==2){
        for (int i=0;i<lengthnew;i++){
            newfile[i]=newfile2[i];
        }
    }
    
    if (index==3){
        for (int i=0;i<lengthnew;i++){
            newfile[i]=newfile3[i];
        }
    }
    
    
    std::ifstream in;
    in.open(newfile);
    
    if (!in.is_open() || minAcceptableID>=maxAcceptableID){
        OK=false;
        return -1;
    }
    
    
    
    int max=200;
    char statistic[max];
    
    int maxline=0;
    
    while (!in.eof()){
        in.getline(statistic,max);
        maxline++;
    }
    
    in.close();
    
    data.students = new Student[maxline];
    for (int i=0;i<maxline;i++){
        data.students[i].studentID=0;
        data.students[i].grade=0;
    }
    rejects.numRejects=0;
    rejects.rejects = new int[maxline];
    for (int i=0;i<10;i++){
        rejects.rejects[i]=0;
    }
    data.numStudents=0;
    
    
    int ID;
    int mark;
    int indexcomma=0;
    bool overcomma = false;
    bool ifvalid=true;
    bool overspace=false;
    int firstnumber;
    int lastnumber;
    int firstdecimal;
    int lastdecimal;
    bool warning=false;
    
    in.open(newfile);
    
    int indexofline =0;
    bool done =false;
    
    while (!done){
        ID=0;
        mark=0;
        ifvalid=true;
        overcomma=false;
        overspace=false;
        if (!in.getline(statistic,max)){
            if (in.eof()){
                done=true;
                break;
            }else{
                ifvalid=false;
            }
        }
        indexofline++;
        
        for (int i=0;statistic[i];i++){
            if ((statistic[i]<'0' || statistic[i]>'9') && statistic[i]!=' ' && statistic[i]!='\t'&& statistic[i]!='+'&& statistic[i]!='-'&&statistic[i]!=','){
                ifvalid=false;
                warning=true;
            }
            if ((statistic[i]=='+'||statistic[i]=='-')&&statistic[i-1]!=','){
                ifvalid=false;
                warning=true;
            }
        }
        
        if (statistic[0]==0||statistic[0]=='\n'){
            ifvalid=false;
            warning=true;
        }
        
        if (ifvalid==true){
            overcomma=true;
            for (int i=0;statistic[i]!=',';i++){
                if (statistic[i]>='0' && statistic[i]<='9'){
                    ID=ID*10+(statistic[i]-'0');
                }
                
                if (statistic[i+1]==','){
                    indexcomma=i+1;
                    overcomma=false;
                }
            }
            
            if (statistic[indexcomma+1]==0){
                overcomma=true;
            }
            
            for (int i=indexcomma+1;statistic[i]!=0;i++){
                if (statistic[i]==','){
                    overcomma=true;
                }
                if (statistic[i]>='0' && statistic[i]<='9'){
                    mark=mark*10+(statistic[i]-'0');
                }
                if (statistic[i+1]==0){
                    break;
                }
            }
            
            if (statistic[indexcomma+1]=='-'){
                mark = (-1)*mark;
            }
            
            for (int i=0;statistic[i]!=',';i++){
                if (statistic[i]>='0'&&statistic[i]<='9'){
                    firstnumber=i;
                    break;
                }
            }
            
            for (int i=0;statistic[i]!=',';i++){
                if (statistic[i]>='0'&&statistic[i]<='9'){
                    lastnumber=i;
                }
            }
            
            for (int i=indexcomma+1;statistic[i];i++){
                if (statistic[i]>='0'&&statistic[i]<='9'){
                    firstdecimal=i;
                    break;
                }
            }
            
            for (int i=indexcomma+1;statistic[i];i++){
                if (statistic[i]>='0'&&statistic[i]<='9'){
                    lastdecimal=i;
                }
            }
            
            for (int i=0;statistic[i];i++){
                if ((statistic[i]==' '||statistic[i]=='\t')&&i>firstnumber&&i<lastnumber){
                    overcomma=true;
                }
                if ((statistic[i]==' '||statistic[i]=='\t')&&i>firstdecimal&&i<lastdecimal){
                    overcomma=true;
                }
            }
        
            if (ID<minAcceptableID || ID>maxAcceptableID || mark<0 || mark>100 || overcomma==true){
                warning=true;
                if (rejects.numRejects>=9){
                    OK=false;
                    return -1;
                }
                rejects.rejects[rejects.numRejects]=indexofline;
                rejects.numRejects++;
            } else {
                data.students[data.numStudents].studentID=ID;
                data.students[data.numStudents].grade=mark;
                data.numStudents++;
            }
        }
    }
    
    in.close();
    
    if (rejects.numRejects>0 && warning==true){
        return rejects.numRejects;
    }
    
    if (warning==true||data.numStudents==0){
        return 1;
    }
        
    return 0;
}

int computeStatistics(Dataset& data, Statistics& stats){
    
    if(OK==false){
        return -1;
    }
    
    stats.minimum=0;
    stats.average=0;
    stats.maximum=0;
    stats.popStdDev=0;
    stats.smplStdDev=0;
    
    for (int i=0;i<10;i++){
        stats.histogram[i]=0;
    }
    
    stats.mode.numModes=0;
    
    
    float sum=0;
    int max=-INT_MAX;
    int min=INT_MAX;
    float squaresum=0;
    
    for (int i=0;i<data.numStudents;i++){
        sum=sum+data.students[i].grade;
        if (data.students[i].grade<min){
            min=data.students[i].grade;
        }
        if (data.students[i].grade>max){
            max=data.students[i].grade;
        }
    }
    
    stats.average=sum/float(data.numStudents);
    stats.minimum=min;
    stats.maximum=max;
    
    for (int i=0;i<data.numStudents;i++){
        if (data.students[i].grade==100){
            stats.histogram[9]++;
        }else{
            stats.histogram[data.students[i].grade/10]++;
        }
    }
    
    for (int i=0;i<data.numStudents;i++){
        squaresum = squaresum + pow((data.students[i].grade-stats.average),2);
    }
    
    stats.popStdDev = sqrt(1/(float)(data.numStudents)*squaresum);
    
    if (data.numStudents-1==0){
        stats.smplStdDev=NAN;
    }else{
        stats.smplStdDev= sqrt(1/(float)(data.numStudents-1)*squaresum);
    }
    
    int m[data.numStudents][2];
    int n;
    for (int i=0;i<data.numStudents;i++){
        n=0;
        m[i][0]=data.students[i].grade;
        for (int j=0;j<data.numStudents;j++){
            if (m[i][0]==data.students[j].grade){
                n++;
            }
        }
        m[i][1]=n;
    }
    
    for (int i=0;i<data.numStudents-1;i++){
        for (int j=i+1;j<data.numStudents;j++){
            if (m[i][0]==m[j][0]){
                m[j][1]=0;
            }
        }
    }
    
    max=-INT_MAX;
    int x=0;
    stats.mode.modes = new int[data.numStudents];
    
    for (int i=0;i<data.numStudents;i++){
        stats.mode.modes[i]=0;
    }
    
    for (int i=0;i<data.numStudents;i++){
        if (max<m[i][1]){
            max=m[i][1];
        }
    }
    
    for (int i=0;i<data.numStudents;i++){
        if (m[i][1]==max){
            stats.mode.modes[x]=m[i][0];
            x++;
        }
    }
    
    stats.mode.numModes=x;
    
    if (x!=0){
        
        selection(stats.mode.modes,x,0);
        
    }
    
    return 0;
}

int writeCSV(const char filename[], const Statistics& stats){
    
    if (OK==false){
        return -1;
    }
    
    int lengthoffilename=0;
    bool ending=false;
    for (int i=0;filename[i+3]!=0;i++){
        if (filename[i]=='.'&&filename[i+1]=='c'&&filename[i+2]=='s'&&filename[i+3]=='v'){
            ending=true;
        }
        lengthoffilename++;
    }
    
    lengthoffilename+=3;
    
    int fnew;
    
    if(ending){
        fnew=lengthoffilename+1;
    }else{
        fnew=lengthoffilename+5;
    }
    
    char newfile[fnew];
    
    if(ending){
        for (int i=0;i<lengthoffilename-4;i++){
            newfile[i]=filename[i];
        }
        newfile[fnew-5]='.';
        newfile[fnew-4]='s';
        newfile[fnew-3]='t';
        newfile[fnew-2]='a';
        newfile[fnew-1]='t';
        newfile[fnew]=0;
    } else {
        for (int i=0;i<lengthoffilename;i++){
            newfile[i]=filename[i];
        }
        newfile[fnew-5]='.';
        newfile[fnew-4]='s';
        newfile[fnew-3]='t';
        newfile[fnew-2]='a';
        newfile[fnew-1]='t';
        newfile[fnew]=0;
    }
    
    std::ofstream out;
    out.open(newfile);
    if(!out.is_open()){
        return -1;
    }
    
    
    out << "Minimum: " << stats.minimum << endl;
    out << "Average: " << stats.average << endl;
    out << "Maximum: " << stats.maximum << endl;
    out << "Population Standard Deviation: " << stats.popStdDev << endl;
    out << "Sample Standard Deviation: " << stats.smplStdDev << endl;
    out << "Modes: ";
    for (int i=0;i<stats.mode.numModes;i++){
        out << stats.mode.modes[i];
        if (i!=stats.mode.numModes-1){
            out << ", ";
        }
    }
    out << endl;
    out << "Histogram:" << endl;
    out << "[0-9]: " << stats.histogram[0] << endl;
    out << "[10-19]: " << stats.histogram[1] << endl;
    out << "[20-29]: " << stats.histogram[2] << endl;
    out << "[30-39]: " << stats.histogram[3] << endl;
    out << "[40-49]: " << stats.histogram[4] << endl;
    out << "[50-59]: " << stats.histogram[5] << endl;
    out << "[60-69]: " << stats.histogram[6] << endl;
    out << "[70-79]: " << stats.histogram[7] << endl;
    out << "[80-89]: " << stats.histogram[8] << endl;
    out << "[90-100]: " << stats.histogram[9] << endl;
    out.close();
    
    return 0;
}
//////////////////////////////////////////////////////////////
//
// Test Driver
//
// Do not remove the #ifndef and its associated #endif
//

#ifndef MARMOSET_TESTING

#define isNaN(X) (X != X)  // NaN is the only float that is not equal to itself

int main(const int argc, const char* const argv[]) {
    
    // Some test driver code here ....
    int minAcceptableID = 0;
    int maxAcceptableID = 2000000;
    
    Dataset data = {0};
    Rejects rejects = {0};
    Statistics stats = {0};
    
    std::cout << std::endl << "Implement some more appropriate tests in main()" << std::endl << std::endl;
    
    if(readCSV(argv[1], minAcceptableID, maxAcceptableID, data, rejects) < 0)
    {
        std::cout << ".csv file could not be read" << std::endl;
    }
    
    if (computeStatistics(data, stats) < 0)
    {
        std::cout << "Stats could not be computed" << std::endl;
    }
    
    if (writeCSV(argv[1], stats) < 0)
    {
        std::cout << ".stat file could not be written" << std::endl;
    }
    
    if (OK==true){
        
        std::cout << "Average: " << stats.average << std::endl;
        std::cout << "Minimum: " << stats.minimum << std::endl;
        std::cout << "Maximum: " << stats.maximum << std::endl;
        std::cout << "Population standard deviation: " << stats.popStdDev << std::endl;
        std::cout << "Sample standard deviation: " << stats.smplStdDev << std::endl;
        
        
        for (unsigned char i = 0; i < stats.mode.numModes; i++)
        {
            std::cout << "Mode: " << stats.mode.modes[i] << std::endl;
        }
        
        for (unsigned char i = 0; i < 10; i++)
        {
            std::cout << "Histogram bin [" << (i*10) << ", " << ((((i+1)*10) - 1) + i/9) << "]: " << stats.histogram[i] << std::endl;
        }
    }
    
    //    cout << rejects.numRejects << endl;
    //
    //    for (int i=0;i<rejects.numRejects;i++){
    //        cout << rejects.rejects[i] << endl;
    //    }
    //
    cout << endl;
    return 0;
}

#endif
