typedef struct Robot Robot;
typedef struct Produit Produit;
typedef struct Commande Commande;
typedef struct Station Station;
typedef struct Entrepot Entrepot;

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
    STANDARD,
    FRAGILE,
    VOLUMINEUX
}CATEGORIE_PRODUIT;

typedef enum{
    STANDARD,
    EXPRESS
}PRIORITE;

typedef enum{
    A_VENIR,
    EN_ATTENTE,
    EN_PREPARATION,
    TERMINEE,
    EN_RETARD,
    REFUSEE
}ETAT_COMMANDE;


struct Robot{
    int id;
    TYPE_ROBOT type;
    ETAT_ROBOT etat;
    int x;
    int y;
    int batterie;
    int charge; //charge en kg (!= de batterie)

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
    PRIORITE priorite;
};