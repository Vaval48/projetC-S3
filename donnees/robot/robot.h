#include <stdio.h>
typedef struct Robot Robot;
typedef struct Produit Produit;
typedef struct Commande Commande;
typedef struct Station Station;
typedef struct Entrepot Entrepot;
typedef struct ElementPile ElementPile;


typedef enum{
    MUR,
    ETAGERE,
    VERS_HAUT,
    VERS_BAS,
    VERS_GAUCHE,
    VERS_DROITE,
    STATION_PREPARATION,
    STATION_CHARGE
}TYPE_CASE;

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

typedef enum{
    STANDARD_PRIORITE,
    EXPRESS
}PRIORITE;

typedef enum{
    A_VENIR,
    EN_ATTENTE_COMMANDE,
    EN_PREPARATION,
    TERMINEE,
    EN_RETARD,
    REFUSEE
}ETAT_COMMANDE;


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

struct Produit{
    int reference;
    char * nom;
    int poid;
    CATEGORIE_PRODUIT categorie;
    int Xetagere;
    int Yetagere;
    int stock;
    TYPE_CASE casePrelev;
};

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

struct ElementPile
{
  char reference[50];
  int quantite;
  int poid;
  CATEGORIE_PRODUIT Produit;
  ElementPile * suivant;
};

Robot * ajoutRobot(Robot * liste, const char * id, TYPE_ROBOT type, int x, int y, int batterie);
Robot * creationListeRobot(FILE * robot);
void afficheListeRobot(Robot * liste);
int convertirTypeRobot(const char * texte, TYPE_ROBOT * type);
const char * nomTypeRobot(TYPE_ROBOT t);