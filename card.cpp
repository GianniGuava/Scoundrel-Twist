#include "card.h"

/*---PUBLIC METHODS---*/
card::card(){
    rank = ranks::ZERO;
    suit = suits::EMPTY;
}

card::card(int r, std::string s){
    rank = r;
    suit = s;
}

int card::get_rank(){ 
    switch(rank){
    case ranks::ZERO:
        return 0
        break;
    
    default:
        break;
    }
}

std::string card::get_suit(){ return suit; }


int card::get_type(){
    if(suit == "H"){ return 1; }
    else if(suit == "D"){ return 2; }
    else if(suit == "S" || suit == "C"){ return 3; }
    else return 0; //Error
}

void card::reset_card(){
    rank = 0;
    suit = "null";
}
