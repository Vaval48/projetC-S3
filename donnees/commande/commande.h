#define COMMANDE_H

#include <stdio.h>
#include "donnees/case.h"
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

typedef struct LigneCommande {
    char produit[10];               // ex : "P0001"
    int quantite;                   // ex : 4
    struct LigneCommande * suivant;
} LigneCommande;

struct Commande{
    int id;
    int tickarrive;
    PRIORITE priorite;
    int echeance;
    Station * station_affectee;
    ETAT_COMMANDE etat;
    int tick_fin;
    LigneCommande * lignes;
    Commande * suivant;
};

struct Station{
    int id;
    TYPE_CASE type;
    int x;
    int y;
};

int convertirPrioriteCommande(const char * texte, PRIORITE * priorite);

LigneCommande * ajoutLigneCommande(LigneCommande * liste, const char * produit, int quantite);
void libereLignesCommande(LigneCommande * liste);

Commande * ajoutCommande(Commande * liste, int id, int tickarrive,PRIORITE priorite, int echeance, Station * station_affectee,ETAT_COMMANDE etat, int tick_fin);
Commande * insererCommandeTrieeTick(Commande * liste, Commande * commande);
Commande * rechercherCommandeId(Commande * liste, int id);
Commande * supprimerCommandeId(Commande * liste, int id);
void afficherListeCommandes(Commande * liste);
void libereListeCommandes(Commande * liste);
Commande * creationListeCommande(FILE * fichier);
