//
//  main.c
//  RicochetRobots
//
//  Created by Baptiste on 28/10/13.
//  Copyright (c) 2013 outadev. All rights reserved.
//

#include <stdio.h>
#include "game.h"

int main(int argc, const char * argv[]) {
    //initialisation du seed pour la PRNG
    srand((int) time(NULL));
    
    //exécution de la boucle principale
    return start();
}