#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commande.h"

int convertirPrioriteCommande(const char * texte, PRIORITE * priorite){
    if (strcmp(texte, "STANDARD_PRIORITE") == 0){
        *priorite = STANDARD_PRIORITE;
        return 1;
    }
    if (strcmp(texte, "EXPRESS") == 0){
        *priorite = EXPRESS;
        return 1;
    }
    return 0;
}

Commande * ajoutCommande(Commande * liste, int id, int tickarrive,
     PRIORITE priorite, int echeance, Station * station_affectee, 
     ETAT_COMMANDE etat, int tick_fin){

        Commande * nouveau = malloc(sizeof(Commande));
        if (nouveau == NULL){
            printf("Problème au cours de l'allocation de mémoire pour une commande.\n");
            return liste;
        }
        nouveau -> id = id;
        nouveau -> tickarrive = tickarrive;
        nouveau -> priorite = priorite;
        nouveau -> echeance = echeance;
        nouveau -> station_affectee = station_affectee;
        nouveau -> etat = etat;
        nouveau -> tick_fin = tick_fin;
        nouveau -> suivant = NULL;
        if (liste == NULL){
            return nouveau;
        }
        Commande * tmp = liste;         //Ajout de la commande à la fin de la liste
        while (tmp -> suivant != NULL){
            tmp = tmp -> suivant;
        }
        tmp -> suivant = nouveau;
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
    if (liste == NULL){
        return NULL;
    }
    Commande *tmp = liste;
    while(tmp != NULL){
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
        free(supprimer);
    }
    return liste;
}

void afficherListeCommandes(Commande *liste){
    Commande *tmp = liste;
    while (tmp != NULL){
        printf("Commande ID: %d | Tick Arrive: %d | Priorité: %d | Echéance: %d | Station affectée : %d | Etat: %d |Tick fin: %d\n",
        tmp->id, tmp->tickarrive, tmp->priorite, tmp->echeance, tmp->station_affectee->id, tmp->etat, tmp->tick_fin);
        tmp = tmp->suivant;
    }
}

void libereListeCommandes(Commande *liste){
    Commande *tmp;
    while (liste != NULL){
        tmp = liste;
        liste = liste->suivant;
        free(tmp);
    }
}