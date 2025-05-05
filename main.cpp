///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 14a - RPG Beta - ECE 205 - Spring 2025
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
#include "Battle.hpp"
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

//The following program demonstrates how you might call some of the functions in your new class
//and produce the sample output shown in the assignment write-up
//you are not required to use this file and can refactor any existing code that you
//already have to produce the same results

int main()
{
    json characterData;
    ifstream inFile("adventure.json");
    if (!inFile) {
        cerr << "Failed to load preset character data.\n";
        return 1;
    }
    inFile >> characterData;

    srand(time(nullptr));
    //declare variables
    string characterName;
    int characterRace;
    string userResponse;
    int characterProfession;
    int actionChoice;
    int makeCharacterChoice;
    int numPlayers;

    while (true) {
        cout << "Would you like to: " << endl;
        cout << "(1) Create your own character(s)" << endl;
        cout << "(2) Use an existing character" << endl;
        cout << "Enter 1 or 2: " << endl;
        cin >> makeCharacterChoice;

        if (makeCharacterChoice < 1 || makeCharacterChoice > 2) {
            cout << "Invalid value! Please enter 1 or 2." << endl;
        } else {
            break;
        }
    }

    std::vector<PlayerCharacter*> adventureParty;

    if (makeCharacterChoice == 1) {
        cout << "How many characters are in your adventure party?: ";
        cin >> numPlayers;

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

            PlayerCharacter *player = nullptr;

            if (characterProfession == 0) {
                player = new Bard(characterName, characterRace);
            } else if (characterProfession == 1) {
                player = new Blacksmith(characterName, characterRace);
            } else if (characterProfession == 2) {
                player = new Hunter(characterName, characterRace);
            }

            player->displayStats();

            if (characterProfession == 0) {
                dynamic_cast<Bard *>(player)->displayBardStats();
            } else if (characterProfession == 1) {
                dynamic_cast<Blacksmith *>(player)->displayBlacksmithStats();
            } else if (characterProfession == 2) {
                dynamic_cast<Hunter *>(player)->displayHunterStats();
            }

            adventureParty.push_back(player);
        }
    }

    else if (makeCharacterChoice == 2) {
        const auto& characters = characterData["characters"];
        cout << "Existing Characters:\n";
        for (size_t i = 0; i < characters.size(); ++i) {
            cout << i + 1 << ". " << characters[i]["name"]
            << ", Race: " << characters[i]["raceName"]
            << ", Profession: " << characters[i]["professionName"] << endl;
        }

        cout << "How many existing characters would you like to use?: ";
        cin >> numPlayers;

        for (int i = 0; i < numPlayers; ++i) {
            int selection;

            while (true) {
                cout << "Enter the number of the character you want to use: ";
                cin >> selection;

                if (selection < 1 || selection > characters.size()) {
                    cout << "Invalid value!" << endl;
                } else {
                    break;
                }
            }

            auto& preset = characters[selection - 1];
            string name = preset["name"];
            int race = preset["raceCode"];
            int profession = preset["profession"];

            PlayerCharacter *player = nullptr;

            if (profession == 0) {
                player = new Bard(name, race);
            } else if (profession == 1) {
                player = new Blacksmith(name, race);
            } else if (profession == 2) {
                player = new Hunter(name, race);
            }

            player->displayStats();

            if (profession == 0) {
                dynamic_cast<Bard *>(player)->displayBardStats();
            } else if (profession == 1) {
                dynamic_cast<Blacksmith *>(player)->displayBlacksmithStats();
            } else if (profession == 2) {
                dynamic_cast<Hunter *>(player)->displayHunterStats();
            }

            adventureParty.push_back(player);
        }
    }

    PlayerCharacter *enemy = new Blacksmith("Huskryn", 3);

    unordered_map<string, json> adventureScenes;
    string currentLocation = characterData["start"];

    for (auto& [key, value] : characterData.items()) {
        if (key != "start" && key != "characters") {
            adventureScenes[key] = value;
        }
    }

    while (adventureScenes.count(currentLocation)) {
        auto& scene = adventureScenes[currentLocation];

        cout << scene["setting"] << "\n";

        // trigger battle
        if (scene["triggerBattle"] == 1) {
            Battle battle(adventureParty, enemy);
            battle.startBattle();

            int aliveCount = 0;
            for (auto* pc : adventureParty)
                if (pc->getHealth() > 0)
                    aliveCount++;

            if (aliveCount == 0) {
                cout << "\nYour party has fallen. The adventure ends here.\n";
                break;
            } else {
                currentLocation = "win";
                continue;
            }
        }

        if (currentLocation == "enter" || currentLocation == "leave") {
            currentLocation = "ending";
            continue;
        }

        if (!scene.contains("option1") || !scene.contains("option2")) {
            break;
        }

        while (true) {
            cout << "(1) " << scene["option1"] << "\n";
            cout << "(2) " << scene["option2"] << "\n";
            cout << "> ";

            int choice;
            cin >> choice;
            if (choice == 1) {
                currentLocation = scene["option1"];
                break;
            } else if (choice == 2) {
                currentLocation = scene["option2"];
                break;
            } else if (choice < 1 || choice > 2) {
                cout << "Invalid value! Please enter 1 or 2.\n";
            }

            if (currentLocation == "ending") {
                cout << "\n" << adventureScenes["ending"]["setting"] << "\n";
                break;
            }
        }
    }

    // Clean up memory for the players in adventureParty
    for (auto* pc : adventureParty) {
        delete pc;  // Delete each PlayerCharacter object
    }

    // Clean up the enemy
    delete enemy;
    
    return 0;
}
