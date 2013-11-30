//
//  player.h
//  RicochetRobots
//
//  Created by Baptiste on 28/10/13.
//  Copyright (c) 2013 outadev. All rights reserved.
//

#ifndef RicochetRobots_player_h
#define RicochetRobots_player_h

#include <unistd.h>

#include "utils.h"
#include "struct.h"
#include "interface.h"

bool checkForObstacle(GameState *state, Direction direction);
bool moveCurrentPlayer(GameState *state, Direction direction);
void moveCurrentPlayerWhilePossible(GameState *state, Direction direction);

Direction getRandomDirection();
Direction waitForDirection();

bool isPlayerOnObjective(Player *player, GameBoard *gameBoard);
Player* getPlayerOnObjective(GameState *state);

char* getRobotStringColor(int color);

#endif
