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
// Affiche le logo du jeu sur la fenêtre en paramètre.
//
void displayLogo(WINDOW *win, int width) {
    if(win == NULL || width < 0) return;
    
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
    mvwprintw(win, 9, 55, "v%s", VERSION);
    
    wrefresh(win);
}

//
// Affiche le menu principal du jeu sur l'écran.
// Si error vaut true, on affiche une erreur à la place du menu.
//
int displayMainMenu() {
    char *choices[] = {
        "Partie solo",
        "Partie multijoueurs",
        "Quitter"
    };
    
    return displayMenu(choices, 3, "MENU PRINCIPAL", true);
}

//
// Affiche le menu de sélection du plateau de jeu sur l'écran.
// Si error vaut true, on affiche une erreur à la place du menu.
//
int displayGameBoardSelectionMenu() {
    char *choices[] = {
        "Plateau predefini",
        "Plateau depuis un fichier",
        "Plateau aleatoire",
        "Retour au menu principal"
    };
    
    return displayMenu(choices, 4, "CHOIX DU PLATEAU", false);
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
    choice = displayMenu(choices, BUILTIN_BOARDS_COUNT, "PLATEAU PREDEFINI...", false);
    
    for(i = 0; i < BUILTIN_BOARDS_COUNT; i++) {
        //on libère la mémoire
        free(choices[i]);
    }
    
    return choice;
}

//
// Affiche le tableau de scores de fin de jeu sur l'écran.
//
void displaySoloGameEnding(GameState *state) {
    if(state == NULL) return;
    
    int i;
    
    WINDOW *win = getMenuWindowNoLogo(ROBOTS_COUNT + 4, "PARTIE TERMINEE", -1, -1);

    mvwprintw(win, 4, 2, "Score total : %d coups", state->turnCount);
    
    for(i = 0; i < ROBOTS_COUNT; i++) {
        mvwprintw(win, 6 + i, 2, "Score de ");
        COL_ON_BOT(win, state->robots[i].robotColor);
        wprintw(win, "%s", getRobotStringColor(state->robots[i].robotColor));
        COL_OFF_BOT(win, state->robots[i].robotColor);
        wprintw(win, " : %d coups", state->robots[i].score);
    }
    
    bool replay = wantsToReplay(win, 7 + ROBOTS_COUNT);
    
    delwin(win);
    
    if(!replay) {
        clear();
        endwin();
        exit(EXIT_SUCCESS);
    }
}

//
// Affiche le tableau de scores de fin de jeu sur l'écran.
//
void displayMultiGameEnding(GameState *state) {
    if(state == NULL) return;
    
    int i;
    char winner[MAX_USERNAME_SIZE];
    
    if(state->players[0].victoryCount == 0) {
        //si le score du meilleur est 0, personne n'a gagné
        strcpy(winner, "PERSONNE !");
    } else if(state->players[0].victoryCount == state->players[1].victoryCount) {
        //si le score du premier est celui du deuxième, il y a égalité
        strcpy(winner, "ÉGALITÉ !");
    } else {
        strcpy(winner, state->players[0].username);
    }
    
    WINDOW *win = getMenuWindowNoLogo(state->playersCount + 4, "PARTIE TERMINEE", -1, -1);
    
    //à ce point, les joueurs sont triés par ordre croissant sur victoryCount
    mvwprintw(win, 4, 2, "Gagnant : %s", winner);
    
    for(i = 0; i < state->playersCount; i++) {
        mvwprintw(win, 6 + i, 2, "Score de %s \t: %d victoires", state->players[i].username, state->players[i].victoryCount);
    }
    
    bool replay = wantsToReplay(win, i + 7);
    
    delwin(win);
    
    if(!replay) {
        clear();
        endwin();
        exit(EXIT_SUCCESS);
    }
}

//
// Demande à l'utilisateur s'il souhaite rejouer.
//
bool wantsToReplay(WINDOW *win, int top) {
    if(win == NULL || top < 0) return false;
    
    //variables pour l'affichage du menu
    ITEM **menuItems = NULL;
    MENU *menu = NULL;
    
    int i = 0, c;
    int nbChoices = 2;
    
    char *choices[] = {
        "Menu Principal",
        "Quitter"
    };
    
    int winWidth = POPUP_WINDOW_WIDTH;
    //largeur du menu = longueur du plus grand des choix possibles
    int menuWidth = 25;
    
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
    
    //on lui précise bien que le menu fait 1 ligne et 2 colonnes
    set_menu_format(menu, 1, 2);
    
    //on associe le menu à une fenêtre et une sous-fenêtre
    set_menu_win(menu, win);
    //fenêtre hauteur largeur x y
    set_menu_sub(menu, derwin(win, nbChoices, menuWidth, top, (winWidth - menuWidth) / 2));
    
    menu_opts_off(menu, O_NONCYCLIC);
    set_menu_mark(menu, ">");
    
    //et hop, on affiche le menu et on rafraîchit.
	post_menu(menu);
	
    refresh();
    wrefresh(win);
    
    curs_set(0);
    noecho();
    
    //boucle pour le menu
    while((c = getch())) {
        switch(c) {
            case KEY_LEFT:
            case KEY_UP:
                menu_driver(menu, REQ_LEFT_ITEM);
                break;
            case KEY_RIGHT:
            case KEY_DOWN:
                menu_driver(menu, REQ_RIGHT_ITEM);
                break;
            case 10: { //entrée
                int choice = item_index(current_item(menu));
                
                unpost_menu(menu);
                free_menu(menu);
                
                for(i = 0; i < nbChoices; ++i)
                    free_item(menuItems[i]);
                
                //si l'indice est 1 on renvoie 0 et vice-versa
                return !choice;
            }
        }
        
        wrefresh(win);
    }
    
    return false;
}

//
// Demande le nombre de joueurs à gérer et le retourne.
//
int askForPlayersCount() {
    return displayNumberPromptMenu("INITIALISATION MULTIJOUEUR", "Nombre de joueurs :", 2, MAX_PLAYERS_COUNT, -1, -1);
}

//
// Demande à chaque joueur son objectif de coups et les stocke dans l'état du jeu.
//
void askForScoreGoals(GameState *state) {
    if(state == NULL) return;
    
    int i;
    
    for(i = 0; i < state->playersCount; i++) {
        char str[MAX_USERNAME_SIZE + 30];
        char title[50];
        
        sprintf(str, "Nombre de coups prévus pour %s :", state->players[i].username);
        sprintf(title, "PREVISIONS POUR DEPLACER LE ROBOT %s", getRobotStringColor(state->robotColorToMove));
        
        state->players[i].goal = displayNumberPromptMenu(title, str, 1, 999, -1, COLS - POPUP_WINDOW_WIDTH - 1);
    }
}

//
// Demande le pseudo de chaque joueur, un par un.
// Retourne le nombre de joueurs
//
void askForPlayersInfo(Player players[], int playersCount) {
    if(players == NULL || playersCount < 0 || playersCount > MAX_PLAYERS_COUNT) return;
    
    int i;
    
    for (i = 0; i < playersCount; i++) {
        char title[22];
        sprintf(title, "Pseudo du joueur %d :", i + 1);
        
        displayTextPromptMenu("PSEUDOS DES JOUEURS", title, players[i].username, MAX_USERNAME_SIZE, -1, -1);
    }
}

//
// Demande le pseudo du joueur et le copie dans chaque robot.
//
void askForSinglePlayerUsername(Player *player) {
    if(player == NULL) return;
    
    displayTextPromptMenu("CHOIX DU PSEUDO", "Pseudo :", player->username, MAX_USERNAME_SIZE, -1, -1);
}

//
// Demande au joueur le chemin du niveau à charger.
//
void askForLevelPath(char path[]) {
    if(path == NULL) return;
    
    displayTextPromptMenu("CHARGER DEPUIS UN FICHIER", "Chemin du fichier niveau :", path, MAX_LVL_PATH_SIZE, -1, -1);
}

//
// Affiche une erreur de chargement du niveau sur la sortie standard.
// Attend que l'utilisateur appuie sur une touche.
//
void displayLevelLoadingError(char message[]) {
    if(message == NULL) return;
    
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
                    
                    COL_ON_BOT_BG(boardWin, state->robots[k].robotColor);
                    
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
                    
                    COL_OFF_BOT_BG(boardWin, state->robots[k].robotColor);
                }
            }
            
            //si la case n'a pas encore de contenu (et donc pas de robot) et que c'est une case objectif
            for (k = 0; k < ROBOTS_COUNT; k++) {
                if(!hasContent && state->gameBoard->objectivesPos[k].x == i && state->gameBoard->objectivesPos[k].y == j) {
                    hasContent = true;
                    
                    COL_ON_BOT(boardWin, k);
                    mvwprintw(boardWin, charLine, charCol + 1, "[X]");
                    COL_OFF_BOT(boardWin, k);
                    
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

//
// Affiche des infos sur le jeu en cours.
//
void displayGameStatus(GameState *state) {
    if(state == NULL) return;
    
    WINDOW *infoWin = newwin((state->playersCount > 1) ? 6 : 5, SECOND_COL_WIDTH, 13, COLS - SECOND_COL_WIDTH - 1);
    box(infoWin, 0, 0);
    
    if(state->playersCount > 1) {
        //si on est en multijoueur
        mvwprintw(infoWin, 1, 2, "Score total \t\t: %d / %d\n", state->currentPlayer->score, state->currentPlayer->goal);
    } else {
        mvwprintw(infoWin, 1, 2, "Score total \t\t: %d\n", state->currentPlayer->score);
    }
    
    mvwprintw(infoWin, 2, 2, "Joueur actuel \t: %s", state->currentPlayer->username);
    mvwprintw(infoWin, 3, 2, "Robot actuel \t\t: ");
    
    COL_ON_BOT(infoWin, state->currentRobot->robotColor);
    wprintw(infoWin, "%s", getRobotStringColor(state->currentRobot->robotColor));
    COL_OFF_BOT(infoWin, state->currentRobot->robotColor);
    
    //si on est en multi, on affiche le robot à déplacer sur l'objectif
    if(state->playersCount > 1) {
        mvwprintw(infoWin, 4, 2, "Robot à déplacer \t: ");
        
        COL_ON_BOT(infoWin, state->robotColorToMove);
        wprintw(infoWin, "%s", getRobotStringColor(state->robotColorToMove));
        COL_OFF_BOT(infoWin, state->robotColorToMove);
    }
    
    refresh();
    wrefresh(infoWin);
    delwin(infoWin);
}

//
// Affiche les scores du jeu en cours.
//
void displayScores(GameState *state) {
    if(state == NULL) return;
    
    int i;
    int height = (state->playersCount > ROBOTS_COUNT) ? state->playersCount + 2 : ROBOTS_COUNT + 2;
    
    WINDOW *scoresWin = newwin(height, SECOND_COL_WIDTH, (state->playersCount > 1) ? 19 : 18, COLS - SECOND_COL_WIDTH - 1);
    box(scoresWin, 0, 0);
    
    for(i = 0; i < ROBOTS_COUNT; i++) {
        mvwprintw(scoresWin, i + 1, 2, "Score de ");
        COL_ON_BOT(scoresWin, state->robots[i].robotColor);
        wprintw(scoresWin, "%s", getRobotStringColor(state->robots[i].robotColor));
        COL_OFF_BOT(scoresWin, state->robots[i].robotColor);
        wprintw(scoresWin, " \t: %d", state->robots[i].score);
    }
    
    if(state->playersCount > 1) {
        for(i = 0; i < state->playersCount; i++) {
            mvwprintw(scoresWin, i + 1, 27, "Score de %s \t: %d", state->players[i].username, state->players[i].victoryCount);
        }
    }
    
    refresh();
    wrefresh(scoresWin);
    delwin(scoresWin);
}

//
// Affiche une fenêtre d'aide sur les commandes disponibles.
//
void displayCommands() {
    WINDOW *cmdWin = newwin(12, SECOND_COL_WIDTH, 1, COLS - SECOND_COL_WIDTH - 1);
    box(cmdWin, 0, 0);
    
    wattron(cmdWin, A_UNDERLINE);
    mvwprintw(cmdWin, 1, 2, "Commandes de partie");
    wattroff(cmdWin, A_UNDERLINE);
    
    mvwprintw(cmdWin, 2, 2, "Echap : quitter la partie");
    mvwprintw(cmdWin, 3, 2, "Flèches directionnelles : déplacer le robot");
    mvwprintw(cmdWin, 4, 2, "X : déplacer dans une direction aléatoire");
    
    wattron(cmdWin, A_UNDERLINE);
    mvwprintw(cmdWin, 6, 2, "Changer de robot");
    wattroff(cmdWin, A_UNDERLINE);
    
    mvwprintw(cmdWin, 7, 2, "R : robot rouge");
    mvwprintw(cmdWin, 8, 2, "B : robot bleu");
    mvwprintw(cmdWin, 9, 2, "V : robot vert");
    mvwprintw(cmdWin, 10, 2, "G : robot gris");
    
    refresh();
    wrefresh(cmdWin);
    delwin(cmdWin);
}

//
// Rafraîchit l'affichage pendant une partie.
// Affiche le plateau de jeu, ainsi qu'un résumé des informations sur la partie en cours.
//
void refreshGameDisplay(GameState *state) {
    if(state == NULL) return;
    
    clear();
    
    displayGameBoard(state);
    displayGameStatus(state);
    displayScores(state);
    displayCommands();
}

//
// Affiche le texte passé en paramètre au centre de la fenêtre.
//
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

//
// Affiche une fenêtre de menu.
//
int displayMenu(char **choices, int nbChoices, char title[], bool logo) {
    if(choices == NULL || nbChoices < 1) return -1;
    
    //variables pour l'affichage du menu
    ITEM **menuItems = NULL;
    MENU *menu = NULL;
    WINDOW *menuWin = NULL;
    
    int i = 0, c;
    int winWidth = POPUP_WINDOW_WIDTH;
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
    menuWin = (logo) ? getMenuWindow(nbChoices, title) : getMenuWindowNoLogo(nbChoices, title, -1, -1);
    
    //on lui précise bien que le menu fait N lignes et 1 colonne
    set_menu_format(menu, nbChoices, 1);
    
    //on associe le menu à une fenêtre et une sous-fenêtre
    set_menu_win(menu, menuWin);
    //fenêtre hauteur largeur x y
    set_menu_sub(menu, derwin(menuWin, nbChoices, menuWidth, (logo) ? 15 : 4, (winWidth - menuWidth) / 2));
    
    menu_opts_off(menu, O_NONCYCLIC);
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
            }
        }
        
        wrefresh(menuWin);
    }
    
    return 0;
}

//
// Affiche une fenêtre de demande de texte.
// Ex: demande du pseudo.
//
void displayTextPromptMenu(char title[], char fieldTitle[], char result[], int n, int yPos, int xPos) {
    if(result == NULL || n < 0) return;
    
    do {
        //variables pour l'affichage du menu
        WINDOW *menuWin = getMenuWindowNoLogo(1, title, yPos, xPos);
        mvwprintw(menuWin, 4, 2, "%s", fieldTitle);
        
        wrefresh(menuWin);
        refresh();
        
        mvwgetnstr(menuWin, 4, (int) strlen(fieldTitle) + 3, result, n);
        
        wclear(menuWin);
        wrefresh(menuWin);
        delwin(menuWin);
    } while(strlen(result) < 1);
}

//
// Affiche une fenêtre de demande d'entier.
// Ex: demande du nombre de joueurs participant.
//
int displayNumberPromptMenu(char title[], char fieldTitle[], int min, int max, int yPos, int xPos) {
    int n = 0;
    
    do {
        //variables pour l'affichage du menu
        WINDOW *menuWin = getMenuWindowNoLogo(1, title, yPos, xPos);
        mvwprintw(menuWin, 4, 2, "%s", fieldTitle);
        
        wrefresh(menuWin);
        refresh();
        
        mvwscanw(menuWin, 4, (int) strlen(fieldTitle) + 3, "%d", &n);
        
        wclear(menuWin);
        wrefresh(menuWin);
        delwin(menuWin);
    } while(n < min || n > max);
    
    return n;
}

//
// Retourne une fenêtre générique avec le logo du jeu.
//
WINDOW* getMenuWindow(int contentHeight, char title[]) {
    if(contentHeight < 0) return NULL;
    
    //hauteur = nombre de choix possibles + 15 (pour le logo)
    int winHeight = contentHeight + WIN_LOGO_TOP_MARGIN + 4;
    int winWidth = POPUP_WINDOW_WIDTH + 10;
    
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
    
    mvprintw(LINES - 1, COLS - 32, "© 2013-2014 Baptiste Candellier");
    
    return win;
}

//
// Retourne une fenêtre popup générique, sans le logo du jeu.
//
WINDOW* getMenuWindowNoLogo(int contentHeight, char title[], int yPos, int xPos) {
    if(contentHeight < 0) return NULL;
    
    //hauteur = nombre de choix possibles + 15 (pour le logo)
    int winHeight = contentHeight + 6;
    int winWidth = POPUP_WINDOW_WIDTH;
    
    //on centre le menu
    int starty = (yPos > 0) ? yPos : (LINES - winHeight) / 2;
	int startx = (xPos > 0) ? xPos : (COLS - winWidth) / 2;
    
    WINDOW *win = newwin(winHeight, winWidth, starty, startx);
    
	//on affiche une bordure autour de la fenêtre
    box(win, 0, 0);
    
    wattron(win, A_UNDERLINE);
    //on affiche un titre
    displayInCenter(win, 1, 0, winWidth, title);
    wattroff(win, A_UNDERLINE);
    
    //bordure du titre
    mvwaddch(win, 2, 0, ACS_LTEE);
    mvwhline(win, 2, 1, ACS_HLINE, winWidth - 1);
    mvwaddch(win, 2, winWidth - 1, ACS_RTEE);
    
    return win;
}