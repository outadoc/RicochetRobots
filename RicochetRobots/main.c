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
    use_default_colors();
    
    //paires de couleurs
    init_pair(ROBOT_RED, COLOR_WHITE, COLOR_RED);
    init_pair(ROBOT_BLUE, COLOR_WHITE, COLOR_BLUE);
    init_pair(ROBOT_GREEN, COLOR_WHITE, COLOR_GREEN);
    init_pair(ROBOT_GREY, COLOR_BLACK, COLOR_YELLOW);
    init_pair(10, COLOR_MAGENTA, COLOR_WHITE);
    
    timeout(-1);
    keypad(stdscr, TRUE);
    
    //exécution de la boucle principale
    return start();
}