#include "card.h" 
#include <iostream> 
#include <ctime> 


Card::Card(){
    isCard = true;
    color = (rand()%5); //sets color, 0=red,1=blue,2=green,3=yellow,4=wild card
    if(color==4){
        color = (rand()%5); //decreases the chances of a wild card
        if(color==4){
            value = (rand()%2)+13; //13=normal or 14=+4
        }
    }if(color != 4 ){
        value = (rand()%13); //sets value, 0,1,2,3,4,5,6,7,8,9,10=skip,11=+2,12=reverse
    }
}

void Card::setColor(int c){
    color = c;

}

void Card::randomize(){
    color = (rand()%5); //sets color, 0=red,1=blue,2=green,3=yellow,4=wild card
    if(color==4){
        color = (rand()%5); //decreases the chances of a wild card
        if(color==4){
            value = (rand()%2)+13; //13=normal or 14=+4
        }
    }if(color != 4 ){
        value = (rand()%13); //sets value, 0,1,2,3,4,5,6,7,8,9,10=skip,11=+2,12=reverse
    }
}
