//
//  score.h
//  RicochetRobots
//
//  Created by Baptiste on 27/12/13.
//  Copyright (c) 2013 Baptiste Candellier. All rights reserved.
//

#ifndef RicochetRobots_score_h
#define RicochetRobots_score_h

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "struct.h"

int loadScoreBoard(Score scores[]);
void saveScoreBoard(Score scores[], int n);
int registerScore(Score score);
int sortByScore(Score *a, Score *b);

#endif
