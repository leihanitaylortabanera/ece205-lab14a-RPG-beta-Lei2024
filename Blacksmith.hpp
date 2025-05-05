///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 14a - RPG Beta - ECE 205 - Spring 2025
//
///
/// @file    Blacksmith.cpp
/// @author  Leihani-Taylor Tabanera <lei2022@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "GameCharacter.hpp"
#include "PlayerCharacterETHAN.hpp"

class Blacksmith : public PlayerCharacter {
private:
    // Unique attributes for blacksmith
    int craftsmanship;
    int metal_manipulation;
public:
    // Constructor
    Blacksmith(const std::string& newName, int newRace);

    // Action Methods
    void weaponStrike();
    void moltenBlast();

    // performAction override
    void performAction(bool isEnemy) override;

    //greet override
    void greet() const override;

    // display stats of the blacksmith
    void displayBlacksmithStats();

    // rollDiceToPerformAction
    int static blacksmithRollDice(int lower, int upper);
};

