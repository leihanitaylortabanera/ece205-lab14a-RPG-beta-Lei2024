///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 12a - Game Character Class Part III - ECE 205 - Spring 2025
//
///
/// @file    main.cpp
/// @author  Leihani-Taylor Tabanera <lei2022@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <vector>
#include "GameCharacter.hpp"
#include "PlayerCharacterETHAN.hpp"
#include "Hunter.hpp"
#include "Blacksmith.hpp"
#include "Bard.hpp"

using namespace std;

//The following program demonstrates how you might call some of the functions in your new class
//and produce the sample output shown in the assignment write-up
//you are not required to use this file and can refactor any existing code that you
//already have to produce the same results

int main()
{
    srand(time(nullptr));
    //declare variables
    string characterName;
    int characterRace;
    string userResponse;
    int characterProfession;
    int actionChoice;
    int numPlayers;

    cout << "How many characters are in your adventure party?: ";
    cin >> numPlayers;

    std::vector<PlayerCharacter*> adventureParty;

    for (int i = 0; i < numPlayers; i++) {
        cout << "\n";
        cout << "Creating Player " << i + 1 << ":" << endl;

        //define variables
        cout << "Enter a name for your character: ";
        cin >> characterName;

        // Checks for valid race input
        while (true) {
            cout << "Enter a race for your character (0 = Dwarf, 1 = Elf, 2 = Human, 3 = Orc): ";
            cin >> characterRace;
            if (characterRace < 0 || characterRace > 3) {
                cout << "Invalid value!" << endl;
            } else {
                break;
            }
        }

        // Checks for valid profession input
        while (true) {
            cout << "Enter a profession for your character (0 = Bard, 1 = Blacksmith, 2 = Hunter): ";
            cin >> characterProfession;
            if (characterProfession < 0 || characterProfession > 2) {
                cout << "Invalid value!" << endl;
            } else {
                break;
            }
        }

        PlayerCharacter* player = nullptr;

        if (characterProfession == 0) {
            player = new Bard(characterName, characterRace);
        } else if (characterProfession == 1) {
            player = new Blacksmith(characterName, characterRace);
        } else if (characterProfession == 2) {
            player = new Hunter(characterName, characterRace);
        }

        player->displayStats();

        if (characterProfession == 0) {
            dynamic_cast<Bard*>(player)->displayBardStats();
        } else if (characterProfession == 1) {
            dynamic_cast<Blacksmith*>(player)->displayBlacksmithStats();
        } else if (characterProfession == 2) {
            dynamic_cast<Hunter*>(player)->displayHunterStats();
        }

        adventureParty.push_back(player);
    }

    // display battle rules
    cout << "Here are the battle rules: " << endl;
    cout << "Each player will select a target, then an action when it's their turn to attack. Actions require a minimum" << endl;
    cout << "dice roll on a 20-sided die (D20) to be successful. If successful, the damage dealt to their foe's health " << endl;
    cout << "will be the dice roll value + unique attribute." << endl;

    cout << "Let the battle commence! BEGIN!" << endl;
    cout << "-----------------------------------" << endl;
    
    while (true) {
        for (size_t i = 0; i < adventureParty.size(); ++i) {
            PlayerCharacter *attacker = adventureParty[i];

            if (attacker->getHealth() <= 0) {
                continue;
            }

            int targetChoice;
            cout << attacker->getName() << "'s turn!" << endl;

            while (true) {
                std::cout << "Choose a target: " << std::endl;
                for (size_t j = 0; j < adventureParty.size(); ++j) {
                    if (i != j && adventureParty[j]->getHealth() > 0) {
                        std::cout << j << ": " << adventureParty[j]->getName() << std::endl;
                    }
                }

                std::cin >> targetChoice;
                if (targetChoice < 0 || targetChoice > adventureParty.size()) {
                    std::cout << "Invalid value!" << std::endl;
                } else {
                    break;
                }
            }

            PlayerCharacter *target = adventureParty[targetChoice];
            attacker->performAction();

            int damage = 0;
            damage = attacker->getDamage(); // checks if the attacker does damage to the target
            if (damage > 0) {
                target->receiveDamage(damage); // if damage is done, the target's health is reduced
            }
            attacker->setDamage(0); // resets damage back to 0

            int healing = 0;
            healing = attacker->getHealthRestored(); // checks if the attacker 
            if (healing > 0) {
                target->receiveHealthRestored(healing);
            }
            attacker->setHealthRestored(0); // resets healing back to 0

            if (target->getHealth() <= 0) {
                cout << "Foe " << target->getName() << "'s Remaining Health: 0" << "\n";
            } else {
                cout << "Foe " << target->getName() << "'s Remaining Health: " << target->getHealth() << "\n";
            }
            std::cout << "-----------------------------------" << std::endl;
        }

        // checks how many characters are alive after every turn
        int aliveCount = 0;
        PlayerCharacter* lastAlive = nullptr;
        for (PlayerCharacter* pc : adventureParty) {
            if (pc->getHealth() > 0) {
                aliveCount++;
                lastAlive = pc;
            }
        }

        // if only one character is alive, the game ends!
        if (aliveCount == 1) {
            cout << "Game Over! " << lastAlive->getName() << " is victorious!" << endl;
            cout << "-----------------------------------" << endl;
            break;
        }
    }
    return 0;
}
