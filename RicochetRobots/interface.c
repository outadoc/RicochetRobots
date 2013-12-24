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
    displayInCenter(win, 1, 4, width, "____  ______________  ________  ______________");
    displayInCenter(win, 2, 4, width, "/ __ \\/  _/ ____/ __ \\/ ____/ / / / ____/_  __/");
    displayInCenter(win, 3, 2, width, "/ /_/ // // /   / / / / /   / /_/ / __/   / /");
    displayInCenter(win, 4, 1, width, "/ _, _// // /___/ /_/ / /___/ __  / /___  / /");
    displayInCenter(win, 5, 0, width, "/_/ ||||__||||__||||__||||__|||_|||||||_/ /_/");
    displayInCenter(win, 6, 3, width, "/ __ \\/ __ \\/ __ )/ __ \\/_  __/ ___/         ");
    displayInCenter(win, 7, 2, width, "/ /_/ / / / / __  / / / / / /  \\____         ");
    displayInCenter(win, 8, 1, width, "/ _, _/ /_/ / /_/ / /_/ / / /  ___/ /         ");
    displayInCenter(win, 9, 0, width, "/_/ |_|\\____/_____/\\____/ /_/  /____/         ");
    
    wrefresh(win);
}

//
// Affiche le menu principal du jeu sur la sortie standard.
// Si error vaut true, on affiche une erreur à la place du menu.
//
int displayMainMenu() {
    char *choices[] = {
        "Partie solo",
        "Partie multijoueurs",
        "Quitter"
    };
    
    return displayMenu(choices, ARRAY_SIZE(choices), "MENU PRINCIPAL");
}

//
// Affiche le menu de sélection du plateau de jeu sur la sortie standard.
// Si error vaut true, on affiche une erreur à la place du menu.
//
int displayGameBoardSelectionMenu() {
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
    int i, choice;
    char *choices[BUILTIN_BOARDS_COUNT];
    
    //on est obligés d'allouer dynamiquement ici
    //on remplit un tableau de strings : Plateau 1, Plateau 2, etc.
    for(i = 0; i < BUILTIN_BOARDS_COUNT; i++) {
        choices[i] = (char *) malloc(sizeof(char) * 12);
        sprintf(choices[i], "Plateau %d", i + 1);
    }
    
    //on affiche le menu
    choice = displayMenu(choices, BUILTIN_BOARDS_COUNT, "PLATEAU PREDEFINI...");
    
    for(i = 0; i < BUILTIN_BOARDS_COUNT; i++) {
        //on libère la mémoire
        free(choices[i]);
    }
    
    return choice;
}

//
// Affiche le tableau de scores de fin de jeu sur la sortie standard.
//
void displayGameEnding(Player *winner, GameState *state) {
    if(state == NULL) return;
    
    int i;
    
    clear();
    
    printw("\n------------------------------------\n");
    printw("Partie terminée !\n");
    
    printw("Gagnant : %s a déplacé le robot ", winner->username);
    
    //COL_ON_BOT(winner->robotColor);
    printw("%s", getRobotStringColor(state->currentRobot->robotColor));
    //COL_OFF_BOT(winner->robotColor);
    
    printw(" sur l'objectif\n");
    
    printw("\nScore total : %d coups\n\n", state->turnCount);
    
    for(i = 0; i < ROBOTS_COUNT; i++) {
        printw("Score de ");
        //COL_ON_BOT(state->players[i].robotColor);
        printw("%s", getRobotStringColor(state->robots[i].robotColor));
        //COL_OFF_BOT(state->players[i].robotColor);
        printw(" : %d coups\n", state->robots[i].score);
    }
    
    printw("\n");
    
    for(i = 0; i < ARRAY_SIZE(state->players); i++) {
        printw("Score de %s : %d coups\n", state->players[i].username, state->players[i].score);
    }
    
    printw("------------------------------------\n\n");
    
    refresh();
}

//
// Demande à l'utilisateur s'il souhaite rejouer.
//
bool wantsToReplay() {
    char answer = '\0';
        
    printw("Voulez-vous rejouer ? (O/n) "); refresh();
    
    nocbreak();
    answer = getch();
    cbreak();
    
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
    
    for (i = 0; i < ROBOTS_COUNT; i++) {
        printw("Pseudo du joueur %d : ", i+1);
        refresh();
        getstr(players[i].username);
    }
}

//
// Demande le pseudo du joueur et le copie dans chaque robot.
//
void askForSinglePlayerUsername(Player *player) {
    if(player == NULL) return;
    
    displayTextPromptMenu("CHOIX DU PSEUDO", "Pseudo :", player->username, MAX_USERNAME_SIZE);
}

//
// Demande au joueur le chemin du niveau à charger.
//
void askForLevelPath(char path[]) {
    if(path == NULL) return;
    
    displayTextPromptMenu("CHARGER DEPUIS UN FICHIER", "Chemin du fichier niveau :", path, MAX_LVL_PATH_SIZE);
}

void displayLevelLoadingError(char message[]) {
    clear();
    printw("Erreur de chargement: %s\n", message);
    refresh();
    getch();
}

//
// Affiche le plateau de jeu.
//
void displayGameBoard(GameState *state) {
    if(state == NULL) return;
    
    int i, j;
    int width = 4 * BOARD_SIZE + 1;
    int height = 2 * BOARD_SIZE + 1;
    
    WINDOW *boardWin = newwin(height, width, (LINES - height) / 2, (FIRST_COL_WIDTH - width) / 2);
    box(boardWin, 0, 0);
    
    for (i = 0; i < BOARD_SIZE; i++) {
        //début de ligne
        for (j = 0; j < BOARD_SIZE; j++) {
            int charLine = i * 2 + 1;
            int charCol = j * 4;
            
            //on affiche les murs verticaux
            //si il y a quelque-chose dans la case actuelle
            int k;
            bool hasContent = false;
            
            for (k = 0; k < ROBOTS_COUNT; k++) {
                //on vérifie, pour chaque robot, si ses coordonnées correspondent à celles de la case actuelle
                if(state->robots[k].position.x == i && state->robots[k].position.y == j) {
                    int l;
                    bool hasObjective = false;
                    
                    hasContent = true;
                    
                    COL_ON_BOT(boardWin, state->robots[k].robotColor);
                    
                    for (l = 0; l < ROBOTS_COUNT; l++) {
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
                    
                    COL_OFF_BOT(boardWin, state->robots[k].robotColor);
                }
            }
            
            //si la case n'a pas encore de contenu (et donc pas de robot) et que c'est une case objectif
            for (k = 0; k < ROBOTS_COUNT; k++) {
                if(!hasContent && state->gameBoard->objectivesPos[k].x == i && state->gameBoard->objectivesPos[k].y == j) {
                    hasContent = true;
                    
                    wattron(boardWin, COLOR_PAIR(10));
                    mvwprintw(boardWin, charLine, charCol + 1, "[X]");
                    wattroff(boardWin, COLOR_PAIR(10));
                    
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
        
        for (j = 0; j < BOARD_SIZE; j++) {
            int charLine = i * 2 + 2;
            int charCol = j * 4;
            
            //on affiche les murs horizontaux, d'une façon analogue aux murs verticaux
            if(i < BOARD_SIZE - 1 &&
               (state->gameBoard->obstacles[i][j] == CELL_WALL_BOTTOM
               || state->gameBoard->obstacles[i][j] == CELL_WALL_BOTTOM_LEFT
               || state->gameBoard->obstacles[i][j] == CELL_WALL_BOTTOM_RIGHT
               || state->gameBoard->obstacles[i+1][j] == CELL_WALL_TOP
               || state->gameBoard->obstacles[i+1][j] == CELL_WALL_TOP_LEFT
               || state->gameBoard->obstacles[i+1][j] == CELL_WALL_TOP_RIGHT)) {
                mvwaddch(boardWin, charLine, charCol + 1, ACS_HLINE);
                mvwaddch(boardWin, charLine, charCol + 2, ACS_HLINE);
                mvwaddch(boardWin, charLine, charCol + 3, ACS_HLINE);
                mvwaddch(boardWin, charLine, charCol + 4, ACS_PLUS);
            } else if(i < BOARD_SIZE - 1 && j < BOARD_SIZE - 1 && (i != BOARD_SIZE/2-1 || j != BOARD_SIZE/2-1)) {
                mvwaddch(boardWin, charLine, charCol + 4, ACS_PLUS);
            }
        }
    }
    
    refresh();
    wrefresh(boardWin);
    delwin(boardWin);
}

void displayGameStatus(GameState *currentGame) {
    if(currentGame == NULL) return;
    
    WINDOW *infoWin = newwin(5, SECOND_COL_WIDTH, 1, COLS - SECOND_COL_WIDTH - 1);
    box(infoWin, 0, 0);
    
    mvwprintw(infoWin, 1, 2, "Score total \t\t: %d\n", currentGame->turnCount);
    mvwprintw(infoWin, 2, 2, "Joueur actuel \t: %s", currentGame->currentPlayer->username);
    mvwprintw(infoWin, 3, 2, "Robot actuel \t\t: ");
    
    COL_ON_BOT(infoWin, currentGame->currentRobot->robotColor);
    wprintw(infoWin, "%s", getRobotStringColor(currentGame->currentRobot->robotColor));
    COL_OFF_BOT(infoWin, currentGame->currentRobot->robotColor);
    
    refresh();
    wrefresh(infoWin);
    delwin(infoWin);
}

void displayScores(GameState *currentGame) {
    if(currentGame == NULL) return;
    
    int i;
    
    WINDOW *scoresWin = newwin(6, SECOND_COL_WIDTH, 7, COLS - SECOND_COL_WIDTH - 1);
    box(scoresWin, 0, 0);
    
    for(i = 0; i < ROBOTS_COUNT; i++) {
        mvwprintw(scoresWin, i + 1, 2, "Score de ");
        COL_ON_BOT(scoresWin, currentGame->robots[i].robotColor);
        wprintw(scoresWin, "%s", getRobotStringColor(currentGame->robots[i].robotColor));
        COL_OFF_BOT(scoresWin, currentGame->robots[i].robotColor);
        wprintw(scoresWin, " \t: %d", currentGame->robots[i].score);
    }
    
    refresh();
    wrefresh(scoresWin);
    delwin(scoresWin);
}

void displayCommands() {
    WINDOW *cmdWin = newwin(11, SECOND_COL_WIDTH, 14, COLS - SECOND_COL_WIDTH - 1);
    box(cmdWin, 0, 0);
    
    wattron(cmdWin, A_UNDERLINE);
    mvwprintw(cmdWin, 1, 2, "Commandes de partie");
    wattroff(cmdWin, A_UNDERLINE);
    
    mvwprintw(cmdWin, 2, 2, "Flèches directionnelles : déplacer le robot");
    mvwprintw(cmdWin, 3, 2, "Echap : quitter la partie");
    
    wattron(cmdWin, A_UNDERLINE);
    mvwprintw(cmdWin, 5, 2, "Changer de robot");
    wattroff(cmdWin, A_UNDERLINE);
    
    mvwprintw(cmdWin, 6, 2, "R : robot rouge");
    mvwprintw(cmdWin, 7, 2, "B : robot bleu");
    mvwprintw(cmdWin, 8, 2, "V : robot vert");
    mvwprintw(cmdWin, 9, 2, "G : robot gris");
    
    refresh();
    wrefresh(cmdWin);
    delwin(cmdWin);
}

//
// Rafraîchit l'affichage pendant une partie.
// Affiche le plateau de jeu, ainsi qu'un résumé des informations sur la partie en cours.
//
void refreshGameDisplay(GameState *currentGame) {
    if(currentGame == NULL) return;
    
    clear();
    
    displayGameBoard(currentGame);
    displayGameStatus(currentGame);
    displayScores(currentGame);
    displayCommands();
}

void displayInCenter(WINDOW *win, int starty, int startx, int width, char *string) {
    int length, x, y;
    
	if(win == NULL) win = stdscr;
	getyx(win, y, x);
	
    if(startx != 0) x = startx;
	if(starty != 0) y = starty;
	if(width == 0) width = 80;
    
	length = (int) strlen(string);
	x = startx + (int) (width - length) / 2;
    
	mvwprintw(win, y, x, "%s", string);
	refresh();
}

int displayMenu(char **choices, int nbChoices, char title[]) {
    //variables pour l'affichage du menu
    ITEM **menuItems = NULL;
    MENU *menu = NULL;
    WINDOW *menuWin = NULL;
    
    int i = 0, c;
    int winWidth = 70;
    //largeur du menu = longueur du plus grand des choix possibles
    int menuWidth = max_strlen(choices, nbChoices) + 2;
    
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
    menuWin = getMenuWindow(nbChoices, title);
    
    //on lui précise bien que le menu fait N lignes et 1 colonne
    set_menu_format(menu, nbChoices, 1);
    
    //on associe le menu à une fenêtre et une sous-fenêtre
    set_menu_win(menu, menuWin);
    //fenêtre hauteur largeur x y
    set_menu_sub(menu, derwin(menuWin, nbChoices, menuWidth, 15, (winWidth - menuWidth) / 2));
    
    set_menu_mark(menu, "> ");
    
    //et hop, on affiche le menu et on rafraîchit.
	post_menu(menu);
	
    refresh();
    wrefresh(menuWin);
    
    curs_set(0);
    noecho();
    
    //boucle pour le menu
    while((c = getch())) {
        switch(c) {
            case KEY_DOWN:
                menu_driver(menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(menu, REQ_UP_ITEM);
                break;
            case 10: { //entrée
                int choice = item_index(current_item(menu));
                
                unpost_menu(menu);
                free_menu(menu);
                
                for(i = 0; i < nbChoices; ++i)
                    free_item(menuItems[i]);
                
                clear();
                refresh();
                
                delwin(menuWin);
                
                echo();
                curs_set(1);
                
                return choice;
                break;
            }
        }
        
        wrefresh(menuWin);
    }
    
    return 0;
}

void displayTextPromptMenu(char title[], char fieldTitle[], char result[], int n) {
    clear(); refresh();
    
    //variables pour l'affichage du menu
    WINDOW *menuWin = getMenuWindow(1, title);;
    mvwprintw(menuWin, WIN_TOP_MARGIN + 2, 2, "%s", fieldTitle);
    
    wrefresh(menuWin);
    
    mvwgetnstr(menuWin, WIN_TOP_MARGIN + 2, (int) strlen(fieldTitle) + 3, result, n);
    
    delwin(menuWin);
    clear(); refresh();
}

int displayNumberPromptMenu(char title[], char fieldTitle[], int min, int max) {
    int n = 0;
    
    do {
        clear(); refresh();
        
        //variables pour l'affichage du menu
        WINDOW *menuWin = getMenuWindow(1, title);;
        mvwprintw(menuWin, WIN_TOP_MARGIN + 2, 2, "%s", fieldTitle);
        
        wrefresh(menuWin);
        
        mvwscanw(menuWin, WIN_TOP_MARGIN + 2, (int) strlen(fieldTitle) + 3, "%d", &n);
        
        delwin(menuWin);
        clear(); refresh();
    } while(n < min || n > max);
    
    return n;
}

WINDOW* getMenuWindow(int contentHeight, char title[]) {
    //hauteur = nombre de choix possibles + 15 (pour le logo)
    int winHeight = contentHeight + WIN_TOP_MARGIN + 4;
    int winWidth = 70;
    
    //on centre le menu
    int starty = (LINES - winHeight) / 2;
	int startx = (COLS - winWidth) / 2;
    
    WINDOW *win = newwin(winHeight, winWidth, starty, startx);
    
	//on affiche une bordure autour de la fenêtre
    box(win, 0, 0);
    
    //on affiche le logo du jeu
	displayLogo(win, winWidth);
    
    //et deux lignes horizontales
    mvwaddch(win, 11, 0, ACS_LTEE);
    mvwhline(win, 11, 1, ACS_HLINE, winWidth - 1);
    mvwaddch(win, 11, winWidth - 1, ACS_RTEE);
    
    wattron(win, A_UNDERLINE);
    //on affiche un titre
    displayInCenter(win, 12, 0, winWidth, title);
    wattroff(win, A_UNDERLINE);
    
    mvwaddch(win, 13, 0, ACS_LTEE);
    mvwhline(win, 13, 1, ACS_HLINE, winWidth - 1);
    mvwaddch(win, 13, winWidth - 1, ACS_RTEE);
    
    return win;
}
