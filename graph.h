//
// Created by Thanh on 09/12/2025.
//

#ifndef WOLF_GRAPH_H
#define WOLF_GRAPH_H


#include "forest.h"
typedef struct Vertex{
    int id;
    Coords* coord;
} Vertex;

typedef struct Edge{
    Vertex* from;
    Vertex* to;
} Edge;

typedef struct Node{
    Edge* edge;
    struct Node* nextNode;
} Node;

typedef struct Graph{
    Node* firstNode;
    int nodeCount;
} Graph;

int exportGraphToMermaid(const Graph* g, const char* filename);


int getNextId();


#endif //WOLF_GRAPH_H