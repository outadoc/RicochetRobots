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
        int choice = 0;
        bool retry = false;

        //on affiche les options du menu principal
        choice = displayMainMenu(false);

        //tant qu'on n'a pas choisi une option correcte du menu
        do {
            retry = false;

            switch (choice) {
                case 0:
                    //si on veut quitter le jeu
                    return 0;
                    break;
                case 1:
                    startSinglePlayer(false);
                    break;
                case 2:
                    startSinglePlayer(true);
                    break;
                case 3: {
                    Player players[MAX_PLAYERS_COUNT];
                    askForPlayersInfo(players);
                    break;
                }
                default:
                    //si le choix est incorrect, on réessaye
                    choice = displayMainMenu(true);
                    retry = true;
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

void startSinglePlayer(int playVsComputer) {
    GameBoard board;
    
    //si askForGameBoard renvoie 0, on est prêts à continuer
    if(askForGameBoard(&board) == 0) {
        
        Player robots[MAX_PLAYERS_COUNT] = {
            {.score = 0, .robotColor = ROBOT_RED,   .position = board.robotsPosition[0], .isBot = false},
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
            Direction direction;
            
            //on demande à l'utilisateur dans quelle direction il veut aller OU si c'est un bot, on récupère une direction aléatoire
            if(newGame.currentPlayer->isBot) {
                direction = getRandomDirection(1);
            } else {
                printf("\nÀ toi de jouer, %s ! ", newGame.currentPlayer->username);
                direction = waitForDirection();
            }
            
            //on déplace le robot dans cette direction
            moveCurrentPlayerWhilePossible(&newGame, direction);
            
            //on passe au joueur suivant
            if(newGame.currentPlayer + 1 > robots + MAX_PLAYERS_COUNT - 1) {
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
