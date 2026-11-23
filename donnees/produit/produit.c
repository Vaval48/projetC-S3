#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produit.h"

void afficheListeProduit(Produit * liste) {
    if (liste == NULL) {
        printf("Aucun produit chargé\n");
        return;
    }
    Produit * tmp = liste;
    while (tmp != NULL) {
        printf("id : %s , nom : %s , poids : %.2f kg , categorie : %s , Xetagere : %d , Yetagere : %d , stock : %d\n",
               tmp->reference,
               tmp->nom,
               tmp->poids,
               nomTypeProduit(tmp->categorie),
               tmp->Xetagere,
               tmp->Yetagere,
               tmp->stock);
        tmp = tmp->suivant;
    }
}

Produit * creationListeProduit(FILE * commande) {
    if (commande == NULL) {
        printf("erreur de création de la liste de produit\n");
        return NULL;
    }
    char id[10];
    char nom[50];
    char categorieTexte[20];
    float poids;
    int Xetagere, Yetagere, stock;
    int c;
    Produit * tete = NULL;
    // on saute la première ligne (en-tête)
    while ((c = fgetc(commande)) != '\n' && c != EOF) {
    }
    while (fscanf(commande, "%9[^;];%49[^;];%f;%19[^;];%d;%d;%d",id, nom, &poids, categorieTexte,&Xetagere, &Yetagere, &stock) == 7) {
        CATEGORIE_PRODUIT categorie;
        if (convertirTypeProduit(categorieTexte, &categorie)) {
            tete = ajoutProduit(tete, id, nom, poids,categorie, Xetagere,Yetagere, stock);
        }
    }
    return tete;
}

Produit * ajoutProduit(Produit * liste, const char * id,const char * nom, float poids,CATEGORIE_PRODUIT categorie,int Xetagere, int Yetagere, int quantite) {
    Produit * nouveau = malloc(sizeof(Produit));
    if (nouveau == NULL) {
        printf("erreur d'allocation\n");
        return liste;
    }
    strcpy(nouveau->reference, id);
    // allocation de mémoire pour le nom
    nouveau->nom = malloc(strlen(nom) + 1);
    if (nouveau->nom == NULL) {
        free(nouveau);
        printf("erreur d'allocation du nom\n");
        return liste;
    }
    strcpy(nouveau->nom, nom);
    nouveau->poids = poids;
    nouveau->categorie = categorie;
    nouveau->Xetagere = Xetagere;
    nouveau->Yetagere = Yetagere;
    nouveau->stock = quantite;
    // case de prélèvement pas encore définie
    nouveau->casePrelev = NON_DEFINI;
    nouveau->suivant = NULL;
    if (liste == NULL) {
        return nouveau;
    }
    Produit * tmp = liste;
    while (tmp->suivant != NULL) {
        tmp = tmp->suivant;
    }
    tmp->suivant = nouveau;
    return liste;
}

const char * nomTypeProduit(CATEGORIE_PRODUIT t) {
    // va lire le type du produit pour le renvoyer sous forme de texte
    switch (t) {
        case FRAGILE:
            return "fragile";
        case STANDARD_PRODUIT:
            return "standard";
        case VOLUMINEUX:
            return "volumineux";
        default:
            return "inconnu";
    }
}

int convertirTypeProduit(const char * texte, CATEGORIE_PRODUIT * type) {
    // convertit le texte du CSV en catégorie de produit
    if (strcmp(texte, "FRAGILE") == 0) {
        *type = FRAGILE;
        return 1;
    }
    if (strcmp(texte, "STANDARD") == 0) {
        *type = STANDARD_PRODUIT;
        return 1;
    }
    if (strcmp(texte, "VOLUMINEUX") == 0) {
        *type = VOLUMINEUX;
        return 1;
    }
    return 0;
}

