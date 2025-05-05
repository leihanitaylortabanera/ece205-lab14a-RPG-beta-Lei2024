///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 14a - RPG Beta - ECE 205 - Spring 2025
//
///
/// @file    Bard.cpp
/// @author  Leihani-Taylor Tabanera <lei2022@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Bard.hpp"

Bard::Bard(const std::string& newName, int newRace) : PlayerCharacter(newName, newRace) {
    // Initialize attributes' points
    charisma = bardRollDice(1,10);
    wisdom = bardRollDice(1,10);
}

// performAction overridden
// inherited method
void Bard::performAction(bool isEnemy) {
    int actionChoice;
    std::cout << "Choose an action for " << name << " (Health: " << getHealth() << "):" << std::endl;
    std::cout << "Option 0 - Healing Melody (min 7 on D20 | healing = roll + Wisdom: " << wisdom << ")" << std::endl;
    std::cout << "Option 1 - Counter Performance (min 5 on D20 | damage = roll + Charisma: " << charisma << ")" << std::endl;
    std::cin >> actionChoice;

    while (true) {
        if (actionChoice == 0) {
            healingMelody();
            break;
        } else if (actionChoice == 1) {
            counterPerformance();
            break;
        } else {
            std::cout << "Invalid choice!" << std::endl;
        }
    }
}

// 1st unique skill of Bard: Healing Melody.
void Bard::healingMelody() {
    int canPerformHealingMelody = 0;
    int healing = 0;

    canPerformHealingMelody = bardRollDice(1,20);
    std::cout << name << " rolled a " << canPerformHealingMelody << "." << std::endl;

    if (canPerformHealingMelody >= 7) {
        healing = canPerformHealingMelody + wisdom;
        std::cout << name << "'s song fills the air, healing those in their presence. Health restored is " << healing << "." << std::endl;
    } else {
        healing = 0;
        std::cout << name << "'s song falters, failing to reach wounded allies. Health restored is 0." << std::endl;
    }

    setHealthRestored(healing);
}

// 2nd unique skill of Bard: Counter Performance.
void Bard::counterPerformance() {
    int canPerformCounterPerformance = 0;
    int damage = 0;
    canPerformCounterPerformance = bardRollDice(1,20);

    std::cout << name << " rolled a " << canPerformCounterPerformance << "." << std::endl;
    
    if (canPerformCounterPerformance >= 5) {
        damage = canPerformCounterPerformance + charisma;
        std::cout << name << " strikes a perfect chord. Damage dealt is " << damage << "." << std::endl;
    } else {
        damage = 0;
        std::cout << "The discordant tune stumbles, failing to disrupt the enemy's attack. Damage dealt is 0." << std::endl;
    }

    setDamage(damage);
}

// Used to determine if the player can perform the Bard's action.
int Bard::bardRollDice(int lower, int upper) {
    return lower + rand() % (upper - lower + 1);
}

// Name of Bard preceeded by their profession with their greeting
void Bard::greet() const {
    std::cout << name << " the Bard: Hello, my name is " << name << "." << std::endl;
}

// Displays profession and 2 unique attributes of the bard.
void Bard::displayBardStats() {
    std::cout << "Profession: Bard" << std::endl;
    std::cout << "Charisma: " << charisma << std::endl;
    std::cout << "Wisdom: " << wisdom << std::endl;
    std::cout << "-----------------------------------" << std::endl;
}
