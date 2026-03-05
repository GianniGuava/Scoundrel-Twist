#ifndef CARD_H
#define CARD_H

#include "common.h"

class card{
    enum class suits{
        /*---DEFAULT SUITS---*/
        HEARTS,
        DIAMONDS,
        SPADES,
        CLUBS,
        EMPTY

        /*---ADDED SUITS---*/
    };

    enum class ranks{
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

        /*---DEFAULT ADDED---*/
    };

    enum class type{
        /*---DEFAULT TYPES---*/
        HEALTH,
        PETS,
        MONSTER
    
        /*---ADDED TYPES---*/

    };
    
    //Class Members
    enum ranks rank;
    enum suits suit; 

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
    card(int r, std::string s);


    /*---Class Functions---*/
    
    /*
    *   Getter for rank 
    */
    int get_rank();

    /*
    *   Getter for suit 
    */
    std::string get_suit();

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