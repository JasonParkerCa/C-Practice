//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <limits.h>
#include <time.h>

//////////////////////////////////////////////////////////////
//
// #includes for local testing only
//


#ifndef MARMOSET_TESTING
#include <iostream>
#endif

//////////////////////////////////////////////////////////////
//
// Enums and structs for use in assignment

#ifndef MARMOSET_TESTING
enum COURSE
{
    CHE102,
    MATH115,
    MATH117,
    ECE105,
    ECE150,
    ECE190,
    Null
};

struct Assignment
{
    COURSE course;
    int    assnNum;      // Assignment number
    int    dueMonth;     // 1-12
    int    dueDay;       // 1-31
    char*  description;  // Assignment description
};

#endif


//////////////////////////////////////////////////////////////
//
// Class declaration; modify but do not remove
bool isEarlier(const Assignment* a1, const Assignment* a2);
bool isEarlier(const Assignment* a1, const Assignment* a2){
    int month1, month2, day1, day2, days1, days2;
    month1=a1->dueMonth;
    day1=a1->dueDay;
    month2=a2->dueMonth;
    day2=a2->dueDay;
    days1=month1*100+day1;
    days2=month2*100+day2;
    if (days1>=days2){
        return false;
    } else {
        return true;
    }
}


class HomeworkQueue
{
public:
    bool                enqueue(const Assignment& assignment);
    const Assignment*   dequeue();
    int                 daysTillDue(const COURSE course);
    const Assignment*   dueIn(const int numDays);
    
    
    HomeworkQueue();    //constructor
    ~HomeworkQueue();   //destructor
private:
    int number;
    Assignment** array;
};


//////////////////////////////////////////////////////////////
//
// Your code here ...
//

bool HomeworkQueue::enqueue(const Assignment& assignment)
{
    if (assignment.dueDay<=0||assignment.dueDay>31||assignment.dueMonth<=0||assignment.dueMonth>12||assignment.course==Null||assignment.description==NULL||assignment.description[0]==0){
        return false;
    }
    
    for (int i=0;i<number;i++){
        if (assignment.course==array[i]->course&&assignment.assnNum==array[i]->assnNum){
            return false;
        }
    }
    
    bool iffind=false;
    if (number==0){
        Assignment* add = new Assignment;
        add->course=assignment.course;
        add->assnNum=assignment.assnNum;
        add->dueDay=assignment.dueDay;
        add->dueMonth=assignment.dueMonth;
        add->description=assignment.description;
        array[0]=add;
        number++;
    } else {
        Assignment* add = new Assignment;
        add->course=assignment.course;
        add->assnNum=assignment.assnNum;
        add->dueDay=assignment.dueDay;
        add->dueMonth=assignment.dueMonth;
        add->description=assignment.description;
        int i=0;
        while (i<number){
            if (isEarlier(add,array[i])){
                for (int j=number;j>=i+1;j--){
                    array[j]=array[j-1];
                }
                array[i]=add;
                iffind=true;
                break;
            }
            i++;
        }
        if (iffind==false){
            array[number]=add;
        }
        number++;
    }
    return true;
}

const Assignment* HomeworkQueue::dequeue()
{
    if (number==0||array==NULL){
        return NULL;
    }
    
    Assignment* quit = array[0];
    for (int i=0;i<number-1;i++){
        array[i]=array[i+1];
    }
    number--;
    return quit;
}

int HomeworkQueue::daysTillDue(const COURSE course)
{
    if (number==0||array==NULL){
        return INT_MAX;
    }
    
    
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime (&rawtime);
    int month=timeinfo->tm_mon+1;
    int day=timeinfo->tm_mday;
    int currentDay=month*30+day;
    int dueDay, leftDay=0;
    
    bool iffound=false;
    
    for (int i=0;i<number;i++){
        if (array[i]->course==course){
            dueDay=array[i]->dueMonth*30+array[i]->dueDay;
            leftDay=dueDay-currentDay;
            iffound=true;
            break;
        }
    }
    
    if (iffound){
        return leftDay;
    } else {
        return INT_MAX;
    }
}

const Assignment* HomeworkQueue::dueIn(const int numDays)
{
    if (numDays<0||number==0||array==NULL){
        Assignment* non = new Assignment;
        non->course=Null;
        return non;
    }
    
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime (&rawtime);
    int month=timeinfo->tm_mon+1;
    int day=timeinfo->tm_mday;
    int currentDay=month*30+day;
    int dueDay, leftDay=0;
    Assignment* due = new Assignment[1000];
    Assignment* copy = new Assignment;
    int index=0;
    
    for (int i=0;i<number;i++){
        dueDay=array[i]->dueMonth*30+array[i]->dueDay;
        leftDay=dueDay-currentDay;
        if (leftDay<=numDays){
            copy->course=array[i]->course;
            copy->assnNum=array[i]->assnNum;
            copy->dueMonth=array[i]->dueMonth;
            copy->dueDay=array[i]->dueDay;
            copy->description=array[i]->description;
            due[index]=*copy;
            index++;
        }
    }
    
    due[index].course=Null;
    
    return due;
}

HomeworkQueue::HomeworkQueue()
{
    number=0;
    array=new Assignment*[1000];
}

HomeworkQueue::~HomeworkQueue()
{
    Assignment* curr;
    for (int i=0;i<number;i++){
        curr=array[i];
        delete curr;
    }
    delete array;
    number=0;
}





#ifndef MARMOSET_TESTING
int main(const int argc, const char* const args[])
{
    //formatting
    std::cout << std::endl;
    
    HomeworkQueue hwq;
    
    char boring[] = "Something something solubility something something gases something";
    
    Assignment someAssignment =
    {
        .course = CHE102,
        .assnNum = 1000000,
        .dueMonth = 12,
        .dueDay = 4,
        .description = boring
    };
    
    if(!hwq.enqueue(someAssignment))
    {
        std::cout << "enqueue() unsuccessful" << std::endl;
    }
    else
    {
        std::cout << "enqueue() successful" << std::endl;
    }
    
    const Assignment* assnInTheQueue = hwq.dequeue();
    
    if (!assnInTheQueue)
    {
        std::cout << "dequeue() unsuccessful" << std::endl;
        
    }
    else
    {
        std::cout << "dequeue() successful" << std::endl;
    }
    
    //formatting
    std::cout << std::endl;
    
    return 0;
}
#endif
