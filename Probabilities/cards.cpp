#include <iostream>
#include <iomanip>
#include <string>
#include <stdio.h>
extern "C" {
#include <stdlib.h>
#include <time.h>
}
using namespace std;

int remainingCards(string* cards);
string deal(string* cards);
string* generateCards();
string* shuffle(string* cards);
void printDeck(string* cards);
void whenToStand(int threshold);
void value(string dealCard, int& total);
void count(string dealCard, int& counting);

int random(int min, int max){
    int random = min + rand() / (RAND_MAX / (max - min + 1) + 1);
    return random;
}

string* generateCards() {
    string* cards = new string[52];
    string add;
    int changeSuit=1;
    for (int i=0;i<52;i++){
        if (changeSuit==14){
            changeSuit=1;
        }
        if (i==0 || i==13 || i==26 || i==39){
            add = "Ace";
        } else if (i==10 || i==23 || i==36 || i==49){
            add = "Jack";
        } else if (i==11 || i==24 || i==37 || i==50){
            add = "Queen";
        } else if (i==12 || i==25 || i==38 || i==51){
            add = "King";
        } else {
            add = to_string(changeSuit);
        }
        cards[i]=add;
        changeSuit++;
    }
    return cards;
}

int remainingCards(string* cards) {
    int number=0;
    for (int i=0;i<52;i++){
        if (cards[i]!="0"){
            number++;
        }
    }
    return number;
}

string deal(string* cards){
    int index = 0;
    string lastcard;
    for (int i=0;i<52;i++){
        if (cards[i]!="0"){
            index=i;
        }
    }
    lastcard=cards[index];
    cards[index]="0";
    return lastcard;
}

string* shuffle(string* cards) {
    string* newcards = new string[52];
    int min=0, max=51;
    int index;
    for (int i=0;i<52;i++){
        index=random(min, max);
        newcards[i]=cards[index];
        for (int j=index;j<51;j++){
            cards[j]=cards[j+1];
        }
        max--;
    }
    return newcards;
}

void printDeck(string* cards){
    for (int i=0;i<52;i++){
        cout << cards[i] << endl;
    }
    cout << endl;
}

void whenToStand(int threshold){
    string* cards = generateCards();
    cards = shuffle(cards);
    string dealCard;
    int bust=0;
    int total=0;
    for (int i=0;i<10000;i++){
        total=0;
        while (total<threshold){
            if (remainingCards(cards)==0){
                cards = generateCards();
                cards = shuffle(cards);
            }
            dealCard = deal(cards);
            value(dealCard,total);
            if (total>21){
                bust++;
                break;
            }
        }
    }
    float fraction = ((float)bust)/((float)10000);
    cout << threshold << ": (" << fraction << ")" << endl;
}

void BlackJack() {
    int counting=0,rightchoice=0;
    int dealerTotal=0,myTotal=0;
    int external=0;
    float result=0;
    string bet,temp;
    string* Black = generateCards();
    Black = shuffle(Black);
    string dealCard;
    bool isReshuffle;
    
    for (int i=0;i<10000+external;i++){
        dealerTotal=0;
        myTotal=0;
        isReshuffle=false;
        temp="";
        if (counting>0){
            bet="high";
        }
        if (counting<0){
            bet="low";
        }
        if (counting==0){
            bet="average";
        }
        
        //dealer
        if (remainingCards(Black)==0){
            Black = generateCards();
            Black = shuffle(Black);
            counting = 0;
            external++;
            continue;
        }
        
        dealCard=deal(Black);
        count(dealCard,counting);
        value(dealCard, dealerTotal);
        
        //imaginary players for counting
        for (int i=0;i<6;i++){
            if (remainingCards(Black)==0){
                Black = generateCards();
                Black = shuffle(Black);
                counting = 0;
                external++;
                isReshuffle=true;
                break;
            }
            dealCard=deal(Black);
            count(dealCard,counting);
        }
        
        if (isReshuffle){
            continue;
        }
        
        //the player
        while (myTotal<18){
            if (remainingCards(Black)==0){
                Black = generateCards();
                Black = shuffle(Black);
                counting = 0;
                external++;
                isReshuffle=true;
                break;
            }
            dealCard=deal(Black);
            count(dealCard,counting);
            value(dealCard, myTotal);
            if (myTotal==21){
                temp="win";
            }
            if (myTotal>21){
                temp="lose";
            }
        }
        
        if (isReshuffle){
            continue;
        }
        
        if (temp=="") {
            while (dealerTotal<17){
                if (remainingCards(Black)==0){
                    Black = generateCards();
                    Black = shuffle(Black);
                    counting = 0;
                    external++;
                    isReshuffle=true;
                    break;
                }
                dealCard=deal(Black);
                count(dealCard,counting);
                value(dealCard, dealerTotal);
                if (dealerTotal>21){
                    temp="win";
                    break;
                }
                if (myTotal<dealerTotal){
                    temp="lose";
                    break;
                }
            }
            
            if (isReshuffle){
                continue;
            }
            
            if (temp=="") {
                if (dealerTotal==myTotal){
                    temp="draw";
                } else if (dealerTotal>myTotal){
                    temp="lose";
                } else {
                    temp="win";
                }
            }
        }
        
        if ((bet=="average"&&temp=="win")||(bet=="high"&&temp=="win")||(bet=="low"&&temp=="lose")||(temp=="draw")){
            rightchoice++;
        }
    }
    result=float(rightchoice)/float(10000);
    cout << "The fraction of the times mading the right decision: " << result << endl;
}

void count(string dealCard, int& counting){
    if (dealCard=="2"||dealCard=="3"||dealCard=="4"||dealCard=="5"||dealCard=="6"){
        counting+=1;
    }
    if (dealCard=="7"||dealCard=="8"||dealCard=="9"){
        counting=counting;
    }
    if (dealCard=="Ace"||dealCard=="Jack"||dealCard=="Queen"||dealCard=="King"||dealCard=="10") {
        counting-=1;
    }
}

void value(string dealCard, int& total){
    if (dealCard=="Ace"){
        if (total>10){
            total+=1;
        } else {
            total+=11;
        }
    }
    if (dealCard=="Jack" || dealCard=="Queen" || dealCard=="King"){
        total+=10;
    }
    if (dealCard!="Jack" && dealCard!="Queen" && dealCard!="King" && dealCard!="Ace"){
        total+=stoi(dealCard);
    }
}

int main(int argc, const char * argv[]) {
    srand((unsigned int)time(NULL));
    cout << endl;
    cout << "-----------------------------------" << endl;
    cout << endl;
    cout << "Question 4:" << endl;
    cout << endl;
    cout << setprecision(4) << fixed;
    for (int i=10;i<=20;i++){
        whenToStand(i);
    }
    cout << endl;
    cout << "-----------------------------------" << endl;
    cout << endl;
    cout << "Question 5:" << endl;
    cout << endl;
    BlackJack();
    cout << endl;
    return 0;
}
