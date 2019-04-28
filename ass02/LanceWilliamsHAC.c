/*Lance-Williams Algorithm for Agglomerative Clustering
  Written by 
  COMP2521 2019 T1
*/
#include <stdlib.h>
#include <stdio.h>
#include "LanceWilliamsHAC.h"
#include "Graph.h"
// #include <limits.h>
#define numVertices numVerticies

/* 
 * Finds Dendrogram using Lance-Williams algorithm (as discussed in the specs) 
   for the given graph g and the specified method for agglomerative clustering.
   Method value 1 represents 'Single linkage', and 2 represents 'Complete linkage'.
   For this assignment, you only need to implement the above two methods. 

   The function returns 'Dendrogram' structure (binary tree) with the required information.
 * 
 */

#define INFINITE 9999

// Merge two dendrograms
static DNode *merge(DNode *a, DNode *b) {
    DNode *new = malloc(sizeof(DNode));
    new->vertex = a->vertex;
    new->left = a;
    new->right = b;
    return(new);
}  


Dendrogram LanceWilliamsHAC(Graph g, int method) {
    // Check if method = 1 or 2?
    int num_nodes = numVerticies(g);
    float distances[num_nodes][num_nodes];
    DNode **dendrograms = malloc(sizeof(DNode) * num_nodes);
    
    // Set distances = ininte
    for (int i = 0; i<num_nodes; i++) {
        for (int j = 0; j<num_nodes; j++) {
            distances[i][j] = INFINITE;
        }
    }
    
    // Initialising Arrays
    for (int i = 0; i < num_nodes; i += 1) {
        // Add inital Dendrograms
        DNode *new = malloc(sizeof(DNode));
        new->vertex = i;
        new->left = NULL;
        new->right = NULL;
        dendrograms[i] = new;
        // Add initial distance graph
        // distances[i][i] = 0;
        AdjList edge = outIncident(g, i);
        while (edge != NULL) {
            float new_distance = 1/(float)(edge->weight);
            if (new_distance < distances[i][edge->w]) {
                distances[i][edge->w] = new_distance;
                distances[edge->w][i] = new_distance;
            }
            edge = edge->next;
        }
        edge = inIncident(g, i);
        while (edge != NULL) {
            float new_distance = 1/(float)(edge->weight);
            if (new_distance < distances[i][edge->w]) {
                distances[i][edge->w] = new_distance;
                distances[edge->w][i] = new_distance;
            }
            edge = edge->next;
        }
    }

    // n-1 merges
    int n = num_nodes -1;
    while (n > 0) {
        
        /*
        for (int i = 0; i<num_nodes; i++) {
            for (int j = 0; j<num_nodes; j++) {
                printf("%f ", distances[i][j]);
            }
            printf("\n");
        }
        */
        
        // find lowest
        float lowest = distances[0][0]; // Equal to INIFINITE
        lowest += 1;
        int v1 = 0;
        int v2 = 0;
        // distances[0][0] always exists

        // Loops through the matrix skipping values that don't have
        // a cluster attached to them, i.e has been merged
        for (int i = 0; i < num_nodes; i += 1) {
            if (dendrograms[i] != NULL){
                for (int j = 0; j < num_nodes; j += 1) {
                    if (dendrograms[j] != NULL) {
                        if (distances[i][j] <= lowest) {
                            lowest = distances[i][j];
                            // Makes v1 the lower value vertex
                            if (i > j) {
                                v1 = j;
                                v2 = i;
                            } else {
                                v1 = i;
                                v2 = j;
                            }
                        }
                    }
                }
            }
        }
        
        // Merge the clusters with lowest distance 
        // Store the merged cluster in the position of the cluster with lower index
        // i.e merging Vertex 1 and Vertex 2 would result in {1,2} stored in {1};
        dendrograms[v1] = merge(dendrograms[v1], dendrograms[v2]);
        dendrograms[v2] = NULL;

        // Update distance array
        for (int i = 0; i < num_nodes; i += 1) {
            if (i == v1) {
                distances[v1][i] = INFINITE;
                distances[i][v1] = INFINITE;
            } else {
                // Single Linkcage
                if (method == 1) {
                    if (distances[v2][i] < distances[v1][i]) {
                        distances[v1][i] = distances[v2][i];
                        distances[i][v1] = distances[v2][i];
                    } 
                    /*
                    if (distances[v1][i] < distances[v2][i]) {
                        distances[v2][i] = distances[v1][i];
                        distances[i][v2] = distances[v1][i];
                    }
                    */
                // Complete Linkcage
                } else if (method == 2) {
                    if (distances[v2][i] > distances[v1][i]) {
                        distances[v1][i] = distances[v2][i];
                        distances[i][v1] = distances[v2][i];
                    } 
                    /*
                    if (distances[v1][i] < distances[v2][i]) {
                        distances[v2][i] = distances[v1][i];
                        distances[i][v2] = distances[v1][i];
                    }
                    */
                } 
                
            }
            
            
        }
        n -=1;
    }

    // Returns 
    // Always exists because clusters are merged into the lower
    return dendrograms[0];
}


void freeDendrogram(Dendrogram d) {

	return;
}



