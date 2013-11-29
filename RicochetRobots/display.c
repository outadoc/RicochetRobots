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

int displayMainMenu(bool error) {
    if(!error) {
        displayLogo();
        
        printf("MENU PRINCIPAL\n");
        printf("--------------\n\n");
        
        printf("1. Partie solo\n");
        printf("2. Partie solo VS ordinateur\n");
        printf("3. Partie multijoueur\n");
        printf("0. -- Quitter\n");
    } else {
        displayMenuError();
    }
    
    int choice = 0;
        
    printf("\nmenu> ");
    scanf("%d", &choice);
    fseek(stdin, 0, SEEK_END);
    
    return choice;
}

int displayGameBoardSelectionMenu(bool error) {
    if(!error) {
        printf("\nCHOIX DU PLATEAU\n");
        printf("----------------\n\n");
        
        printf("1. Plateau prédéfini\n");
        printf("2. Plateau depuis un fichier\n");
        printf("3. Plateau aléatoire\n");
        printf("0. -- Retour au menu principal\n");
    } else {
        displayMenuError();
    }
    
    int choice = 0;
    
    printf("\nplateau> ");
    scanf("%d", &choice);
    fseek(stdin, 0, SEEK_END);
    
    return choice;
}

int displayGameBoardList() {
    int boardNb = 0;
    
    printf("Numéro du plateau à charger (entre 1 et %d) : ", BUILTIN_BOARDS_COUNT);
    scanf("%d", &boardNb);
    
    return boardNb;
}

void displayMenuError() {
    printf("Woops. Mauvaise option.");
}

void displayGameEnding(int score, Player *winner, GameState *state) {
    if(state == NULL) return;
    
    int i;
    
    printf("\n------------------------------------\n");
    printf("Partie terminée !\n");
    printf("Gagnant : %s a déplacé le robot %s%s%s sur l'objectif\n", winner->username, getAnsiColorFromRobotColor(winner->robotColor), getRobotStringColor(winner->robotColor), ANSI_COLOR_RESET);
    printf("\nScore total : %d coups\n\n", score);
    
    for(i = 0; i < MAX_PLAYERS_COUNT; i++) {
        printf("Score de %s%s%s : %d coups\n", getAnsiColorFromRobotColor(state->players[i].robotColor), getRobotStringColor(state->players[i].robotColor), ANSI_COLOR_RESET, state->players[i].score);
    }
    
    printf("------------------------------------\n\n");
}

bool wantsToReplay() {
    char answer = '\0';
    
    //vidage du buffer
    while (getchar() != '\n');
    
    printf("\nVoulez-vous rejouer ? (O/n) ");
    answer = fgetc(stdin);
    
    //si on veut rejouer, retourner 1, sinon 0
    if(answer == 'o' || answer == 'O') {
        return true;
    } else {
        return false;
    }
}

void askForPlayersInfo(Player players[]) {
    if(players == NULL) return;
    
    int i;
    
    for (i = 0; i < MAX_PLAYERS_COUNT; i++) {
        printf("Pseudo du joueur %d : ", i+1);
        
        //on récupère 14 caractères (+1 pour le \0) dans username
        fgets(players[i].username, MAX_USERNAME_SIZE - 1, stdin);
        
        //enlève le \n de fin de chaîne
        removeCarriageReturn(players[i].username);
    }
}

void askForSinglePlayerUsername(Player robots[]) {
    if(robots == NULL) return;
    
    int i;
    char username[MAX_USERNAME_SIZE];
    
    printf("Votre pseudo : ");
    //vidage du buffer
    fseek(stdin, 0, SEEK_END);
    
    //on récupère 14 caractères (+1 pour le \0) dans username
    fgets(username, MAX_USERNAME_SIZE - 1, stdin);
    
    //enlève le \n de fin de chaîne
    removeCarriageReturn(username);
    
    for (i = 0; i < MAX_PLAYERS_COUNT; i++) {
        if(!robots[i].isBot) strcpy(robots[i].username, username);
        else sprintf(robots[i].username, "CPU%d", i);
    }
}

void askForLevelPath(char path[]) {
    printf("Entrez le chemin du fichier niveau : ");
    
    fseek(stdin, 0, SEEK_END);
    
    //on récupère 14 caractères (+1 pour le \0) dans username
    fgets(path, MAX_LVL_PATH_SIZE - 1, stdin);
    
    //enlève le \n de fin de chaîne
    removeCarriageReturn(path);
}

void displayGameBoard(GameState *state) {
    if(state == NULL) return;
    
    int i, j;
    
    for (i = 0; i < BOARD_SIZE; i++) {
        if(i == 0) {
            printf("\n+");
            
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
            int k;
            bool hasContent = false;
            
            for (k = 0; k < MAX_PLAYERS_COUNT; k++) {
                //on vérifie, pour chaque robot, si ses coordonnées correspondent à celles de la case actuelle
                if(state->players[k].position.x == i && state->players[k].position.y == j) {
                    hasContent = true;
                    
                    if(state->gameBoard->obstacles[i][j] == CELL_OBJECTIVE) {
                        printf("%s%s[@]%s", getAnsiColorFromRobotColor(k), ANSI_BG_COLOR_MAGENTA, ANSI_COLOR_RESET);
                    } else {
                        printf("%s[@]%s", getAnsiColorFromRobotColor(k), ANSI_COLOR_RESET);
                    }
                    
                }
            }
            
            //si la case n'a pas encore de contenu (et donc pas de robot) et que c'est une case objectif
            if(!hasContent && state->gameBoard->obstacles[i][j] == CELL_OBJECTIVE) {
                hasContent = true;
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
    if(currentGame == NULL) return;
    
    displayGameBoard(currentGame);
    
    printf("\n-----------------------------\n");
    printf("Tour %d\n", currentGame->turnCount);
    printf("Joueur actuel : %s%s%s (%s)\n", getAnsiColorFromRobotColor(currentGame->currentPlayer->robotColor), getRobotStringColor(currentGame->currentPlayer->robotColor), ANSI_COLOR_RESET, currentGame->currentPlayer->username);
    printf("Score : %d\n",
           currentGame->players[0].score
           + currentGame->players[1].score
           + currentGame->players[2].score
           + currentGame->players[3].score);
    printf("-----------------------------\n");
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
