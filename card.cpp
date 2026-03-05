#include "card.h"

/*---PRIVATE METHODS---*/
void card::setSuit(std::string s){
    auto it = card::suits.find(s); 
    if(it != card::suits.end()){ card::suit = s; }
    else{ card::suit = "Empty"; }
}

/*---PUBLIC METHODS---*/
card::card(){
    rank = ranks["0"];
    suit = "Empty";
}

card::card(std::string r, std::string s){
    rank = ranks[r];
    setSuit(s);
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
