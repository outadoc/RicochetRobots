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
#include <string.h>

#include "display.h"
#include "game.h"
#include "player.h"

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
    
    initRobots(players);
    
    for (i = 0; i < 4; i++) {
        printf("Pseudo du joueur %d : ", i+1);
        
        //vidage du buffer
        fseek(stdin, 0, SEEK_END);
        
        //dangereux ça, on risque de se prendre des buffer overflows dans la tronche
        //TODO: rendre secure
        scanf("%s", players[i].username);
    }
}

void askForSinglePlayerUsername(Player robots[])
{
    char username[10];
    int i;
    
    printf("Votre pseudo : ");
    
    //vidage du buffer
    fseek(stdin, 0, SEEK_END);
    
    //dangereux ça, on risque de se prendre des buffer overflows dans la tronche
    //TODO: rendre secure
    scanf("%s", username);
    
    for (i = 0; i < 4; i++) {
        strcpy(username, robots[i].username);
    }
}

int askForGameBoard(GameBoard *board)
{
    int choice = 0, retry = 0;
    
    printf("\nCHOIX DU PLATEAU\n");
    printf("----------------\n\n");
    
    printf("1. Plateau prédéfini\n");
    printf("2. Plateau depuis un fichier\n");
    printf("3. Plateau aléatoire\n");
    printf("0. -- Retour au menu principal\n");
    
    //tant qu'on n'a pas choisi une option correcte du menu
    do {
        retry = 0;
        printf("\nplateau> ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                *board = getBuiltInBoardAtIndex(0);
                break;
            }
            case 0:
                return 1;
                break;
            default:
                printf("Sérieusement ?");
                retry = 1;
                break;
        }
    } while(retry);
    
    return 0;
}

void displayGameBoard(GameState *currentGame)
{
    int i, j;
    
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            if(currentGame->gameBoard->initialRobotsPlacement[i][j] != -1) {
                printf("[%d+%d]", currentGame->gameBoard->data[i][j], currentGame->gameBoard->initialRobotsPlacement[i][j]);
            } else {
                printf("[%d]", currentGame->gameBoard->data[i][j]);
            }
        }
        
        printf("\n");
    }
}
