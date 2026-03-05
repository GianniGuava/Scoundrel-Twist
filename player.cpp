class player{
    int health;
    int weapon;

    // Metrics for later
    // int kills = 0;
    // int times_ran_away = 0;
    // int times_hit = 0;

    public:

    player(){
        //God mode for devs
        //health = 10000;
        health = 20;
        weapon = 0;
    }

    void reset_player(){
        //God mode for devs
        //health = 10000;
        health = 20;
        weapon = 0;
    }

    int get_weapon(){ return weapon; }

    int get_health(){ return health; }

    void equip_weapon(int damage){ weapon = damage; }

    void heal(int amount){ 
        health += amount;
        //comment out below for god mode
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