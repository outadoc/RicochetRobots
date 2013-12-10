//
//  board.c
//  RicochetRobots
//
//  Created by Baptiste on 28/'L'/'B'.
//  Copyright (c) 20'B' outadev. All rights reserved.
//
// Fonctions et structures relatives au plateau de jeu
//

#include <stdio.h>

#include "board.h"

//
// Retourne un plateau prédéfini à l'indice fourni.
//
GameBoard getBuiltInBoardAtIndex(int index) {
    GameBoard builtinBoards[] = {
    {
            //premier plateau
            .obstacles = {
                //placement des murs du premier plateau
                {'E', 'E', 'E', 'R', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'R', 'E', 'E', 'E', 'E'},
                {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'W', 'E', 'E'},
                {'E', 'E', 'E', 'E', 'E', 'Y', 'E', 'E', 'E', 'Y', 'E', 'E', 'E', 'E', 'E', 'E'},
                {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'B'},
                {'B', 'E', 'X', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'},
                {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'V', 'E', 'E', 'E', 'E', 'E', 'E', 'V', 'E'},
                {'E', 'W', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'U', 'L', 'E', 'E', 'E'},
                {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'W', 'X', 'E', 'E', 'E', 'E', 'E', 'E', 'E'},
                {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'V', 'Y', 'E', 'E', 'E', 'E', 'E', 'E', 'E'},
                {'E', 'E', 'E', 'E', 'V', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'X', 'E', 'E', 'B'},
                {'B', 'E', 'E', 'E', 'E', 'E', 'W', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'},
                {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'},
                {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'X', 'E', 'W', 'E', 'E', 'E', 'E', 'E', 'E'},
                {'E', 'X', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'V', 'E'},
                {'E', 'E', 'E', 'Y', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'Y', 'E', 'E', 'E', 'E'},
                {'E', 'E', 'E', 'E', 'E', 'R', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'L', 'E'}
            },
            .robotsPos = {
                {.x = 0, .y = 3},
                {.x = 12, .y = 10},
                {.x = 11, .y = 11},
                {.x = 8, .y = 4}
            },
            .objectivesPos = {
                {.x = 10, .y = 15},
                {.x = -1, .y = -1},
                {.x = -1, .y = -1},
                {.x = -1, .y = -1}
            }
        },
        {
            //deuxième plateau
            .obstacles = {
                //placement des murs du deuxième plateau
                {'E', 'E', 'E', 'E', 'R', 'E', 'E', 'E', 'E', 'E', 'E', 'L', 'E', 'E', 'E', 'E'},
                {'E', 'E', 'Y', 'E', 'E', 'E', 'E', 'E', 'E', 'V', 'E', 'E', 'E', 'E', 'E', 'E'},
                {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'X', 'E'},
                {'E', 'V', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'},
                {'B', 'E', 'E', 'E', 'E', 'E', 'W', 'E', 'E', 'E', 'Y', 'E', 'E', 'E', 'E', 'B'},
                {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'},
                {'E', 'E', 'E', 'E', 'E', 'X', 'E', 'E', 'E', 'E', 'E', 'E', 'W', 'E', 'E', 'E'},
                {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'W', 'X', 'E', 'E', 'E', 'E', 'E', 'E', 'E'},
                {'E', 'E', 'E', 'E', 'E', 'Y', 'E', 'V', 'Y', 'E', 'E', 'E', 'E', 'E', 'E', 'E'},
                {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'X', 'E', 'E', 'B'},
                {'E', 'E', 'X', 'E', 'E', 'E', 'E', 'E', 'E', 'V', 'E', 'E', 'E', 'E', 'E', 'E'},
                {'B', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'},
                {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'},
                {'E', 'E', 'E', 'E', 'W', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'Y', 'E'},
                {'E', 'E', 'E', 'E', 'E', 'E', 'V', 'E', 'E', 'W', 'E', 'E', 'E', 'E', 'E', 'E'},
                {'E', 'E', 'E', 'E', 'R', 'E', 'E', 'E', 'E', 'E', 'R', 'E', 'E', 'E', 'E', 'E'}
            },
            .robotsPos = {
                {.x = 0, .y = 11},
                {.x = 0, .y = 9},
                {.x = 12, .y = 8},
                {.x = 12, .y = 15}
            },
            .objectivesPos = {
                {.x = 6, .y = 5},
                {.x = -1, .y = -1},
                {.x = -1, .y = -1},
                {.x = -1, .y = -1}
            }
        },
        {
            //deuxième plateau
            .obstacles = {
                //placement des murs du deuxième plateau
                {'E', 'E', 'E', 'R', 'E', 'E', 'E', 'E', 'E', 'E', 'R', 'E', 'E', 'E', 'E', 'E'},
                {'E', 'E', 'E', 'E', 'E', 'E', 'V', 'E', 'E', 'X', 'E', 'E', 'E', 'E', 'E', 'E'},
                {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'Y', 'E', 'E', 'E', 'E'},
                {'E', 'X', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'B'},
                {'E', 'E', 'E', 'E', 'E', 'W', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'},
                {'E', 'E', 'Y', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'V', 'E', 'E'},
                {'B', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'},
                {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'W', 'X', 'E', 'W', 'E', 'E', 'E', 'E', 'E'},
                {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'V', 'Y', 'E', 'E', 'E', 'E', 'E', 'E', 'E'},
                {'E', 'E', 'E', 'E', 'V', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'X', 'E', 'E', 'B'},
                {'E', 'X', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'V', 'E', 'E', 'E', 'E', 'E', 'E'},
                {'B', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'},
                {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'},
                {'E', 'E', 'E', 'E', 'E', 'E', 'W', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'B', 'L'},
                {'E', 'E', 'Y', 'E', 'E', 'E', 'E', 'E', 'E', 'W', 'E', 'E', 'E', 'E', 'E', 'E'},
                {'E', 'E', 'E', 'R', 'E', 'E', 'E', 'E', 'E', 'E', 'R', 'E', 'E', 'E', 'E', 'E'}
            },
            .robotsPos = {
                {.x = 10, .y = 11},
                {.x = 10, .y = 13},
                {.x = 6, .y = 3},
                {.x = 4, .y = 9}
            },
            .objectivesPos = {
                {.x = 5, .y = 13},
                {.x = -1, .y = -1},
                {.x = -1, .y = -1},
                {.x = -1, .y = -1}
            }
        }
    };
    
    if(index >= 0 && index < BUILTIN_BOARDS_COUNT) {
        return builtinBoards[index];
    } else {
        return getEmptyGameBoard();
    }
}

//
// Retourne un plateau vide.
//
GameBoard getEmptyGameBoard() {
    return (GameBoard) {
        //deuxième plateau
        .obstacles = {
            //placement des murs du deuxième plateau
            {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'},
            {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'},
            {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'},
            {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'},
            {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'},
            {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'},
            {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'},
            {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'},
            {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'},
            {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'},
            {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'},
            {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'},
            {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'},
            {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'},
            {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'},
            {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'},
        },
        .robotsPos = {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
        .objectivesPos = {{0, 0}, {-1, -1}, {0, 0}, {0, 0}}
    };
}

//
// Demande à l'utilisateur de choisir un plateau de jeu.
// Retourne 0 si tout se passe bien.
//
int askForGameBoard(GameBoard *board) {
    int choice = 0;
    bool retry = false;
    
    choice = displayGameBoardSelectionMenu(false);
    
    //tant qu'on n'a pas choisi une option correcte du menu
    do {
        retry = false;
        
        switch (choice) {
            case 1: {
                int boardNb = 0;
                
                do {
                    boardNb = displayGameBoardList(false);
                } while(boardNb < 1 || boardNb > BUILTIN_BOARDS_COUNT);
                
                *board = getBuiltInBoardAtIndex(boardNb - 1);
                break;
            }
            case 2: {
                char path[MAX_LVL_PATH_SIZE];
                askForLevelPath(path);
                return loadBoardFromFile(board, path);
                break;
            }
            case 0:
                return 1;
                break;
            default:
                choice = displayGameBoardSelectionMenu(true);
                retry = true;
                break;
        }
    } while(retry);
    
    return 0;
}

//
// Charge un plateau de jeu depuis le chemin fourni.
// En cas d'erreur, on l'affiche sur la sortie standard et on retourne un code 1. Sinon, on retourne 0.
//
int loadBoardFromFile(GameBoard *board, const char path[]) {
    if(board == NULL) return 1;
    
    //on initialise le plateau avec des valeurs par défaut
    *board = getEmptyGameBoard();
    
    FILE *level = fopen(path, "r");
    
    if(level == NULL) {
        //si le fichier n'a pas pu être chargé
        perror("Erreur");
        
        //on ferme le fichier
        fclose(level);
        return 1;
    }
    
    char c;
    int i = 0;
    
    //on vérifie si on n'est pas à la fin du fichier et on recule le curseur comme si de rien n'était
    while((c = getc(level)) != EOF) {
        ungetc(c, level);
        
        //on s'attend à trouver 5 lignes pour les coordonnées des 4 robots + celles de l'objectif
        while(i < MAX_PLAYERS_COUNT * 2) {
            //on vérifie si la ligne n'est pas vide ou un commentaire et on recule le curseur comme si de rien n'était
            if((c = getc(level)) != '#' && c != '\n') {
                ungetc(c, level);
                
                char id;
                
                int rbtX, rbtY;
                int objX, objY;
                
                int tabIndex = 0;
                
                //on récupère l'id du robot et ses coordonnées
                fscanf(level, "%c %d %d, %d %d\n", &id, &rbtX, &rbtY, &objX, &objY);
                
                switch (id) {
                    case 'R':
                        //robot rouge
                        tabIndex = ROBOT_RED;
                        break;
                    case 'V':
                        //robot vert
                        tabIndex = ROBOT_GREEN;
                        break;
                    case 'B':
                        //robot bleu
                        tabIndex = ROBOT_BLUE;
                        break;
                    case 'G':
                        //robot gris
                        tabIndex = ROBOT_GREY;
                        break;
                    default:
                        //on ferme le fichier
                        fclose(level);
                        printw("Caractère coordonnée interdit : %c\n", id);
                        return 1;
                        break;
                }
                
                board->robotsPos[tabIndex].x = rbtX;
                board->robotsPos[tabIndex].y = rbtY;
                
                board->objectivesPos[tabIndex].x = objX;
                board->objectivesPos[tabIndex].y = objY;

                i++;
            } else {
                //si c'est un commentaire, on ignore la ligne complète
                while((c = getc(level)) != '\n');
            }
        }
        
        i = 0;
        
        //pour chaque ligne du tableau
        while(i < BOARD_SIZE) {
            if((c = getc(level)) == '\n') {
                //si la ligne est vide, on ne fait rien
                continue;
            } else if(c == '#') {
                //si c'est un commentaire, on ignore la ligne complète
                while((c = getc(level)) != '\n');
            } else {
                int j;
                
                //on recule le curseur
                ungetc(c, level);
                
                //pour chaque caractère de la ligne
                for(j = 0; j < BOARD_SIZE; j++) {
                    //on récupère le caractère sous le curseur
                    char cell = getc(level);
                    
                    //si le caractère est invalide, on annule
                    if(cell != CELL_EMPTY
                       && cell != CELL_WALL_BOTTOM
                       && cell != CELL_WALL_LEFT
                       && cell != CELL_WALL_RIGHT
                       && cell != CELL_WALL_TOP
                       && cell != CELL_WALL_BOTTOM_LEFT
                       && cell != CELL_WALL_BOTTOM_RIGHT
                       && cell != CELL_WALL_TOP_LEFT
                       && cell != CELL_WALL_TOP_RIGHT) {
                        //on ferme le fichier
                        fclose(level);
                        printw("Caractère obstacle interdit : %c\n", cell);
                        return 1;
                    } else {
                        //si tout va bien, on insère le caractère dans le tableau
                        board->obstacles[i][j] = cell;
                    }
                }
                
                //on récupère le caractère de fin de ligne
                getc(level);
                
                //on passe à la ligne suivante
                i++;
            }
        }
        
        //on ferme le fichier
        fclose(level);
        printw("Chargement OK\n");
        
        return 0;
    }
    
    //j'ai nommé ce point du code le "confusion ending".
    //on ferme le fichier
    fclose(level);
    printw("WTF\n");
    return 0;
}
