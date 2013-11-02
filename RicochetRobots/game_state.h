//
//  game_state.h
//  RicochetRobots
//
//  Created by Baptiste on 28/10/13.
//  Copyright (c) 2013 outadev. All rights reserved.
//

#ifndef RicochetRobots_game_state_h
#define RicochetRobots_game_state_h

#include "player.h"
#include "board.h"

//état du jeu en cours
struct GameState {
    //nombre de tours
    int turnCount;
    
    //joueur courant
    Player* currentPlayer;
    
    Player players[4];
    GameBoard* gameBoard;
    
    //position des robots
    GameBoard robotPositions[BOARD_SIZE][BOARD_SIZE];
};

typedef struct GameState GameState;

void startNewGame(GameBoard board);
GameState gameConfig();

#endif
