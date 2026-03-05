#include "deck.h"
std::vector<card> unshuffled_deck; 
std::deque<card> shuffled_deck;

void create_unshuffled_deck(){
    if(!unshuffled_deck.empty()){
        std::cout << "Unshuffled Deck already made!" << std::endl;
        return;
    }
    for(int suit : card::SUITS){
        for(int rank : ranks){
            card temp(rank, suit);
            unshuffled_deck.push_back(temp);
        }
    }
}

/*---PUBLIC METHODS---*/

void become_draw_deck(std::vector<card> exclude_cards){
    create_unshuffled_deck();

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    //Debug a seed
    //unsigned seed = 526130411;
    std::cout << "seed for debug purposes: " << seed << std::endl;
    auto rng = std::default_random_engine(seed);
    //std::cout << rng() % 10 + 1 << std::endl;
    std::shuffle(std::begin(unshuffled_deck), std::end(unshuffled_deck), rng);

    while(!unshuffled_deck.empty()){
        bool match = false; //flag for a card matching something in the exclusion deck
        card temp = unshuffled_deck.back();
        unshuffled_deck.pop_back();

        for(card playing_card : exclude_cards){
            //If the card that has been popped does not equal ANY of the exclusion cards:
            if((temp.get_rank() == playing_card.get_rank()) && (temp.get_suit() == playing_card.get_suit())){ 
                match = true;
                break; 
            }else{ match = false; }
        }

        if(!match){ 
            shuffled_deck.push_front(temp);
            //std::cout << "[" << temp.get_rank() << '|' << temp.get_suit() << "] ";
        }
    }
}

card front(){ return shuffled_deck.front(); }

bool empty(){ return shuffled_deck.empty(); }

int size(){ return shuffled_deck.size(); }

void push_front(card temp){ shuffled_deck.push_front(temp); }

void push_back(card temp){ shuffled_deck.push_back(temp); }

void pop_front(){ shuffled_deck.pop_front(); }

//void pop_back(){ shuffled_deck.pop_back(); }
