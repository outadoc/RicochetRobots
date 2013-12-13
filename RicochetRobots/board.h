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
Coords getRandomCoords();
GameBoard getBuiltInBoardAtIndex(int index);

GameBoard getEmptyGameBoard();

int askForGameBoard(GameBoard *board);

#endif
