#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <deque>

class card{
    int rank;
    std::string suit; 
    //Clubs & Spades (C & S) = Monsters
    //Diamonds (D) = Weapon
    //Hearts (H) = Health

    public:
    card(){
        rank = 0;
        suit = "null";
    }

    card(int r, std::string s){
        rank = r;
        suit = s;
    }

    std::string display_info(){
        std::string info = "[" + rank + '|' + suit + "]";
    }

    int get_rank(){ return rank; }

    std::string get_suit(){ return suit; }

    //Monster = 1, Weapon = 2, Health = 3
    int get_type(){
        if(suit == "S" || suit == "C"){ return 1; }
        else if(suit == "D"){ return 2; }
        else if(suit == "H"){ return 3; }
        else return 0; //Error
    }
};

class deck{
    std::vector<card> unshuffled_deck; 
    std::deque<card> shuffled_deck;

    std::string suits[4] = {"S", "C", "H", "D"};  
    int ranks[13] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    
    void create_unshuffled_deck(){
        if(!unshuffled_deck.empty()){
            std::cout << "Unshuffled Deck already made!" << std::endl;
            return;
        }
        for(std::string suit : suits){
            for(int rank : ranks){
                card temp(rank, suit);
                unshuffled_deck.push_back(temp);
            }
        }
    }

    public:
    void become_draw_deck(std::vector<card> exclude_cards){
        create_unshuffled_deck();

        auto rng = std::default_random_engine{};
        std::shuffle(std::begin(unshuffled_deck), std::end(unshuffled_deck), rng);

        while(!unshuffled_deck.empty()){
            card temp = unshuffled_deck.back();
            unshuffled_deck.pop_back();

            for(card playing_card : exclude_cards){
                //If the card that has been popped does not equal ANY of the exclusion cards:
                if(!((temp.get_rank() == playing_card.get_rank()) && 
                      temp.get_suit() == playing_card.get_suit())){
                    shuffled_deck.push_front(temp);
                }
            }
        }
    }

    card front(){ return shuffled_deck.front(); }

    void push_front(card temp){ shuffled_deck.push_front(temp); }

    void push_back(card temp){ shuffled_deck.push_back(temp); }

    void pop_front(){ shuffled_deck.pop_front(); }

    //void pop_back(){ shuffled_deck.pop_back(); }
};

class player{
    int health = 20;
    int weapon = 0;

    // Metrics for later
    // int kills = 0;
    // int times_ran_away = 0;
    // int times_hit = 0;

    public:

    void attack_bare_handed(int damage){
        health -= damage;
    }

    void attack_weapon(int damage, int weapon){
        damage -= weapon;
        if(damage < 0){ damage = 0; }
        health -= damage;
    }
};

int main(){
    std::cout << "Loading..." << std::endl;
    //Default generated set. Can use user input in the future or in settings
    std::vector<std::string> default_exclude_suits = {"D", "H"};
    std::vector<int> default_exclude_ranks = {11, 12, 13, 14};
    std::vector<card> default_exclude_cards;

    for(std::string suit : default_exclude_suits){
        for(int rank : default_exclude_ranks){
            card temp(rank, suit);
            default_exclude_cards.push_back(temp);
        }
    }

    bool play_again = true;
    while(play_again){
        //Start menu
        std::string response;
        std::cout << "Would you like to play? (y/n): ";
        std::cin >> response;

        if(response != "y"){ break; }

        //Initialize game environment
        //The Draw Deck
        deck draw_deck;
        draw_deck.become_draw_deck(default_exclude_cards);

        //The Hand Deck
        card hand[4];

        //The Weapon Slot Deck;
        deck weapon_slot_deck;

        //The Discard Deck
        deck discard_deck;

        bool alive = true;
        while(alive){
            //display hands
            std::cout << "Printing current hand..." << std::endl;

            for(int i = 0; i < 4; i++){
                card temp = draw_deck.front();
                draw_deck.pop_front();
                hand[i] = temp;
            }

            std::cout << hand[0].display_info() << " "
            << hand[1].display_info() << " "
            << hand[2].display_info() << " "
            << hand[3].display_info() << std::endl;

            int choice;
            while(true){
                std::cout << "Play a card (1, 2, 3, 4) or run (5): ";
                std::cin >> choice;

                if(choice < 1 || choice > 5){ break; }
                else{ std::cout << "Type your answer again." << std::endl; }
            }
                
            switch(choice){
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
            }
        }
        
        play_again = false;
    }

    return 0;
};