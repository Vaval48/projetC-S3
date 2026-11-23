#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "donnees.h"

int convertirTypeRobot(const char * texte, TYPE_ROBOT * type){
    if (strcmp(texte, "LEGER") == 0){
        *type = LEGER;
        return 1;
    }
    if (strcmp(texte, "STANDARD") == 0){
        *type = STANDARD;
        return 1;
    }
    if (strcmp(texte, "LOURD") == 0){
        *type = LOURD;
        return 1;
    }
    return 0;   // type inconnu
}

const char * nomTypeRobot(TYPE_ROBOT t){
    switch (t){
        case LEGER:    return "léger";
        case STANDARD: return "standard";
        case LOURD:    return "lourd";
        default:       return "inconnu";
    }
}

Robot * ajoutRobot(Robot * liste, const char * id, TYPE_ROBOT type, int x, int y, int batterie){
    Robot * nouveau = malloc(sizeof(Robot));
    if (nouveau == NULL){
        printf("erreur d'allocation\n");
        return liste;
    }

    strcpy(nouveau->id, id);
    nouveau->type = type;
    nouveau->x = x;
    nouveau->y = y;
    nouveau->batterie = batterie;
    nouveau->suivant = NULL;

    if (liste == NULL){
        return nouveau;
    }

    Robot * tmp = liste;
    while (tmp->suivant != NULL){
        tmp = tmp->suivant;
    }
    tmp->suivant = nouveau;

    return liste;
}

Robot * creationListeRobot(FILE * robot){
    if (robot == NULL){
        printf("erreur de création de la liste de robot\n");
        return NULL;
    }

    char id[10];
    char typeTexte[20];
    TYPE_ROBOT type;
    int x, y, batterie;
    int c;
    Robot * tete = NULL;

    // on saute la première ligne (en-tête)
    while ((c = fgetc(robot)) != '\n' && c != EOF) {
    }

    while (fscanf(robot, " %9[^;];%19[^;];%d;%d;%d", id, typeTexte, &x, &y, &batterie) == 5){
        if (convertirTypeRobot(typeTexte, &type)){
            tete = ajoutRobot(tete, id, type, x, y, batterie);
        } else {
            printf("type de robot inconnu : %s (robot %s ignoré)\n", typeTexte, id);
        }
    }

    return tete;
}

void afficheListeRobot(Robot * liste){ // surtout pour tester le chargement
    if (liste == NULL){
        printf("Aucun robot chargé\n");
        return;
    }
    Robot * tmp = liste;
    while (tmp != NULL){
        printf("id : %s , type de robot : %s , x : %d , y : %d , batterie : %d\n",
               tmp->id, nomTypeRobot(tmp->type), tmp->x, tmp->y, tmp->batterie);
        tmp = tmp->suivant;
    }
}