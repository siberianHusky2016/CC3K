#include "Floor.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <iomanip> 
#include "InputException.h"
#include "NoPotionsToUse.h"
#include "Surroundings.h"
#include "Shade.h"
#include "Drow.h"
#include "Vampire.h"
#include "Troll.h"
#include "Goblin.h"
#include "Chamber.h"
#include "RaceDNE.h"
#include "InputException.h"
#include "Surroundings.h"
#include "BoostAtk.h"
#include "BoostDef.h"
#include "PoisonHealth.h"
#include "RestoreHealth.h"
#include "WoundAtk.h"
#include "WoundDef.h"
#include "Human.h"
#include "Dwarf.h"
#include "Elf.h"
#include "Orc.h"
#include "Dragon.h"
#include "Merchant.h"
#include "Halfling.h"
#include "Treasures.h"
#include "DirectionNotAllowed.h"
#include "NoEnemiesToAtk.h"

// Constructor
Floor::Floor(){
    for(int i = 0; i < 25; i++){
        std::vector<Cell> temp;
        for(int j = 0; j < 79; j++){
            Cell cell{i, j}; 
            temp.emplace_back(cell);
        }
        floor.emplace_back(temp);
    }
    createChamber();
}

// Set Floor with default floor plan
void Floor::set_Floor(std::string character, int i){
    level = i; 
    std::ifstream infile{"default_floor.txt"};
    std::string floor = "";
    for (int j = 0; j < 25; j++){
        std::string line; 
        std::getline(infile, line); 
        floor += line; 
        floor += "\n";
    }
    set_Floor(character,floor,i);
    generatePlayerandStairway(character);
    generateItems();
    generateEnemies();
}

// Set Floor with custome floor plan when the plan file name is in command line argument
void Floor::set_Floor(std::string character, std::string file, int i){
    std::string s;
    level = i; 
    std::istringstream ss1{file};
    int counter_r = 0;
    int counter_c = 0;
    std::string one_floor = "";
    // std::vector<Cell> temp;
    std::shared_ptr<DisplayableObjects> object;
    while(std::getline(ss1,s)){
        counter_c = 0;
        for(char const &c : s){ 
            if (counter_c == 79) {
                break; 
            }           
            /////////////////////////////
            if((c == '|') || (c == '-')){
                floor[counter_r][counter_c].setDefault(std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<Surroundings>(Surroundings("wall", c))));
            } else if(c == '.') {
                floor[counter_r][counter_c].setDefault(std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<Surroundings>(Surroundings("floor", c))));
            /////////////////////////////
            } else if (c == '+'){
                    floor[counter_r][counter_c].setDefault(std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<Surroundings>("Door",'+'))); // door
            } else if (c == '#'){
                    floor[counter_r][counter_c].setDefault(std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<Surroundings>("Passage",'#'))); // passage
            } else if (c == ' '){
                    floor[counter_r][counter_c].setDefault(std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<Surroundings>("Nothing", ' '))); //  nothing 
            } else if (c == '\\'){
                    floor[counter_r][counter_c].setDefault(std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<Surroundings>("Stairway", '\\'))); //  nothing 
                    StairwayPos.emplace_back(counter_r); 
                    StairwayPos.emplace_back(counter_c); 
            }else {
                floor[counter_r][counter_c].setDefault(std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<Surroundings>(Surroundings("floor", '.'))));
                if(c== '@'){
                    std::shared_ptr<DisplayableObjects> tempPlayer;
                    if(character == "s") {
                        tempPlayer = std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<Shade>());
                    } else if(character == "d") {
                        tempPlayer = std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<Drow>()); 
                    } else if(character == "v") {
                        tempPlayer = std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<Vampire>()); 
                    } else if(character == "t") {
                        tempPlayer = std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<Troll>()); 
                    } else if(character == "g") {
                        tempPlayer = std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<Goblin>()); 
                    } else {
                        throw RaceDNE(); 
                    }
                    floor[counter_r][counter_c].setObject(tempPlayer);
                    PlayerPos.emplace_back(counter_r); 
                    PlayerPos.emplace_back(counter_c); 
                }else if (c == '0'){
                    floor[counter_r][counter_c].setObject(std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<RestoreHealth>())); // RH
                }else if (c == '1'){
                    floor[counter_r][counter_c].setObject(std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<BoostAtk>())); // BA
                }else if (c == '2'){
                    floor[counter_r][counter_c].setObject(std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<BoostDef>())); // BD
                }else if (c == '3'){
                    floor[counter_r][counter_c].setObject(std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<PoisonHealth>())); // PH
                }else if (c == '4'){
                    floor[counter_r][counter_c].setObject(std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<WoundAtk>())); // WA
                }else if (c == '5'){
                    floor[counter_r][counter_c].setObject(std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<WoundDef>())); // WD
                }else if (c == '6'){
                    floor[counter_r][counter_c].setObject(std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<Treasures>("Normal"))); // normal
                }else if (c == '7'){
                    floor[counter_r][counter_c].setObject(std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<Treasures>("Small"))); // small
                }else if (c == '8'){
                    floor[counter_r][counter_c].setObject(std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<Treasures>("MerchantH"))); // merchant
                }else if (c == '9'){
                    floor[counter_r][counter_c].setObject(std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<Treasures>("DragonH"))); // dragon hord
                }else if (c == 'M'){
                    floor[counter_r][counter_c].setObject(std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<Merchant>())); // Merchant
                }else if (c == 'E'){
                    floor[counter_r][counter_c].setObject(std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<Elf>())); // elses
                }else if (c == 'D'){
                    floor[counter_r][counter_c].setObject(std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<Dragon>())); // dragon 
                }else if (c == 'H'){
                    floor[counter_r][counter_c].setObject(std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<Human>())); // Human 
                }else if (c == 'W'){
                    floor[counter_r][counter_c].setObject(std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<Dwarf>())); // Dwarf     
                }else if (c == 'L'){
                    floor[counter_r][counter_c].setObject(std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<Halfling>())); // Halfing     
                }else if (c == 'O'){
                    floor[counter_r][counter_c].setObject(std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<Orc>())); // Orc     
                }
            }
            counter_c++;
        }
        counter_r++;
        if (counter_r == 25) {
            break; 
        } 
        
    }
    createChamber(); 
}

// Set the chambers by adding references of Cells to each Chamber in Chambers. 
void Floor::createChamber(){
    Chamber chamber_1;
    Chamber chamber_2;
    Chamber chamber_3;
    Chamber chamber_4;
    Chamber chamber_5;
    for( int r = 0; r < 25; r++){
        for(int c = 0; c< 79;c++){
            if((r == 3)||(r == 4)){
                if((c >= 3) && (c <= 28)){
                    chamber_1.addCell(floor[r][c]);
                }
                if((c >= 39) && (c <= 61)){
                    chamber_2.addCell(floor[r][c]);
                }
            }
            if((r ==5)){
                if((c >= 3) && (c <= 28)){
                    chamber_1.addCell(floor[r][c]);
                }
                if((c >= 39) && (c <= 69)){
                    chamber_2.addCell(floor[r][c]);
                }
            }if(r == 6){
                 if((c >= 3) && (c <= 28)){
                    chamber_1.addCell(floor[r][c]);
                }
                if((c >=39) && (c <= 72)){
                    chamber_2.addCell(floor[r][c]);
                }
            }if((r >= 8)&&(r<= 12)){
                if((c >= 61) && (c <= 75)){
                    chamber_2.addCell(floor[r][c]);
                }
            }if((r>= 10) && (r<=12)){
                if((c>= 38) && (c <= 49)){
                    chamber_3.addCell(floor[r][c]);
                }
            }if((r >= 15) && (r <= 21)){
                if ((c>= 4 ) && (c<= 24)){
                    chamber_4.addCell(floor[r][c]);
                }
            }if((r >= 16) && (r <= 18)){
                if ((c>= 65 ) && (c<= 75)){
                    chamber_5.addCell(floor[r][c]);
                }
            }
            if((r >= 19) && (r <= 21)){
                if ((c>= 37 ) && (c<= 75)){
                    chamber_5.addCell(floor[r][c]);
                }
        }
       
    }
    }
    Chambers.emplace_back(chamber_5);
    Chambers.emplace_back(chamber_4);
    Chambers.emplace_back(chamber_3);
    Chambers.emplace_back(chamber_2);
    Chambers.emplace_back(chamber_1);
}

// Return a randomly chosen index for Chambers
int Floor::chooseChamber(){
    return rand() % 5;
} 
    
// Get a Chamber from Chambers by index
Chamber Floor::getChamber(int index){
    return Chambers[index];
}

// Generate Players and Stairway
void Floor::generatePlayerandStairway(std::string character){
    std::shared_ptr<Player> temp;
    std::vector<int> dpos{-1, -1}; 
    if(character == "s"){
        temp = std::make_shared<Shade>();
    }else if(character == "d"){
        temp =std::make_shared<Drow>();
    }else if(character == "v"){
        temp =std::make_shared<Vampire>();
    }else if(character == "t"){
        temp =std::make_shared<Troll>(); 
    }else if(character == "g"){
        temp = std::make_shared<Goblin>(); 
    } else {
        throw RaceDNE(); 
    }
    int play_loc = chooseChamber();

    Chamber play_cham = getChamber(play_loc);

    std::vector<int> player_tile = play_cham.chooseTile(dpos); 

    floor[player_tile[0]][player_tile[1]].setObject(temp);
    PlayerPos.emplace_back(player_tile[0]);
    PlayerPos.emplace_back(player_tile[1]);

    int stair_loc = this->chooseChamber();
    while(stair_loc == play_loc){
        stair_loc = this->chooseChamber();
    }
    Chamber stair_cham = getChamber(stair_loc);

    std::vector<int> stair_tile = stair_cham.chooseTile(dpos); 

    floor[stair_tile[0]][stair_tile[1]].setDefault(std::make_shared<Surroundings>(Surroundings("Stairs", '\\')));
    StairwayPos.emplace_back(stair_tile[0]);
    StairwayPos.emplace_back(stair_tile[1]);
}

// Generate all kinds of gold and potions
void Floor::generateItems(){
    for(int i = 0; i < 10 ; i ++){
        Chamber item_cham = getChamber(chooseChamber());
        while (item_cham.isEmpty()){
            item_cham = getChamber(chooseChamber());
        }
        std::vector<int> tile = item_cham.chooseTile(StairwayPos); 

        Cell & item_cell = floor[tile[0]][tile[1]]; 
        
        int ran_pot = rand() % 6 + 1;
        if(ran_pot == 1){
            std::shared_ptr<DisplayableObjects> pt1 = std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<BoostAtk>()); 
            item_cell.setObject(pt1);
        }else if (ran_pot == 2){
            std::shared_ptr<DisplayableObjects> pt2 = std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<BoostDef>()); 
            item_cell.setObject(pt2);
        }else if (ran_pot == 3){
            std::shared_ptr<DisplayableObjects> pt3 = std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<RestoreHealth>());
            item_cell.setObject(pt3);
        }else if (ran_pot == 4){
            std::shared_ptr<DisplayableObjects> pt4 = std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<PoisonHealth>()); 
            item_cell.setObject(pt4);
        }else if (ran_pot == 5){
            std::shared_ptr<DisplayableObjects> pt5 = std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<WoundAtk>()); 
            item_cell.setObject(pt5);
        }else if (ran_pot == 6){
            std::shared_ptr<DisplayableObjects> pt6 = std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<WoundDef>()); 
            item_cell.setObject(pt6);
        }
    }

    for(int i = 0; i < 10 ; i ++){
        Chamber gold_cham = getChamber(chooseChamber());
        while (gold_cham.isEmpty()){
            gold_cham = getChamber(chooseChamber());
        }
        std::vector<int> tile = gold_cham.chooseTile(StairwayPos); 
        Cell & gold_cell = floor[tile[0]][tile[1]];

        int ran_gold = rand() % 8;
        if (ran_gold <= 1){
            auto smallGold = std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<Treasures>("Small"));
            gold_cell.setObject(smallGold);
        } else if (ran_gold == 2) {
            // start of dragon h
            auto dragon = std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<Dragon>());
            auto dragonGold = std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<Treasures>("DragonH"));
            gold_cell.setObject(dragonGold);

            int r = gold_cell.getr();
            int c = gold_cell.getc();

            bool set = false;

            while(set == false){
                int random = rand()%7;
                if(random == 1){
                    if(r >= 1 && c <= 30){
                        if(floor[r-1][c+1].enemyCanGetOn()){
                            set = true;
                            floor[r-1][c+1].setObject(dragon); 
                        }
                    }
                }else if(random == 2){
                    if(r>= 1){
                        if(floor[r-1][c].enemyCanGetOn()){
                            set = true;
                            floor[r-1][c].setObject(dragon); 
                        }
                    }
                }if(random == 3){
                    if(r >= 1 && c >= 1){
                        if(floor[r-1][c-1].enemyCanGetOn()){
                            set = true;
                            floor[r-1][c-1].setObject(dragon); 
                        }
                    }
                }if(random == 4){
                    if(c <= 30){
                        if(floor[r][c+1].enemyCanGetOn()){
                            set = true;
                            floor[r-1][c+1].setObject(dragon); 
                        }
                    }
                }if(random == 5){
                    if(c >= 1){
                        if(floor[r][c-1].enemyCanGetOn()){
                            set = true;
                            floor[r-1][c+1].setObject(dragon); 
                        }
                    }
                }if(random == 6){
                    if(r <= 79 && c <= 30){
                        if(floor[r+1][c+1].enemyCanGetOn()){
                            set = true;
                            floor[r-1][c+1].setObject(dragon); 
                        }
                    }
                }if(random == 7){
                    if(r <= 79){
                        if(floor[r+1][c].enemyCanGetOn()){
                            set = true;
                            floor[r-1][c+1].setObject(dragon); 
                        }
                    }
                }
                if(random == 0){
                    if(r <= 79 && c >= 1) {
                        if(floor[r+1][c-1].enemyCanGetOn()){
                            set = true;
                            floor[r-1][c+1].setObject(dragon); 
                        }
                    }
                }
            }
            // end of dragon
        } else {
            auto normalGold = std::dynamic_pointer_cast<DisplayableObjects>(std::make_shared<Treasures>("Normal"));
            gold_cell.setObject(normalGold);
        }
         
    }
}

// Generate all enemies except Dragons
void Floor::generateEnemies(){
    for(int k = 0; k < 20; k++){
        Chamber enemy_cham = getChamber(chooseChamber());
        while(enemy_cham.isEmpty()){
            enemy_cham = getChamber(chooseChamber());
        }
        std::vector<int> tile = enemy_cham.chooseTile(StairwayPos); 
        Cell & enemy_cell = floor[tile[0]][tile[1]];

        int ran_en = rand() % 18;
        if(ran_en <= 3){
            auto h1 = std::make_shared<Human>();
            enemy_cell.setObject(h1);      //human
        }else if (ran_en <= 6){
            auto h2 = std::make_shared<Dwarf>();
            enemy_cell.setObject(h2);      // Dwarf
        }else if (ran_en <= 11){
            auto h3 = std::make_shared<Elf>();
            enemy_cell.setObject(h3);      // elf
        }else if (ran_en <= 13){
            auto h4 = std::make_shared<Orc>();
            enemy_cell.setObject(h4);      //Orc 
        }else if (ran_en <= 15){
            auto h5 = std::make_shared<Merchant>();
            enemy_cell.setObject(h5);      //Merchant
        }else if (ran_en <= 17){
            auto h6 = std::make_shared<Halfling>();
            enemy_cell.setObject(h6);      //Halfing
        }
    }
}

// Everything moves, with Player moving to the direction given
std::string Floor::step(std::string playerDirection, bool enemies_can_move){
    if(playerDirection != ""){
        std::vector<int> chosen_direction = this->DirectionLocation(playerDirection); 
        int rwhere = chosen_direction[0]; 
        int cwhere = chosen_direction[1]; 
        if (floor[rwhere][cwhere].playerCanGetOn() || floor[rwhere][cwhere].getObject()->getIdentity() == "Collectible") {
            if (floor[rwhere][cwhere].getObject()->getIdentity() == "Collectible") {
                std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player> (floor[PlayerPos[0]][PlayerPos[1]].getObject());
                std::shared_ptr<Treasures> t = std::dynamic_pointer_cast<Treasures> (floor[rwhere][cwhere].getObject());
                player->changeGold(t->getSize()); 
                floor[rwhere][cwhere].setObject(floor[PlayerPos[0]][PlayerPos[1]].getObject()); 
                floor[PlayerPos[0]][PlayerPos[1]].setObject(nullptr); 
            } else {
                floor[rwhere][cwhere].swap(floor[PlayerPos[0]][PlayerPos[1]]); 
            }
            PlayerPos[0] = rwhere; 
            PlayerPos[1] = cwhere; 
        } else {
            throw DirectionNotAllowed(); 
        }
    }
    
    if(enemies_can_move){ // if enemy is not frozen
        for(int i = 0; i < 25; i++){
            for(int j = 0; j < 79; j++){
                if(floor[i][j].getObject()->getIdentity() == "enemy"){
                    std::vector<Cell> list; 
                    if(floor[i][j].getObject()->getType() == 'D'){
                        for (int u = i-1; u <= i+1; u++) {
                            for (int v = j-1; v <= j+1; v++) {
                                if ((u == i) && (v == j)) {
                                    continue; 
                                }if ((u < 0) || (v < 0) || (u >= 25) || (v >= 79)) {
                                    continue; 
                                }if(floor[u][v].getObject()->getName() == "DragonH") {
                                    for(int a = u-1; a <= u+1; a++){
                                        for(int b = v-1; b <= v+1; b++){
                                            if ((a == u) && (b == v)) {
                                                continue; 
                                            } else if ((a == i) && (b == j)) {
                                                continue; 
                                            } else if ((u < 0) || (v < 0) || (u >= 25) || (v >= 79)) {
                                                continue; 
                                            }
                                            if((a>=i-1) && (a <= i+1) && (b >= j -1) && (b <= j +1)){
                                                list.push_back(floor[a][b]);
                                            }                                        
                                        }
                                    }
                                }
                            }
                        }
                    } else { 
                        for (int u = i-1; u <= i+1; u++) {
                            for (int v = j-1; v <= j+1; v++) {
                                if ((u == i) && (v == j)) {
                                    continue; 
                                } 
                                if ((u < 0) || (v < 0) || (u >= 25) || (v >= 79)) {
                                    continue; 
                                }
                                if (!floor[u][v].enemyCanGetOn()){
                                    continue; 
                                }
                                list.push_back(floor[u][v]); 
                            }
                        }
                    }
                    if (list.size() == 0) {
                        continue; 
                    } 
                    int index = rand() % list.size(); 
                    int rwhere = list[index].getr(); 
                    int cwhere = list[index].getc(); 
                    floor[rwhere][cwhere].swap(floor[i][j]); 
                }
            }
        }
    }
    // Write if sees potion
    std::string result = "PC moves " + compass[playerDirection] + "."; 
    return result; 

}

// Return the cell coordinate with respect to the direction of current player position. 
// Throw error if out of bounds. 
std::vector<int> Floor::DirectionLocation(std::string direction) {
    int rwhere = PlayerPos[0]; 
    int cwhere = PlayerPos[1]; 
    if (direction == "no") {
        rwhere --; 
    } else if (direction == "so") {
        rwhere ++; 
    } else if (direction == "ea") {
        cwhere ++; 
    } else if (direction == "we") {
        cwhere --; 
    } else if (direction == "ne") {
        rwhere --; 
        cwhere ++; 
    } else if (direction == "nw") {
        rwhere --; 
        cwhere --; 
    } else if (direction == "se") {
        rwhere ++; 
        cwhere ++; 
    } else if (direction == "sw") {
        rwhere ++; 
        cwhere --; 
    } else {
        throw DirectionNotAllowed(); 
    } 
    if (rwhere < 0 || rwhere >= 25 || cwhere < 0 || cwhere >= 79) {
        throw DirectionNotAllowed(); 
    } 
    std::vector<int> chosen_direction {rwhere, cwhere}; 
    return chosen_direction; 
}

// Player use the potion in the desired location, throw error when there is no potion in the direction
std::string Floor::usePotion(std::string direction) {
    int row = PlayerPos[0]; 
    int col = PlayerPos[1]; 
    std::vector<int> chosen_direction = this->DirectionLocation(direction); 
    int rwhere = chosen_direction[0]; 
    int cwhere = chosen_direction[1]; 
    std::string result; 
    if (floor[rwhere][cwhere].getObject()->getType() == 'P') {
        std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(floor[row][col].getObject());
        std::shared_ptr<Potions> p = std::dynamic_pointer_cast<Potions>(floor[rwhere][cwhere].getObject());
        result = p->applyEffect(player); 
        floor[rwhere][cwhere].setObject(floor[row][col].getObject()); 
        floor[row][col].setObject(nullptr); 
        PlayerPos[0] = rwhere; 
        PlayerPos[1] = cwhere; 
    } else {
        throw NoPotionsToUse(); 
    }
    return result; 
}

// Player attack the enemy in the direction specified
std::string Floor::attackEnemies(std::string direction){
    int row = PlayerPos[0]; 
    int col = PlayerPos[1]; 
    std::vector<int> chosen_direction = this->DirectionLocation(direction); 
    int rwhere = chosen_direction[0]; 
    int cwhere = chosen_direction[1]; 
    if (floor[rwhere][cwhere].getObject()->getIdentity() == "enemy") {
        std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player> (floor[row][col].getObject());
        std::shared_ptr<Enemies> enemy = std::dynamic_pointer_cast<Enemies> (floor[rwhere][cwhere].getObject());
        std::string player_attack = player->attack(enemy); 
        if (player_attack[player_attack.length() - 5] == 'i') { // enemy slained.
            if (enemy->getType() ==  'D') {
                for(int x = rwhere-1; x <= rwhere+1; x++) {
                    for(int y = cwhere-1; y <= cwhere+1; y++) { 
                        if (floor[x][y].getObject()->getName() == "DragonH") {
                            std::shared_ptr<Treasures> t = std::dynamic_pointer_cast<Treasures> (floor[x][y].getObject());
                            t->setIdentity("Collectible"); 
                        }
                    }
                } 
            }
            
            bool enemy_was_human = false; 
            if (enemy->getType() == 'H') {
                enemy_was_human = true; 
            }
            if (enemy_was_human) {
                std::shared_ptr<Treasures> t = std::make_shared<Treasures>("Normal");
                std::vector<Cell> list; 
                for (int u = rwhere-1; u <= rwhere+1; u++) {
                    for (int v = cwhere-1; v <= cwhere+1; v++) {
                        if ((u == rwhere) && (v == cwhere)) {
                            continue; 
                        } 
                        if ((u < 0) || (v < 0) || (u >= 25) || (v >= 79)) {
                            continue; 
                        }
                        if (!floor[u][v].enemyCanGetOn()){
                            continue; 
                        }
                        list.push_back(floor[u][v]); 
                    }
                }
                if (list.size() == 0) {
                    player->changeGold(2);
                    return player_attack; 
                } 
                int index = rand() % (list.size()); 
                floor[list[index].getr()][list[index].getc()].setObject(t); 
            }
            
            floor[rwhere][cwhere].setObject(floor[row][col].getObject()); 
            floor[row][col].setObject(nullptr); 
            return player_attack; 
        }
        std::string enemy_attack = enemy->attack(player); 
        if (enemy_attack[enemy_attack.length() - 5] == 'd') { // PC is dead.
            // floor[row][col].setObject(nullptr); 
            return player_attack + " " + enemy_attack; 
        } 
        return player_attack + " " + enemy_attack; 
    } else {
        throw NoEnemiesToAtk(); 
    }
}

// Enemy Autoattack after moving
std::string Floor::EnemySearchForAtk() {
    std::string result = ""; 
    for(int i = 0; i < 25; i++){
        for(int j = 0; j < 79; j++){
            if(floor[i][j].getObject()->getIdentity() == "enemy"){
                if (floor[i][j].getObject()->getType() == 'D') {
                    for (int u = i-1; u <= i+1; u++) {
                        for (int v = j-1; v <= j+1; v++) {
                            if ((u == i) && (v == j)) {
                                continue; 
                            } 
                            if ((u < 0) || (v < 0) || (u >= 25) || (v >= 79)) {
                                continue; 
                            }
                            if (floor[u][v].getObject()->getName() == "DragonH"){
                                for(int a = u-1; a <= u+1; a++){
                                    for(int b = v-1; b <= v+1; b++){
                                        if(floor[a][b].getObject()->getIdentity() == "player"){
                                            std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player> (floor[a][b].getObject());
                                            std::shared_ptr<Enemies> enemy = std::dynamic_pointer_cast<Enemies> (floor[i][j].getObject());
                                            std::string enemy_attack = enemy->attack(player); 
                                            if (enemy_attack[enemy_attack.length() - 5] == 'd') {
                                                result = result + enemy_attack; 
                                            } 
                                            std::string player_attack = player->attack(enemy); 
                                            if (player_attack[player_attack.length() - 5] == 'i') {
                                                floor[i][j].setObject(nullptr); 
                                                for(int x = i-1; x <= i+1; x++) {
                                                    for(int y = j-1; y <= j+1; y++) { 
                                                        if (floor[x][y].getObject()->getName() == "DragonH") {
                                                            std::shared_ptr<Treasures> t = std::dynamic_pointer_cast<Treasures> (floor[x][y].getObject());
                                                            t->setIdentity("Collectible"); 
                                                        }
                                                    }
                                                } 
                                                result = result + enemy_attack + " " + player_attack; 
                                            }
                                            result = result + enemy_attack + " " + player_attack; 
                                        }
                                    }
                                }
                            }
                        }
                     }
                } else {
                    std::vector<Cell> list; 
                    // std::cout << floor[i][j].getObject()->getType();
                    if (floor[i][j].getObject()->getType() == 'M') {
                        std::shared_ptr<Merchant> m = std::dynamic_pointer_cast<Merchant>(floor[i][j].getObject()); 
                        if (!m->getHostile()) {
                            continue; 
                        }
                    }
                    for (int u = i-1; u <= i+1; u++) {
                        for (int v = j-1; v <= j+1; v++) {
                            if ((u == i) && (v == j)) {
                                continue; 
                            } 
                            if ((u < 0) || (v < 0) || (u >= 25) || (v >= 79)) {
                                continue; 
                            }
                            if (floor[u][v].getObject()->getIdentity() == "player"){
                                std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player> (floor[u][v].getObject());
                                std::shared_ptr<Enemies> enemy = std::dynamic_pointer_cast<Enemies> (floor[i][j].getObject());
                                std::string enemy_attack = enemy->attack(player); 
                                if (enemy_attack[enemy_attack.length() - 5] == 'd') {
                                    result += enemy_attack; 
                                    break; 
                                } 
                                result += enemy_attack; 
                                std::string player_attack = player->attack(enemy); 
                                if (player_attack[player_attack.length() - 5] == 'i') {
                                    bool enemy_was_human = false; 
                                    if (enemy->getType() == 'H') {
                                        enemy_was_human = true; 
                                    }
                                    if (enemy_was_human) {
                                        std::shared_ptr<Treasures> t = std::make_shared<Treasures>("Normal");
                                        std::vector<Cell> list; 
                                        for (int x = i-1; x <= i+1; x++) {
                                            for (int y = j-1; y <= j+1; y++) {
                                                if ((x == i) && (y == j)) {
                                                    continue; 
                                                } 
                                                if ((x < 0) || (y < 0) || (x >= 25) || (y >= 79)) {
                                                    continue; 
                                                }
                                                if (!floor[x][y].enemyCanGetOn()){
                                                    continue; 
                                                }
                                                list.push_back(floor[x][v]); 
                                            }
                                        }
                                        if (list.size() == 0) {
                                            player->changeGold(2);
                                            return player_attack; 
                                        } 
                                        int index = rand() % (list.size()); 
                                        floor[list[index].getr()][list[index].getc()].setObject(t); 
                                    }
                                    floor[i][j].setObject(floor[u][v].getObject()); 
                                    floor[u][v].setObject(nullptr); 
                                    PlayerPos[0] = i; 
                                    PlayerPos[1] = j; 
                                    result = result + " " + player_attack; 
                                    break; 
                                }
                                result += player_attack; 
                            }
                        }
                    }
                }
            }
        }
    }
    if (result == "") {
        return "None"; 
    }
    return result; 
}

// Update the floor after everything moved
void Floor::update() {
    for (int i = 0; i<25; i++) {
        for (int j = 0; j<79; j++) {
            floor[i][j].update(); 
        }
    }
} 

// Check if a player has reached the stairs and should go to the next level
bool Floor::checkNextFloor() {
    if (StairwayPos[0] == PlayerPos[0] && StairwayPos[1] == PlayerPos[1]) {
        return true; 
    }
    return false; 
}

// Check if player is on the stair
bool Floor::playeronstair(){
    return (PlayerPos[0] == StairwayPos[0]) && ( PlayerPos[1] == StairwayPos[1]) ;
}

// Copy the current player health to the new floor, discard potion effects on atk and def
void Floor::copyPlayerHealth(Floor & other) {
    std::shared_ptr<Player> old_player = std::dynamic_pointer_cast<Player>(other.floor[other.PlayerPos[0]][other.PlayerPos[1]].getObject()); 
    std::shared_ptr<Player> new_player = std::dynamic_pointer_cast<Player>(floor[PlayerPos[0]][PlayerPos[1]].getObject()); 
    new_player->changeHP(old_player->getHP() - new_player->getHP()); 
}

// Friend function to print the floor
std::ostream & operator<<( std::ostream & out, Floor & f ) {
    for (auto n : f.floor) {
        for (auto m : n) {
            out << m.getObjectType();
        }
        out<<std::endl;
    }

    std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(f.floor.at(f.PlayerPos.at(0)).at(f.PlayerPos.at(1)).getObject());
    std::string result = "Race: ";
    result += player->getName();
    result += " Gold: ";
    result += std::to_string(player->getGold());
    out << std::left << std::setw(68) << result << std::setw(7) << "Floor: " << (f.level + 1) << std::endl;
    out << "HP: " << player->getHP() << std::endl;
    out << "Atk: " << player->getAtk() << std::endl;
    out << "Def: " << player->getDef() << std::endl; 
    out << "Action: " ;
    
    return out;
}

