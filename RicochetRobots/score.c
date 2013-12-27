//
//  score.c
//  RicochetRobots
//
//  Created by Baptiste on 27/12/13.
//  Copyright (c) 2013 outadev. All rights reserved.
//

#include "score.h"

int loadScoreBoard(Score scores[]) {
    int i;
    
    char path[MAX_LVL_PATH_SIZE];
    FILE* scoreFile = NULL;
    
    //on ouvre le fichier ~/.outadev/ricochet-robots/scores.csv
    sprintf(path, "%s/.outadev/ricochet-robots/scores.csv", getenv("HOME"));
    scoreFile = fopen(path, "r");
    
    if(scoreFile == NULL) {
        scores = NULL;
        return 0;
    }
    
    for(i = 0; i < MAX_SAVED_SCORES; i++) {
        if(fscanf(scoreFile, "%s,%s,%d\n", scores[i].username, scores[i].boardName, &scores[i].score) == EOF) {
            return i;
        }
    }
    
    return MAX_SAVED_SCORES;
}

void saveScoreBoard(Score scores[], int n) {
    int i;
    
    char path[MAX_LVL_PATH_SIZE];
    FILE* scoreFile = NULL;
    
    //on ouvre le fichier ~/.outadev/ricochet-robots/scores.csv
    sprintf(path, "%s/.outadev/ricochet-robots/scores.csv", getenv("HOME"));
    scoreFile = fopen(path, "w");
    
    if(scoreFile == NULL) {
        scores = NULL;
        return;
    }
    
    for(i = 0; i < n && i < MAX_SAVED_SCORES; i++) {
        fprintf(scoreFile, "%s,%s,%d\n", scores[i].username, scores[i].boardName, scores[i].score);
    }
}

int registerScore(Score score) {
    int n;
    Score scores[MAX_SAVED_SCORES + 1];
    
    //on charge les scores existants
    n = loadScoreBoard(scores);
    
    if(scores == NULL) return 0;
    
    n++;
    //on ajoute le score au tableau
    scores[n] = score;
    //on trie le tout
    qsort(scores, n, sizeof(Score), (compfn) sortByScore);
    
    saveScoreBoard(scores, n);
    return n;
}

//
// Fonction de tri pour qsort.
// Trie les joueurs par score croissant.
//
int sortByScore(Score *a, Score *b) {
    return (a->score > b->score);
}
