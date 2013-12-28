//
//  utils.h
//  RicochetRobots
//
//  Created by Baptiste on 29/11/13.
//  Copyright (c) 2013 Baptiste Candellier. All rights reserved.
//

#ifndef RicochetRobots_utils_h
#define RicochetRobots_utils_h

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>

int rand_between(int min, int max);
int max_strlen(char **str, int n);
int mkpath(char* file_path, unsigned int mode);
void getPrefsPath(char path[], char fileName[]);

#endif
