//
//  utils.c
//  RicochetRobots
//
//  Created by Baptiste on 29/11/13.
//  Copyright (c) 2013 outadev. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#include "utils.h"

//
// Supprime le retour chariot à la fin d'une chaîne de caractères.
// Utile avec fgets.
//
void removeCarriageReturn(char str[]) {
    size_t ln = strlen(str) - 1;
    if (str[ln] == '\n') str[ln] = '\0';
}

//
// Génère un entier pseudo aléatoire compris entre min et max.
//
int rand_between(int min, int max) {
    return rand() % (max - min) + min;
}

int max_strlen(char **str, int n) {
    int i;
    int maxlen = 0;
    
    for(i = 0; i < n; i++) {
        int currlen = (int) strlen(str[i]);
        if(currlen > maxlen) maxlen = currlen;
    }
    
    return maxlen;
}