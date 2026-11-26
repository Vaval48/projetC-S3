#ifndef ROBOT_H
#define ROBOT_H

#include <stdio.h>
typedef struct Robot Robot;
typedef struct Produit Produit;
typedef struct Commande Commande;
typedef struct Station Station;
typedef struct Entrepot Entrepot;
typedef struct ElementPile ElementPile;


typedef enum{
    LEGER,
    STANDARD,
    LOURD
}TYPE_ROBOT;

typedef enum{
    LIBRE,
    EN_MISSION,
    EN_ATTENTE,
    EN_CHARGE,
    EN_PANNE
}ETAT_ROBOT;


struct Robot{
    char id[10];
    TYPE_ROBOT type;
    ETAT_ROBOT etat;
    int x;
    int y;
    int batterie;
    int charge; //charge en kg (!= de batterie)
    Robot * suivant;
    ElementPile * bac;
};

Robot * ajoutRobot(Robot * liste, const char * id, TYPE_ROBOT type, int x, int y, int batterie);
Robot * creationListeRobot(FILE * robot);
void afficheListeRobot(Robot * liste);
int convertirTypeRobot(const char * texte, TYPE_ROBOT * type);

#endif