//
//  utils.c
//  RicochetRobots
//
//  Created by Baptiste on 29/11/13.
//  Copyright (c) 2013 outadev. All rights reserved.
//

#include <stdio.h>
#include <string.h>

//
// Supprime le retour chariot à la fin d'une chaîne de caractères.
// Utile avec fgets.
//
void removeCarriageReturn(char str[]) {
    size_t ln = strlen(str) - 1;
    if (str[ln] == '\n') str[ln] = '\0';
}