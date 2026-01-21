#ifndef WOLF_PATHMAP_H
#define WOLF_PATHMAP_H

#include "forest.h"
#include "coords.h"

// Carte pour suivre le passage de l'enfant
typedef unsigned char PathMap[FOREST_HEIGHT][FOREST_WIDTH];

/* Initialiser la carte de trajet (tout à 0) */
void initPathMap(PathMap map);

/* position visitée */
void markVisited(PathMap map, Coords coords);

/* Exporter la carte vers un fichier texte */
int exportPathMap(const PathMap map, const char *filename);



#endif // WOLF_PATHMAP_H