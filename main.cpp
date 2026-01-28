#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <stack>

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
    std::stack<card> shuffled_deck;

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
    void create_draw_deck(std::vector<std::string> exclude_suits, std::vector<int> exclude_ranks){
        create_unshuffled_deck();

        auto rng = std::default_random_engine{};
        std::shuffle(std::begin(unshuffled_deck), std::end(unshuffled_deck), rng);

        while(!unshuffled_deck.empty()){
            card temp = unshuffled_deck.back();
            unshuffled_deck.pop_back();

            if(std::count(exclude_ranks.begin()))
        }
    }

    deck(std::stack<card> sd){
        shuffled_deck = sd;
    }
};

class player{

};

int main(){
    return 0;
};