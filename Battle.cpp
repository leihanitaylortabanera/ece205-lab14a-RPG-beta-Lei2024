///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 14a - RPG Beta - ECE 205 - Spring 2025
//
///
/// @file    Battle.cpp
/// @author  Leihani-Taylor Tabanera <lei2022@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Battle.hpp"


Battle::Battle(std::vector<PlayerCharacter*> adventureParty, PlayerCharacter* enemy) : adventureParty(adventureParty), enemy(enemy) {}

void Battle::startBattle() {
    while (true) {
        for (size_t i = 0; i < adventureParty.size(); ++i) {
            PlayerCharacter *attacker = adventureParty[i];

            if (attacker->getHealth() <= 0) {
                continue;
            }

            std::cout << attacker->getName() << "'s turn!" << std::endl;

            attacker->performAction(false);

            int damage = 0;
            damage = attacker->getDamage(); // checks if the attacker does damage to the target
            if (damage > 0) {
                enemy->receiveDamage(damage); // if damage is done, the target's health is reduced
            }
            attacker->setDamage(0); // resets damage back to 0

            int healing = 0;
            healing = attacker->getHealthRestored(); // checks if the attacker
            if (healing > 0) {
                attacker->receiveHealthRestored(healing);
            }
            attacker->setHealthRestored(0); // resets healing back to 0

            if (enemy->getHealth() <= 0) {
                std::cout << enemy->getName() << "'s Remaining Health: 0" << "\n";
            } else {
                std::cout << enemy->getName() << "'s Remaining Health: " << enemy->getHealth() << "\n";
            }
            std::cout << "-----------------------------------" << std::endl;

            if (enemy->getHealth() <= 0) {
                std::cout << "The battle is over! The adventure team is victorious!" << std::endl;
                std::cout << "-----------------------------------" << std::endl;
                break;
            }
        }

        if (enemy->getHealth() <= 0) {
            break;
        }

        // enemy's turn
        std::cout << "Enemy's Turn!" << std::endl;
        int randomTarget;
        randomTarget = rand() % adventureParty.size();
        PlayerCharacter *enemyTarget = adventureParty[randomTarget];

        while (enemyTarget->getHealth() <= 0) {
            randomTarget = rand() % adventureParty.size();
            PlayerCharacter *enemyTarget = adventureParty[randomTarget];
        }

        int damage = 0;
        enemy->performAction(true);
        damage = enemy->getDamage();
        if (damage > 0) {
            enemyTarget->receiveDamage(damage); // if damage is done, the target's health is reduced
        }
        enemy->setDamage(0); // resets damage back to 0

        if (enemyTarget->getHealth() <= 0) {
            std::cout << enemyTarget->getName() << "'s Remaining Health: 0" << "\n";
        } else {
            std::cout << enemyTarget->getName() << "'s Remaining Health: " << enemyTarget->getHealth() << "\n";
        }
        std::cout << "-----------------------------------" << std::endl;

        // checks how many characters are alive after every turn
        int aliveCount = 0;
        PlayerCharacter *lastAlive = nullptr;
        for (PlayerCharacter *pc: adventureParty) {
            if (pc->getHealth() > 0) {
                aliveCount++;
                lastAlive = pc;
            }
        }

        if (aliveCount == 0) {
            std::cout << "The battle is concluded. The enemy has slained the adventure party." << std::endl;
            std::cout << "-----------------------------------" << std::endl;
            break;
        }
    }
}
