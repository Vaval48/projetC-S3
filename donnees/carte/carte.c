#include <stdio.h>
#include <stdlib.h>
#include "carte.h"
char * creationListeCarte(FILE * carte, int * longueur, int * largeur){
    if (carte == NULL){
        printf("Erreur : fichier de carte introuvable\n");
        return NULL;
    }

    if (fscanf(carte, "%d %d", longueur, largeur) != 2 || *longueur <= 0 || *largeur <= 0){
        printf("Erreur : dimensions de la carte invalides\n");
        return NULL;
    }

    int c;
    // on saute la ligne des dimensions//
    while ((c = fgetc(carte)) != '\n' && c != EOF) {
    }

    int total = (*longueur + 1) * (*largeur);    // +1 par ligne pour le \n
    char * tableau = malloc(total + 1);          // +1 pour le '\0' final
    if (tableau == NULL){
        printf("Erreur d'allocation de la carte\n");
        return NULL;
    }

    int i = 0;
    while (i < total && (c = fgetc(carte)) != EOF){
        tableau[i++] = c;
    }

    // dernière ligne sans \n dans le fichier : on le rajoute
    if (i == total - 1){
        tableau[i++] = '\n';
    }

    if (i < total){
        printf("Erreur : la carte est incomplète (%d caractères sur %d)\n", i, total);
        free(tableau);
        return NULL;
    }

    tableau[total] = '\0';
    return tableau;
}

void affichageCarte(char * carte){
    if (carte == NULL){
        printf("Aucune carte à afficher\n");
        return;
    }
    printf("%s",carte);
}