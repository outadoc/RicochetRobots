//
//  player.h
//  RicochetRobots
//
//  Created by Baptiste on 28/10/13.
//  Copyright (c) 2013 Baptiste Candellier. All rights reserved.
//

#ifndef RicochetRobots_player_h
#define RicochetRobots_player_h

#include <unistd.h>

#include "utils.h"
#include "struct.h"
#include "interface.h"

bool checkForObstacle(GameState *state, Direction direction);
bool moveCurrentRobot(GameState *state, Direction direction);
void moveCurrentRobotWhilePossible(GameState *state, Direction direction);

Direction getRandomDirection(GameState *state);
Direction waitForDirection(GameState *state);

bool isRobotOnObjective(Robot *robot, GameBoard *gameBoard);
bool areAllRobotsOnTheirObjectives(Robot robots[], GameBoard *gameBoard);

char* getRobotStringColor(int color);
int getColorPairFromRobotColor(int color);
int getBGColorPairFromRobotColor(int color);

int sortByGoal(Player *a, Player *b);
int sortPlayersByScore(Player *a, Player *b);

#endif
