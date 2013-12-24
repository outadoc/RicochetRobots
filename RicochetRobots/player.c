//
//  player.c
//  RicochetRobots
//
//  Created by Baptiste on 28/10/13.
//  Copyright (c) 2013 outadev. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "player.h"

//
// Vérifie si on peut déplacer le joueur courant dans la direction fournie.
// Retourne true s'il y a un obstacle, false sinon.
//
bool checkForObstacle(GameState *state, Direction direction) {
    if(state == NULL || direction > 3) return true;
    
    int i;
    
    //on créé deux structures de coordonnées
    //une pour la position actuelle (juste une copie pratique), et une pour la position cible
    Coords currPos = state->currentRobot->position, target = currPos;
    
    //pour chaque direction, on vérifie si il y a un mur qui nous bloque et on renvoie true le cas échéant
    switch (direction) {
        case DIRECTION_DOWN:
            target.x++;
            
            if(target.x > BOARD_SIZE - 1
                    || state->gameBoard->obstacles[currPos.x][currPos.y] == CELL_WALL_BOTTOM
                    || state->gameBoard->obstacles[currPos.x][currPos.y] == CELL_WALL_BOTTOM_LEFT
                    || state->gameBoard->obstacles[currPos.x][currPos.y] == CELL_WALL_BOTTOM_RIGHT
                    || state->gameBoard->obstacles[target.x][target.y] == CELL_WALL_TOP
                    || state->gameBoard->obstacles[target.x][target.y] == CELL_WALL_TOP_LEFT
                    || state->gameBoard->obstacles[target.x][target.y] == CELL_WALL_TOP_RIGHT) return true;
            break;
        case DIRECTION_LEFT:
            target.y--;
            
            if(target.y < 0
                    || state->gameBoard->obstacles[currPos.x][currPos.y] == CELL_WALL_LEFT
                    || state->gameBoard->obstacles[currPos.x][currPos.y] == CELL_WALL_BOTTOM_LEFT
                    || state->gameBoard->obstacles[currPos.x][currPos.y] == CELL_WALL_TOP_LEFT
                    || state->gameBoard->obstacles[target.x][target.y] == CELL_WALL_RIGHT
                    || state->gameBoard->obstacles[target.x][target.y] == CELL_WALL_BOTTOM_RIGHT
                    || state->gameBoard->obstacles[target.x][target.y] == CELL_WALL_TOP_RIGHT) return true;
            break;
        case DIRECTION_RIGHT:
            target.y++;
            
            if(target.y > BOARD_SIZE - 1
                    || state->gameBoard->obstacles[currPos.x][currPos.y] == CELL_WALL_RIGHT
                    || state->gameBoard->obstacles[currPos.x][currPos.y] == CELL_WALL_BOTTOM_RIGHT
                    || state->gameBoard->obstacles[currPos.x][currPos.y] == CELL_WALL_TOP_RIGHT
                    || state->gameBoard->obstacles[target.x][target.y] == CELL_WALL_LEFT
                    || state->gameBoard->obstacles[target.x][target.y] == CELL_WALL_TOP_LEFT
                    || state->gameBoard->obstacles[target.x][target.y] == CELL_WALL_BOTTOM_LEFT) return true;
            break;
        case DIRECTION_UP:
            target.x--;
            
            if(target.x < 0
                    || state->gameBoard->obstacles[currPos.x][currPos.y] == CELL_WALL_TOP
                    || state->gameBoard->obstacles[currPos.x][currPos.y] == CELL_WALL_TOP_LEFT
                    || state->gameBoard->obstacles[currPos.x][currPos.y] == CELL_WALL_TOP_RIGHT
                    || state->gameBoard->obstacles[target.x][target.y] == CELL_WALL_BOTTOM
                    || state->gameBoard->obstacles[target.x][target.y] == CELL_WALL_BOTTOM_LEFT
                    || state->gameBoard->obstacles[target.x][target.y] == CELL_WALL_BOTTOM_RIGHT) return true;
            break;
    }
    
    //on vérifie aussi si un autre joueur nous bloque
    for(i = 0; i < ROBOTS_COUNT; i++) {
        if(state->robots[i].robotColor != state->currentRobot->robotColor
            && state->robots[i].position.x == target.x
            && state->robots[i].position.y == target.y) {
           return true;
        }
    }
    
    return false;
}

//
// Déplace le joueur courant dans la direction fournie.
// Retourne true si on a pu le déplacer, false sinon.
//
bool moveCurrentRobot(GameState *state, Direction direction) {
    if(state == NULL || direction > 3) return false;
    
    if(!checkForObstacle(state, direction)) {
        switch (direction) {
            case DIRECTION_DOWN:
                state->currentRobot->position.x++;
                break;
            case DIRECTION_LEFT:
                state->currentRobot->position.y--;
                break;
            case DIRECTION_RIGHT:
                state->currentRobot->position.y++;
                break;
            case DIRECTION_UP:
                state->currentRobot->position.x--;
                break;
        }
        
        //on endort le programme pendant 100 millisecondes
        usleep(100 * 1000);
        refreshGameDisplay(state);
        
        return true;
    }
    
    return false;
}

//
// Déplace l'utilisateur courant dans la direction fournie, jusqu'à ce qu'il rencontre un obstacle.
//
void moveCurrentRobotWhilePossible(GameState *state, Direction direction) {
    if(state == NULL || direction > 3) return;
    
    //tant qu'on peut déplacer le robot courant, on le fait
    while(moveCurrentRobot(state, direction));
    
    //on augmente les compteurs
    state->currentPlayer->score++;
    state->currentRobot->score++;
    state->turnCount++;
}

//
// Retourne une direction aléatoire.
//
Direction getRandomDirection(GameState *state) {
    //repos de 1 seconde avant le déplacement
    usleep(1000 * 1000);
    
    int dir = 0;
    
    //tant qu'il y a un obstacle dans la direction choisie aléatoirement
    do {
        //on choisit un nombre compris entre 0 et 4
        //(avec l'arrondi à l'unité, le nombre est finalement 0, 1, 2 ou 3)
        dir = rand_between(0, 4);
    } while(checkForObstacle(state, dir));
    
    return dir;
}

//
// Demande à l'utilisateur dans quelle direction il souhaite se déplacer.
//
Direction waitForDirection(GameState *state) {
    int c;
    
    do {
        noecho();
        c = getch();
        echo();
        
        //on fait un premier switch:
        //si on ne demande pas directement une direction, il faudra traiter la demande, mais sans bouger le robot (on continue donc la boucle)
        switch(c) {
            case 'r':
            case 'R':
                state->currentRobot = &state->robots[ROBOT_RED];
                refreshGameDisplay(state);
                break;
            case 'b':
            case 'B':
                state->currentRobot = &state->robots[ROBOT_BLUE];
                refreshGameDisplay(state);
                break;
            case 'v':
            case 'V':
                state->currentRobot = &state->robots[ROBOT_GREEN];
                refreshGameDisplay(state);
                break;
            case 'g':
            case 'G':
                state->currentRobot = &state->robots[ROBOT_GREY];
                refreshGameDisplay(state);
                break;
            case KEY_RESIZE:
                //si on a redimensionné le terminal, on rafraîchit l'affichage
                refreshGameDisplay(state);
                break;
        }
        
    } while(c != KEY_DOWN && c != KEY_LEFT && c != KEY_RIGHT && c != KEY_UP && c != KEY_ESC_ALT);
    
    switch (c) {
        case KEY_DOWN:
            return DIRECTION_DOWN;
            break;
        case KEY_LEFT:
            return DIRECTION_LEFT;
            break;
        case KEY_RIGHT:
            return DIRECTION_RIGHT;
            break;
        case KEY_UP:
            return DIRECTION_UP;
            break;
        case KEY_ESC_ALT:
            return -1;
            break;
    }
    
    return 0;
}

//
// Retourne la chaîne de caractère correspondant à la couleur du robot fournie.
//
char* getRobotStringColor(int color) {
    switch (color) {
        case ROBOT_RED:
            return "ROUGE";
            break;
        case ROBOT_GREEN:
            return "VERT";
            break;
        case ROBOT_BLUE:
            return "BLEU";
            break;
        case ROBOT_GREY:
            return "GRIS";
            break;
        default:
            return "inconnu";
            break;
    }
}

//
// Retourne la paire de couleurs ncurses correspondant au robot.
//
int getBGColorPairFromRobotColor(int color) {
    switch (color) {
        case ROBOT_RED:
            return 1;
            break;
        case ROBOT_GREEN:
            return 2;
            break;
        case ROBOT_BLUE:
            return 3;
            break;
        case ROBOT_GREY:
            return 4;
            break;
        default:
            return -1;
            break;
    }
}

//
// Retourne la paire de couleurs ncurses correspondant au robot.
//
int getColorPairFromRobotColor(int color) {
    return 10 + getBGColorPairFromRobotColor(color);
}

//
// Vérifie si un joueur est sur l'objectif.
// Retourne true s'il l'est, false sinon.
//
bool isRobotOnObjective(Robot *robot, GameBoard *gameBoard) {
    if(robot == NULL || gameBoard == NULL) return false;
    
    int i;
    
    for (i = 0; i < ROBOTS_COUNT; i++) {
        if(gameBoard->objectivesPos[i].x == robot->position.x
           && gameBoard->objectivesPos[i].y == robot->position.y) return true;
    }
    
    return false;
}

//
// Retourne le joueur qui est sur l'objectif.
// Retourne NULL si aucun ne l'est.
//
Player* getRobotOnObjective(GameState *state) {
    if(state == NULL) return NULL;
    
    int i;
    
    for (i = 0; i < ROBOTS_COUNT; i++) {
        if(isRobotOnObjective(&state->robots[i], state->gameBoard)) return &state->players[i];
    }
    
    return NULL;
}
