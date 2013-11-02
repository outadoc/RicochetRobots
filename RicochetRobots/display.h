//
//  display.h
//  RicochetRobots
//
//  Created by Baptiste on 28/10/13.
//  Copyright (c) 2013 outadev. All rights reserved.
//

#ifndef RicochetRobots_display_h
#define RicochetRobots_display_h

#include "board.h"
#include "player.h"

void displayMainMenu();
void listBuiltInBoards();
void displayLogo();

void askForPlayersInfo(Player players[]);
GameBoard askForGameBoard();

#endif
