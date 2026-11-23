#include <stdio.h>
#include <stdlib.h>
#include "affichages/affichages.h"
#include "menus/menus.h"
#include "donnees/robot/robot.h"
#include "donnees/produit/produit.h"
#include "donnees/commande/commande.h"
int main(){
    Robot * listeRobot = creationListeRobot(fopen("scenarios/01_exemple/robots.csv","r"));
    Produit * listeProduit = creationListeProduit(fopen("scenarios/04_grand/produits.csv","r"));
    Commande * listeCommande = creationListeCommande(fopen("scenarios/01_exemple/commandes.csv","r"));
    afficheListeRobot(listeRobot);
    afficherListeCommandes(listeCommande);
    return 0;
}