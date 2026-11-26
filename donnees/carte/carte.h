#include <stdio.h>
#include <stdlib.h>

char * creationListeCarte(FILE * carte, int * longueur, int * largeur);
void affichageCarte(const char * carte, int longueur, int largeur);
int indiceCarte(int x, int y, int longueur);