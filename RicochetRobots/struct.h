//
//  struct.h
//  RicochetRobots
//
//  Created by Baptiste on 23/11/13.
//  Copyright (c) 2013 outadev. All rights reserved.
//
//  Définition des structures et constantes utiles pour tout le programme
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
#define MAX_LVL_NAME_SIZE       15  //taille maximale du nom d'un niveau
#define MAX_PLAYERS_COUNT       15  //nombre maximal de joueurs
#define MAX_SAVED_SCORES_COUNT  20  //nombre maximal de scores sauvegardés

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

//macros pour rendre l'utilisation des couleurs plus simples avec les robots
//couleur de texte
#define COL_ON_BOT(win, col)         wattron((win), COLOR_PAIR(getColorPairFromRobotColor((col))))
#define COL_OFF_BOT(win, col)        wattroff((win), COLOR_PAIR(getColorPairFromRobotColor((col))))

//couleur de fond
#define COL_ON_BOT_BG(win, col)         wattron((win), COLOR_PAIR(getBGColorPairFromRobotColor((col))))
#define COL_OFF_BOT_BG(win, col)        wattroff((win), COLOR_PAIR(getBGColorPairFromRobotColor((col))))

//un petit typedef pour que le compilateur ne sorte pas un warning au niveau du qsort
typedef int (*compfn)(const void*, const void*);

// DÉFINITION DES STRUCTURES //
/****************************************/

//structure pour les coordonnées des robots
typedef struct {
    int x;
    int y;
} Coords;

//structure pour décrire les joueurs
typedef struct {
    int score;                          //score du joueur
    int victoryCount;                   //nombre de victoires du joueur (multi)
    int goal;                           //objectif de coups pour gagner (multi)
    char username[MAX_USERNAME_SIZE];   //pseudo du joueur
} Player;

//structure pour décrire un high-score
typedef struct {
    int score;                          //le score en question
    char username[MAX_USERNAME_SIZE];   //le pseudo du joueur qui a eu ce score
    char boardName[MAX_LVL_NAME_SIZE];  //le nom du plateau sur lequel ce score a été atteint
} Score;

//structure pour décrire un robot
typedef struct {
    int robotColor;     //couleur du robot
    Coords position;    //position du robot
    int score;          //score du robot
} Robot;

//structure du plateau de jeu
typedef struct {
    char name[MAX_LVL_NAME_SIZE];           //nom du plateau
    char obstacles[BOARD_SIZE][BOARD_SIZE]; //matrice emplacement des obstacles
    Coords robotsPos[ROBOTS_COUNT];         //position des robots
    Coords objectivesPos[ROBOTS_COUNT];     //position des objectifs
} GameBoard;

//état du jeu en cours
typedef struct {
    int turnCount;          //nombre de tours
    int playersCount;       //nombre de joueurs
    int robotColorToMove;   //couleur du robot à déplacer (multi)
    
    Player* currentPlayer;  //joueur courant
    Player* players;        //liste des joueurs
    
    Robot* currentRobot;    //robot courant
    Robot* robots;          //liste des robots
    
    GameBoard* gameBoard;   //plateau de jeu
} GameState;

#endif
