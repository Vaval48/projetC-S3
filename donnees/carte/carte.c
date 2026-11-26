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
    // on saute la fin de la ligne des dimensions
    while ((c = fgetc(carte)) != '\n' && c != EOF) {
    }

    int total = (*longueur) * (*largeur);
    char * tableau = malloc(total);
    if (tableau == NULL){
        printf("Erreur d'allocation de la carte\n");
        return NULL;
    }

    int i = 0;
    while (i < total && (c = fgetc(carte)) != EOF){
        if (c != '\n' && c != '\r'){      // les fins de ligne ne sont pas stockées
            tableau[i++] = (char) c;
        }
    }

    if (i < total){
        printf("Erreur : la carte est incomplète (%d caractères sur %d)\n", i, total);
        free(tableau);
        return NULL;
    }

    return tableau;
}

void affichageCarte(const char * carte, int longueur, int largeur){
    if (carte == NULL){
        printf("Aucune carte à afficher\n");
        return;
    }

    for (int y = 0; y < largeur; y++){
        for (int x = 0; x < longueur; x++){
            printf("%c", carte[y * longueur + x]);
        }
        printf("\n");
    }
}

int indiceCarte(int x, int y, int longueur){//pour placer les éléments plus rapidement sur la carte (c'est la conversion coordonnées x,y en un indice de tableau simple)//
    return y * longueur + x;
}