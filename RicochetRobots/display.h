//
//  display.h
//  RicochetRobots
//
//  Created by Baptiste on 28/10/13.
//  Copyright (c) 2013 outadev. All rights reserved.
//

#ifndef RicochetRobots_display_h
#define RicochetRobots_display_h

#include "game.h"
#include "player.h"
#include "struct.h"
#include "utils.h"

int displayMainMenu(bool error);
int displayGameBoardSelectionMenu(bool error);
int displayGameBoardList();

bool wantsToReplay();
void displayMenuError();

void listBuiltInBoards();
void displayLogo();
void displayGameEnding(int score, Player *winner, GameState *state);

void displayGameBoard(GameState *state);
void refreshDisplay(GameState *currentGame);

void askForPlayersInfo(Player players[]);
void askForSinglePlayerUsername(Player robots[]);
void askForLevelPath(char path[]);

char* getAnsiColorFromRobotColor(int color);

#endif
