//
//  player.h
//  RicochetRobots
//
//  Created by Baptiste on 28/10/13.
//  Copyright (c) 2013 outadev. All rights reserved.
//

#ifndef RicochetRobots_player_h
#define RicochetRobots_player_h

//constantes pour la couleur des robots
#define ROBOT_RED 0
#define ROBOT_GREEN 1
#define ROBOT_BLUE 2
#define ROBOT_GREY 3

struct Player {
    int robotColor;
    char username[15];
    int score;
};

typedef struct Player Player;

void initRobots(Player robots[]);

#endif
