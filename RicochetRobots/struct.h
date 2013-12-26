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

#define BOARD_SIZE              16  //taille d'un plateau de jeu
#define BUILTIN_BOARDS_COUNT    3   //nombre de grilles prédéfinies
#define ROBOTS_COUNT            4   //nombre de robots
#define MAX_USERNAME_SIZE       15  //taille maximale d'un pseudo
#define MAX_LVL_PATH_SIZE       300 //taille maximale du chemin d'un fichier niveau
#define MAX_PLAYERS_COUNT       15  //nombre maximal de joueurs

// IDENTIFIANTS DES COULEURS DES ROBOTS //
/****************************************/

#define ROBOT_RED   0
#define ROBOT_GREEN 1
#define ROBOT_BLUE  2
#define ROBOT_GREY  3

// IDENTIFIANTS DES DIRECTIONS //
/****************************************/

#define DIRECTION_UP    0   //haut
#define DIRECTION_RIGHT 1   //droite
#define DIRECTION_DOWN  2   //bas
#define DIRECTION_LEFT  3   //gauche

// IDENTIFIANTS DES CASES //
/****************************************/

//cases spéciales
#define CELL_EMPTY              'E' //case vide

//murs simples
#define CELL_WALL_LEFT          'L' //mur à gauche
#define CELL_WALL_TOP           'U' //mur en haut
#define CELL_WALL_RIGHT         'R' //mur à droite
#define CELL_WALL_BOTTOM        'B' //mur en base

//murs en L
#define CELL_WALL_BOTTOM_LEFT   'V' //mur en bas et à gauche
#define CELL_WALL_TOP_LEFT      'W' //mur en haut et à gauche
#define CELL_WALL_TOP_RIGHT     'X' //mur en haut et à droite
#define CELL_WALL_BOTTOM_RIGHT  'Y' //mur en bas et à droite

#define COL_ON_BOT(win, col)         wattron((win), COLOR_PAIR(getColorPairFromRobotColor((col))))
#define COL_OFF_BOT(win, col)        wattroff((win), COLOR_PAIR(getColorPairFromRobotColor((col))))

#define COL_ON_BOT_BG(win, col)         wattron((win), COLOR_PAIR(getBGColorPairFromRobotColor((col))))
#define COL_OFF_BOT_BG(win, col)        wattroff((win), COLOR_PAIR(getBGColorPairFromRobotColor((col))))

// DÉFINITION DES STRUCTURES //
/****************************************/

//structure pour les coordonnées des robots
typedef struct {
    int x;
    int y;
} Coords;

//structure pour décrire les joueurs
typedef struct {
    int score;
    int victoryCount;
    int goal;
    char username[MAX_USERNAME_SIZE];
} Player;

typedef struct {
    int robotColor;
    Coords position;
    int score;
} Robot;

//structure du plateau de jeu
typedef struct {
    char obstacles[BOARD_SIZE][BOARD_SIZE];
    Coords robotsPos[ROBOTS_COUNT];
    Coords objectivesPos[ROBOTS_COUNT];
} GameBoard;

//état du jeu en cours
typedef struct {
    //nombre de tours
    int turnCount;
    //nombre de joueurs
    int playersCount;
    int robotColorToMove;
    
    Player* currentPlayer;
    Player* players;
    
    Robot* currentRobot;
    Robot* robots;
    
    GameBoard* gameBoard;
} GameState;

#endif
