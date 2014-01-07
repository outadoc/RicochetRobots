//
//  display.h
//  RicochetRobots
//
//  Created by Baptiste on 28/10/13.
//  Copyright (c) 2013 Baptiste Candellier. All rights reserved.
//

#ifndef RicochetRobots_display_h
#define RicochetRobots_display_h

//define pour la touche "echap"
#define KEY_ESC_ALT 27

//marge haut de la fenêtre avec le logo
#define WIN_LOGO_TOP_MARGIN 13
//largeur de la fenêtre popup sans le logo
#define POPUP_WINDOW_WIDTH  60

//taille de la deuxième colonne
#define SECOND_COL_WIDTH    60
//taille de la première colonne
#define FIRST_COL_WIDTH     (COLS - SECOND_COL_WIDTH)

//largeur du logo
#define LOGO_WIDTH  52

#include <ctype.h>
#include <string.h>

#include <ncurses.h>
#include <menu.h>

#include "game.h"
#include "player.h"
#include "struct.h"
#include "utils.h"

void initDisplay();

int displayMainMenu();
int displayGameBoardSelectionMenu();
int displayGameBoardList();
void displayRobotCaptureMessage(Robot robots[]);

bool wantsToReplay(WINDOW *win, int top);

void displayLogo(WINDOW *win, int width);
void displaySoloGameEnding(GameState *state);
void displayMultiGameEnding(GameState *state);
void displayLeaderboard();

void displayGameBoard(GameState *state);
void displayGameStatus(GameState *state);
void refreshGameDisplay(GameState *state);

int askForPlayersCount();
void askForPlayersInfo(Player players[], int playersCount);
void askForScoreGoals(GameState *state);

void askForSinglePlayerUsername(Player robots[]);
void askForLevelPath(char path[]);
void displayLevelLoadingError(char message[]);

void displayInCenter(WINDOW *win, int starty, int startx, int width, char *string);
int displayMenu(char **choices, int nbChoices, char title[], bool logo);

WINDOW* getMenuWindow(int contentHeight, char title[]);
WINDOW* getMenuWindowNoLogo(int contentHeight, char title[], int yPos, int xPos);

void displayTextPromptMenu(char title[], char fieldTitle[], char result[], int n, int yPos, int xPos);
int displayNumberPromptMenu(char title[], char fieldTitle[], int min, int max, int yPos, int xPos);

#endif
