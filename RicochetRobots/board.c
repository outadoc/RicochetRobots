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

GameBoard getBuiltInBoardAtIndex(int index) {
    GameBoard builtinBoards[] = {
    {
            //premier plateau
            .obstacles = {
                //placement des murs du premier plateau
                {'E', 'E', 'E', 'R', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'R', 'E', 'E', 'E', 'E'},
                {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'R', 'U', 'E', 'E'},
                {'E', 'E', 'E', 'E', 'E', 'B', 'L', 'E', 'E', 'B', 'L', 'E', 'E', 'E', 'E', 'E'},
                {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'B'},
                {'B', 'E', 'U', 'L', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'},
                {'E', 'E', 'E', 'E', 'E', 'E', 'R', 'B', 'E', 'E', 'E', 'E', 'E', 'R', 'B', 'E'},
                {'R', 'U', 'E', 'E', 'E', 'E', 'E', 'B', 'B', 'E', 'E', 'U', 'L', 'E', 'E', 'E'},
                {'E', 'E', 'E', 'E', 'E', 'E', 'R', 'E', 'E', 'L', 'E', 'E', 'E', 'E', 'E', 'E'},
                {'E', 'E', 'E', 'E', 'E', 'E', 'R', 'E', 'E', 'L', 'E', 'E', 'E', 'E', 'E', 'E'},
                {'E', 'E', 'E', 'R', 'B', 'E', 'E', 'U', 'U', 'E', 'E', 'E', 'U', 'L', 'E', 'B'},
                {'B', 'E', 'E', 'E', 'E', 'R', 'U', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'O'},
                {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'B', 'E', 'B', 'E', 'E', 'E', 'E', 'E', 'E'},
                {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'R', 'E', 'L', 'E', 'E', 'E', 'E', 'E', 'E'},
                {'E', 'U', 'L', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'R', 'B', 'E'},
                {'E', 'E', 'E', 'B', 'L', 'E', 'E', 'E', 'E', 'E', 'E', 'B', 'L', 'E', 'E', 'E'},
                {'E', 'E', 'E', 'E', 'E', 'R', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'L', 'E'},
            },
            .robotsPosition = {
                {.x = 0, .y = 3},
                {.x = 12, .y = 10},
                {.x = 11, .y = 11},
                {.x = 8, .y = 4}
            }
        },
        {
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
            .robotsPosition = {
                {.x = 0, .y = 3},
                {.x = 12, .y = 10},
                {.x = 11, .y = 11},
                {.x = 8, .y = 4}
            }
        }
    };
    
    if(index >= 0 && index < BUILTIN_BOARDS_COUNT) {
        return builtinBoards[index];
    } else {
        return getEmptyGameBoard();
    }
}

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
        .robotsPosition = {
            {.x = 0, .y = 0},
            {.x = 0, .y = 0},
            {.x = 0, .y = 0},
            {.x = 0, .y = 0}
        }
    };
}

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
                loadBoardFromFile(board, path);
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

void loadBoardFromFile(GameBoard *board, const char path[]) {
    if(board == NULL) return;
    
    //on initialise le plateau avec des valeurs par défaut
    *board = getEmptyGameBoard();
    
    FILE *level = fopen(path, "r");
    
    if(level == NULL) {
        //si le fichier n'a pas pu être chargé
        perror("Erreur : ");
        
        //on ferme le fichier
        fclose(level);
        return;
    }
    
    char c;
    int i = 0;
    
    //on vérifie si on n'est pas à la fin du fichier et on recule le curseur comme si de rien n'était
    while((c = getc(level)) != EOF) {
        ungetc(c, level);
        
        //on s'attend à trouver 4 lignes pour les coordonnées des 4 robots
        while(i < MAX_PLAYERS_COUNT) {
            //on vérifie si la ligne n'est pas vide ou un commentaire et on recule le curseur comme si de rien n'était
            if((c = getc(level)) != '#' && c != '\n') {
                ungetc(c, level);
                
                char robot;
                int x, y;
                
                //on récupère l'id du robot et ses coordonnées
                fscanf(level, "%c %d %d\n", &robot, &x, &y);
                
                switch (robot) {
                    case 'B':
                        board->robotsPosition[0].x = x;
                        board->robotsPosition[0].y = y;
                        break;
                    case 'R':
                        board->robotsPosition[1].x = x;
                        board->robotsPosition[1].y = y;
                        break;
                    case 'V':
                        board->robotsPosition[2].x = x;
                        board->robotsPosition[2].y = y;
                        break;
                    case 'G':
                        board->robotsPosition[3].x = x;
                        board->robotsPosition[3].y = y;
                        break;
                    default:
                        //on ferme le fichier
                        fclose(level);
                        return;
                        break;
                }

                i++;
            } else {
                //si c'est un commentaire, on ignore la ligne complète
                while((c = getc(level)) != '\n');
            }
        }
        
        i = 0;
        
        //pour chaque ligne
        while(i < BOARD_SIZE) {
            //si la ligne n'est pas vide ou un commentaire
            if((c = getc(level)) != '#' && c != '\n') {
                int j;
                
                //on recule le curseur
                ungetc(c, level);
                
                //pour chaque caractère de la ligne
                for(j = 0; j < BOARD_SIZE; j++) {
                    //on récupère le caractère sous le curseur
                    char cell = getc(level);
                    
                    //si le caractère est invalide, on annule
                    if(cell != CELL_EMPTY
                       && cell != CELL_OBJECTIVE
                       && cell != CELL_WALL_BOTTOM
                       && cell != CELL_WALL_LEFT
                       && cell != CELL_WALL_RIGHT
                       && cell != CELL_WALL_TOP) {
                        //on ferme le fichier
                        fclose(level);
                        return;
                    } else {
                        //si tout va bien, on insère le caractère dans le tableau
                        board->obstacles[i][j] = cell;
                    }
                }
                
                //on récupère le caractère de fin de ligne
                getc(level);
                
                //on passe à la ligne suivante
                i++;
            } else {
                //si c'est un commentaire, on ignore la ligne complète
                while((c = getc(level)) != '\n');
            }
        }
        
        //on ferme le fichier
        fclose(level);
        printf("Chargement OK\n");
        
        return;
    }
    
    //on ferme le fichier
    fclose(level);
}

