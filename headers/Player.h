#ifndef PLAYER_H
#define PLAYER_H
#include "card.h"
#include <iostream> 
using namespace std; 


class Player {
    public:
        int cards;
        int order;
        Card hand[30];
        bool isComp;
        
        Player();
        void drawCard();  
        void playCard(int input);  
        // void drawCard(Card cardArray);
 
};

#endif


