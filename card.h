#ifndef CARD_H
#define CARD_H

#include "common.h"

class card{
    std::unordered_set<std::string> suits{
        /*---DEFAULT SUITS---*/
        "Empty",
        "Hearts",
        "Diamonds",
        "Spades",
        "Clubs"

        /*---ADDED SUITS---*/
    };

    std::unordered_map<std::string, int> ranks = {
        /*---DEFAULT RANKS---*/
        {"0", 0},   //Empty
        {"2", 2},
        {"3", 3},
        {"4", 4},
        {"5", 5},
        {"6", 6},
        {"7", 7},
        {"8", 8},
        {"9", 9},
        {"10", 10},
        {"Jack", 11},
        {"Queen", 12},
        {"King", 13},
        {"Ace", 14}

        /*---ADDED RANKS---*/
    };



    enum class type{
        /*---DEFAULT TYPES---*/
        HEALTH,
        PETS,
        MONSTER
    
        /*---ADDED TYPES---*/

    };
    
    //Class Members
    int rank;
    std::string suit; 

    /*
    ################################
    --------PRIVATE  METHODS--------      
    ################################
    */

    void setSuit(std::string s);

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
    card(std::string r, std::string s);


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