#include "player.h"
#include <iostream>
using namespace std; 


Player::Player(){
        cards = 7;
        order = 0;
        isComp = false;
        for(int i=cards;i<20;i++){
                hand[i].isCard = false;
        }
}
            
void Player::drawCard() {
    hand[cards].isCard = true;
    cards++;
}

void Player::playCard(int input){
        int i = input -1;
        for(;hand[i].isCard;i++){
                hand[i] = hand[i+1];
        }
        hand[i-1].isCard = false;
        hand[i].randomize();
        cards--;
}

