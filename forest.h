//
// Created by remyk on 03/12/2025.
//

#ifndef WOLF_FOREST_H
#define WOLF_FOREST_H

#define FOREST_WIDTH 80
#define FOREST_HEIGHT 40
#define FOREST_CHOICE 2

typedef unsigned char Forest[FOREST_HEIGHT][FOREST_WIDTH];

typedef struct Coords {
    unsigned char y;
    unsigned char x;
    //il faut se souvenir que le tableau va marcher en Forest[HAUTEUR][LONGUEUR] donc la position sera child(y,x) et non child(x,y)
} Coords;

void import_forest(Forest forest);

//TODO : ça serait bien d'avoir une fonction dans Forest qui permetterait de connaitre les bords de la foret (débattable)

#endif //WOLF_FOREST_H