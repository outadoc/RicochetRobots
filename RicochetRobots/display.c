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
    
    printf("MENU PRINCIPAL\n");
    printf("--------------\n\n");
    
    printf("1. Partie solo\n");
    printf("2. Partie multi\n");
    printf("0. -- Quitter\n");
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

void askForPlayersInfo(Player players[])
{
    int i;
    
    players[0].robotColor = ROBOT_RED;   //FORCE ROUGE !
    players[1].robotColor = ROBOT_GREEN; //FORCE VERTE !
    players[2].robotColor = ROBOT_BLUE;  //FORCE BLEUE !
    players[3].robotColor = ROBOT_GREY;  //FORCE... arf
    
    for (i = 0; i < 4; i++) {
        printf("Pseudo du joueur %d : ", i+1);
        
        //vidage du buffer
        fseek(stdin, 0, SEEK_END);
        scanf("%s", players[i].username);
    }
}

GameBoard askForGameBoard()
{
    int choice = 0;
    GameBoard board;
    
    printf("CHOIX DU PLATEAU\n");
    printf("----------------\n\n");
    
    printf("1. Plateau prédéfini");
    printf("2. Plateau depuis un fichier");
    printf("3. Plateau aléatoire");
    printf("0. -- Retour au menu principal");
    
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            
            break;
        default:
            break;
    }
    
    return board;
}
