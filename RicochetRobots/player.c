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
    
    Coords target = {
        .x = state->currentPlayer->position.x,
        .y = state->currentPlayer->position.y
    };
    
    switch (direction) {
        case DIRECTION_DOWN:
            target.x++;
            
            if(target.x > BOARD_SIZE - 1
                    || state->gameBoard->obstacles[target.x-1][target.y] == CELL_WALL_BOTTOM
                    || state->gameBoard->obstacles[target.x][target.y] == CELL_WALL_TOP) return true;
            break;
        case DIRECTION_LEFT:
            target.y--;
            
            if(target.y < 0
                    || state->gameBoard->obstacles[target.x][target.y+1] == CELL_WALL_LEFT
                    || state->gameBoard->obstacles[target.x][target.y] == CELL_WALL_RIGHT) return true;
            break;
        case DIRECTION_RIGHT:
            target.y++;
            
            if(target.y > BOARD_SIZE - 1
                    || state->gameBoard->obstacles[target.x][target.y-1] == CELL_WALL_RIGHT
                    || state->gameBoard->obstacles[target.x][target.y] == CELL_WALL_LEFT) return true;
            break;
        case DIRECTION_UP:
            target.x--;
            
            if(target.x < 0
                    || state->gameBoard->obstacles[target.x+1][target.y] == CELL_WALL_TOP
                    || state->gameBoard->obstacles[target.x][target.y] == CELL_WALL_BOTTOM) return true;
            break;
    }
    
    for(i = 0; i < MAX_PLAYERS_COUNT; i++) {
        if(state->players[i].robotColor != state->currentPlayer->robotColor
            && state->players[i].position.x == target.x
            && state->players[i].position.y == target.y) {
           return true;
        }
    }
    
    return false;
}

//
// Déplace le joueur courant dans la direction fournie.
// Retourne true si on a pu le déplacer, false sinon.
//
bool moveCurrentPlayer(GameState *state, Direction direction) {
    if(state == NULL || direction > 3) return false;
    
    if(!checkForObstacle(state, direction)) {
        switch (direction) {
            case DIRECTION_DOWN:
                state->currentPlayer->position.x++;
                break;
            case DIRECTION_LEFT:
                state->currentPlayer->position.y--;
                break;
            case DIRECTION_RIGHT:
                state->currentPlayer->position.y++;
                break;
            case DIRECTION_UP:
                state->currentPlayer->position.x--;
                break;
        }
        
        //on endort le programme pendant 100 millisecondes
        usleep(100 * 1000);
        refreshDisplay(state);
        
        return true;
    }
    
    return false;
}

//
// Déplace l'utilisateur courant dans la direction fournie, jusqu'à ce qu'il rencontre un obstacle.
//
void moveCurrentPlayerWhilePossible(GameState *state, Direction direction) {
    if(state == NULL || direction > 3) return;
    
    //tant qu'on peut déplacer le joueur courant, on le fait
    while(moveCurrentPlayer(state, direction));
    
    //on augmente les compteurs
    state->currentPlayer->score++;
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
Direction waitForDirection(Player *player) {
    int c;
    
    printw("\nA toi de jouer, %s ! ", player->username);
    refresh();
    
    fseek(stdin, 0, SEEK_END);
    
    do {
        c = getch();
    } while(c != KEY_DOWN && c != KEY_LEFT && c != KEY_RIGHT && c != KEY_UP);
    
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
// Vérifie si un joueur est sur l'objectif.
// Retourne true s'il l'est, false sinon.
//
bool isPlayerOnObjective(Player *player, GameBoard *gameBoard) {
    if(player == NULL || gameBoard == NULL) return false;
    
    return (gameBoard->objectivePos.x == player->position.x
            && gameBoard->objectivePos.y == player->position.y);
}

//
// Retourne le joueur qui est sur l'objectif.
// Retourne NULL si aucun ne l'est.
//
Player* getPlayerOnObjective(GameState *state) {
    if(state == NULL) return NULL;
    
    int i;
    
    for (i = 0; i < MAX_PLAYERS_COUNT; i++) {
        if(isPlayerOnObjective(&state->players[i], state->gameBoard)) return &state->players[i];
    }
    
    return NULL;
}
