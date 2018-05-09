//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//
#include <time.h>
#include <limits.h>
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
#ifndef MARMOSET_TESTING
enum COURSE {CHE102, MATH115, MATH117, ECE105, ECE150, ECE190, Null};

struct Assignment
{
    COURSE course; // CHE102, MATH117, etc.
    int assnNum; // Assignment Number
    int dueMonth; // Month due (1-12)
    int dueDay; // Day due (1-31)
    char* description; // Assignment description
};

struct HomeworkQueue
{
    Assignment* assn;
    HomeworkQueue* nextInQueue;
};

#endif

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove
//

bool enqueue(HomeworkQueue*& queue, const Assignment& assignment);
const Assignment* dequeue(HomeworkQueue*& queue);
int daysTillDue(const HomeworkQueue* q, const COURSE course);
const Assignment* dueIn(const HomeworkQueue* q, const int numDays);
bool isEarlier(const Assignment& a1, const Assignment& a2);

//////////////////////////////////////////////////////////////
//
// Function definitions. PLEASE USE HELPER FUNCTIONS
//

bool isEarlier(const Assignment& a1, const Assignment& a2){
    int month1, month2, day1, day2, days1, days2;
    month1=a1.dueMonth;
    day1=a1.dueDay;
    month2=a2.dueMonth;
    day2=a2.dueDay;
    days1=month1*100+day1;
    days2=month2*100+day2;
    if (days1>=days2){
        return false;
    } else {
        return true;
    }
}


bool enqueue(HomeworkQueue*& queue, const Assignment& assignment)
{
    int month=0;
    int day=0;
    int days1=0;
    int days2=0;
    int daysleft;
    
    time_t rawtime;
    struct tm * timeinfo;
    
    time(&rawtime);
    timeinfo = localtime (&rawtime);
    
    month=timeinfo->tm_mon+1;
    day=timeinfo->tm_mday;
    
    days1=month*30+day;
    
    
    if (assignment.dueMonth<=0 || assignment.dueMonth>=13){
        return false;
    }
    
    if (assignment.dueDay<=0 || assignment.dueDay>=32){
        return false;
    }
    
    if ((assignment.dueMonth==1 || assignment.dueMonth==3 || assignment.dueMonth==5 || assignment.dueMonth==7 || assignment.dueMonth==8 || assignment.dueMonth==10 || assignment.dueMonth==12)&&assignment.dueDay>31){
        return false;
    }
    
    if ((assignment.dueMonth==4 || assignment.dueMonth==6 || assignment.dueMonth==9 || assignment.dueMonth==11)&&assignment.dueDay>30){
        return false;
    }
    
    if (assignment.dueMonth==2&&assignment.dueDay>28){
        return false;
    }
    
    Assignment* copy = new Assignment;
    copy->course=assignment.course;
    copy->assnNum=assignment.assnNum;
    copy->dueMonth=assignment.dueMonth;
    copy->dueDay=assignment.dueDay;
    copy->description=assignment.description;
    
    days2=copy->dueMonth*30+copy->dueDay;
    
    daysleft=days2-days1;
    
    if (daysleft<0){
        return false;
    }
    
    int i=1;
    int position;
    HomeworkQueue* head = queue;
    
    if (queue->nextInQueue==NULL){
        queue->assn=copy;
    }
    
    HomeworkQueue *p = new HomeworkQueue;
    p->assn = copy;
    
    while (queue->nextInQueue!=NULL){
        if (copy->course==(*(queue->assn)).course && copy->assnNum==(*(queue->assn)).assnNum){
            return false;
        }
        queue=queue->nextInQueue;
    }
    
    queue=head;
    
    while (queue->nextInQueue!=NULL){
        if (isEarlier(*p->assn,*queue->assn)){
            position=i;
            break;
        }
        queue=queue->nextInQueue;
        i++;
    }
    
    queue=head;
    
    for (int j=1;j<=i-2;j++){
        queue=queue->nextInQueue;
    }
    
    p->nextInQueue=queue->nextInQueue;
    queue->nextInQueue=p;
    
    queue=head;
    
    return true;
}

const Assignment* dequeue(HomeworkQueue*& queue)
{
    if (queue->assn==NULL && queue->nextInQueue==NULL){
        return NULL;
    }
    
    if (queue->nextInQueue==NULL && queue->assn!=NULL){
        Assignment* first = new Assignment;
        first->course=(*queue->assn).course;
        first->assnNum=(*queue->assn).assnNum;
        first->dueMonth=(*queue->assn).dueMonth;
        first->dueDay=(*queue->assn).dueDay;
        first->description=(*queue->assn).description;
        delete(queue);
        return first;
    }
    
    HomeworkQueue* head = new HomeworkQueue;
    head=queue;
    Assignment* normal = new Assignment;
    queue=queue->nextInQueue;
    normal->course=(*queue->assn).course;
    normal->assnNum=(*queue->assn).assnNum;
    normal->dueMonth=(*queue->assn).dueMonth;
    normal->dueDay=(*queue->assn).dueDay;
    normal->description=(*queue->assn).description;
    queue=head;
    delete(queue);
    return normal;
}

int daysTillDue(const HomeworkQueue* q, const COURSE course)
{
    
    
    int daysleft=0;
    bool found=false;
    
    if (q->nextInQueue==NULL && (*(q->assn)).course==course){
        found=true;
    }
    
    if (q->nextInQueue==NULL && q->assn==NULL){
        return INT_MAX;
    }
    
    while (q->nextInQueue!=NULL) {
        if ((*(q->assn)).course==course){
            found=true;
            break;
        }
        q=q->nextInQueue;
    };
    
    if (found==false){
        return INT_MAX;
    }
    
    int month=0;
    int day=0;
    int days1=0;
    int days2=0;
    
    struct tm * timeinfo;
    time_t rawtime;
    
    rawtime=time(NULL);
    timeinfo = localtime (&rawtime);
    month=timeinfo->tm_mon+1;
    day=timeinfo->tm_mday;
    
    days1=month*30+day;
    days2=(*(q->assn)).dueMonth*30+(*(q->assn)).dueDay;
    daysleft=days2-days1;
    
    return daysleft;
}

const Assignment* dueIn(const HomeworkQueue* q, const int numDays)
{
    
    Assignment* next = new Assignment;
    if (numDays<0||q==NULL||q->assn==NULL){
        next->course=Null;
        return next;
    }
    
    
    int month=0;
    int day=0;
    int days1=0;
    int days2=0;
    int daysleft;
    
    time_t rawtime;
    struct tm * timeinfo;
    
    time(&rawtime);
    timeinfo = localtime (&rawtime);
    
    month=timeinfo->tm_mon+1;
    day=timeinfo->tm_mday;
    
    days1=month*30+day;
    
    int i=0;
    
    const HomeworkQueue* head;
    head=q;
    
    for (; q!=NULL;q=q->nextInQueue){
        days2=(*(q->assn)).dueMonth*30+(*(q->assn)).dueDay;
        daysleft=days2-days1;
        if (daysleft<=numDays){
            i++;
        }
    }
    
    Assignment *copy = new Assignment[i+1];
    
    q=head;
    
    i=0;
    
    for (; q!=NULL;q=q->nextInQueue){
        days2=(*(q->assn)).dueMonth*30+(*(q->assn)).dueDay;
        daysleft=days2-days1;
        if (daysleft<=numDays){
            copy[i].course=(*(q->assn)).course;
            copy[i].assnNum=(*(q->assn)).assnNum;
            copy[i].dueMonth=(*(q->assn)).dueMonth;
            copy[i].dueDay=(*(q->assn)).dueDay;
            copy[i].description=(*(q->assn)).description;
            i++;
        }
    }
    
    Assignment* None = new Assignment;
    None->course=Null;
    copy[i]=*None;
    
    return copy;
    
}

//////////////////////////////////////////////////////////////
//
// Test Driver
//
// Do not remove the #ifndef and its associated #endif
//

#ifndef MARMOSET_TESTING

int main(const int argc, const char* const argv[]) {
    // Some test driver code here ....
    std::cout << std::endl << "Implement some more appropriate tests in main()" << std::endl << std::endl;
    
    HomeworkQueue* p_queue = new HomeworkQueue;
    p_queue->nextInQueue = NULL;
    p_queue->assn = NULL;
    
    char sampleDescription[] = "Sequential Execution";
    Assignment assn1 =
    {
        .course = ECE150,
        .assnNum = 0,
        .dueMonth = 9,
        .dueDay = 15,
        .description = sampleDescription
    };
    
    bool enqueueSuccess = enqueue(p_queue, assn1);
    
    if(enqueueSuccess)
    {
        std::cout << "assn1 enqueued successfully" << std::endl << std::endl;
        
    }
    else
    {
        std::cout << "enqueue() failed" << std::endl << std::endl;
    }
    
    const Assignment* p_firstAssignmentInQueue = dequeue(p_queue);
    
    if (p_firstAssignmentInQueue)
    {
        std::cout << "Dequeue successful..." << std::endl;
        std::cout << "Course: " << p_firstAssignmentInQueue->course << std::endl;
        std::cout << "Assignment #: " << p_firstAssignmentInQueue->assnNum << std::endl;
        std::cout << "Day due: " << p_firstAssignmentInQueue->dueDay << std::endl;
        std::cout << "Month due: " << p_firstAssignmentInQueue->dueMonth << std::endl;
        std::cout << "Description: " << p_firstAssignmentInQueue->description << std::endl;
    }
    else
    {
        std::cout << "dequeue() failed" << std::endl;
    }
    
    //    delete p_queue;
    
    return 0;
}

#endif
