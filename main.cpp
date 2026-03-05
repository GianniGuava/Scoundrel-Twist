#include <card.cpp>



//Initialize Player as global
player person;

int play_card(card (&draw)[4], int index, bool healed, card weapon){
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

    switch(type){
        case 1:
            if(!healed){ 
                person.heal(rank); 
                std::cout << "You have healed " << rank << " points of health and are now at " 
                << person.get_health() << " points of health." << std::endl;
            }else{ std::cout << "You have already healed in this room, so this potion will go to waste." << std::endl; }
            return_code = 1;
            break;
        case 2:
            person.equip_weapon(rank);
            std::cout << "Your new weapon deals " << person.get_weapon() << " damage." << std::endl; 
            return_code = 2;
            break;
        case 3:
            if(person.get_weapon() == 0){
                std::cout << "You will fight this monster bare handed." << std::endl;
                person.attack_bare_handed(rank);
                return_code = 3;

                if(person.get_health() > 0){ std::cout<< "Your current health is: " << person.get_health() << std::endl; }
                else{ return_code = 5;}
                break;
            }else{
                if(weapon.get_type() == 3 && //Perhaps doesn't check properly because I got weapon degraded message on a new sword.
                   weapon.get_rank() <= draw[index].get_rank()){
                    std::cout << "Your weapon is too degraded, you will be forced to fight barehanded" << std::endl;
                    person.attack_bare_handed(rank);
                    return_code = 3;
                }else{
                    std::string fighting_style = "x";
                    while(!(fighting_style == "B" || fighting_style == "W")){
                        std::cout << "Would you like to fight this monster bare handed(B) or with your weapon(W)?: ";
                        std::cin >> fighting_style; 
                    }
                    if(fighting_style == "B"){ 
                        person.attack_bare_handed(rank); 
                        return_code = 3;
                    }
                    else if(fighting_style == "W"){ 
                        person.attack_weapon(rank); 
                        return_code = 4;
                    }
                }
                
                std::cout << "Monster slain." << std::endl;
                if(person.get_health() > 0){ std::cout<< "Your current health is: " << person.get_health() << std::endl; }
                else{ return_code = 5;}
                break;
            }

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
                if(hand[i].get_type() == 0){
                    hand[i] = draw_deck.front();
                    draw_deck.pop_front();
                }
                std::cout << "[" << hand[i].get_rank() << '|' << hand[i].get_suit() << "] ";
            }
            std::cout << std::endl;

            int choice;
            while(true){
                std::cout << "Play a card (0, 1, 2, 3) or run (4): ";
                std::cin >> choice;

                if((choice > 0 || choice < 5)){ 
                    if(choice == 4 && has_run){ std::cout << "You cannot run from this room." << std::endl; }
                    else{ break; }
                }
                std::cout << "Type your answer again." << std::endl;
            }
                
            if(choice == 4){ //Run
                has_run = true;
                for(int i = 0; i < 4; i++){
                    draw_deck.push_back(hand[i]);
                    hand[i].reset_card();
                }
            }else{ //Picked a card
                has_run = false;
                
                int choice1 = choice;
                int choice2 = choice;
                int choice3 = choice;
                for(int i = 0; i < 3; i++){
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
                            << "and " <<
                            "[" << hand[choice2].get_rank() << '|' << hand[choice2].get_suit() << "] " 
                            << "(0, 1, 2, 3)" << std::endl;
                            std::cin >> choice3;
                            if((choice3 != choice1) && (choice3 != choice2) && (choice3 >= 0) && (choice3 <= 3)){
                                choice = choice3;
                                break;
                            }else{ std::cout << "Type your answer again." << std::endl; }
                        }
                    }

                    int action = play_card(hand, choice, has_healed, weapon_slot_deck.front()); 
    
                    switch(action){
                        case 1: //1 = Used health potion
                            //Add more later here for health potion stats handling
                            has_healed = true;
                            continue;
                        case 2: //2 = Equipped a new weapon
                            has_healed = false;
                            if(weapon_slot_deck.empty()){ weapon_slot_deck.push_front(hand[choice]); }
                            else{ 
                                for(int i = 0; i < weapon_slot_deck.size(); i++){
                                    discard_deck.push_front(weapon_slot_deck.front());
                                    weapon_slot_deck.pop_front();
                                }
                            }
                            continue;
                        case 3: //3 = Fought bare handed
                            has_healed = false;
                            discard_deck.push_front(hand[choice]);
                            continue;
                        case 4: //4 = Fought with weapon
                            has_healed = false;
                            weapon_slot_deck.push_front(hand[choice]);
                            continue;
                        case 5: //5 = Died
                            has_healed = false;
                            alive = false;
                            break;
                    }
                    if(!alive){ break; }
                }
                hand[choice1].reset_card();
                hand[choice2].reset_card();
                hand[choice3].reset_card();
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

        person.reset_player();
    }

    return 0;
};