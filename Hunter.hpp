///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 14a - RPG Beta - ECE 205 - Spring 2025
//
///
/// @file    Hunter.cpp
/// @author  Leihani-Taylor Tabanera <lei2022@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "GameCharacter.hpp"
#include "PlayerCharacterETHAN.hpp"

class Hunter : public PlayerCharacter {
private:
    // Unique attributes for Hunter
    int stealth;
    int aim_accuracy;

public:
    // Constructor
    Hunter(const std::string& name, int newRace);

    // Action methods
    void arrowBarrage();
    void backstabShot();

    // performAction override
    void performAction(bool isEnemy) override;

    // greet override
    void greet() const override;

    // print out stats of the hunter
    void displayHunterStats();

    // rollDiceToPerformAction
    int static hunterRollDice(int lower, int upper);
};