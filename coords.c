//
// Created by Nicolas Gouaux on 21/01/2026.
//

#include "coords.h"


Coords createCoords(unsigned char x, unsigned char y) {
    Coords coords;
    coords.x = x;
    coords.y = y;
    return coords;
}

int coordsEqual(Coords c1, Coords c2) {
    return (c1.x == c2.x && c1.y == c2.y);
}