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

int start() {
    //boucle principale : on en sort avec un return
    while(1) {
        int choice = 0, retry = 0;

        //on affiche les options du menu principal
        choice = displayMainMenu(0);

        //tant qu'on n'a pas choisi une option correcte du menu
        do {
            retry = 0;

            switch (choice) {
                case 0:
                    //si on veut quitter le jeu
                    return 0;
                    break;
                case 1: {
                    startSinglePlayer();
                    break;
                }
                case 2: {
                    Player players[4];
                    askForPlayersInfo(players);
                    break;
                }
                default:
                    //si le choix est incorrect, on réessaye
                    choice = displayMainMenu(1);
                    retry = 1;
                    break;
            }
        } while(retry);

        //on demande au joueur s'il veut rejouer : dans le cas contraire, on quitte le jeu
        if(!wantsToReplay()) return 0;
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

void startSinglePlayer() {
    GameBoard board;
    
    //si askForGameBoard renvoie 0, on est prêts à continuer
    if(askForGameBoard(&board) == 0) {
        int playVsComputer = askSoloMode();
        
        Player robots[4] = {
            {.score = 0, .robotColor = ROBOT_RED,   .position = board.robotsPosition[0], .isBot = 0},
            {.score = 0, .robotColor = ROBOT_GREEN, .position = board.robotsPosition[1], .isBot = playVsComputer},
            {.score = 0, .robotColor = ROBOT_BLUE,  .position = board.robotsPosition[2], .isBot = playVsComputer},
            {.score = 0, .robotColor = ROBOT_GREY,  .position = board.robotsPosition[3], .isBot = playVsComputer},
        };
        
        //on demande le pseudo du joueur
        askForSinglePlayerUsername(robots);
        
        //instanciation du jeu
        GameState newGame = {
            .turnCount = 0,
            .currentPlayer = &robots[0],
            .players = robots,
            .gameBoard = &board
        };
        
        //on met à jour l'affichage une première fois
        refreshDisplay(&newGame);
        
        //tant qu'aucun robot n'est sur l'objectif
        while(getPlayerOnObjective(&newGame) == NULL) {
            //on demande à l'utilisateur dans quelle direction il veut aller OU si c'est un bot, on récupère une direction aléatoire
            Direction direction = (newGame.currentPlayer->isBot) ? getRandomDirection(1) : waitForDirection();
            
            //on déplace le robot dans cette direction
            moveCurrentPlayerWhilePossible(&newGame, direction);
            
            //on passe au joueur suivant
            if(newGame.currentPlayer + 1 > robots + 3) {
                newGame.currentPlayer = &robots[0];
            } else {
                newGame.currentPlayer++;
            }
            
            //on met à jour l'affichage après chaque tour
            refreshDisplay(&newGame);
        }
        
        //un joueur est arrivé sur l'objectif, fin du jeu
        displayGameEnding(newGame.turnCount, getPlayerOnObjective(&newGame));
    }
}
