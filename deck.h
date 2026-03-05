#ifndef DECK_H
#define DECK_H

#include "card.h"

class deck{
    //Class Members
    std::vector<card> unshuffled_deck; 
    std::deque<card> shuffled_deck;

    /*
    *   Creates a full deck unfiltered
    */
    void create_unshuffled_deck();

    /*
    ################################
    --------PUBLIC - METHODS--------      
    ################################
    */
    public:

    /*
    *   Readies this deck object for being draw_deck 
    *   with filtering for excluded cards
    */
    void become_draw_deck(std::vector<card> exclude_cards);

    /*
    *   Returns card at the top of deck
    */
    card front();

    /*
    *   Returns true if empty, false if not
    */
    bool empty();

    /*
    *   Returns size of deck 
    */
    int size();

    /*
    *   Pushes card onto top of deck
    */
    void push_front();

    /*
    *   Pushes card onto back of deck
    */
    void push_back();

    /*
    *   Pops card off top of deck
    */
    void pop_front();

    /*
    *    Pops card from back of deck
    */
    //void pop_back();
};

#endif 