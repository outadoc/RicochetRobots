//
//  game.h
//  RicochetRobots
//
//  Created by Baptiste on 28/10/13.
//  Copyright (c) 2013 outadev. All rights reserved.
//

#ifndef RicochetRobots_game_h
#define RicochetRobots_game_h

#define VERSION "0.1"

#define KEY_UP 'z'
#define KEY_LEFT 'q'
#define KEY_DOWN 's'
#define KEY_RIGHT 'd'

#include "player.h"
#include "board.h"

int start();
int handleMainMenu();
int wantsToReplay();

void startNewGame(GameBoard board);
int waitForDirection();
GameState gameConfig();

#endif
