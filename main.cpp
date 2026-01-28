#include <iostream>
#include <string>
#include <stack>

class card{
    int rank;
    std::string suit; 
    //Clubs & Spades = Monsters
    //Diamons = Weapon
    //Hearts = Health

    card(int r, std::string s){
        rank = r;
        suit = s;
    }
};

class deck{
    std::stack<card> card_deck;
};

class player{

};

int main(){
    return 0;
};