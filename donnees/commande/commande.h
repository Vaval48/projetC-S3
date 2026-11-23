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