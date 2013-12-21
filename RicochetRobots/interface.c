//
//  display.c
//  RicochetRobots
//
//  Created by Baptiste on 28/10/13.
//  Copyright (c) 2013 outadev. All rights reserved.
//
// Fonctions et structures relatives à l'affichage
//

#include <stdio.h>
#include <string.h>

#include "interface.h"

//
// Affiche le logo du jeu sur la sortie standard.
//
void displayLogo(WINDOW *win, int width) {
    //on affiche chaque ligne du logo sur la WINDOW spécifiée
    //ça rend pas super dans le code, mais il faut jouer avec les espaces blancs et le décalage à gauche pour affiche correctement
    print_in_middle(win, 1, 4, width, "____  ______________  ________  ______________");
    print_in_middle(win, 2, 4, width, "/ __ \\/  _/ ____/ __ \\/ ____/ / / / ____/_  __/");
    print_in_middle(win, 3, 2, width, "/ /_/ // // /   / / / / /   / /_/ / __/   / /");
    print_in_middle(win, 4, 1, width, "/ _, _// // /___/ /_/ / /___/ __  / /___  / /");
    print_in_middle(win, 5, 0, width, "/_/ ||||__||||__||||__||||__|||_|||||||_/ /_/");
    print_in_middle(win, 6, 3, width, "/ __ \\/ __ \\/ __ )/ __ \\/_  __/ ___/         ");
    print_in_middle(win, 7, 2, width, "/ /_/ / / / / __  / / / / / /  \\____         ");
    print_in_middle(win, 8, 1, width, "/ _, _/ /_/ / /_/ / /_/ / / /  ___/ /         ");
    print_in_middle(win, 9, 0, width, "/_/ |_|\\____/_____/\\____/ /_/  /____/         ");
    
    wrefresh(win);
}

//
// Affiche le menu principal du jeu sur la sortie standard.
// Si error vaut true, on affiche une erreur à la place du menu.
//
int displayMainMenu(bool error) {
    char *choices[] = {
        "Partie solo",
        "Partie solo VS ordinateur",
        "Partie multijoueurs",
        "Quitter"
    };
    
    return displayMenu(choices, ARRAY_SIZE(choices), "MENU PRINCIPAL");
}

//
// Affiche le menu de sélection du plateau de jeu sur la sortie standard.
// Si error vaut true, on affiche une erreur à la place du menu.
//
int displayGameBoardSelectionMenu(bool error) {    
    char *choices[] = {
        "Plateau predefini",
        "Plateau depuis un fichier",
        "Plateau aleatoire",
        "Retour au menu principal"
    };
    
    return displayMenu(choices, ARRAY_SIZE(choices), "CHOIX DU PLATEAU");
}

//
// Demande à l'utilisateur quel plateau de jeu prédéfini il souhaite charger.
//
int displayGameBoardList() {
    int choice = 0;
    
    printw("Numéro du plateau à charger (entre 1 et %d) : ", BUILTIN_BOARDS_COUNT);
    refresh();
    
    do {
        //on récupère un chiffre
        //on ne veut PAS réagir sur un KEY_RESIZE (redimensionnement du terminal)
        choice = getch();
    } while(choice == KEY_RESIZE);
    
    printw("\n");
    
    //on retourne le vrai chiffre (en soustrayant la valeur de '0'
    return choice - '0';
}

//
// Affiche une erreur de choix de menu sur la sortie standard.
//
void displayMenuError() {
    printw("Woops. Mauvaise option.");
    refresh();
}

//
// Affiche le tableau de scores de fin de jeu sur la sortie standard.
//
void displayGameEnding(int score, Player *winner, GameState *state) {
    if(state == NULL) return;
    
    int i;
    
    clear();
    
    printw("\n------------------------------------\n");
    printw("Partie terminée !\n");
    
    printw("Gagnant : %s a déplacé le robot ", winner->username);
    
    COL_ON_BOT(winner->robotColor);
    printw("%s", getRobotStringColor(winner->robotColor));
    COL_OFF_BOT(winner->robotColor);
    
    printw(" sur l'objectif\n");
    
    printw("\nScore total : %d coups\n\n", score);
    
    for(i = 0; i < MAX_PLAYERS_COUNT; i++) {
        printw("Score de ");
        COL_ON_BOT(state->players[i].robotColor);
        printw("%s", getRobotStringColor(state->players[i].robotColor));
        COL_OFF_BOT(state->players[i].robotColor);
        printw(" : %d coups\n", state->players[i].score);
    }
    
    printw("------------------------------------\n\n");
    
    refresh();
}

//
// Demande à l'utilisateur s'il souhaite rejouer.
//
bool wantsToReplay() {
    char answer = '\0';
        
    printw("\nVoulez-vous rejouer ? (O/n) ");
    refresh();
    
    answer = getch();
    
    //si on veut rejouer, retourner 1, sinon 0
    if(answer == 'o' || answer == 'O') {
        return true;
    } else {
        return false;
    }
}

//
// Demande le pseudo de chaque joueur, un par un.
//
void askForPlayersInfo(Player players[]) {
    if(players == NULL) return;
    
    int i;
    
    for (i = 0; i < MAX_PLAYERS_COUNT; i++) {
        printw("Pseudo du joueur %d : ", i+1);
        
        refresh();
        
        //on récupère 14 caractères (+1 pour le \0) dans Player.username
        getstr(players[i].username);
    }
}

//
// Demande le pseudo du joueur et le copie dans chaque robot.
//
void askForSinglePlayerUsername(Player robots[]) {
    if(robots == NULL) return;
    
    int i;
    char username[MAX_USERNAME_SIZE];
    
    printw("Votre pseudo : ");
    refresh();
    
    //on récupère 14 caractères (+1 pour le \0) dans username
    getstr(username);
    
    for (i = 0; i < MAX_PLAYERS_COUNT; i++) {
        if(!robots[i].isBot) strcpy(robots[i].username, username);
        else sprintf(robots[i].username, "CPU%d", i);
    }
}

//
// Demande au joueur le chemin du niveau à charger.
//
void askForLevelPath(char path[]) {
    printw("Entrez le chemin du fichier niveau : ");
    refresh();
    
    //on récupère 14 caractères (+1 pour le \0) dans path
    getstr(path);
}

//
// Affiche le plateau de jeu.
//
void displayGameBoard(GameState *state) {
    if(state == NULL) return;
    
    int i, j;
    
    WINDOW *boardWin = newwin(2 * BOARD_SIZE + 1, 4 * BOARD_SIZE + 1, 0, 0);
    box(boardWin, 0, 0);
    
    for (i = 0; i < BOARD_SIZE - 1; i++) {
        //début de ligne
        for (j = 0; j < BOARD_SIZE; j++) {
            int charLine = i * 2 + 1;
            int charCol = j * 4;
            
            //on affiche les murs verticaux
            //si il y a quelque-chose dans la case actuelle
            int k;
            bool hasContent = false;
            
            for (k = 0; k < MAX_PLAYERS_COUNT; k++) {
                //on vérifie, pour chaque robot, si ses coordonnées correspondent à celles de la case actuelle
                if(state->players[k].position.x == i && state->players[k].position.y == j) {
                    int l;
                    bool hasObjective = false;
                    
                    hasContent = true;
                    
                    COL_ON_BOT(state->players[k].robotColor);
                    
                    for (l = 0; l < MAX_PLAYERS_COUNT; l++) {
                        //si on a un objectif ici
                        if(state->gameBoard->objectivesPos[l].x == i && state->gameBoard->objectivesPos[l].y == j) {
                            hasObjective = true;
                            break;
                        }
                    }
                    
                    if(hasObjective) {
                        mvwprintw(boardWin, charLine, charCol + 1, "[X]");
                    } else {
                        mvwprintw(boardWin, charLine, charCol + 1, "   ");
                    }
                    
                    COL_OFF_BOT(state->players[k].robotColor);
                    
                }
            }
            
            //si la case n'a pas encore de contenu (et donc pas de robot) et que c'est une case objectif
            for (k = 0; k < MAX_PLAYERS_COUNT; k++) {
                if(!hasContent && state->gameBoard->objectivesPos[k].x == i && state->gameBoard->objectivesPos[k].y == j) {
                    hasContent = true;
                    
                    attron(COLOR_PAIR(10));
                    mvwprintw(boardWin, charLine, charCol + 1, "[X]");
                    attroff(COLOR_PAIR(10));
                    
                    break;
                }
            }
            
            //si on doit afficher un mur à droite : si il y a un mur à droite dans la case actuelle ou un mur à gauche dans la case directement à droite
            //on n'oublie pas de prendre en compte les murs en L
            if(state->gameBoard->obstacles[i][j] == CELL_WALL_RIGHT
               || state->gameBoard->obstacles[i][j] == CELL_WALL_BOTTOM_RIGHT
               || state->gameBoard->obstacles[i][j] == CELL_WALL_TOP_RIGHT
               || (j < BOARD_SIZE && state->gameBoard->obstacles[i][j+1] == CELL_WALL_LEFT)
               || (j < BOARD_SIZE && state->gameBoard->obstacles[i][j+1] == CELL_WALL_BOTTOM_LEFT)
               || (j < BOARD_SIZE && state->gameBoard->obstacles[i][j+1] == CELL_WALL_TOP_LEFT)
               || j == BOARD_SIZE - 1) {
                mvwaddch(boardWin, charLine, charCol + 4, ACS_VLINE);
            }
        }
        
        for (j = 0; j < BOARD_SIZE - 1; j++) {
            int charLine = i * 2 + 2;
            int charCol = j * 4;
            
            //on affiche les murs horizontaux, d'une façon analogue aux murs verticaux
            if(state->gameBoard->obstacles[i][j] == CELL_WALL_BOTTOM
               || state->gameBoard->obstacles[i][j] == CELL_WALL_BOTTOM_LEFT
               || state->gameBoard->obstacles[i][j] == CELL_WALL_BOTTOM_RIGHT
               || (i < BOARD_SIZE && state->gameBoard->obstacles[i+1][j] == CELL_WALL_TOP)
               || (i < BOARD_SIZE && state->gameBoard->obstacles[i+1][j] == CELL_WALL_TOP_LEFT)
               || (i < BOARD_SIZE && state->gameBoard->obstacles[i+1][j] == CELL_WALL_TOP_RIGHT)) {
                mvwaddch(boardWin, charLine, charCol + 1, ACS_HLINE);
                mvwaddch(boardWin, charLine, charCol + 2, ACS_HLINE);
                mvwaddch(boardWin, charLine, charCol + 3, ACS_HLINE);
                mvwaddch(boardWin, charLine, charCol + 4, ACS_PLUS);
            } else if(!(i == BOARD_SIZE/2-1 && j == BOARD_SIZE/2-1)) {
                mvwaddch(boardWin, charLine, charCol + 4, ACS_PLUS);
            }
        }
    }
    
    wrefresh(boardWin);
}

//
// Rafraîchit l'affichage pendant une partie.
// Affiche le plateau de jeu, ainsi qu'un résumé des informations sur la partie en cours.
//
void refreshDisplay(GameState *currentGame) {
    if(currentGame == NULL) return;
    
    displayGameBoard(currentGame);
    
    WINDOW *infoWin = newwin(6, 35, 0, 4 * BOARD_SIZE + 5);
    box(infoWin, 0, 0);
    
    mvwprintw(infoWin, 1, 2, "Tour %d\n", currentGame->turnCount);
    mvwprintw(infoWin, 2, 2, "Joueur actuel : %s", currentGame->currentPlayer->username);
    mvwprintw(infoWin, 3, 2, "Robot actuel : ");
    
    COL_ON_BOT(currentGame->currentPlayer->robotColor);
    wprintw(infoWin, "%s", getRobotStringColor(currentGame->currentPlayer->robotColor));
    COL_OFF_BOT(currentGame->currentPlayer->robotColor);
    
    mvwprintw(infoWin, 4, 2, "Score : %d\n",
           currentGame->players[0].score
           + currentGame->players[1].score
           + currentGame->players[2].score
           + currentGame->players[3].score);
    
    wrefresh(infoWin);
}

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string) {
    int length, x, y;
	float temp;
    
	if(win == NULL)
		win = stdscr;
    
	getyx(win, y, x);
	
    if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;
    
	length = (int) strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int) temp;
    
	mvwprintw(win, y, x, "%s", string);
	refresh();
}

int displayMenu(char **choices, int nbChoices, char title[]) {
    //variables pour l'affichage du menu
    ITEM **menuItems = NULL;
    MENU *menu = NULL;
    WINDOW *menuWin = NULL;
    
    int i = 0;
    
    //largeur du menu = longueur du plus grand des choix possibles
    int menuWidth = max_strlen(choices, nbChoices) + 1;
    
    //hauteur = nombre de choix possibles + 15 (pour le logo)
    int winHeight = nbChoices + 17;
    int winWidth = 70;
    
    //on centre le menu
    int starty = (LINES - winHeight) / 2;
	int startx = (COLS - winWidth) / 2;
    
    noecho();
    clear();
    
    //on alloue de la mémoire pour initialiser les éléments du menu
    menuItems = (ITEM **) calloc(nbChoices + 1, sizeof(ITEM *));
    
    //on créé de nouveaux éléments à partir des choix fournis
    for(i = 0; i < nbChoices; i++) {
        menuItems[i] = new_item(choices[i], NULL);
    }
    
    //on met un élément nul à la fin du tableau
    menuItems[nbChoices] = (ITEM *) NULL;
    
    //on initialise le menu
    menu = new_menu((ITEM **) menuItems);
    
    //création d'une fenêtre pour le menu
    menuWin = newwin(winHeight, winWidth, starty, startx);
    
	//on associe le menu à une fenêtre et une sous-fenêtre
    set_menu_win(menu, menuWin);
    //fenêtre hauteur largeur x y
    set_menu_sub(menu, derwin(menuWin, nbChoices, menuWidth, 15, (winWidth - menuWidth) / 2));
    
    //on lui précise bien que le menu fait N lignes et 1 colonne
    set_menu_format(menu, nbChoices, 1);
    
	//on affiche une bordure autour de la fenêtre
    box(menuWin, 0, 0);
    
    //on affiche le logo du jeu
	displayLogo(menuWin, winWidth);
    
    //et deux lignes horizontales
    mvwaddch(menuWin, 11, 0, ACS_LTEE);
    mvwhline(menuWin, 11, 1, ACS_HLINE, winWidth - 1);
    mvwaddch(menuWin, 11, winWidth - 1, ACS_RTEE);
    
    //on affiche un titre
    print_in_middle(menuWin, 12, 0, winWidth, title);
    
    mvwaddch(menuWin, 13, 0, ACS_LTEE);
    mvwhline(menuWin, 13, 1, ACS_HLINE, winWidth - 1);
    mvwaddch(menuWin, 13, winWidth - 1, ACS_RTEE);
    
	//et hop, on affiche le menu et on rafraîchit.
	post_menu(menu);
	wrefresh(menuWin);
    
    refresh();
    
    //caractère courant
    int c;
    
    //boucle pour le menu
    while((c = getch())) {
        switch(c) {
            case KEY_DOWN:
                menu_driver(menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(menu, REQ_UP_ITEM);
                break;
            case 10: {
                int choice = item_index(current_item(menu));
                unpost_menu(menu);
                free_menu(menu);
                
                for(i = 0; i < nbChoices; ++i)
                    free_item(menuItems[i]);
                
                clear();
                refresh();
                
                delwin(menuWin);
                echo();
                
                return choice;
                break;
            }
        }
        
        wrefresh(menuWin);
    }
    
    return 0;
}
