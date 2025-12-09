#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "wolf.h"
#include "forest.h"

#ifndef WOLF__CHILD_H_
#define WOLF__CHILD_H_


typedef struct {
  Coords coords;
  unsigned char isSafe;
  unsigned char isDead;
} Child;

typedef unsigned char Map[FOREST_HEIGHT][FOREST_WIDTH];


void isSafe (Child child);

void AddVisitedPosition(Child child, Map *map);

int isGameOver(GameStep step, Child child, const Wolf *wolf);

void moveChildStep(Child *child, const Forest forest);

void initChild(Child *child, unsigned char start_y, unsigned char start_x);

#endif //WOLF__CHILD_H_
