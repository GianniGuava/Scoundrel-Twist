#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <deque>

class card{
    int rank;
    std::string suit; 
    //Clubs & Spades = Monsters
    //Diamonds = Weapon
    //Hearts = Health

    public:
    card(int r, std::string s){
        rank = r;
        suit = s;
    }

    int get_rank(){ return rank; }

    std::string get_suit(){ return suit; }
};

class deck{
    std::vector<card> unshuffled_deck; 
    std::deque<card> shuffled_deck;

    std::string suits[4] = {"Spades", "Clubs", "Hearts", "Diamonds"};  
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
    //Default generated set. Can use user input in the future or in settings
    std::vector<std::string> default_exclude_suits = {"Diamonds", "Hearts"};
    std::vector<int> default_exclude_ranks = {11, 12, 13, 14};
    std::vector<card> default_exclude_cards;

    for(std::string suit : default_exclude_suits){
        for(int rank : default_exclude_ranks){
            card temp(rank, suit);
            default_exclude_cards.push_back(temp);
        }
    }

    //The Draw Deck
    deck draw_deck;
    draw_deck.become_draw_deck(default_exclude_cards);

    //The Hand Deck
    deck hand_deck;

    //The Discard Deck
    deck discard_deck;

    return 0;
};