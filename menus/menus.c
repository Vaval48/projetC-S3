#include <stdio_ext.h>
#include <stdlib.h>
#include "affichages/affichages.h"

void menu(){
    int etat_menu = 0;
    if(etat_menu == 0){
        printf("===Simulateur d’entrepôt logistique===\n");
        printf("Choix du scénario à charger:\n");
        printf("(1)exemple\n");
        printf("(2)petit\n");
        printf("(3)moyen\n");
        printf("(4)grand\n");
        scanf("%d",&etat_menu);
    }
    if(etat_menu == 1){
        affichageCarte(fopen("scenarios/01_exemple/carte.txt","r"));
    }
    if(etat_menu == 2){
        affichageCarte(fopen("scenarios/02_petit/carte.txt","r"));
    }
    if(etat_menu == 3){
        affichageCarte(fopen("scenarios/03_moyen/carte.txt","r"));
    }
    if(etat_menu == 4){
        affichageCarte(fopen("scenarios/04_grand/carte.txt","r"));
    }
    
}