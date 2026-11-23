void afficheListeProduit(Produit * liste){ // surtout pour tester le chargement
    if (liste == NULL){
        printf("Aucun produit chargé\n");
        return;
    }
    Produit * tmp = liste;
    while (tmp != NULL){
        printf("id : %s , x : %d , y : %d , poids : %d\n",
               tmp->id, tmp->x, tmp->y, tmp->poids);
        tmp = tmp->suivant;
    }
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

Robot