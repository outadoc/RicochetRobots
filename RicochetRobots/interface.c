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

#include "interface.h"

//
// Affiche le logo du jeu sur la sortie standard.
//
void displayLogo() {
    clear();
    
    printw("    ____  ______________  ________  ______________\n");
    printw("   / __ \\/  _/ ____/ __ \\/ ____/ / / / ____/_  __/\n");
    printw("  / /_/ // // /   / / / / /   / /_/ / __/   / /\n");
    printw(" / _, _// // /___/ /_/ / /___/ __  / /___  / /\n");
    printw("/_/ ||||__||||__||||__||||__|||_|||||||_/ /_/\n");
    printw("   / __ \\/ __ \\/ __ )/ __ \\/_  __/ ___/\n");
    printw("  / /_/ / / / / __  / / / / / /  \\__ \n");
    printw(" / _, _/ /_/ / /_/ / /_/ / / /  ___/ /\n");
    printw("/_/ |_|\\____/_____/\\____/ /_/  /____/    v%s\n\n", VERSION);
    
    refresh();
}

//
// Affiche le menu principal du jeu sur la sortie standard.
// Si error vaut true, on affiche une erreur à la place du menu.
//
int displayMainMenu(bool error) {
    if(!error) {
        displayLogo();
        
        printw("MENU PRINCIPAL\n");
        printw("--------------\n\n");
        
        printw("1. Partie solo\n");
        printw("2. Partie solo VS ordinateur\n");
        printw("3. Partie multijoueur\n");
        printw("0. -- Quitter\n");
    } else {
        displayMenuError();
    }
    
    int choice = 0;
    
    printw("\nmenu> ");
    refresh();
    
    do {
        //on récupère un chiffre
        //on ne veut PAS réagir sur un KEY_RESIZE (redimensionnement du terminal)
        choice = getch();
    } while(choice == KEY_RESIZE);
    
    printw("\n");
    
    //on retourne le vrai chiffre (en soustrayant la valeur de '0'
    return choice - '0';
}

//
// Affiche le menu de sélection du plateau de jeu sur la sortie standard.
// Si error vaut true, on affiche une erreur à la place du menu.
//
int displayGameBoardSelectionMenu(bool error) {
    if(!error) {
        clear();
        
        printw("\nCHOIX DU PLATEAU\n");
        printw("----------------\n\n");
        
        printw("1. Plateau prédéfini\n");
        printw("2. Plateau depuis un fichier\n");
        printw("3. Plateau aléatoire\n");
        printw("0. -- Retour au menu principal\n");
    } else {
        displayMenuError();
    }
    
    int choice = 0;
    
    printw("\nplateau> ");
    refresh();
    
    do {
        //on récupère un chiffre
        //on ne veut PAS réagir sur un KEY_RESIZE (redimensionnement du terminal)
        choice = getch();
    } while(choice == KEY_RESIZE);
    
    printw("\n");
    
    //on retourne le vrai chiffre (en soustrayant la valeur de '0'
    return choice - '0';
}

//
// Demande à l'utilisateur quel plateau de jeu prédéfini il souhaite charger.
//
int displayGameBoardList() {
    int choice = 0;
    
    printw("Numéro du plateau à charger (entre 1 et %d) : ", BUILTIN_BOARDS_COUNT);
    refresh();
    
    do {
        //on récupère un chiffre
        //on ne veut PAS réagir sur un KEY_RESIZE (redimensionnement du terminal)
        choice = getch();
    } while(choice == KEY_RESIZE);
    
    printw("\n");
    
    //on retourne le vrai chiffre (en soustrayant la valeur de '0'
    return choice - '0';
}

//
// Affiche une erreur de choix de menu sur la sortie standard.
//
void displayMenuError() {
    printw("Woops. Mauvaise option.");
    refresh();
}

//
// Affiche le tableau de scores de fin de jeu sur la sortie standard.
//
void displayGameEnding(int score, Player *winner, GameState *state) {
    if(state == NULL) return;
    
    int i;
    
    clear();
    
    printw("\n------------------------------------\n");
    printw("Partie terminée !\n");
    
    printw("Gagnant : %s a déplacé le robot ", winner->username);
    
    COL_ON_BOT(winner->robotColor);
    printw("%s", getRobotStringColor(winner->robotColor));
    COL_OFF_BOT(winner->robotColor);
    
    printw(" sur l'objectif\n");
    
    printw("\nScore total : %d coups\n\n", score);
    
    for(i = 0; i < MAX_PLAYERS_COUNT; i++) {
        printw("Score de ");
        COL_ON_BOT(state->players[i].robotColor);
        printw("%s", getRobotStringColor(state->players[i].robotColor));
        COL_OFF_BOT(state->players[i].robotColor);
        printw(" : %d coups\n", state->players[i].score);
    }
    
    printw("------------------------------------\n\n");
    
    refresh();
}

//
// Demande à l'utilisateur s'il souhaite rejouer.
//
bool wantsToReplay() {
    char answer = '\0';
        
    printw("\nVoulez-vous rejouer ? (O/n) ");
    refresh();
    
    answer = getch();
    
    //si on veut rejouer, retourner 1, sinon 0
    if(answer == 'o' || answer == 'O') {
        return true;
    } else {
        return false;
    }
}

//
// Demande le pseudo de chaque joueur, un par un.
//
void askForPlayersInfo(Player players[]) {
    if(players == NULL) return;
    
    int i;
    
    for (i = 0; i < MAX_PLAYERS_COUNT; i++) {
        printw("Pseudo du joueur %d : ", i+1);
        
        refresh();
        
        //on récupère 14 caractères (+1 pour le \0) dans Player.username
        getstr(players[i].username);
    }
}

//
// Demande le pseudo du joueur et le copie dans chaque robot.
//
void askForSinglePlayerUsername(Player robots[]) {
    if(robots == NULL) return;
    
    int i;
    char username[MAX_USERNAME_SIZE];
    
    printw("Votre pseudo : ");
    refresh();
    
    //on récupère 14 caractères (+1 pour le \0) dans username
    getstr(username);
    
    for (i = 0; i < MAX_PLAYERS_COUNT; i++) {
        if(!robots[i].isBot) strcpy(robots[i].username, username);
        else sprintf(robots[i].username, "CPU%d", i);
    }
}

//
// Demande au joueur le chemin du niveau à charger.
//
void askForLevelPath(char path[]) {
    printw("Entrez le chemin du fichier niveau : ");
    refresh();
    
    //on récupère 14 caractères (+1 pour le \0) dans path
    getstr(path);
}

//
// Affiche le plateau de jeu.
//
void displayGameBoard(GameState *state) {
    if(state == NULL) return;
    
    int i, j;
    
    for (i = 0; i < BOARD_SIZE; i++) {
        if(i == 0) {
            printw("\n+");
            
            for (j = 0; j < BOARD_SIZE; j++) {
                //première ligne ? on affiche une ligne de "-"
                printw("---+");
            }
        }
        
        //début de ligne
        printw("\n|");
        
        for (j = 0; j < BOARD_SIZE; j++) {
            //on affiche les murs verticaux
            //si il y a quelque-chose dans la case actuelle
            int k;
            bool hasContent = false;
            
            for (k = 0; k < MAX_PLAYERS_COUNT; k++) {
                //on vérifie, pour chaque robot, si ses coordonnées correspondent à celles de la case actuelle
                if(state->players[k].position.x == i && state->players[k].position.y == j) {
                    int l;
                    bool hasObjective = false;
                    
                    hasContent = true;
                    
                    COL_ON_BOT(state->players[k].robotColor);
                    
                    for (l = 0; l < MAX_PLAYERS_COUNT; l++) {
                        //si on a un objectif ici
                        if(state->gameBoard->objectivesPos[l].x == i && state->gameBoard->objectivesPos[l].y == j) {
                            hasObjective = true;
                            break;
                        }
                    }
                    
                    if(hasObjective) {
                        printw("[X]");
                    } else {
                        printw("   ");
                    }
                    
                    COL_OFF_BOT(state->players[k].robotColor);
                    
                }
            }
            
            //si la case n'a pas encore de contenu (et donc pas de robot) et que c'est une case objectif
            for (k = 0; k < MAX_PLAYERS_COUNT; k++) {
                if(!hasContent && state->gameBoard->objectivesPos[k].x == i && state->gameBoard->objectivesPos[k].y == j) {
                    hasContent = true;
                    
                    attron(COLOR_PAIR(10));
                    printw("[X]");
                    attroff(COLOR_PAIR(10));
                    
                    break;
                }
            }
            
            //si il n'y a rien dans la case, on affiche un espace
            if(!hasContent) printw("   ");
            
            //si on doit afficher un mur à droite : si il y a un mur à droite dans la case actuelle ou un mur à gauche dans la case directement à droite
            //on n'oublie pas de prendre en compte les murs en L
            if(state->gameBoard->obstacles[i][j] == CELL_WALL_RIGHT
               || state->gameBoard->obstacles[i][j] == CELL_WALL_BOTTOM_RIGHT
               || state->gameBoard->obstacles[i][j] == CELL_WALL_TOP_RIGHT
               || (j < BOARD_SIZE && state->gameBoard->obstacles[i][j+1] == CELL_WALL_LEFT)
               || (j < BOARD_SIZE && state->gameBoard->obstacles[i][j+1] == CELL_WALL_BOTTOM_LEFT)
               || (j < BOARD_SIZE && state->gameBoard->obstacles[i][j+1] == CELL_WALL_TOP_LEFT)
               || j == BOARD_SIZE - 1) {
                printw("|");
            } else {
                printw(" ");
            }
        }
        
        printw("\n+");
        
        for (j = 0; j < BOARD_SIZE; j++) {
            //on affiche les murs horizontaux, d'une façon analogue aux murs verticaux
            if(state->gameBoard->obstacles[i][j] == CELL_WALL_BOTTOM
               || state->gameBoard->obstacles[i][j] == CELL_WALL_BOTTOM_LEFT
               || state->gameBoard->obstacles[i][j] == CELL_WALL_BOTTOM_RIGHT
               || (i < BOARD_SIZE && state->gameBoard->obstacles[i+1][j] == CELL_WALL_TOP)
               || (i < BOARD_SIZE && state->gameBoard->obstacles[i+1][j] == CELL_WALL_TOP_LEFT)
               || (i < BOARD_SIZE && state->gameBoard->obstacles[i+1][j] == CELL_WALL_TOP_RIGHT)
               || i == BOARD_SIZE - 1) {
                printw("---+");
            } else if(i == BOARD_SIZE/2-1 && j == BOARD_SIZE/2-1) {
                printw("    ");
            } else {
                printw("   +");
            }
        }
    }
    
    printw("\n");
}

//
// Rafraîchit l'affichage pendant une partie.
// Affiche le plateau de jeu, ainsi qu'un résumé des informations sur la partie en cours.
//
void refreshDisplay(GameState *currentGame) {
    if(currentGame == NULL) return;
    
    clear();
    
    displayGameBoard(currentGame);
    
    printw("\n-----------------------------\n");
    printw("Tour %d\n", currentGame->turnCount);
    
    printw("Joueur actuel : ");
    
    COL_ON_BOT(currentGame->currentPlayer->robotColor);
    printw("%s", getRobotStringColor(currentGame->currentPlayer->robotColor));
    COL_OFF_BOT(currentGame->currentPlayer->robotColor);
    
    printw(" (%s)\n", currentGame->currentPlayer->username);
    
    printw("Score : %d\n",
           currentGame->players[0].score
           + currentGame->players[1].score
           + currentGame->players[2].score
           + currentGame->players[3].score);
    
    printw("-----------------------------\n");
    
    refresh();
}
