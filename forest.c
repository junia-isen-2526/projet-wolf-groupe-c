#include "forest.h"
#include <stdio.h>
#include <string.h>

int loadForest(Forest forest, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erreur ouverture fichier forêt");
        return -1;
    }

    for (int y = 0; y < FOREST_HEIGHT; y++) {
        char buffer[FOREST_WIDTH + 10]; // Buffer avec marge
        if (fgets(buffer, sizeof(buffer), file) == NULL) {
            printf("Attention: forêt incomplète (ligne %d manquante)\n", y);
            // Remplir le reste avec des espaces
            for (int x = 0; x < FOREST_WIDTH; x++) {
                forest[y][x] = 0;
            }
            continue;
        }

        // Convertir chaque caractère
        for (int x = 0; x < FOREST_WIDTH; x++) {
            if (x < (int)strlen(buffer) && buffer[x] == '1') {
                forest[y][x] = 1;
            } else {
                forest[y][x] = 0;
            }
        }
    }

    fclose(file);
    return 0;
}

int isValidPosition(const Forest forest, Coords coords) {
    // Vérifier les limites
    if (coords.x >= FOREST_WIDTH || coords.y >= FOREST_HEIGHT) {
        return 0;
    }
    // Vérifier s'il n'y a pas d'arbre (0 = OK, 1 = arbre)
    return forest[coords.y][coords.x] == 0;
}

int isSafeZone(Coords coords) {
    // L'enfant est en sécurité sur les bordures de la forêt
    return (coords.x == 0 || coords.x == FOREST_WIDTH - 1 ||
            coords.y == 0 || coords.y == FOREST_HEIGHT - 1);
}

