//
//  board.h
//  RicochetRobots
//
//  Created by Baptiste on 28/10/13.
//  Copyright (c) 2013 outadev. All rights reserved.
//

#ifndef RicochetRobots_board_h
#define RicochetRobots_board_h

#include "struct.h"
#include "display.h"

void loadBoardFromFile(GameBoard board, const char path[]);
void getRandomBoard(GameBoard board);
GameBoard getBuiltInBoardAtIndex(int index);

int askForGameBoard(GameBoard *board);

#endif
