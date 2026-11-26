#include "donnees/robot/robot.h"
#include "donnees/carte/carte.h"

char * ajoutDesRobotsCarte(char * carte, Robot * listeRobots, int longueurCarte, int largeurCarte){
    if (carte == NULL){
        return NULL;
    }

    Robot * tmp = listeRobots;
    while (tmp != NULL){
        int x = tmp->x;
        int y = tmp->y;

        if (x >= 0 && x < longueurCarte && y >= 0 && y < largeurCarte){
            carte[indiceCarte(x, y, longueurCarte)] = 'R';
        } else {
            printf("robot %s hors de la carte (%d, %d)\n", tmp->id, x, y);
        }

        tmp = tmp->suivant;
    }
    return carte;
}