
#include <stdio.h>
#include <stdlib.h>

void affichageCarte(FILE *carte)
{
    int longueur = 0;
    int largeur = 0;

    if (carte == NULL)
    {
        printf("Pas d'affichage de la carte");
        return;
    }

    fscanf(carte, "%d %d", &longueur, &largeur); //récupération de la longueur et largeur//
    fgetc(carte); //retour à la ligne//

    char * tableau = calloc((longueur + 1) * largeur,sizeof(char)); // allocation de la taille du tableau qui stocke les caractères de la carte//

    for(int i = 0; i< (longueur + 1) * largeur;i++){ //cette boucle va chercher à remplir le tableau , l'indice i correspond au I+1 ème caractère de la carte//
        tableau[i] = fgetc(carte);
    }
    for (int i = 0; i < (longueur + 1) * largeur; i++)
    {
        printf("%c", tableau[i]);
    }

    free(tableau);
    fclose(carte);
}
