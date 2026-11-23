#include <stdio_ext.h>
#include <stdlib.h>
#include "affichages/affichages.h"


void menu(){
    int etat_menu = 0;

    printf("╔══════════════════════════════════════════════════╗\n");
    printf("║        SIMULATEUR D'ENTREPOT LOGISTIQUE          ║\n");
    printf("╠══════════════════════════════════════════════════╣\n");
    printf("║  Veuillez choisir le scenario a charger :        ║\n");
    printf("║                                                  ║\n");
    printf("║       [ 1 ] Exemple                              ║\n");
    printf("║       [ 2 ] Petit                                ║\n");
    printf("║       [ 3 ] Moyen                                ║\n");
    printf("║       [ 4 ] Grand                                ║\n");
    printf("║                                                  ║\n");
    printf("║       [ 0 ] Quitter                              ║\n");
    printf("╚══════════════════════════════════════════════════╝\n\n");
    printf(" > Votre choix : ");
    scanf("%d", &etat_menu);
    printf("\n");

    if(etat_menu == 0){
        printf("Au revoir !\n");
        exit(0);
    }
    else if(etat_menu == 1){
        affichageCarte(fopen("scenarios/01_exemple/carte.txt","r"));
    }
    else if(etat_menu == 2){
        affichageCarte(fopen("scenarios/02_petit/carte.txt","r"));
    }
    else if(etat_menu == 3){
        affichageCarte(fopen("scenarios/03_moyen/carte.txt","r"));
    }
    else if(etat_menu == 4){
        affichageCarte(fopen("scenarios/04_grand/carte.txt","r"));
    }    
}