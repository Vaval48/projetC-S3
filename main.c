#include <stdio.h>
#include <stdlib.h>
#include "affichages/affichages.h"
#include "menus/menus.h"

int main(){
    FILE * carte = fopen("scenarios/01_exemple/carte.txt","r");
    affichageCarte(carte);
    return 0;
}