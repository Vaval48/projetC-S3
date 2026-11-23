#include <stdio.h>
#include "robot.h"

typedef struct Commande Commande;
typedef struct Station Station;

typedef enum{
    A_VENIR,
    EN_ATTENTE_COMMANDE,
    EN_PREPARATION,
    TERMINEE,
    EN_RETARD,
    REFUSEE
}ETAT_COMMANDE;

typedef enum{
    STANDARD_PRIORITE,
    EXPRESS
}PRIORITE;

struct Commande{
    int id;
    int tickarrive;
    PRIORITE priorite;
    int echeance;
    Station * station_affectee;
    ETAT_COMMANDE etat;
    int tick_fin;
    Commande * suivant;
};

struct Station{
    int id;
    TYPE_CASE type;
    int x;
    int y;
};


