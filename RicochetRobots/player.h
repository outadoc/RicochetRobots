//
//  player.h
//  RicochetRobots
//
//  Created by Baptiste on 28/10/13.
//  Copyright (c) 2013 outadev. All rights reserved.
//

#ifndef RicochetRobots_player_h
#define RicochetRobots_player_h

#include "board.h"

//constantes pour la couleur des robots
#define ROBOT_RED 0
#define ROBOT_GREEN 1
#define ROBOT_BLUE 2
#define ROBOT_GREY 3

#define DIRECTION_UP 0
#define DIRECTION_RIGHT 1
#define DIRECTION_DOWN 2
#define DIRECTION_LEFT 3

typedef struct {
    int robotColor;
    char username[15];
    int score;
    Coords position;
} Player;

int checkForObstacle(Player *robot, GameBoard *board, int direction);
int movePlayer(Player *player, GameBoard *board, int direction);
void movePlayerWhilePossible(Player *player, GameBoard *board, int direction);
int isPlayerOnObjective(Player *player, GameBoard *gameBoard);

char* getRobotStringColor(int color);

#endif
