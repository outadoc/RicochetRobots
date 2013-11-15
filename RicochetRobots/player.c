//
//  player.c
//  RicochetRobots
//
//  Created by Baptiste on 28/10/13.
//  Copyright (c) 2013 outadev. All rights reserved.
//

#include <stdio.h>
#include "player.h"

void initRobots(Player robots[]) {
    robots[0].robotColor = ROBOT_RED;   //FORCE ROUGE !
    robots[1].robotColor = ROBOT_GREEN; //FORCE VERTE !
    robots[2].robotColor = ROBOT_BLUE;  //FORCE BLEUE !
    robots[3].robotColor = ROBOT_GREY;  //FORCE... arf

    robots[0].score = robots[1].score = robots[2].score = robots[3].score = 0;
}
