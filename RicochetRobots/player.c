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

int checkForObstacle(GameState *state, Direction direction) {
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
                    || state->gameBoard->obstacles[target.x][target.y] == CELL_WALL_TOP) return 1;
            break;
        case DIRECTION_LEFT:
            target.y--;
            
            if(target.y < 0
                    || state->gameBoard->obstacles[target.x][target.y+1] == CELL_WALL_LEFT
                    || state->gameBoard->obstacles[target.x][target.y] == CELL_WALL_RIGHT) return 1;
            break;
        case DIRECTION_RIGHT:
            target.y++;
            
            if(target.y > BOARD_SIZE - 1
                    || state->gameBoard->obstacles[target.x][target.y-1] == CELL_WALL_RIGHT
                    || state->gameBoard->obstacles[target.x][target.y] == CELL_WALL_LEFT) return 1;
            break;
        case DIRECTION_UP:
            target.x--;
            
            if(target.x < 0
                    || state->gameBoard->obstacles[target.x+1][target.y] == CELL_WALL_TOP
                    || state->gameBoard->obstacles[target.x][target.y] == CELL_WALL_BOTTOM) return 1;
            break;
    }
    
    for(i = 0; i < 4; i++) {
        if(state->players[i].robotColor != state->currentPlayer->robotColor
            && state->players[i].position.x == target.x
            && state->players[i].position.y == target.y) {
           return 1;
        }
    }
    
    return 0;
}

int moveCurrentPlayer(GameState *state, Direction direction) {
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
        
        return 1;
    } else {
        return 0;
    }
}

void moveCurrentPlayerWhilePossible(GameState *state, Direction direction) {
    while(moveCurrentPlayer(state, direction));
    
    state->currentPlayer->score++;
    state->turnCount++;
}

int getRandomDirection() {
    return rand() % (3-0) + 0;
}

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

int isPlayerOnObjective(Player *player, GameBoard *gameBoard) {
    return (gameBoard->obstacles[player->position.x][player->position.y] == CELL_OBJECTIVE);
}

Player* getPlayerOnObjective(GameState *state) {
    int i;
    
    for (i = 0; i < 4; i++) {
        if(isPlayerOnObjective(&state->players[i], state->gameBoard)) return &state->players[i];
    }
    
    return NULL;
}
