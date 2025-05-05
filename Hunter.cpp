///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 14a - RPG Beta - ECE 205 - Spring 2025
//
///
/// @file    Hunter.cpp
/// @author  Leihani-Taylor Tabanera <lei2022@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Hunter.hpp"

// Constructor for Hunter
Hunter::Hunter(const std::string& newName, int newRace) : PlayerCharacter(newName, newRace) {
    // Initialize attributes' points
    stealth = hunterRollDice(1,10);
    aim_accuracy = hunterRollDice(1,10);
}

// performAction overridden
// inherited method
void Hunter::performAction(bool isEnemy) {
    int actionChoice;
    std::cout << "Choose an action for " << name << " (Health: " << getHealth() << "):" << std::endl;
    std::cout << "Option 0 - Arrow Barrage (min 6 on D20 | damage = roll + Aim Accuracy: " << aim_accuracy << ")" << std::endl;
    std::cout << "Option 1 - Backstab Shot (min 3 on D20 | damage = roll + Stealth: " << stealth << ")" << std::endl;
    std::cin >> actionChoice;

    while (true) {
        if (actionChoice == 0) {
            arrowBarrage();
            break;
        } else if (actionChoice == 1) {
            backstabShot();
            break;
        } else {
            std::cout << "Invalid choice!" << std::endl;
        }
    }
}

// 1st unique skill of Hunter: Arrow Barrage.
void Hunter::arrowBarrage() {
    int canPerformArrowBarrage;
    int damage;

    canPerformArrowBarrage = hunterRollDice(1,20);
    std::cout << name << " rolled a " << canPerformArrowBarrage << std::endl;

    if (canPerformArrowBarrage >= 6) {
        damage = canPerformArrowBarrage + aim_accuracy;
        std::cout << "A hail of arrows rains down, striking " << name << "'s enemies from all sides. Damage dealt is " << damage << ".\n" << std::endl;
    } else {
        damage = 0;
        std::cout << name << "'s arrows fall short, the barrage failing to reach its target. Damage dealt is 0.\n" << std::endl;
    }
    setDamage(damage);
}

// 2nd unique skill of Hunter: Backstab Shot.
void Hunter::backstabShot() {
    int canPerformBackstabShot;
    int damage;

    canPerformBackstabShot = hunterRollDice(1,20);
    std::cout << name << " rolled a " << canPerformBackstabShot << std::endl;

    if (canPerformBackstabShot >= 3) {
        damage = canPerformBackstabShot + stealth;
        std::cout << name << " vanishes into the gloom, draws a silent breath, and unleashes a precise shot straight into the enemy’s blind spot. Damage dealt is " << damage << "." << std::endl;
    } else {
        damage = 0;
        std::cout << name << " tries to blend into the surroundings, but they have been spotted instantly and their arrow was dodged instantly. Damage dealt is 0." << std::endl;
    }
    setDamage(damage);
}

// Used to determine if the player can perform the Hunter's action
int Hunter::hunterRollDice(int lower, int upper) {
    return lower + rand() % (upper - lower + 1);
}

// Name of Hunter preceeded by their profession with their greeting
void Hunter::greet() const {
    std::cout << name << " the Hunter: Hello, my name is " << name << "." << std::endl;
}

// Displays profession and 2 unique attributes of the hunter.
void Hunter::displayHunterStats() {
    std::cout << "Profession: Hunter" << std::endl;
    std::cout << "Stealth: " << stealth << std::endl;
    std::cout << "Aim Accuracy: " << aim_accuracy << std::endl;
    std::cout << "-----------------------------------" << std::endl;
}