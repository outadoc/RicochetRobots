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
#define CELL_EMPTY 0
#define CELL_OBJECTIVE 1

//mur gauche
#define CELL_WALL_LEFT 10
//mur haut
#define CELL_WALL_TOP 11
//mur droite
#define CELL_WALL_RIGHT 12
//mur bas
#define CELL_WALL_BOTTOM 13


//structure du plateau de jeu
typedef struct {
    char obstacles[BOARD_SIZE][BOARD_SIZE];
    char initialRobotsPlacement[BOARD_SIZE][BOARD_SIZE];
} GameBoard;

void loadBoardFromFile(GameBoard board, const char path[]);
void getRandomBoard(GameBoard board);

GameBoard getBuiltInBoardAtIndex(int index);

#endif
