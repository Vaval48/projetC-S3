#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commande.h"

int convertirPrioriteCommande(const char * texte, PRIORITE * priorite){
    if (strcmp(texte, "STANDARD") == 0){      // texte du CSV
        *priorite = STANDARD_PRIORITE;        // valeur de l'enum
        return 1;
    }
    if (strcmp(texte, "EXPRESS") == 0){
        *priorite = EXPRESS;
        return 1;
    }
    return 0;
}

LigneCommande * ajoutLigneCommande(LigneCommande * liste, const char * produit, int quantite){
    LigneCommande * nouvelle = malloc(sizeof(LigneCommande));
    if (nouvelle == NULL){
        printf("Problème d'allocation pour une ligne de commande.\n");
        return liste;
    }
    strncpy(nouvelle->produit, produit, sizeof(nouvelle->produit) - 1);
    nouvelle->produit[sizeof(nouvelle->produit) - 1] = '\0';
    nouvelle->quantite = quantite;
    nouvelle->suivant = NULL;

    if (liste == NULL){
        return nouvelle;
    }
    LigneCommande * tmp = liste;
    while (tmp->suivant != NULL){
        tmp = tmp->suivant;
    }
    tmp->suivant = nouvelle;
    return liste;
}

void libereLignesCommande(LigneCommande * liste){
    LigneCommande * tmp;
    while (liste != NULL){
        tmp = liste;
        liste = liste->suivant;
        free(tmp);
    }
}

/* Découpe "P0001x4|P0002x1" et construit la liste de lignes */
static LigneCommande * parseLignes(char * texte){
    LigneCommande * lignes = NULL;

    // retire un éventuel \r (fichier Windows)
    texte[strcspn(texte, "\r\n")] = '\0';

    char * token = strtok(texte, "|");
    while (token != NULL){
        char produit[10];
        int quantite;
        if (sscanf(token, "%9[^x]x%d", produit, &quantite) == 2){
            lignes = ajoutLigneCommande(lignes, produit, quantite);
        } else {
            printf("ligne de commande mal formée : %s\n", token);
        }
        token = strtok(NULL, "|");
    }
    return lignes;
}

/* ---------- Commandes ---------- */

Commande * ajoutCommande(Commande * liste, int id, int tickarrive,
     PRIORITE priorite, int echeance, Station * station_affectee,
     ETAT_COMMANDE etat, int tick_fin){

    Commande * nouveau = malloc(sizeof(Commande));
    if (nouveau == NULL){
        printf("Problème au cours de l'allocation de mémoire pour une commande.\n");
        return liste;
    }
    nouveau->id = id;
    nouveau->tickarrive = tickarrive;
    nouveau->priorite = priorite;
    nouveau->echeance = echeance;
    nouveau->station_affectee = station_affectee;
    nouveau->etat = etat;
    nouveau->tick_fin = tick_fin;
    nouveau->lignes = NULL;          // rempli ensuite par creationListeCommande
    nouveau->suivant = NULL;

    if (liste == NULL){
        return nouveau;
    }
    Commande * tmp = liste;          // ajout à la fin de la liste
    while (tmp->suivant != NULL){
        tmp = tmp->suivant;
    }
    tmp->suivant = nouveau;
    return liste;
}

Commande *insererCommandeTrieeTick(Commande *liste, Commande *commande){
    if (commande == NULL){
        return liste;
    }
    if (liste == NULL || commande->tickarrive < liste->tickarrive){
        commande->suivant = liste;
        return commande;
    }
    Commande *tmp = liste;
    while (tmp->suivant != NULL && tmp->suivant->tickarrive <= commande->tickarrive){
        tmp = tmp->suivant;
    }
    commande->suivant = tmp->suivant;
    tmp->suivant = commande;
    return liste;
}

Commande *rechercherCommandeId(Commande *liste, int id){
    Commande *tmp = liste;
    while (tmp != NULL){
        if (tmp->id == id){
            return tmp;
        }
        tmp = tmp->suivant;
    }
    return NULL;
}

Commande *supprimerCommandeId(Commande *liste, int id){
    if (liste == NULL){
        return NULL;
    }

    if (liste->id == id){
        Commande *tmp = liste;
        liste = liste->suivant;
        libereLignesCommande(tmp->lignes);
        free(tmp);
        return liste;
    }

    Commande *tmp = liste;
    while (tmp->suivant != NULL && tmp->suivant->id != id){
        tmp = tmp->suivant;
    }
    Commande *supprimer = tmp->suivant;
    if (supprimer != NULL){
        tmp->suivant = supprimer->suivant;
        libereLignesCommande(supprimer->lignes);
        free(supprimer);
    }
    return liste;
}

void afficherListeCommandes(Commande *liste){
    Commande *tmp = liste;
    while (tmp != NULL){
        printf("Commande ID: %d | Tick arrivée: %d | Priorité: %d | Echéance: %d | ",
               tmp->id, tmp->tickarrive, tmp->priorite, tmp->echeance);
        if (tmp->station_affectee != NULL){
            printf("Station affectée: %d | ", tmp->station_affectee->id);
        } else {
            printf("Station affectée: aucune | ");
        }
        printf("Etat: %d | Tick fin: %d\n", tmp->etat, tmp->tick_fin);

        printf("   Lignes :");
        LigneCommande * l = tmp->lignes;
        while (l != NULL){
            printf(" %s x%d", l->produit, l->quantite);
            l = l->suivant;
        }
        printf("\n");

        tmp = tmp->suivant;
    }
}

void libereListeCommandes(Commande *liste){
    Commande *tmp;
    while (liste != NULL){
        tmp = liste;
        liste = liste->suivant;
        libereLignesCommande(tmp->lignes);
        free(tmp);
    }
}

Commande * creationListeCommande(FILE * fichier){
    if (fichier == NULL){
        printf("erreur de création de la liste de commandes\n");
        return NULL;
    }

    int id, tickarrive, echeance;
    char prioriteTexte[20];
    char lignesTexte[100];
    PRIORITE priorite;
    int c;
    Commande * tete = NULL;

    // on saute l'en-tête
    while ((c = fgetc(fichier)) != '\n' && c != EOF) {
    }

    while (fscanf(fichier, " C%d;%d;%19[^;];%d;%99[^\n]",
                  &id, &tickarrive, prioriteTexte, &echeance, lignesTexte) == 5){
        if (convertirPrioriteCommande(prioriteTexte, &priorite)){
            tete = ajoutCommande(tete, id, tickarrive, priorite, echeance,
                                 NULL, EN_ATTENTE_COMMANDE, -1);

            // on rattache les lignes à la commande qui vient d'être ajoutée
            Commande * cmd = rechercherCommandeId(tete, id);
            if (cmd != NULL){
                cmd->lignes = parseLignes(lignesTexte);
            }
        } else {
            printf("priorité inconnue : %s (commande %d ignorée)\n", prioriteTexte, id);
        }
    }

    return tete;
}