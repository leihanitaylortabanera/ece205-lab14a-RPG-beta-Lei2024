///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 12b - Game Character Class Part III - ECE 205 - Spring 2025
//
///
/// @file    Bard.hpp
/// @author  Leihani-Taylor Tabanera <lei2022@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include <vector>
#include "GameCharacter.hpp"
#include "PlayerCharacterETHAN.hpp"

class Bard : public PlayerCharacter {
private:
    // Unique attributes for Bard
    int charisma;
    int wisdom;
public:
    // Constructor
    Bard(const std::string& newName, int newRace);

    // Action Methods
    void healingMelody();
    void counterPerformance();

    // performAction override
    virtual void performAction() override;

    // greet override
    void greet() const override;

    // display stats of the bard
    void displayBardStats();

    // rollDiceToPerformAction
    int static bardRollDice(int lower, int upper);
};
