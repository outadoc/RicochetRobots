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
#include "game.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"


void displayMainMenu();
void listBuiltInBoards();
void displayLogo();

void displayGameBoard(GameBoard *board);
void refreshDisplay(GameState *currentGame);

void askForPlayersInfo(Player players[]);
int askForGameBoard(GameBoard *board);
void askForSinglePlayerUsername(Player robots[]);

char* getAnsiColorFromRobotColor(int color);

#endif
