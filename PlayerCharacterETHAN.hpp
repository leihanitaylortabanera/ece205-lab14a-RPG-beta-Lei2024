#pragma once
#include "GameCharacter.hpp"

class PlayerCharacter : public GameCharacter {
private:
    int race;
    int health;
    int strength;
    int agility;
    int defense;
    int damage;
    int health_restored;
    int targetChoice;

public:
    PlayerCharacter(const std::string& newName, int newRace);

    void rollDice();
    void displayStats() const;
    void setRace(int newRace);
    int getRace() const;

    int getHealth() const;
    void setHealth(int newHealth);

    int getHealthRestored() const;
    void setHealthRestored(int newHealthRestored);

    void receiveHealthRestored(int healing);

    int getDamage() const;
    void setDamage(int newDamage);

    void reactToUser(const std::string& userInput);

    virtual void performAction(bool isEnemy);

    void receiveDamage(int damage);
    void receiveHealth(int health);
};
