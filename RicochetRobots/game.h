//
//  game.h
//  RicochetRobots
//
//  Created by Baptiste on 28/10/13.
//  Copyright (c) 2013 outadev. All rights reserved.
//

#ifndef RicochetRobots_game_h
#define RicochetRobots_game_h

#include "interface.h"
#include "board.h"
#include "struct.h"

//un petit typedef pour que le compilateur ne sorte pas un warning au niveau du qsort
typedef int (*compfn)(const void*, const void*);

int start();
int handleMainMenu();

int startSinglePlayer();
int startMultiPlayer();

int sortByGoal(Player *a, Player *b);

#endif
