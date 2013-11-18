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

void displayMainMenu() {
    displayLogo();

    printf("MENU PRINCIPAL\n");
    printf("--------------\n\n");

    printf("1. Partie solo\n");
    printf("2. Partie multi\n");
    printf("0. -- Quitter\n");
}

void displayLogo() {
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

void askForPlayersInfo(Player players[]) {
    int i;

    for (i = 0; i < 4; i++) {

        printf("Pseudo du joueur %d : ", i+1);

        //on récupère 14 caractères (+1 pour le \0) dans username
        fgets(players[i].username, 14, stdin);

        //enlève le \n de fin de chaîne
        size_t ln = strlen(players[i].username) - 1;
        if (players[i].username[ln] == '\n')
            players[i].username[ln] = '\0';
    }
}

void askForSinglePlayerUsername(Player robots[]) {
    char username[15];
    int i;

    printf("Votre pseudo : ");

    //vidage du buffer
    while(getchar()!='\n');

    //on récupère 14 caractères (+1 pour le \0) dans username
    fgets(username, 14, stdin);

    //enlève le \n de fin de chaîne
    size_t ln = strlen(username) - 1;
    if (username[ln] == '\n')
        username[ln] = '\0';

    for (i = 0; i < 4; i++) {
        strcpy(robots[i].username, username);
    }
}

int askForGameBoard(GameBoard *board) {
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
                int boardNb = 0;

                do {
                    printf("Numéro du plateau à charger (entre 1 et %d) : ", BUILTIN_BOARDS_COUNT);
                    scanf("%d", &boardNb);
                } while(boardNb < 1 || boardNb > BUILTIN_BOARDS_COUNT);

                *board = getBuiltInBoardAtIndex(boardNb - 1);
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

void displayGameBoard(GameState *state) {
    int i, j;

    for (i = 0; i < BOARD_SIZE; i++) {
        if(i == 0) {
            printf("+");

            for (j = 0; j < BOARD_SIZE; j++) {
                //première ligne ? on affiche une ligne de "-"
                printf("---+");
            }
        }

        //début de ligne
        printf("\n|");

        for (j = 0; j < BOARD_SIZE; j++) {
            //on affiche les murs verticaux
            //si il y a quelque-chose dans la case actuelle
            int k, hasContent = 0;
            
            for (k = 0; k < 4; k++) {
                //on vérifie, pour chaque robot, si ses coordonnées correspondent à celles de la case actuelle
                if(state->players[k].position.x == i && state->players[k].position.y == j) {
                    hasContent = 1;
                    
                    if(state->gameBoard->obstacles[i][j] == CELL_OBJECTIVE) {
                        printf("%s%s[@]%s", getAnsiColorFromRobotColor(k), ANSI_BG_COLOR_MAGENTA, ANSI_COLOR_RESET);
                    } else {
                        printf("%s[@]%s", getAnsiColorFromRobotColor(k), ANSI_COLOR_RESET);
                    }
                   
                }
            }
            
            //si la case n'a pas encore de contenu (et donc pas de robot) et que c'est une case objectif
            if(!hasContent && state->gameBoard->obstacles[i][j] == CELL_OBJECTIVE) {
                hasContent = 1;
                printf("%s(O)%s", ANSI_BG_COLOR_MAGENTA, ANSI_COLOR_RESET);
            }
            
            //si il n'y a pas de robot dans la case, on affiche un espace
            if(!hasContent) printf("   ");

            //si on doit afficher un mur à droite : si il y a un mur à droite dans la case actuelle ou un mur à gauche dans la case directement à droite
            if(state->gameBoard->obstacles[i][j] == CELL_WALL_RIGHT
               || (j < BOARD_SIZE && state->gameBoard->obstacles[i][j+1] == CELL_WALL_LEFT)
               || j == BOARD_SIZE - 1) {
                printf("|");
            } else {
              printf(" ");
            }
        }

        printf("\n+");

        for (j = 0; j < BOARD_SIZE; j++) {
            //on affiche les murs horizontaux
            if(state->gameBoard->obstacles[i][j] == CELL_WALL_BOTTOM
               || (i < BOARD_SIZE && state->gameBoard->obstacles[i+1][j] == CELL_WALL_TOP)
               || i == BOARD_SIZE - 1) {
                printf("---+");
            } else if(j == BOARD_SIZE -1) {
                printf("   +");
            } else {
                printf("   +");
            }
        }
    }

    printf("\n");
}

void refreshDisplay(GameState *currentGame) {
    printf("\n+++++++++++++++++++++++++++++\n");
    printf("Tour %d\n", currentGame->turnCount);
    printf("Joueur actuel : %s (%s)\n", getRobotStringColor(currentGame->currentPlayer->robotColor), currentGame->currentPlayer->username);
    printf("Score : %d\n",
             currentGame->players[0].score
           + currentGame->players[1].score
           + currentGame->players[2].score
           + currentGame->players[3].score);
    printf("+++++++++++++++++++++++++++++\n\n");

    displayGameBoard(currentGame);
}

char* getAnsiColorFromRobotColor(int color) {
    switch (color) {
        case ROBOT_RED:
            return ANSI_COLOR_RED;
            break;
        case ROBOT_GREEN:
            return ANSI_COLOR_GREEN;
            break;
        case ROBOT_BLUE:
            return ANSI_COLOR_BLUE;
            break;
        case ROBOT_GREY:
            return ANSI_COLOR_YELLOW;
            break;
        default:
            return ANSI_COLOR_RESET;
            break;
    }
}
