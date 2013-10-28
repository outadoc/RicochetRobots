//
//  game_state.h
//  RicochetRobots
//
//  Created by Baptiste on 28/10/13.
//  Copyright (c) 2013 outadev. All rights reserved.
//

#ifndef RicochetRobots_game_state_h
#define RicochetRobots_game_state_h

//état du jeu en cours
struct GameState {
    //joueur courant
    Player* currentPlayer;
    //position des robots
    Board robotPositions[BOARD_SIZE][BOARD_SIZE];
    //nombre de tours
    int turnCount;
};

typedef struct GameState GameState;

void startNewGame(GameBoard board);

#endif
