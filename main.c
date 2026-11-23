#include <stdio.h>
#include <stdlib.h>
#include "affichages/affichages.h"
#include "menus/menus.h"
#include "donnees/donnees.h"
int main(){
    Robot * listeRobot = creationListeRobot(fopen("scenarios/01_exemple/robots.csv","r"));
    afficheListeRobot(listeRobot);
    return 0;
}