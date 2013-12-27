//
//  score.c
//  RicochetRobots
//
//  Created by Baptiste on 27/12/13.
//  Copyright (c) 2013 Baptiste Candellier. All rights reserved.
//
//  Fonctions relatives au système de high-scores
//

#include "score.h"

//
// Charge le fichier de scores.
// Insère les scores dans l'array passé en paramètre.
//
int loadScoreBoard(Score scores[]) {
    int i;
    
    char path[MAX_LVL_PATH_SIZE];
    FILE* scoreFile = NULL;
    
    //on ouvre le fichier ~/.Baptiste Candellier/ricochet-robots/scores.csv
    getPrefsPath(path, "scores.csv");
    scoreFile = fopen(path, "r");
    
    if(scoreFile == NULL) {
        scores = NULL;
        return 0;
    }
    
    for(i = 0; i < MAX_SAVED_SCORES_COUNT; i++) {
        //on lit chaque ligne du fichier sous la forme pseudo,score,plateau
        int err = fscanf(scoreFile, "%[^,],%[^,],%d\n", scores[i].username, scores[i].boardName, &scores[i].score);
        if(err == EOF) {
            fclose(scoreFile);
            return i;
        }
    }
    
    fclose(scoreFile);
    return MAX_SAVED_SCORES_COUNT - 1;
}

//
// Écrit les scores passés en paramètres sur le disque.
//
void saveScoreBoard(Score scores[], int n) {
    int i;
    
    char path[MAX_LVL_PATH_SIZE];
    FILE* scoreFile = NULL;
    
    //on cherche le fichier ~/.Baptiste Candellier/ricochet-robots/scores.csv
    getPrefsPath(path, "scores.csv");
    
    //on créé le chemin du fichier, puisque fopen ne le fait pas pour nous
    mkpath(path, 0755);
    
    //on l'ouvre en écriture
    scoreFile = fopen(path, "w");
    
    if(scoreFile == NULL) {
        scores = NULL;
        return;
    }
    
    for(i = 0; i < n && i < MAX_SAVED_SCORES_COUNT; i++) {
        //on écrit chaque score dans le fichier au format CSV
        fprintf(scoreFile, "%s,%s,%d\n", scores[i].username, scores[i].boardName, scores[i].score);
    }
    
    fclose(scoreFile);
}

//
// Enregistre un score dans la base de données.
//
int registerScore(Score score) {
    int n;
    Score scores[MAX_SAVED_SCORES_COUNT + 1];
    
    //on charge les scores existants
    n = loadScoreBoard(scores);
    
    if(scores == NULL) return 0;
    
    //on ajoute le score au tableau
    scores[n] = score;
    
    n++;
    
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
    //on trie en fonction du score
    if(a->score > b->score) return true;
    else if(a->score < b->score) return false;
    
    //puis en fonction du nom du plateau
    if(strcmp(a->boardName, b->boardName) > 0) return true;
    
    return false;
}
