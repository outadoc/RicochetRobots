//
//  player.h
//  RicochetRobots
//
//  Created by Baptiste on 28/10/13.
//  Copyright (c) 2013 outadev. All rights reserved.
//

#ifndef RicochetRobots_player_h
#define RicochetRobots_player_h

#include "struct.h"

int checkForObstacle(GameState *state, int direction);
int moveCurrentPlayer(GameState *state, int direction);
void moveCurrentPlayerWhilePossible(GameState *state, int direction);
void randomPlayerMove(GameState *state);

int isPlayerOnObjective(Player *player, GameBoard *gameBoard);
int isAnyPlayerOnObjective(GameState *state);

char* getRobotStringColor(int color);

#endif
