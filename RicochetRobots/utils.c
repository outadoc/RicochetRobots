//
//  utils.c
//  RicochetRobots
//
//  Created by Baptiste on 29/11/13.
//  Copyright (c) 2013 outadev. All rights reserved.
//
//  Fonctions diverses et utiles
//

#include "utils.h"

//
// Génère un entier pseudo aléatoire compris entre min (compris) et max (non compris).
//
int rand_between(int min, int max) {
    return rand() % (max - min) + min;
}

//
// Retourne la longueur du string le plus grand parmi un tableau de strings
//
int max_strlen(char **str, int n) {
    if(str == NULL || n <= 0) return 0;
    
    int i;
    int maxlen = 0;
    
    for(i = 0; i < n; i++) {
        int currlen = (int) strlen(str[i]);
        if(currlen > maxlen) maxlen = currlen;
    }
    
    return maxlen;
}

//
// Créé tous les dossiers intermédiaires nécessaires à la création d'un fichier.
// Utile lorsqu'elle est exécutée avant fopen, vu que l'ouverture échouera si le dossier
// parent n'existe pas.
//
// Source : StackOverflow
//
int mkpath(char* file_path, mode_t mode) {
    assert(file_path && *file_path);
    char* p;
    for (p=strchr(file_path+1, '/'); p; p=strchr(p+1, '/')) {
        *p='\0';
        if (mkdir(file_path, mode)==-1) {
            if (errno!=EEXIST) { *p='/'; return -1; }
        }
        *p='/';
    }
    return 0;
}

//
// Retourne le chemin complet pour un fichier de préférences utilisateur.
//
void getPrefsPath(char path[], char fileName[]) {
    sprintf(path, "%s/.outadev/ricochet-robots/%s", getenv("HOME"), fileName);
}