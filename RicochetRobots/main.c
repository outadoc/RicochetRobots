//
//  main.c
//  RicochetRobots
//
//  Created by Baptiste on 28/10/13.
//  Copyright (c) 2013 Baptiste Candellier. All rights reserved.
//

#include <ncurses.h>
#include "game.h"

int main(int argc, const char * argv[]) {
    //initialisation du seed pour la PRNG
    srand((int) time(NULL));
    
    //initalisation de ncurses
    initDisplay();
    
    //exécution de la boucle principale
    start();
    
    //fin du mode curses
    clear();
    endwin();
    
    return EXIT_SUCCESS;
}