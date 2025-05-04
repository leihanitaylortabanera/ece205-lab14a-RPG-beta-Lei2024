///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 12b - Game Character Class Part III - ECE 205 - Spring 2025
//
///
/// @file    Blacksmith.cpp
/// @author  Leihani-Taylor Tabanera <lei2022@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Blacksmith.hpp"

Blacksmith::Blacksmith(const std::string& newName, int newRace) : PlayerCharacter(newName, newRace) {
    // Initialize attributes' points
    craftsmanship = blacksmithRollDice(1,10);
    metal_manipulation = blacksmithRollDice(1,10);
}

// performAction overridden
// inherited method
void Blacksmith::performAction() {
    int actionChoice;
    std::cout << "Choose an action for " << name << " (Health: " << getHealth() << "):" << std::endl;
    std::cout << "Option 0 - Weapon Strike (min 4 on D20 | damage = roll + Craftsmanship: " << craftsmanship << ")" << std::endl;
    std::cout << "Option 1 - Molten Blast (min 5 on D20 | damage = roll + Metal Manipulation: " << metal_manipulation << ")" << std::endl;
    std::cin >> actionChoice;

    while (true) {
        if (actionChoice == 0) {
            weaponStrike();
            break;
        } else if (actionChoice == 1) {
            moltenBlast();
            break;
        } else {
            std::cout << "Invalid choice!" << std::endl;
        }
    }
}

// 1st unique skill of Blacksmith: Weapon Strike.
void Blacksmith::weaponStrike() {
    int canPerformWeaponStrike;
    int damage;

    canPerformWeaponStrike = blacksmithRollDice(1,20);
    std::cout << "You rolled a " << canPerformWeaponStrike << std::endl;

    if (canPerformWeaponStrike >= 4) {
        damage = canPerformWeaponStrike + craftsmanship;
        std::cout << "You swing with might, your weapon cutting through the foe. Damage dealt is " << damage << "." << std::endl;
    } else {
        damage = 0;
        std::cout << "Your strike misses its mark, and your enemy evades with ease. Damage dealt is 0." << std::endl;
    }
    setDamage(damage);
}

// 2nd unique skill of Blacksmith: Molten Blast.
void Blacksmith::moltenBlast() {
    int canPerformMoltenBlast;
    int damage;

    canPerformMoltenBlast = blacksmithRollDice(1,20);
    std::cout << "You rolled a " << canPerformMoltenBlast << std::endl;

    if (canPerformMoltenBlast >= 5) {
        damage = canPerformMoltenBlast + metal_manipulation;
        std::cout << "A torrent of molten energy erupts, scorching everything in its path. Damage dealt is " << damage << "." << std::endl;
    } else {
        damage = 0;
        std::cout << "The molten fury sputters, unable to form into a blast. Damage dealt is 0." << std::endl;
    }
    setDamage(damage);
}

// Used to determine if the player can perform the Blacksmith's action.
int Blacksmith::blacksmithRollDice(int lower, int upper) {
    return lower + rand() % (upper - lower + 1);
}

// Name of Blacksmith preceeded by their profession with their greeting
void Blacksmith::greet() const {
    std::cout << name << " the Blacksmith: Hello, my name is " << name << "." << std::endl;
}

// Displays profession and 2 unique attributes of the blacksmith.
void Blacksmith::displayBlacksmithStats() {
    std::cout << "Profession: Blacksmith" << std::endl;
    std::cout << "Craftsmanship: " << craftsmanship << std::endl;
    std::cout << "Metal Manipulation: " << metal_manipulation << std::endl;
    std::cout << "-----------------------------------" << std::endl;
}