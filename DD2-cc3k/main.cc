#include "main.h"

int main(int argc, char * argv[]) {
    // Loop Control Variables
    // srand(1000); 
    bool playing = true; 
    bool in_a_game = true; 
    bool enemies_can_move = true; 
    std::shared_ptr<Merchant> m = std::make_shared<Merchant>(); 

    // start the game
    while (playing) {
        m->setFriendly(); 
        // Construct the floors
        std::vector<Floor> floors; 
        for (int i = 0; i < 5; i++) {
            floors.emplace_back(Floor()); 
        }
        // Read in player character
        std::cout << "Please choose a race to spawn as: "; 
        std::string player_character; 
        bool player_is_alive = true; 
        bool player_beat_the_game = false; 
        in_a_game = true; 
        std::cin >> player_character; 
        // Set up the floor, retake character input in the character input was invalid
        try {
            if (argc > 1) {
                std::ifstream infile{ argv[1] };
                if (infile.is_open()) {
                    for (int i = 0; i < 5; i++) {
                        std::string floor = "";
                        for (int j = 0; j < 25; j++){
                            std::string line; 
                            std::getline(infile, line); 
                            floor += line; 
                            floor += "\n";
                            // std::cout << "read in a floor" << std::endl; 
                        }
                        floors[i].set_Floor(player_character, floor, i); 
                        // std::cout << "generated a floor" << std::endl; 
                    }
                } else {
                    for (int i = 0; i < 5; i++) {
                        floors[i].set_Floor(player_character, i); 
                    }
                }
            } else {
                for (int i = 0; i < 5; i++) {
                    floors[i].set_Floor(player_character, i); 
                }
            }
        } catch (InputException &e) {
            e.printMsg(); 
            continue; 
        }

        // Iterate through each floor; 
        while (in_a_game) {
            int i = 0; 
            bool on_this_floor = true; 
            int turn = 0; // records the turns on this floor
            std::string action_result; 
            std::string player_action; 

            // do stuff on active floor 
            while (on_this_floor) {
                if (turn == 0) {
                    std::cout << floors[i]; 
                    std::cout << "Player Character has been spawned." << std::endl; 
                    turn++; 
                    continue; 
                } 
                bool turn_is_over = false; 
                while (!turn_is_over) { // 1 action 1 turn
                    if (!player_is_alive) {
                        std::cout << "Game Over!" << std:: endl; 
                        std::cout << "If you want to play again press \"r\", if you want to quit press \"q\": "; 
                    }
                    std::cout << "Input: "; 
                    std::cin >> player_action; 
                    if (player_action == "q") { // player quits the game
                        turn_is_over = true; 
                        on_this_floor = false; 
                        in_a_game = false; 
                        playing = false; 
                        if (player_is_alive) {
                            std::cout << "Player Character has chosen death!" << std::endl; 
                        }
                        std::cout << "Exiting Game!" << std::endl; 
                        continue; 
                    } else if (player_action == "r") { // player restart the game
                        turn_is_over = true; 
                        on_this_floor = false; 
                        in_a_game = false; 
                        std::cout << "Game Restarting ..." << std::endl; 
                        continue; 
                    } else if (player_action == "f" && player_is_alive && !player_beat_the_game) { // player freezes or unfreezes the enemies
                        enemies_can_move = !enemies_can_move; 
                        if (enemies_can_move) {
                            std::cout << "The enemies are unfrozen" << std::endl; 
                        } else {
                            std::cout << "The enemies are frozen" << std::endl; 
                        }
                    } else if ((player_action == "no" ||
                                player_action == "so" ||
                                player_action == "ea" ||
                                player_action == "we" ||
                                player_action == "ne" ||
                                player_action == "nw" ||
                                player_action == "se" ||
                                player_action == "sw") && player_is_alive && !player_beat_the_game) { // player move in this direction; 
                        try {
                            action_result = floors[i].step(player_action, enemies_can_move); 
                            floors[i].update(); 
                            action_result += "\nEnemy Auto Attck: "; 
                            action_result += floors[i].EnemySearchForAtk(); 
                            if (action_result[action_result.length() - 5] == 'd') {
                                player_is_alive = false; 
                                std::cout << floors[i] << action_result << std::endl; 
                                continue; 
                            } 
                            turn++; 
                            turn_is_over = true; 
                            std::cout << floors[i] << action_result << std::endl; 
                            if(floors[i].playeronstair()){ // player moved on to the stair, move to next level
                                if (i <= 3) {
                                    floors[i+1].copyPlayerHealth(floors[i]); 
                                    std::cout << floors[i+1] << "PC have reached the next floor!" << std::endl;
                                }
                                i++;
                                if (i == 5) {// Player wins the game
                                    std::cout << "You have won! You have beaten the cc3k!" << std:: endl; 
                                    std::cout << "If you want to play again press \"r\", if you want to quit press \"q\". " <<std::endl;
                                    player_beat_the_game = true; 
                                    continue; 
                                }
                            }
                        } catch (InputException &e) {
                            e.printMsg(); 
                        }
                        
                    } else if (player_action[0] == 'u' && player_is_alive && !player_beat_the_game) { // player uses a potion; 
                        std::string potion_direction; 
                        std::cin >> potion_direction;
                        try {
                            action_result = floors[i].usePotion(potion_direction); 
                            floors[i].step("", enemies_can_move); 
                            floors[i].update(); 
                            action_result += "\nEnemy Auto Attck: "; 
                            action_result += floors[i].EnemySearchForAtk(); 
                            if (action_result[action_result.length() - 5] == 'd') {
                                player_is_alive = false; 
                                std::cout << floors[i] << action_result << std::endl; 
                                continue; 
                            } 
                            std::cout << floors[i] << action_result << std::endl; 
                            turn++; 
                        } catch (InputException &e) {
                            e.printMsg(); 
                        }
                        
                    } else if (player_action[0] == 'a' && player_is_alive && !player_beat_the_game) { // player attacks an enemy; 
                        std::string attack_direction; 
                        std::cin >> attack_direction;
                        try {
                            action_result = floors[i].attackEnemies(attack_direction); 
                            if (action_result[action_result.length() - 5] == 'd') {
                                player_is_alive = false; 
                                std::cout << floors[i] << action_result << std::endl; 
                                continue; 
                            } 
                            floors[i].step("", enemies_can_move); 
                            floors[i].update(); 
                            action_result += "\nEnemy Auto Attck: "; 
                            action_result += floors[i].EnemySearchForAtk(); 
                            if (action_result[action_result.length() - 5] == 'd') {
                                player_is_alive = false; 
                                std::cout << floors[i] << action_result << std::endl; 
                                continue; 
                            } 
                            std::cout << floors[i] << action_result << std::endl; 
                            turn++; 
                        } catch (InputException &e) {
                            e.printMsg(); 
                        } 
                        
                    } else {// invalid input, retake a new input
                        std::cout << "Invalid Input! Please input again" << std::endl; 
                    }
                } 
            } 
        } 
    } 
    // Program ends
    return 0; 
}

