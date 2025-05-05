///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 14a - RPG Beta - ECE 205 - Spring 2025
//
///
/// @file    Battle.hpp
/// @author  Leihani-Taylor Tabanera <lei2022@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "PlayerCharacterETHAN.hpp"
#include <vector>

class Battle {
public:
    Battle(std::vector<PlayerCharacter*> adventureParty, PlayerCharacter* enemy);
    void startBattle();
private:
    std::vector<PlayerCharacter*> adventureParty;
    PlayerCharacter* enemy;
};

