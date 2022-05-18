#include <iostream> 
#include <random>
#include <time.h>
#include <fstream>
#include "card.h"
#include "player.h"
using namespace std;


//the function that ties everything together into one round that a player plays
//this takes in all they players in the game, what round it is, what card is in the center, and which direction the game is going
//the output is the remaining amount of cards that a player has in their hand
int playRound(Player playerArray[],int& round,Card& center,bool& direction);

//this prints all of the formatted cards in someone's hand, as well as a draw card option with a number associated with each
//input is the desired player
//there is no output since this function just prints the cards
void printHand(Player currPlayer); 

//this prints the color of the card
//takes in the desired card
//no output since the function just prints
void printColor(Card hand);

//determines if the action that the player has chosen is one that they can do
//the input is the player whose turn it is, the card in the center, and what action the player picked
//the output is either valid or invalid, which indicates if the player needs to try a different action
bool validPlay(Player currPlayer,Card center,int input); 

//this makes the function of whatever card played work (skip skipping a player, +4 giving the next player 4 cards, etc.)
//input is all of the players in the game, what round it is, the card in the center, the action the player took, and which direction the game is going
//the output is all of the changed values that are pass by reference
void action(Player playerArray[],int& round,Card& center,int input,bool& direction);

//determines if the round should go up or down depending on the direction of the game
//input is what round it is, and which direction the game is going
//output is the round which is pass by reference
void roundUpDown(int& round,bool direction); //incriments the round in the correct direction

//similar to printHand, this prints the card in the center
//input is just the card in the center
//no output since this function just prints
void printCenter(Card center); //prints the card in the center pile

//this automatically decides the first card can be played in a players hand
//input is the player whose turn it is, and the card in the center
//ouput is the action that should be taken to play the first card that can be played
int compAction(Player compPlayer,Card center);

//This takes the action that a player wants to take (playing a card or drawing a card)
//input is the player, and the card in the center
//output is the numeric action associated with what the player wants to do
int playerInput(Player& currPlayer,Card center);

int main() {
int choice;
do{
cout << "1 - Read Contents" << endl;
cout << "2 - Start Uno Game" << endl; 
cin >> choice;
cin.ignore();

if(choice==1)
{
string filename;
ifstream infile; 
do{
    cout << "TYPE FILE NAME: ";
    getline(cin,filename);
    infile.open(filename);
}while(infile.fail());
string text;
while(getline(infile,text))
        {
        cout << text << endl; 
        }
        cout << endl;
        infile.close(); 
    }
}while(choice!=2);

srand(time(NULL)); //seeding time for all rand functions
// Write C++ code here
Player playerArray[4]; //array of all the players in the game
int unoWinner=1; //used to check if a player has 0 cards or not - ending the game if they do have 0
int round=0; //used to determine who is playing the current round
Card center; //this is the card in the center pile that people play on top of
bool direction=true; //indicates which way around the circle the game is going
int comps; //holds the number of computer players in the game

playerArray[0].order = 0; //setting the order for the game
playerArray[1].order = 1;
playerArray[2].order = 2;
playerArray[3].order = 3;

cout << "Welcome to 4 player Uno! All you have to do is press the number that corresponds to the card you want to play!" << endl << endl;
cout << "How many computer players would you like? ";
cin >> comps;

for(int i=3;i>=(4-comps);i--){ //sets computer players to appropriate number starting at player 4 and working down
    playerArray[i].isComp = true;
}

for(;center.color == 4;){ //ensures that the center card never starts off as a wild card
    center.randomize();
}


for(;unoWinner!=0;){ //repeats playRound until someone plays all their cards
    unoWinner = playRound(playerArray,round,center,direction); //checks if someone has no cards
    roundUpDown(round,direction);
}cout << "\n\n";

for(int i = 0;i<5;i++){ //checks each player to see if they have 0 cards
    if(playerArray[i].cards == 0){ //checking if specific player has 0 cards
        cout << "Player " << i+1 << " wins!"; //that player won
    }
}

return 0;
}


bool validPlay(Player currPlayer,Card center,int input){
if((currPlayer.hand[input-1].color == center.color) || (currPlayer.hand[input-1].color == 4) || (currPlayer.hand[input-1].value == center.value) || (currPlayer.cards < input)){ //checking if the card played is the same color or value as the card in the center, or if the player is drawing a card
    return true; //returns that the card can be played
}else{
    return false; //returns that the card can't be played
}
}

int playRound(Player playerArray[],int& round,Card& center,bool& direction){
int input; //takes in the action that the player wants to do (which card they play or draw card)
int cardsLeft; //integer that holds how many cards will be left in the players hand at the end of the round


cout << endl << "=================================================================================================" << endl << "It's player " << round+1 << "'s turn!" << endl;
printCenter(center); //prints the center card
cout << "Play or draw a card: " << "\n\n";
printHand(playerArray[round]); //prints the current players hand

input = playerInput(playerArray[round],center);


if(input>playerArray[round].cards){ //check if the player drew a card
    cardsLeft = playerArray[round].cards + 1; //the number of cards they will have at the end of the round will be the amount they have now +1
}else{ //if the player plays a card
    cardsLeft = playerArray[round].cards - 1; //the number of cards they will have at the end of the round will be the amount of cars they have now -1
}

action(playerArray,round,center,input,direction); //the action associated with the card played or drawn is taken

return cardsLeft; //returns how many cards the current player has so that the game will end if they reach 0 cards
}

void printColor(Card hand){
if(hand.color == 0){ //checks if the color is red
    cout << "Red"; //red
}else if(hand.color == 1){ //checks if the color is blue
    cout << "Blue"; //blue
}else if(hand.color == 2){ //checks if the color is green
    cout << "Green"; //green
}else if(hand.color == 3){ //checks if the color is yellow
    cout << "Yellow"; //yellow
}else{ //wild or wild+4
    cout << "Wild";
}
}

void printHand(Player currPlayer){
int i=0;
for (;currPlayer.hand[i].isCard;i++){ //adds each card in the player's hand into one string
    cout << "\t\t" <<(char)254u << (char)254u << (char)254u << endl; //prints the top 3 squares of the card
    cout << i+1 << ". |\t"; //prints an indication of which number correlates to which card
    printColor(currPlayer.hand[i]); //prints the color of the card

    if((currPlayer.hand[i].value >= 0) && (currPlayer.hand[i].value <= 9)){ //all this prints the correct middle of the card...
        cout << "\t" << (char)254u << currPlayer.hand[i].value << (char)254u << endl; //if the card is numeric 0-9
    }else if(currPlayer.hand[i].value == 10){
        cout << "\t" << (char)254u << "X" << (char)254u << endl; //if the card is a skip
    }else if(currPlayer.hand[i].value == 11){
        cout << "\t" << "+2" << (char)254u << endl; //if the card is a +2
    }else if(currPlayer.hand[i].value == 12){
        cout << "\t<=>" << endl; //if the card is a reverse
    }else if((currPlayer.hand[i].value == 13)){
        cout << "\t" <<(char)254u << (char)254u << (char)254u << endl; //if the card is a regular wild
    }else if((currPlayer.hand[i].value == 14)){ //...until here
        cout << "\t" << "+4" << (char)254u << endl; //if the card is a wild +4
    }
    cout << "\t\t" <<(char)254u << (char)254u << (char)254u << "\n\n"; //prints the bottom 3 squares of the card

}cout << i+1 << ". |\tDraw Card\n\n"; //includes drawing a card as an option for the player
}

void action(Player playerArray[],int& round,Card& center,int input,bool& direction){

if(playerArray[round].cards < input){ //checks if the player wanted to draw a card
    playerArray[round].drawCard(); //the player draws the card
    return; //there are no more actions to take so it returns
}

if(playerArray[round].hand[input-1].color == 4 ){ //checking if the player played a wild card
    int hold;
    if(!(playerArray[round].isComp)){ //checks if the player isn't a computer
        cout << "What color would you like to make it? 1. Red | 2. Blue | 3. Green | 4. Yellow" << endl;
        cin >> hold;
    }else{ //if the player is a computer, the color they pick is randomly generated
        hold = ((rand()%4) + 1);
    }
    center.color = hold-1; //sets the color of the center to the color the player chose
    center.value = playerArray[round].hand[input-1].value; //sets the value of the center to the value of the card played

    if(playerArray[round].hand[input-1].value == 14){ //checks if the wild card played was regular or +4
        if(direction){ //+4 when going in the positive direction
            playerArray[round+1].drawCard(); //makes the next player draw 4 cards
            playerArray[round+1].drawCard();
            playerArray[round+1].drawCard();
            playerArray[round+1].drawCard();

            playerArray[round].playCard(input); //the card is played
            roundUpDown(round,direction); //the round is incrimented since the next player is skipped
            return; //returns since there are no more actions to take
        }else{ //+4 when going in the negative direction
            playerArray[round-1].drawCard(); //makes the next player draw 4 cards
            playerArray[round-1].drawCard();
            playerArray[round-1].drawCard();
            playerArray[round-1].drawCard();

            playerArray[round].playCard(input); //the card is played
            roundUpDown(round,direction); //the round is incrimented since the next player is skipped
            return; //returns since there are no more acitons to take
        }
    }
    playerArray[round].playCard(input); //the normal wild card is played
    return; //returns since there are no more actions for a normal wild card to take
}

center.color = playerArray[round].hand[input-1].color; //sets the color of the center to the color of the card played
center.value = playerArray[round].hand[input-1].value; //sets the value of the center to the color of the card played

if(playerArray[round].hand[input-1].value == 10){ //when the card played is a skip
    playerArray[round].playCard(input); //plays the card
    roundUpDown(round,direction); //incriments to skip the next player
    return; //returns since there are no more actions to take
}else if(playerArray[round].hand[input-1].value == 11){ //when the card is a +2
    if(direction){ //+2 in the positive direction
        playerArray[round+1].drawCard(); //the next player draws two cards
        playerArray[round+1].drawCard();
        playerArray[round].playCard(input); //the card is played
        roundUpDown(round,direction); //incriments an extra time to skip the player that drew
        return; //returns since there are no more actions to take
    }else{ //+2 in the negative direction
        playerArray[round-1].drawCard(); //the next player draws two cards
        playerArray[round-1].drawCard();
        playerArray[round].playCard(input); //the card is played
        roundUpDown(round,direction); //incriments an extra time to skips the player that drew
        return; //returns since there are no more actions to take
    }
}else if(playerArray[round].hand[input-1].value == 12){ //when the card is a reverse
    if(direction){//if going positive...
        direction = false; //switches to negative
    }else{ //if going negative...
        direction = true; //switches to positive
    }
}
playerArray[round].playCard(input); //the card is played
}

void roundUpDown(int& round,bool direction){
if(direction){ //if the game is going in the positive direction
    if(round == 3){ //if its player 4's turn going up
        round = 0;
    }else{
        round++; //incriments up
    }
}else{ //if the game is going in the negative direction
    if(round == 0){ //if its player 1's turn going down
        round = 3;
    }else{
        round--; //incriments down
    }
}
}

void printCenter(Card center){
cout << "\t\t****Top of the Deck****" << endl; //the indication of which card is being printed
cout << "\t\t\t\t" <<(char)254u << (char)254u << (char)254u << endl; //prints the top 3 squares of the card
    cout << "\t\t\t";
    printColor(center); //prints the color of the card
    if((center.value >= 0) && (center.value <= 9)){ //all this prints the correct middle of the card...
        cout << "\t" << (char)254u << center.value << (char)254u << endl; //if the card is numeric 0-9
    }else if(center.value == 10){
        cout << "\t" << (char)254u << "X" << (char)254u << endl; //if the card is a skip
    }else if(center.value == 11){
        cout << "\t" << "+2" << (char)254u << endl; //if the card is a +2
    }else if(center.value == 12){
        cout << "\t<=>" << endl; //if the card is a reverse
    }else if((center.value == 13)){
        cout << "\t" <<(char)254u << (char)254u << (char)254u << endl; //if the card is a regular wild
    }else if((center.value == 14)){ //...until here
        cout << "\t" << "+4" << (char)254u << endl; //if the card is a wild +4
    }
    cout << "\t\t\t\t" <<(char)254u << (char)254u << (char)254u << endl; //prints the bottom of the card
cout << "\t\t****               ****" << "\n\n"; //bottom indication that the card is the center card
}

int compAction(Player compPlayer,Card center){
int i=0;
for(;i<compPlayer.cards;i++){ //checks each card in a players hand
    if((compPlayer.hand[i].color == center.color) || (compPlayer.hand[i].value == center.value) || (compPlayer.hand[i].color == 4)){ //checks the color and value of the card and compares it with the card in the center
        return i+1; //returns the card that can be played
    }
}
return i+1; //returns a draw card action since none of the cards can be played
}

int playerInput(Player& currPlayer,Card center){
int input; //holds what action the player wants to do
bool canPlay = false; //holds whether the action the player took can be done
string uno;
if(!(currPlayer.isComp)){ //if a player isn't a computer, it will ask them what they want to do
    if((currPlayer.cards !=2) || (compAction(currPlayer,center) > currPlayer.cards)){ //checks if they don't have 2 cards or if they have to draw a card
        while(!canPlay){ //continues to ask a player what to do until they input something that they can do
            cout << "What would you like to do? ";
            cin >> input;
            cout << "\n\n";
            canPlay = validPlay(currPlayer,center,input); //takes in whether the action taken can be done or not
        }
    }else{
        cout << "What would you like to do? ";
        cin >> uno;
        if((uno[0] == 85) || (uno[0] == 117)){ //checks if the player did say uno (if the first letter was a 'u')
            while(!canPlay){ //continues to ask a player what to do until they input something that they can do
                cout << endl << "What card would you like to play? ";
                cin >> input;
                cout << "\n\n";
                canPlay = validPlay(currPlayer,center,input); //takes in whether the action taken can be done or not
            }
        }else{ //the player did not type uno
            cout << endl << "You forgot to say uno! +2 cards!" << endl;
            currPlayer.drawCard(); //player draws 2 cards
            currPlayer.drawCard();
            printHand(currPlayer); //reprints the players hand so they can play the card they want
            while(!canPlay){ //continues to ask a player what to do until they input something that they can do
                cout << endl << "What card would you like to play? ";
                cin >> input;
                cout << "\n\n";
                canPlay = validPlay(currPlayer,center,input); //takes in whether the action taken can be done or not
            }
        }
    }
}else{ //otherwise the action the player takes is decided for them
    input = compAction(currPlayer,center); //gets the first playable card in a players hand
}
return input;
}
