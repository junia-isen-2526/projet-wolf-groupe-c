#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef WOLF__WOLF_H_
#define WOLF__WOLF_H_

#define MAXLines 50
#define MAX_LINE_LENGTH 50
#define MAXClothes 50
#include "forest.h"

typedef enum {
  STEP_COMPTINE,
  STEP_DRESSING,
  STEP_WOLF_MOVE
} GameStep;

typedef struct {
  int x;
  int y;
  int active;
} Wolf;

int readLines(const char *filename, char lines[MAXLines][MAX_LINE_LENGTH]);

int playComptineStep(char rhyme[MAXLines][MAX_LINE_LENGTH], int rhymeCount);

int wolfDressingStep(Wolf *wolf, const char clothes[MAXClothes][MAX_LINE_LENGTH], int clothesCount);

void moveWolfStep(Wolf *wolf);

#endif //WOLF__WOLF_H_
