#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wolf.h"

#ifndef WOLF__CHILD_H_
#define WOLF__CHILD_H_

#include "forest.h"

typedef struct {
  unsigned char x;
  unsigned char y;
  unsigned char isSafe;
} Child;

typedef unsigned char Map[FOREST_HEIGHT][FOREST_WIDTH];


void isSafe (Child child);

void AddVisitedPosition(Child child, Map *map);

int isGameOver(GameStep step, Child child, const Wolf *wolf);

void moveChildStep(const Child *child);

void initChild(Child *child, unsigned char start_y, unsigned char start_x);

#endif //WOLF__CHILD_H_
