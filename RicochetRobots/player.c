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
            return (y + 1 > BOARD_SIZE
                    || board->obstacles[x][y] == CELL_WALL_BOTTOM
                    || board->obstacles[x][y+1] == CELL_WALL_TOP);
            break;
        case DIRECTION_LEFT:
            return (x - 1 < 0
                    || board->obstacles[x][y] == CELL_WALL_LEFT
                    || board->obstacles[x-1][y] == CELL_WALL_RIGHT);
            break;
        case DIRECTION_RIGHT:
            return (x + 1 > BOARD_SIZE
                    || board->obstacles[x][y] == CELL_WALL_RIGHT
                    || board->obstacles[x+1][y] == CELL_WALL_LEFT);
            break;
        case DIRECTION_UP:
            return (y - 1 < 0
                    || board->obstacles[x][y] == CELL_WALL_TOP
                    || board->obstacles[x][y-1] == CELL_WALL_BOTTOM);
            break;
    }
    
    return 0;
}

int movePlayer(Player *player, GameBoard *board, int direction) {
    if(!checkForObstacle(player, board, direction)) {
        switch (direction) {
            case DIRECTION_DOWN:
                player->position.y++;
                break;
            case DIRECTION_LEFT:
                player->position.x--;
                break;
            case DIRECTION_RIGHT:
                player->position.x++;
                break;
            case DIRECTION_UP:
                player->position.y--;
                break;
        }
        
        return 0;
    } else {
        return 1;
    }
}
