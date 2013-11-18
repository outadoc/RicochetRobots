//
//  game.c
//  RicochetRobots
//
//  Created by Baptiste on 28/10/13.
//  Copyright (c) 2013 outadev. All rights reserved.
//
// Fonctions et structures relatives à la boucle globale
//

#include <stdio.h>
#include <unistd.h>

#include "game.h"
#include "display.h"

int start() {
    //boucle principale : on en sort avec un return
    while(1) {
        int choice = 0, retry = 0;

        //on affiche les options du menu principal
        displayMainMenu();

        //tant qu'on n'a pas choisi une option correcte du menu
        do {
            retry = 0;

            //on demande son choix à l'utilisateur
            choice = handleMainMenu();

            switch (choice) {
                case 0:
                    //si on veut quitter le jeu
                    return 0;
                    break;
                case 1: {
                    GameBoard board;

                    if(askForGameBoard(&board) == 0) {
                        //si askForGameBoard renvoie 0, on est prêts à continuer
                        
                        Player robots[4] = {
                            {.score = 0, .robotColor = ROBOT_RED, .position = board.robotsPosition[0]},
                            {.score = 0, .robotColor = ROBOT_GREEN, .position = board.robotsPosition[1]},
                            {.score = 0, .robotColor = ROBOT_BLUE, .position = board.robotsPosition[2]},
                            {.score = 0, .robotColor = ROBOT_GREY, .position = board.robotsPosition[3]},
                        };
                        
                        askForSinglePlayerUsername(robots);

                        GameState newGame = {
                            .turnCount = 0,
                            .currentPlayer = &robots[0],
                            .players = robots,
                            .gameBoard = &board
                        };
                        
                        refreshDisplay(&newGame);
                        
                        while(!isPlayerOnObjective(newGame.currentPlayer, newGame.gameBoard)) {
                            int direction = waitForDirection();
                            
                            movePlayerWhilePossible(newGame.currentPlayer, newGame.gameBoard, direction);
                            
                            if(newGame.currentPlayer + 1 > robots + 3) {
                                newGame.currentPlayer = &robots[0];
                            } else {
                                newGame.currentPlayer++;
                            }
                            
                            newGame.turnCount++;
                            refreshDisplay(&newGame);
                        }
                        
                    }
                    break;
                }
                case 2: {
                    Player players[4];
                    askForPlayersInfo(players);
                    break;
                }
                default:
                    //si le choix est incorrect, on réessaye
                    printf("Mmh. J'ai bien peur que ce choix ne soit un peu trop impulsif.");
                    retry = 1;
                    break;
            }
        } while(retry);

        //on demande au joueur s'il veut rejouer : dans le cas contraire, on quitte le jeu
        if(!wantsToReplay()) return 0;
    }
}

int handleMainMenu() {
    int choice = 0;

    printf("\nmenu> ");
    scanf("%d", &choice);
    while(getchar()!='\n');
    return choice;
}

int wantsToReplay() {
    char answer = '\0';

    //vidage du buffer
    while (getchar() != '\n');

    printf("\nVoulez-vous rejouer ? (O/n) ");
    answer = fgetc(stdin);

    //si on veut rejouer, retourner 1, sinon 0
    if(answer == 'o' || answer == 'O') {
        return 1;
    } else {
        return 0;
    }
}

int waitForDirection() {
    char c;
    
    do {
        c = getchar();
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
