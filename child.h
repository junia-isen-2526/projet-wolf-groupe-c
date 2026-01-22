
#ifndef WOLF_CHILD_H
#define WOLF_CHILD_H

#include "coords.h"
#include "forest.h"
#include "graph.h"

typedef struct {
    Coords coords;
    Coords startCoords;
    unsigned char isSafe;
    unsigned char isDead;
} Child;

/* Initialiser l'enfant */
void initChild(Child *child, Coords startPos);

/* Vérifier si l'enfant est safe */
void updateSafeStatus(Child *child);

/* Déplacer l'enfant */
int moveChildStep(Child *child, const Forest forest, Graph *g);

/* Vérifier si l'enfant est mangé par le loup */
int isChildEaten(const Child *child, int wolfX, int wolfY);

/* Trouver une position aléatoire valide sur bord de la forêt */
Coords findRandomEdgePosition(const Forest forest);

#endif // WOLF_CHILD_H