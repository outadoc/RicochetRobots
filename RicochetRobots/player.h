//
//  player.h
//  RicochetRobots
//
//  Created by Baptiste on 28/10/13.
//  Copyright (c) 2013 outadev. All rights reserved.
//

#ifndef RicochetRobots_player_h
#define RicochetRobots_player_h

enum Robots {
    RED, GREEN, BLUE, GREY
};

struct Player {
    int robotColor;
    char username[];
    int score;
};

typedef struct Player Player;

#endif
