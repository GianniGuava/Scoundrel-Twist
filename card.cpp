#include "card.h"

/*---PUBLIC METHODS---*/
card::card(){
    rank = RANKS::ZERO;
    suit = SUITS::EMPTY;
}

card::card(int r, int s){
    rank = r;
    suit = s;
}

std::string card::rankToString(){
    switch(rank){
        case RANKS::ZERO:
            return "0";
        case RANKS::TWO:
            return "2";
        case RANKS::THREE:
            return "3";
        case RANKS::FOUR:
            return "4";
        case RANKS::FIVE:
            return "5";
        case RANKS::SIX:
            return "6";
        case RANKS::SEVEN:  
            return "7";
        case RANKS::EIGHT:
            return "8";
        case RANKS::NINE:
            return "9";
        case RANKS::TEN:
            return "10";
        case RANKS::JACK:
            return "Jack";
        case RANKS::QUEEN:
            return "Queen";
        case RANKS::KING:
            return "King";
        case RANKS::ACE:
            return "Ace";
    }
}

std::string card::suitToString(){
    switch(suit){
        case SUITS::EMPTY:
            return "Empty";
        case SUITS::HEARTS:
            return "Hearts";
        case SUITS::DIAMONDS:
            return "Diamonds";
        case SUITS::SPADES:
            return "Spades";
        case SUITS::CLUBS:
            return "Clubs";
    }
}

int card::get_rank(){ return rank; }

int card::get_suit(){ return suit; }

int card::get_type(){
    if(suit == SUITS::HEARTS){ return TYPE::HEALTH; }
    else if(suit == SUITS::DIAMONDS){ return TYPE::PETS; }
    else if(suit == SUITS::SPADES || suit == SUITS::CLUBS){ return TYPE::MONSTER; }
    else return TYPE::ERROR;
}

void card::reset_card(){
    rank = RANKS::ZERO;
    suit = SUITS::EMPTY;
}
