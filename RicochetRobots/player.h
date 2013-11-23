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

//état du jeu en cours
typedef struct {
    //nombre de tours
    int turnCount;
    
    //joueur courant
    Player* currentPlayer;
    Player* players;
    
    GameBoard* gameBoard;
    
    //position actuelle des robots
    char currRobotsPos[BOARD_SIZE][BOARD_SIZE];
} GameState;

int checkForObstacle(GameState *state, int direction);
int moveCurrentPlayer(GameState *state, int direction);
void moveCurrentPlayerWhilePossible(GameState *state, int direction);
void randomPlayerMove(GameState *state);

int isPlayerOnObjective(Player *player, GameBoard *gameBoard);
int isAnyPlayerOnObjective(GameState *state);

char* getRobotStringColor(int color);

#endif
