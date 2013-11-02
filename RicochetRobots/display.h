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
#include "game_state.h"

void displayMainMenu();
void listBuiltInBoards();
void displayLogo();

void displayGameBoard(GameState currentGame);

void askForPlayersInfo(Player players[]);
int askForGameBoard(GameBoard *board);
void askForSinglePlayerUsername(Player robots[]);

#endif
