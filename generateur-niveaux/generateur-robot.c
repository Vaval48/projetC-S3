#include <stdlib.h>
#include "donnees/robot/robot.h"

void generateurRobot(int nombreRobot) {
    char ** listeIdRobot = malloc(sizeof(char *) * nombreRobot);
    TYPE_ROBOT listeType = malloc(sizeof(TYPE_ROBOT) * nombreRobot);
    for (int i = 0; i < nombreRobot; i++) {
        listeIdRobot[i] = malloc(sizeof(char) * 10);
        int numero = i + 1; // Mettre juste "i" pour commencer à R00
        listeIdRobot[i][0] = 'R';
        listeIdRobot[i][1] = '0' + (numero / 10); // Chiffre des dizaines
        listeIdRobot[i][2] = '0' + (numero % 10); // Chiffre des unités
        listeIdRobot[i][3] = '\0';                // Fin de la chaîne obligatoire en C

        listeType[i] = rand()%3;
    }
    
}
