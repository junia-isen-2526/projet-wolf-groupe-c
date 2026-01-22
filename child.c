/* ========================================================
   CHILD.C - Implémentation de l'enfant (CORRIGÉE v2)
   ======================================================== */

#include "child.h"
#include <stdlib.h>
#include <stdio.h>

void initChild(Child *child, Coords startPos) {
    if (!child) return;

    child->coords = startPos;
    child->startCoords = startPos;
    child->isDead = 0;
    child->isSafe = 0; // Ne jamais commencer en sécurité
}

void updateSafeStatus(Child *child) {
    if (!child) return;
    child->isSafe = isSafeZone(child->coords);
}

int moveChildStep(Child *child, const Forest forest, Graph *g) {
    if (!child || !forest || !g) return -1;

    // Vérifier d'abord si l'enfant est déjà en sécurité
    if (child->isSafe) {
        printf("[ENFANT] En securite aux coordonnees (%d, %d)\n",
               child->coords.x, child->coords.y);
        return 1;  // Jeu terminé avec succès
    }

    // Générer un déplacement aléatoire (8 directions)
    // Directions : NW=0, N=1, NE=2, W=3, E=4, SW=5, S=6, SE=7
    int dx[] = {-1,  0,  1, -1,  1, -1,  0,  1};
    int dy[] = {-1, -1, -1,  0,  0,  1,  1,  1};

    // Essayer de trouver un déplacement valide
    for (int attempt = 0; attempt < 8; attempt++) {
        int dir = rand() % 8;
        int newX = child->coords.x + dx[dir];
        int newY = child->coords.y + dy[dir];

        // Vérifier les limites AVANT de créer les coordonnées
        if (newX < 0 || newX >= FOREST_WIDTH ||
            newY < 0 || newY >= FOREST_HEIGHT) {
            continue;
        }

        // Vérifier si la nouvelle position est valide
        Coords newCoords = createCoords((unsigned char)newX, (unsigned char)newY);
        if (isValidPosition(forest, newCoords)) {
            // Enregistrer le mouvement dans le graphe
            addEdge(g, child->coords, newCoords);

            // Mettre à jour les coordonnées
            child->coords = newCoords;
            updateSafeStatus(child);

            printf("[ENFANT] Deplace vers (%d, %d)\n", newX, newY);
            return 0;  // Mouvement réussi
        }
    }

    // Si aucun mouvement n'est possible
    printf("[ENFANT] Bloque en (%d, %d)\n",
           child->coords.x, child->coords.y);
    return 0;
}

int isChildEaten(const Child *child, int wolfX, int wolfY) {
    if (!child) return 0;
    return (child->coords.x == wolfX && child->coords.y == wolfY);
}