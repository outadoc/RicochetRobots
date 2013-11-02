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
#include "game.h"
#include "display.h"

int start()
{
    //boucle principale : on en sort avec un return;
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
                    printf("OUÉÉÉÉ, ALLEZ VIENS ON JOUE À RICAUCHAY RAUBAUTS\n");
                    break;
                }
                case 2: {
                    Player players[4];
                    askForPlayersInfo(players);
                    break;
                }
                default:
                    //si le choix est incorrect, on réessaye
                    printf("Choix incorrect.");
                    retry = 1;
                    break;
            }
        } while(retry);
        
        //on demande au joueur s'il veut rejouer : dans le cas contraire, on quitte le jeu
        if(!wantsToReplay()) return 0;
    }
}

int handleMainMenu()
{
    int choice = 0;
    
    printf("\nmenu> ");
    scanf("%d", &choice);
    return choice;
}

int wantsToReplay()
{
    char answer = '\0';
    
    //vidage du buffer
    fseek(stdin, 0, SEEK_END);
    
    printf("\nVoulez-vous rejouer ? (O/n) ");
    answer = fgetc(stdin);
    
    //si on veut rejouer, retourner 1, sinon 0
    if(answer == 'o' || answer == 'O') {
        return 1;
    } else {
        return 0;
    }
}