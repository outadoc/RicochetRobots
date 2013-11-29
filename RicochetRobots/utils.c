//
//  utils.c
//  RicochetRobots
//
//  Created by Baptiste on 29/11/13.
//  Copyright (c) 2013 outadev. All rights reserved.
//

#include <stdio.h>
#include <string.h>

void removeCarriageReturn(char str[]) {
    size_t ln = strlen(str) - 1;
    if (str[ln] == '\n') str[ln] = '\0';
}