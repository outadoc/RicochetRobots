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

//
// Boucle principale du jeu.
//
int start() {
    //boucle principale : on en sort avec un return
    while(1) {
        int choice = 0;
        bool retry = false;

        //on affiche les options du menu principal
        choice = displayMainMenu();

        //tant qu'on n'a pas choisi une option correcte du menu
        do {
            retry = false;

            switch (choice) {
                case 3:
                    //si on veut quitter le jeu
                    return 0;
                    break;
                case 0:
                    if(startSinglePlayer() == 1) {
                        choice = displayMainMenu();
                        retry = true;
                    }
                    break;
                case 1: {
                    Player players[ROBOTS_COUNT];
                    askForPlayersInfo(players);
                    break;
                }
                default:
                    //si le choix est incorrect, on réessaye
                    choice = displayMainMenu();
                    retry = true;
                    break;
            }
        } while(retry);

        //on demande au joueur s'il veut rejouer : dans le cas contraire, on quitte le jeu
        if(!wantsToReplay()) return 0;
    }
}

//
// Boucle de partie.
// Demande à l'utilisateur les infos nécessaires au lancement de la partie, puis exécute la boucle jusqu'à la fin du jeu.
//
int startSinglePlayer() {
    GameBoard board;
    
    //si askForGameBoard renvoie 0, on est prêts à continuer
    if(askForGameBoard(&board) == 0) {
        
        Robot robots[ROBOTS_COUNT] = {
            {.robotColor = ROBOT_RED,   .position = board.robotsPos[ROBOT_RED]},
            {.robotColor = ROBOT_GREEN, .position = board.robotsPos[ROBOT_GREEN]},
            {.robotColor = ROBOT_BLUE,  .position = board.robotsPos[ROBOT_BLUE]},
            {.robotColor = ROBOT_GREY,  .position = board.robotsPos[ROBOT_GREY]},
        };
        
        Player players[] = {
            {.score = 0, .isBot = false}
        };
        
        //on demande le pseudo du joueur
        askForSinglePlayerUsername(players);
        
        //instanciation du jeu
        GameState newGame = {
            .turnCount = 0,
            .currentPlayer = &players[0],
            .players = players,
            .currentRobot = &robots[0],
            .robots = robots,
            .gameBoard = &board
        };
        
        //on met à jour l'affichage une première fois
        refreshDisplay(&newGame);
        
        //on fait disparaitre le curseur
        curs_set(0);
        
        //tant qu'aucun robot n'est sur l'objectif
        while(getRobotOnObjective(&newGame) == NULL) {
            Direction direction;
            
            //on demande à l'utilisateur dans quelle direction il veut aller OU si c'est un bot, on récupère une direction aléatoire
            if(newGame.currentPlayer->isBot) {
                direction = getRandomDirection(&newGame);
            } else {
                direction = waitForDirection(&newGame);
            }
            
            //on déplace le robot dans cette direction
            moveCurrentRobotWhilePossible(&newGame, direction);
            newGame.currentRobot = &robots[newGame.turnCount % ROBOTS_COUNT];
            
            //on met à jour l'affichage après chaque tour
            refreshDisplay(&newGame);
        }
        
        //hop, on fait réapparaitre le curseur
        curs_set(1);
        
        //un joueur est arrivé sur l'objectif, fin du jeu
        displayGameEnding(getRobotOnObjective(&newGame), &newGame);
    } else {
        refresh();
        return 1;
    }
    
    return 0;
}
