
#ifndef WOLF_FOREST_H
#define WOLF_FOREST_H

#include "coords.h"

#define FOREST_WIDTH 80
#define FOREST_HEIGHT 40
#define FOREST_CHOICE 2

typedef unsigned char Forest[FOREST_HEIGHT][FOREST_WIDTH];

/* Charger la forêt depuis le fichier txt */
int loadForest(Forest forest, const char *filename);

/* Vérifier si une position est valide (pas d'arbre) */
int isValidPosition(const Forest forest, Coords coords);

/* Vérifier si on est en sécurité */
int isSafeZone(Coords coords);


#endif // WOLF_FOREST_H
