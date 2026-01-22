#include "child.h"
#include <stdlib.h>
#include <stdio.h>

void initChild(Child *child, Coords startPos) {
    if (!child) return;

    child->coords = startPos;
    child->startCoords = startPos;
    child->isDead = 0;
    child->isSafe = 0; // Ne jamais commencer en sécurité
    child->hasLeftEdge = 0; // L'enfant n'a pas encore quitté le bord
}

void updateSafeStatus(Child *child) {
    if (!child) return;

    // Vérifier si l'enfant est sur un bord
    int onEdge = isSafeZone(child->coords);

    // Si l'enfant n'est PAS sur un bord, marquer qu'il a quitté le bord
    if (!onEdge) {
        child->hasLeftEdge = 1;
    }

    // L'enfant est en sécurité seulement s'il est sur un bord ET qu'il a déjà quitté un bord avant
    child->isSafe = (onEdge && child->hasLeftEdge);
}

int moveChildStep(Child *child, const Forest forest, Graph *g) {
    if (!child || !forest || !g) return -1;

    // Vérifier d'abord si l'enfant est déjà en sécurité
    if (child->isSafe) {
        printf("[ENFANT] En securite aux coordonnees (%d, %d)\n",
               child->coords.x, child->coords.y);
        return 1;  // Jeu terminé ok
    }

    // Générer déplacement aléatoire (8 directions)
    int dx[] = {-1,  0,  1, -1,  1, -1,  0,  1};
    int dy[] = {-1, -1, -1,  0,  0,  1,  1,  1};

    // Essayer de trouver un déplacement valide
    for (int attempt = 0; attempt < 8; attempt++) {
        int dir = rand() % 8;
        int newX = child->coords.x + dx[dir];
        int newY = child->coords.y + dy[dir];

        // Vérifier les limites
        if (newX < 0 || newX >= FOREST_WIDTH ||
            newY < 0 || newY >= FOREST_HEIGHT) {
            continue;
        }

        // Vérifier si new pos valide
        Coords newCoords = createCoords((unsigned char)newX, (unsigned char)newY);
        if (isValidPosition(forest, newCoords)) {
            // Enregistrer le mouvement dans le graphe
            addEdge(g, child->coords, newCoords);

            // Mettre à jour les coordonnées
            child->coords = newCoords;
            updateSafeStatus(child);

            printf("[ENFANT] Deplace vers (%d, %d) [hasLeftEdge=%d, isSafe=%d]\n",
                   newX, newY, child->hasLeftEdge, child->isSafe);
            return 0;  // Mouvement réussi
        }
    }

    return 0;
}

int isChildEaten(const Child *child, int wolfX, int wolfY) {
    if (!child) return 0;
    return (child->coords.x == wolfX && child->coords.y == wolfY);
}

Coords findRandomEdgePosition(const Forest forest) {
    Coords result;
    int validPositions[FOREST_WIDTH * 2 + FOREST_HEIGHT * 2][2];
    int count = 0;

    // Parcourir tous les bords pour trouver les positions valides

    // Bord haut (y = 0)
    for (int x = 0; x < FOREST_WIDTH; x++) {
        Coords test = createCoords(x, 0);
        if (isValidPosition(forest, test)) {
            validPositions[count][0] = x;
            validPositions[count][1] = 0;
            count++;
        }
    }

    // Bord bas (y = FOREST_HEIGHT - 1)
    for (int x = 0; x < FOREST_WIDTH; x++) {
        Coords test = createCoords(x, FOREST_HEIGHT - 1);
        if (isValidPosition(forest, test)) {
            validPositions[count][0] = x;
            validPositions[count][1] = FOREST_HEIGHT - 1;
            count++;
        }
    }

    // Bord gauche (x = 0)
    for (int y = 1; y < FOREST_HEIGHT - 1; y++) {  // Éviter les coins déjà comptés
        Coords test = createCoords(0, y);
        if (isValidPosition(forest, test)) {
            validPositions[count][0] = 0;
            validPositions[count][1] = y;
            count++;
        }
    }

    // Bord droit (x = FOREST_WIDTH - 1)
    for (int y = 1; y < FOREST_HEIGHT - 1; y++) {  // Éviter les coins déjà comptés
        Coords test = createCoords(FOREST_WIDTH - 1, y);
        if (isValidPosition(forest, test)) {
            validPositions[count][0] = FOREST_WIDTH - 1;
            validPositions[count][1] = y;
            count++;
        }
    }

    // Choisir une position aléatoire parmi les valides
    if (count > 0) {
        int index = rand() % count;
        result = createCoords(validPositions[index][0], validPositions[index][1]);
        printf("[INIT] %d positions valides trouvées sur les bords\n", count);
        printf("[INIT] Position choisie: (%d, %d)\n", result.x, result.y);
    } else {
        // Si aucune position valide sur les bords (cas improbable)
        printf("[ERREUR] Aucune position valide sur les bords !\n");
        result = createCoords(0, 0);
    }

    return result;
}