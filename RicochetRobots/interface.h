//
//  display.h
//  RicochetRobots
//
//  Created by Baptiste on 28/10/13.
//  Copyright (c) 2013 outadev. All rights reserved.
//

#ifndef RicochetRobots_display_h
#define RicochetRobots_display_h

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

#define WIN_TOP_MARGIN 13
#define SECOND_COL_WIDTH 60
#define FIRST_COL_WIDTH (COLS - SECOND_COL_WIDTH)

#include <ctype.h>
#include <string.h>

#include <ncurses.h>
#include <menu.h>

#include "game.h"
#include "player.h"
#include "struct.h"
#include "utils.h"

int displayMainMenu();
int displayGameBoardSelectionMenu();
int displayGameBoardList();

bool wantsToReplay();

void listBuiltInBoards();
void displayLogo(WINDOW *win, int width);
void clearScreen();
void displayGameEnding(Player *winner, GameState *state);

void displayGameBoard(GameState *state);
void displayGameStatus(GameState *currentGame);
void refreshGameDisplay(GameState *currentGame);

void askForPlayersInfo(Player players[]);
void askForSinglePlayerUsername(Player robots[]);
void askForLevelPath(char path[]);
void displayLevelLoadingError(char message[]);

void displayInCenter(WINDOW *win, int starty, int startx, int width, char *string);
int displayMenu(char **choices, int nbChoices, char title[]);
WINDOW* getMenuWindow(int contentHeight, char title[]);
void displayTextPromptMenu(char title[], char fieldTitle[], char result[], int n);

#endif
