#include <iostream>
#include <cstdlib>
#include <ctime>
#include "PlayerCharacterETHAN.hpp"

class string;

PlayerCharacter::PlayerCharacter(const std::string& newName, int newRace) {
    name = newName;
    setRace(newRace);
    health = 100;
    rollDice();
}

void PlayerCharacter::rollDice() {
    srand(static_cast<unsigned>(time(0)));
    strength = rand() % 10 + 1;
    agility = rand() % 10 + 1;
    defense = rand() % 10 + 1;
}

void PlayerCharacter::displayStats() const {
    static const std::string races[] = { "Dwarf", "Elf", "Human", "Orc" };

    std::cout << "\n---------- Stats for " << name << " ----------\n";
    std::cout << "Race: " << races[race] << "\n";
    std::cout << "Health: " << health << "\n";
    std::cout << "Strength: " << strength << "\n";
    std::cout << "Agility: " << agility << "\n";
    std::cout << "Defense: " << defense << "\n";
    std::cout << "-----------------------------------\n";
}

void PlayerCharacter::setRace(int newRace) {
    race = newRace;
}

int PlayerCharacter::getDamage() const{
    return damage;
}

void PlayerCharacter::setDamage(int newDamage) {
    damage = newDamage;
}

int PlayerCharacter::getHealthRestored() const {
    return health_restored;
}

void PlayerCharacter::setHealthRestored(int newHealthRestored) {
    health_restored = newHealthRestored;
}

void PlayerCharacter::receiveHealthRestored(int healing) {
    setHealth(getHealth() + healing);
    if (getHealth() > 100) {
        setHealth(100);
    }
}

int PlayerCharacter::getRace() const {
    return race;
}

void PlayerCharacter::reactToUser(const std::string& userInput) {
    std::cout << name << ": ";
    if (userInput == "hello") {
        greet();
    } else {
        std::cout << "I'm sorry, I don't understand." << std::endl;
    }
}

void PlayerCharacter::performAction(bool isEnemy) {
    std::cout << "I'm sorry, there's nothing I can do." << std::endl;
}

int PlayerCharacter::getHealth() const {
    return health;
}

void PlayerCharacter::setHealth(int newHealth) {
    health = newHealth;
}

void PlayerCharacter::receiveDamage(int damage) {
    setHealth(getHealth() - damage);
}
