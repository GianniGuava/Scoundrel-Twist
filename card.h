#ifndef CARD_H
#define CARD_H

#include "common.h"

class card{
    enum SUITS{
        /*---DEFAULT SUITS---*/
        EMPTY,
        HEARTS,
        DIAMONDS,
        SPADES,
        CLUBS

        /*---ADDED SUITS---*/

    };

    enum RANKS{
        /*---DEFAULT RANKS---*/
        ZERO,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        JACK,
        QUEEN,
        KING,
        ACE
        /*---ADDED RANKS---*/

    };

    enum TYPE{
        /*---DEFAULT TYPES---*/
        ERROR,
        HEALTH,
        PETS,
        MONSTER
    
        /*---ADDED TYPES---*/

    };
    
    //Class Members
    int rank;
    int suit; 

    /*
    ################################
    --------PUBLIC - METHODS--------      
    ################################
    */
    public:

    /*---Constructors---*/
    
    /*
    *   Empty Constructor
    */
    card();

    /*
    *   Constructor for deck building
    */
    card(int r, int s);


    /*---Class Functions---*/

    /*
    *   Returns rank as a string
    *   Must be kept updated with tables
    */
    std::string rankToString();

    /*
    *   Returns suit as a string
    *   Must be kept updated with tables
    */
    std::string suitToString();
    
    /*
    *   Getter for rank 
    */
    int get_rank();

    /*
    *   Getter for suit 
    */
    int get_suit();

    /*
    *   Returns "type" converted from rank
    */
    int get_type();

    /*
    *   Resets card to empty card: [0|null]
    */
    void reset_card();
};

#endif