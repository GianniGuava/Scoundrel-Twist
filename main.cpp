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

    int get_rank(){ return rank; }

    std::string get_suit(){ return suit; }

    //Health = 1, Weapon = 2, Monster = 3
    int get_type(){
        if(suit == "H"){ return 1; }
        else if(suit == "D"){ return 2; }
        else if(suit == "S" || suit == "C"){ return 3; }
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
            bool match = false; //flag for a card matching something in the exclusion deck
            card temp = unshuffled_deck.back();
            unshuffled_deck.pop_back();
            std::cout << "[" << temp.get_rank() << '|' << temp.get_suit() << "] ";

            for(card playing_card : exclude_cards){
                //If the card that has been popped does not equal ANY of the exclusion cards:
                if((temp.get_rank() == playing_card.get_rank()) && (temp.get_suit() == playing_card.get_suit())){ 
                    match = true;
                    break; 
                }else{ match = false; }
            }

            if(!match){ shuffled_deck.push_front(temp); }
        }
    }

    card front(){ return shuffled_deck.front(); }

    bool empty(){ return shuffled_deck.empty(); }

    int size(){ return shuffled_deck.size(); }

    void push_front(card temp){ shuffled_deck.push_front(temp); }

    void push_back(card temp){ shuffled_deck.push_back(temp); }

    void pop_front(){ shuffled_deck.pop_front(); }

    //void pop_back(){ shuffled_deck.pop_back(); }
};

class player{
    int health;
    int weapon;

    // Metrics for later
    // int kills = 0;
    // int times_ran_away = 0;
    // int times_hit = 0;

    public:

    player(){
        health = 20;
        weapon = 0;
    }

    void reset_player(){
        health = 20;
        weapon = 0;
    }

    int get_weapon(){ return weapon; }

    int get_health(){ return health; }

    void equip_weapon(int damage){ weapon = damage; }

    void heal(int amount){ 
        health += amount;
        if(health > 20){ health = 20; }
    }

    void attack_bare_handed(int damage){
        health -= damage;
    }

    void attack_weapon(int damage){
        damage -= weapon;
        if(damage < 0){ damage = 0; }
        health -= damage;
    }
};

//Initialize Player as global
player person;

int play_card(card (&draw)[4], int index, bool healed){
    //Only accepts 0-3 by this point
    int type = draw[index].get_type();
    int rank = draw[index].get_rank();

    /*
    return codes:
    1 = Used health potion
    2 = Equipped a new weapon
    3 = Fought bare handed
    4 = Fought with weapon
    5 = Died
    */

    int return_code;

    if(type == 1){ 
        if(!healed){ 
            person.heal(rank); 
            std::cout << "You have healed " << rank << " points of health and are now at " << person.get_health() << " points of health." << std::endl;
        }else{ std::cout << "You have already healed in this room, so this potion will go to waste." << std::endl; }
        return_code = 1;
    }else if(type == 2){ 
        person.equip_weapon(rank);
        std::cout << "Your new weapon deals " << person.get_weapon() << " damage." << std::endl; 
        return_code = 2;
    }else{ //Has to be type monster (3)
        if(person.get_weapon() == 0){
            std::cout << "You will fight this monster bare handed." << std::endl;
            person.attack_bare_handed(rank);
            return_code = 3;
        }else{
            std::string fighting_style = "x";
            while(fighting_style != "B" || fighting_style != "W"){
                std::cout << "Would you like to fight this monster bare handed(B) or with your weapon(W)?: ";
                std::cin >> fighting_style; 
            }
            if(fighting_style == "B"){ person.attack_bare_handed(rank); }
            else if(fighting_style == "W"){ person.attack_weapon(rank); }
            return_code = 4;
        }
        std::cout << "Monster slain." << std::endl;
        if(person.get_health() > 0){ std::cout<< "Your current health is: " << person.get_health(); }
        else{ return_code = 5;}
    }

    return return_code;
}

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
        //Rule tracking variables
        bool has_healed = false;
        bool has_run = false;

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

        //Play loop
        bool alive = true;
        while(alive){
            //Check if draw deck has enough cards
            if(draw_deck.size() < 4){
                std::cout << "You win!" << std::endl;
                break;
            }

            //display hands
            std::cout << "Printing current hand..." << std::endl;

            for(int i = 0; i < 4; i++){
                hand[i] = draw_deck.front();
                draw_deck.pop_front();
            }

            for(int i = 0; i < 4; i++){
                std::cout << "[" << hand[i].get_rank() << '|' << hand[i].get_suit() << "] ";
            }
            std::cout << std::endl;

            int choice;
            while(true){
                std::cout << "Play a card (0, 1, 2, 3) or run (4): ";
                std::cin >> choice;

                if(choice > 0 || choice < 5){ break; }
                else{ std::cout << "Type your answer again." << std::endl; }
            }
                
            if(choice == 5){ //Run
                has_run = true;
                for(int i = 0; i < 4; i++){
                    draw_deck.push_back(hand[i]);
                    hand[i] = card();
                }
            }
            else{ //Picked a card
                has_run = false;
                
                int choice1 = choice;
                int choice2 = choice;
                int choice3 = choice;
                for(int i = 0; i < 3; i++){

std::cout << "[" << hand[i].get_rank() << '|' << hand[i].get_suit() << "] ";

                    if(i == 1){
                        while(true){
                            std::cout << "Pick another card other than " << 
                            "[" << hand[choice1].get_rank() << '|' << hand[choice1].get_suit() << "] " 
                            << "(0, 1, 2, 3)" << std::endl;
                            std::cin >> choice2;
                            if((choice2 != choice1) && (choice2 >= 0) && (choice2 <= 3)){
                                choice = choice2;
                                break;
                            }else{ std::cout << "Type your answer again." << std::endl; }
                        }
                    }else if(i == 2){
                        while(true){
                            std::cout << "Pick another card other than " <<
                            "[" << hand[choice1].get_rank() << '|' << hand[choice1].get_suit() << "] "
                            << "and" <<
                            "[" << hand[choice1].get_rank() << '|' << hand[choice1].get_suit() << "] " 
                            << "(0, 1, 2, 3)" << std::endl;
                            std::cin >> choice3;
                            if((choice3 != choice1) && (choice3 != choice2) && (choice3 >= 0) && (choice3 <= 3)){
                                choice = choice3;
                                break;
                            }else{ std::cout << "Type your answer again." << std::endl; }
                        }
                    }

                    int action = play_card(hand, choice, has_healed); 
    
                    switch(action){
                        case 1: //1 = Used health potion
                            //Add more later here for health potion stats handling
                            continue;
                        case 2: //2 = Equipped a new weapon
                            if(weapon_slot_deck.empty()){ weapon_slot_deck.push_front(hand[choice]); }
                            else{ 
                                for(int i = 0; i < weapon_slot_deck.size(); i++){
                                    discard_deck.push_front(weapon_slot_deck.front());
                                    weapon_slot_deck.pop_front();
                                }
                            }
                        case 3: //3 = Fought bare handed
                            discard_deck.push_front(hand[choice]);
                            hand[choice] = card();
                        case 4: //4 = Fought with weapon
                            weapon_slot_deck.push_front(hand[choice]);
                            hand[choice] = card();
                        case 5: //5 = Died
                            alive = false;
                            break;
                    }
                }
            }
        }

        if(alive){
            int score = person.get_health();
            int potion = 0;
            for(card check : hand){
                if((check.get_suit() == "H") && (check.get_rank() > potion)){ 
                    potion = check.get_rank(); 
                }
            }
            score += potion;

            std::cout << "Your score: " << score << std::endl;
        }else{
            std::cout << "You died." << std::endl;
        }

        std::string playing_again;
        std::cout << "Would you like to play again? (y/n): ";
        std::cin >> playing_again;

        if(playing_again == "y"){ play_again = true; }
        else{ play_again = false;}

        person.reset_player();
    }

    return 0;
};