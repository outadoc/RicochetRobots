//
//  board.h
//  RicochetRobots
//
//  Created by Baptiste on 28/10/13.
//  Copyright (c) 2013 outadev. All rights reserved.
//

#ifndef RicochetRobots_board_h
#define RicochetRobots_board_h

#define BOARD_SIZE 16

//structure du plateau de jeu
struct GameBoard {
    char data[BOARD_SIZE][BOARD_SIZE];
};

typedef struct GameBoard GameBoard;

void loadBoardFromFile(char board[][], const char path[]);
void getRandomBoard(char board[][]);
void getBuiltInBoard(int id);

#endif
