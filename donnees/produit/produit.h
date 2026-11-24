#include <stdio.h>
#include "donnees/case.h"
typedef enum {
    STANDARD_PRODUIT,
    FRAGILE,
    VOLUMINEUX
} CATEGORIE_PRODUIT;

typedef struct Produit {
    char reference[10];
    char *nom;
    float poids;
    CATEGORIE_PRODUIT categorie;
    int Xetagere;
    int Yetagere;
    int stock;
    TYPE_CASE casePrelev;
    struct Produit *suivant;
} Produit;

typedef struct ElementPile {
    char reference[50];
    int stock;
    float poids;
    CATEGORIE_PRODUIT categorie;
    struct ElementPile *suivant;
} ElementPile;

void afficheListeProduit(Produit *liste);
Produit *creationListeProduit(FILE *commande);
Produit *ajoutProduit(Produit *liste, const char *id,const char *nom, float poids,CATEGORIE_PRODUIT categorie,int Xetagere, int Yetagere, int quantite);
const char *nomTypeProduit(CATEGORIE_PRODUIT t);
int convertirTypeProduit(const char *texte,CATEGORIE_PRODUIT *type);

