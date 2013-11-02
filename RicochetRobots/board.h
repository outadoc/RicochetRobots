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

//constantes pour la valeur des cases
#define CELL_EMPTY 0
#define CELL_OBJECTIVE 1

#define CELL_WALL_SIMPLE_LEFT 10
#define CELL_WALL_SIMPLE_TOP 11
#define CELL_WALL_SIMPLE_RIGHT 12
#define CELL_WALL_SIMPLE_BOTTOM 13

#define CELL_WALL_DOUBLE_TOP_LEFT 20
#define CELL_WALL_DOUBLE_TOP_RIGHT 21
#define CELL_WALL_DOUBLE_BOTTOM_LEFT 22
#define CELL_WALL_DOUBLE_BOTTOM_RIGHT 23

#define CELL_WALL_ALL_SIDES 24


//structure du plateau de jeu
struct GameBoard {
    char data[BOARD_SIZE][BOARD_SIZE];
    char initialRobotsPlacement[BOARD_SIZE][BOARD_SIZE];
};

typedef struct GameBoard GameBoard;

void loadBoardFromFile(GameBoard board, const char path[]);
void getRandomBoard(GameBoard board);

GameBoard* getBuiltInBoards();

#endif
