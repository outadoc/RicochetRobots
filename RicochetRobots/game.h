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

//état du jeu en cours
typedef struct {
    //nombre de tours
    int turnCount;
    //scores
    int scores[4];
    
    //joueur courant
    Player* currentPlayer;
    
    Player* players;
    GameBoard* gameBoard;
    
    //position actuelle des robots
    char currRobotsPos[BOARD_SIZE][BOARD_SIZE];
} GameState;

void startNewGame(GameBoard board);
int waitForDirection();
GameState gameConfig();

#endif
