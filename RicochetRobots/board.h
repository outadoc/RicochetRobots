//
//  board.h
//  RicochetRobots
//
//  Created by Baptiste on 28/10/13.
//  Copyright (c) 2013 outadev. All rights reserved.
//

#ifndef RicochetRobots_board_h
#define RicochetRobots_board_h

//taille d'un plateau de jeu
#define BOARD_SIZE 16
//nombre de grilles prédéfinies
#define BUILTIN_BOARDS_COUNT 2

//constantes pour la valeur des cases
#define CELL_EMPTY 'E'
#define CELL_OBJECTIVE 'O'

//mur gauche
#define CELL_WALL_LEFT 'L'
//mur haut
#define CELL_WALL_TOP 'U'
//mur droite
#define CELL_WALL_RIGHT 'R'
//mur bas
#define CELL_WALL_BOTTOM 'B'


//structure du plateau de jeu
typedef struct {
    char obstacles[BOARD_SIZE][BOARD_SIZE];
    char initialRobotsPlacement[BOARD_SIZE][BOARD_SIZE];
} GameBoard;

void loadBoardFromFile(GameBoard board, const char path[]);
void getRandomBoard(GameBoard board);

GameBoard getBuiltInBoardAtIndex(int index);

#endif
