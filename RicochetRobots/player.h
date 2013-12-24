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

#define KEY_ESC_ALT 27

bool checkForObstacle(GameState *state, Direction direction);
bool moveCurrentRobot(GameState *state, Direction direction);
void moveCurrentRobotWhilePossible(GameState *state, Direction direction);

Direction getRandomDirection(GameState *state);
Direction waitForDirection(GameState *state);

bool isRobotOnObjective(Robot *robot, GameBoard *gameBoard);
Player* getRobotOnObjective(GameState *state);

char* getRobotStringColor(int color);
int getColorPairFromRobotColor(int color);

#endif
