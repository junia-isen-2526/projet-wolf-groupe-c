#include "pathmap.h"
#include <stdio.h>
#include <string.h>

void initPathMap(PathMap map) {
    memset(map, 0, sizeof(PathMap));
}

void markVisited(PathMap map, Coords coords) {
    if (coords.x < FOREST_WIDTH && coords.y < FOREST_HEIGHT) {
        map[coords.y][coords.x] = 1;
    }
}

int exportPathMap(const PathMap map, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Erreur ouverture fichier map trajet");
        return -1;
    }

    for (int y = 0; y < FOREST_HEIGHT; y++) {
        for (int x = 0; x < FOREST_WIDTH; x++) {
            fprintf(file, "%c", map[y][x] ? '1' : ' ');
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Carte de trajet exportée vers %s\n", filename);
    return 0;
}
