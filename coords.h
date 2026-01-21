#ifndef WOLF_COORDS_H
#define WOLF_COORDS_H

typedef struct {
    unsigned char x;
    unsigned char y;
} Coords;

/* Créer des coordonnées */
Coords createCoords(unsigned char x, unsigned char y);

/* Comparer deux coordonnées */
int coordsEqual(Coords c1, Coords c2);

#endif // WOLF_COORDS_H