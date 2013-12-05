//
//  struct.h
//  RicochetRobots
//
//  Created by Baptiste on 23/11/13.
//  Copyright (c) 2013 outadev. All rights reserved.
//

#ifndef RicochetRobots_struct_h
#define RicochetRobots_struct_h

#include <stdbool.h>

// TYPEDEFS PRATIQUES
/****************************************/

typedef int Direction;  //la direction est un entier

// PROPRIÉTÉS GLOBALES //
/****************************************/

//version du jeu
#define VERSION "0.1a"

// TAILLE CONSTANTES //
/****************************************/

#define BOARD_SIZE 16           //taille d'un plateau de jeu
#define BUILTIN_BOARDS_COUNT 3  //nombre de grilles prédéfinies
#define MAX_PLAYERS_COUNT 4     //nombre maximal de joueurs
#define MAX_USERNAME_SIZE 15    //taille maximale d'un pseudo
#define MAX_LVL_PATH_SIZE 300   //taille maximale du chemin d'un fichier niveau

// IDENTIFIANTS DES COULEURS DES ROBOTS //
/****************************************/

#define ROBOT_RED 1
#define ROBOT_GREEN 2
#define ROBOT_BLUE 3
#define ROBOT_GREY 4

// IDENTIFIANTS DES DIRECTIONS //
/****************************************/

#define DIRECTION_UP 0      //haut
#define DIRECTION_RIGHT 1   //droite
#define DIRECTION_DOWN 2    //bas
#define DIRECTION_LEFT 3    //gauche

// IDENTIFIANTS DES CASES //
/****************************************/

#define CELL_EMPTY 'E'       //case vide
#define CELL_OBJECTIVE 'O'   //case objectif

#define CELL_WALL_LEFT 'L'   //mur à gauche
#define CELL_WALL_TOP 'U'    //mur en haut
#define CELL_WALL_RIGHT 'R'  //mur à droite
#define CELL_WALL_BOTTOM 'B' //mur en base

// DÉFINITION DES STRUCTURES //
/****************************************/

//structure pour les coordonnées des robots
typedef struct {
    int x;
    int y;
} Coords;

//structure pour décrire les joueurs
typedef struct {
    int robotColor;
    char username[MAX_USERNAME_SIZE];
    int score;
    Coords position;
    bool isBot;
} Player;

//structure du plateau de jeu
typedef struct {
    char obstacles[BOARD_SIZE][BOARD_SIZE];
    Coords robotsPosition[MAX_PLAYERS_COUNT];
} GameBoard;

//état du jeu en cours
typedef struct {
    //nombre de tours
    int turnCount;
    
    //joueur courant
    Player* currentPlayer;
    Player* players;
    
    GameBoard* gameBoard;
    
    //position actuelle des robots
    char currRobotsPos[BOARD_SIZE][BOARD_SIZE];
} GameState;

#endif
