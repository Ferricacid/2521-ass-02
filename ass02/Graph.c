/*
Graph interface for Assignment 02 (2521): Social Network Analysis.
*/

// Library includes.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// File includes.

#include "Graph.h"

// Static prototypes.

static int validVertex(Graph g, Vertex v);
static AdjList createAdjList();

// Structs.

typedef struct GraphRep {
	int noVertices; // number vertices.
	int noEdges; // number edges.
	int **edges; // matrix of weights between nodes. 0 == no edge.
} GraphRep;

// Functions.

// Create a new Graph (from John Shepherd Lab 08)
Graph newGraph(int noNodes) {
	assert(noNodes > 0);

	GraphRep *new = malloc(sizeof(*new));
	assert(new != NULL);
	*new = (GraphRep){.noVertices = noNodes,
	                  .noEdges = 0};
	
	new->edges = calloc((size_t) noNodes, sizeof(int *));
	assert(new->edges != NULL);
	for (int v = 0; v < noNodes; v++) {
		new->edges[v] = calloc((size_t) noNodes, sizeof(int));
		assert(new->edges[v] != 0);
	}

	return new;
}

void insertEdge(Graph g, Vertex src, Vertex dest, int weight) {
	assert((g != NULL) && validVertex(g, src) && validVertex(g, dest));

	if (g->edges[src][dest] != 0) {
		// Edge already exists.
		return;
	}

	g->edges[src][dest] = weight;
	g->noEdges++;
}

void removeEdge(Graph g, Vertex src, Vertex dest) {
	assert((g != NULL) && validVertex(g, src) && validVertex(g, dest));

	if (g->edges[src][dest] == 0) {
		// Edge doesn't exist.
		return;
	}

	g->edges[src][dest] = 0;
	g->noEdges--;
}

bool adjacent(Graph g, Vertex src, Vertex dest) {
	assert(g != NULL);

	if (g->edges[src][dest] != 0) {
		return true;
	}

	return false;
}

int numVerticies(Graph g) {
	assert(g != NULL);

	return g->noVertices;
}

AdjList outIncident(Graph g, Vertex v) {
	AdjList out = createAdjList();

	for (int i = 0; i < g->noVertices; i++) {
		// Check adjacency for every other vertex.
		if ((i != v) && (adjacent(g, v, i) == true)) {
			// If out->w = -1, it is new.
			if (out->w == -1) {
				out->w = i;
				out->weight = g->edges[v][i];
				out->next = NULL;
			}
			else {
				AdjList curr = out;
				while (curr->next != NULL) {
					curr = curr->next;
				}
				curr->next = createAdjList();
				curr->next->w = i;
				curr->next->weight = g->edges[v][i];
				curr->next->next = NULL;
			}
		}
	}

	if (out->w == -1) {
		// No adjacencies.
		free(out);
		return NULL;
	}

	return out;
}

AdjList inIncident(Graph g, Vertex v) {
	AdjList in = createAdjList();

	for (int i = 0; i < g->noVertices; i++) {
		// Check adjacency for every other vertex.
		if ((i != v) && (adjacent(g, i, v) == true)) {
			// If in->w = -1, it is new.
			if (in->w == -1) {
				in->w = i;
				in->weight = g->edges[i][v];
				in->next = NULL;
			}
			else {
				AdjList curr = in;
				while (curr->next != NULL) {
					curr = curr->next;
				}
				curr->next = createAdjList();
				curr->next->w = i;
				curr->next->weight = g->edges[i][v];
				curr->next->next = NULL;
			}
		}
	}

	if (in->w == -1) {
		// No adjacencies.
		free(in);
		return NULL;
	}

	return in;
}

void  showGraph(Graph g) {
	assert(g != NULL);

	printf("Number of vertices: %d\n", g->noVertices);
	printf("Number of edges: %d\n", g->noEdges);

	int v, w;
	for (v = 0; v < g->noVertices; v++) {
		printf("%d\n", v);
		for (w = 0; w < g->noVertices; w++) {
			if (g->edges[v][w]) {
				printf("\t (%d)\n", g->edges[v][w]);
			}
		}
		printf("\n");
	}
}

void  freeGraph(Graph g) {
	assert(g != NULL);

	for (int v = 0; v < g->noVertices; v++) {
		free(g->edges[v]);
	}
	free(g->edges);
	free(g);
}

// Static functions.

static int validVertex(Graph g, Vertex v) {
	return ((g != NULL) && (v >= 0) && (v < g->noVertices));
}

static AdjList createAdjList() {
	AdjList new = malloc(sizeof(AdjList));
	assert(new != NULL);
	new->w = -1;
	new->weight = -1;
	new->next = NULL;
	return new;
}
