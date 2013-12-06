//
//  main.c
//  RicochetRobots
//
//  Created by Baptiste on 28/10/13.
//  Copyright (c) 2013 outadev. All rights reserved.
//

#include <ncurses.h>
#include "game.h"

int main(int argc, const char * argv[]) {
    //initialisation du seed pour la PRNG
    srand((int) time(NULL));
    
    //initalisation de ncurses
    //écran
    initscr();
    
    //init couleurs
    start_color();
    //utiliser les couleurs par défaut du terminal
    use_default_colors();
    
    //paires de couleurs pour chaque robot
    init_pair(ROBOT_RED, COLOR_WHITE, COLOR_RED);
    init_pair(ROBOT_BLUE, COLOR_WHITE, COLOR_BLUE);
    init_pair(ROBOT_GREEN, COLOR_WHITE, COLOR_GREEN);
    init_pair(ROBOT_GREY, COLOR_BLACK, COLOR_YELLOW);
    
    //autres paires de couleurs
    init_pair(10, COLOR_MAGENTA, COLOR_WHITE);

    //activation des touches fléchées etc.
    keypad(stdscr, true);
    
    //exécution de la boucle principale
    start();
    
    //fin de la fenêtre
    endwin();
    
    return 0;
}