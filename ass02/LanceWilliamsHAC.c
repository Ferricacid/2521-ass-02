/*Lance-Williams Algorithm for Agglomerative Clustering
  Written by 
  COMP2521 2019 T1
*/
#include <stdlib.h>
#include <stdio.h>
#include "LanceWilliamsHAC.h"
#include "Graph.h"
#define numVertices numVerticies

/* 
 * Finds Dendrogram using Lance-Williams algorithm (as discussed in the specs) 
   for the given graph g and the specified method for agglomerative clustering.
   Method value 1 represents 'Single linkage', and 2 represents 'Complete linkage'.
   For this assignment, you only need to implement the above two methods. 

   The function returns 'Dendrogram' structure (binary tree) with the required information.
 * 
 */

#define INFINITE 99999

Dendrogram LanceWilliamsHAC(Graph g, int method) {
    int num_nodes = numVerticies(g);
    float distances[num_nodes][num_nodes] = {{INFINITE}};

    for (int i = 0; i < num_nodes; i += 1) {
        distances[i][i] = 0;
        AdjList edges = outIncident(g, i);
        while (edges != NULL) {
            int distance = 1/edges->weight;
            if distance < distances[i][edges->w] {
                distances[i][edges->w] = 1/edges->weight;
            }
            edge = edge->next;
        }
        AdjList edges = inIncident(g, i);
        while (edges != NULL) {
            int distance = 1/edges->weight;
            if distance < distances[i][edges->w] {
                distances[i][edges->w] = 1/edges->weight;
            }
            edge = edge->next;
        }
        
    }


    return NULL;
}


void freeDendrogram(Dendrogram d) {

	return;
}



