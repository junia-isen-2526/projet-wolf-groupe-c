#ifndef WOLF_GRAPH_H
#define WOLF_GRAPH_H

#include "coords.h"

typedef struct Vertex {
    int id;
    Coords coords;
    struct Vertex *next; // Pour liste chaînée de sommets
} Vertex;

typedef struct Edge {
    Vertex *from;
    Vertex *to;
} Edge;

typedef struct GraphNode {
    Edge *edge;
    struct GraphNode *nextNode;
} GraphNode;

typedef struct {
    GraphNode *firstEdge;
    Vertex *firstVertex; // Liste des sommets
    int nodeCount;
    int edgeCount;
} Graph;

/* Créer un nouveau graphe vide */
Graph* createGraph(void);

/* Ajouter une arête (déplacement enfant) */
int addEdge(Graph *graph, Coords from, Coords to);

/* Exporter le graphe en format Mermaid */
int exportGraphToMermaid(const Graph *graph, const char *filename);

/* Libérer la mémoire du graphe */
void freeGraph(Graph *graph);

/* Afficher les stats du graphe (debug) */
void printGraphStats(const Graph *graph);

#endif // WOLF_GRAPH_H