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
    init_pair(1, COLOR_WHITE, COLOR_RED);
    init_pair(2, COLOR_WHITE, COLOR_GREEN);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_BLACK, COLOR_YELLOW);
    
    //autres paires de couleurs
    //case objectif
    init_pair(10, COLOR_MAGENTA, COLOR_WHITE);

    //activation des touches fléchées etc.
    keypad(stdscr, true);
    
    set_tabsize(4);
    
    //exécution de la boucle principale
    start();
    
    //fin du mode curses
    clear();
    endwin();
    
    return 0;
}