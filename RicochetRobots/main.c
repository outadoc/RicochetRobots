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
    
    initscr();
    start_color();
    
    //paires de couleurs
    init_pair(ROBOT_RED, -1, COLOR_RED);
    init_pair(ROBOT_BLUE, -1, COLOR_BLUE);
    init_pair(ROBOT_GREEN, -1, COLOR_GREEN);
    init_pair(ROBOT_GREY, -1, COLOR_YELLOW);
    init_pair(10, COLOR_MAGENTA, -1);
    
    attron(COLOR_PAIR(1));
    
    timeout(-1);
    keypad(stdscr, TRUE);
    
    //exécution de la boucle principale
    return start();
}