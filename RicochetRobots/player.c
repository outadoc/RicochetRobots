//
//  player.c
//  RicochetRobots
//
//  Created by Baptiste on 28/10/13.
//  Copyright (c) 2013 outadev. All rights reserved.
//

#include <stdio.h>
#include "player.h"

int checkForObstacle(Player *player, GameBoard *board, int direction) {
    int x = player->position.x;
    int y = player->position.y;
    
    switch (direction) {
        case DIRECTION_DOWN:
            return (x + 1 > BOARD_SIZE - 1
                    || board->obstacles[x][y] == CELL_WALL_BOTTOM
                    || board->obstacles[x+1][y] == CELL_WALL_TOP);
            break;
        case DIRECTION_LEFT:
            return (y - 1 < 0
                    || board->obstacles[x][y] == CELL_WALL_LEFT
                    || board->obstacles[x][y-1] == CELL_WALL_RIGHT);
            break;
        case DIRECTION_RIGHT:
            return (y + 1 > BOARD_SIZE - 1
                    || board->obstacles[x][y] == CELL_WALL_RIGHT
                    || board->obstacles[x][y+1] == CELL_WALL_LEFT);
            break;
        case DIRECTION_UP:
            return (x - 1 < 0
                    || board->obstacles[x][y] == CELL_WALL_TOP
                    || board->obstacles[x-1][y] == CELL_WALL_BOTTOM);
            break;
    }
    
    return 0;
}

int movePlayer(Player *player, GameBoard *board, int direction) {
    if(!checkForObstacle(player, board, direction)) {
        switch (direction) {
            case DIRECTION_DOWN:
                player->position.x++;
                break;
            case DIRECTION_LEFT:
                player->position.y--;
                break;
            case DIRECTION_RIGHT:
                player->position.y++;
                break;
            case DIRECTION_UP:
                player->position.x--;
                break;
        }
        
        return 1;
    } else {
        return 0;
    }
}

void movePlayerWhilePossible(Player *player, GameBoard *board, int direction) {
    while(movePlayer(player, board, direction));
}

char* getRobotStringColor(int color) {
    switch (color) {
        case ROBOT_RED:
            return "rouge";
            break;
        case ROBOT_GREEN:
            return "vert";
            break;
        case ROBOT_BLUE:
            return "bleu";
            break;
        case ROBOT_GREY:
            return "gris";
            break;
        default:
            return "inconnu";
            break;
    }
}

