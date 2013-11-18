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

#define ANSI_COLOR_RESET   "\x1b[0m"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"

#define ANSI_BG_COLOR_RED     "\x1b[41m"
#define ANSI_BG_COLOR_GREEN   "\x1b[42m"
#define ANSI_BG_COLOR_YELLOW  "\x1b[43m"
#define ANSI_BG_COLOR_BLUE    "\x1b[44m"
#define ANSI_BG_COLOR_MAGENTA "\x1b[45m"

void displayMainMenu();
void listBuiltInBoards();
void displayLogo();
void displayGameEnding(int score, Player *winner);

void displayGameBoard(GameState *state);
void refreshDisplay(GameState *currentGame);

void askForPlayersInfo(Player players[]);
int askForGameBoard(GameBoard *board);
void askForSinglePlayerUsername(Player robots[]);

char* getAnsiColorFromRobotColor(int color);

#endif
