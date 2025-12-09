//
// Created by Thanh on 09/12/2025.
//

#ifndef WOLF_GRAPH_H
#define WOLF_GRAPH_H


#include "forest.h"
typedef struct {
    int id;
    Coords coord;
} Vertex;

typedef struct {
    Vertex from;
    Vertex to;
} Edge;

typedef struct {
    Edge* edge;
    Node* nextNode;
} Node;

typedef struct {
    Node* firstNode;
    int nodeCount;
} Graph;

int getNextId();


#endif //WOLF_GRAPH_H