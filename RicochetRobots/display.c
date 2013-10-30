//
//  display.c
//  RicochetRobots
//
//  Created by Baptiste on 28/10/13.
//  Copyright (c) 2013 outadev. All rights reserved.
//
// Fonctions et structures relatives à l'affichage
//

#include <stdio.h>
#include "display.h"
#include "game.h"

void displayMainMenu()
{
    displayLogo();
    
    printf("1. Partie solo\n");
    printf("2. Partie multi\n");
    printf("0. Quitter\n");
}

void displayLogo()
{
    printf("    ____  ______________  ________  ______________\n");
    printf("   / __ \\/  _/ ____/ __ \\/ ____/ / / / ____/_  __/\n");
    printf("  / /_/ // // /   / / / / /   / /_/ / __/   / /\n");
    printf(" / _, _// // /___/ /_/ / /___/ __  / /___  / /\n");
    printf("/_/ ||||__||||__||||__||||__|||_|||||||_/ /_/\n");
    printf("   / __ \\/ __ \\/ __ )/ __ \\/_  __/ ___/\n");
    printf("  / /_/ / / / / __  / / / / / /  \\__ \n");
    printf(" / _, _/ /_/ / /_/ / /_/ / / /  ___/ /\n");
    printf("/_/ |_|\\____/_____/\\____/ /_/  /____/    v%s\n\n", VERSION);
    
}