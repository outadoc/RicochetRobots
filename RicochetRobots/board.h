//
//  board.h
//  RicochetRobots
//
//  Created by Baptiste on 28/10/13.
//  Copyright (c) 2013 outadev. All rights reserved.
//

#ifndef RicochetRobots_board_h
#define RicochetRobots_board_h

#include <errno.h>

#include "struct.h"
#include "interface.h"

int loadBoardFromFile(GameBoard *board, const char path[]);
void getRandomBoard(GameBoard *board);
Coords getRandomCoords(GameBoard *board);
GameBoard getBuiltInBoardAtIndex(int index);

bool areCoordsInList(Coords coords_t[], Coords coords);
GameBoard getEmptyGameBoard();
void resetMap(GameState *state);

int askForGameBoard(GameBoard *board);

#endif
