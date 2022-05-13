#ifndef CARD_H
#define CARD_H
using namespace std; 


class Card{ 
 public:
    //Our attributes 
        int color; //color 
        int value; //value 
        bool isCard; //is this card accessable by the player
    public:
    //default constrcutor
        Card();
        void setColor(int c);
        void randomize();


};

#endif 
