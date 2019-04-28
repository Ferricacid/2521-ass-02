// Dijkstra ADT interface for Ass2 (COMP2521)

// Library includes.

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>


// File includes.
#include "Dijkstra.h"
#include "PQ.h"

// DEFINE
#define INFINITY 99999


// Helper function to remove list
static void freeList(PredNode *head) {
    PredNode *temp = head;
    while (head != NULL) {
        head = head->next;
        free(temp);
        temp = head;
    }
}

// Helper to create a new PredNode
static PredNode *newNode(Vertex v) {
    PredNode *new = malloc(sizeof(PredNode));
    new->v = v;
    new->next = NULL;
    return(new);
}



ShortestPaths dijkstra(Graph g, Vertex v) {

    ShortestPaths *paths = malloc(sizeof(ShortestPaths));
    paths->noNodes = numVerticies(g);
    paths->src = v;

    int *dist = dist = malloc(sizeof(int) * numVerticies(g));
    PredNode **pred = malloc(sizeof(PredNode) * numVerticies(g));

    // Initally set distance to every node to infinity
    for (int i = 0; i < numVerticies(g); i += 1) {
        dist[i] = INFINITY;
        pred[i] = NULL;
    }

    // Set distances for adjacent edges to source
    adjListNode *edge = outIncident(g, v);
    while (edge != NULL) {
        dist[edge->w] = edge->weight;
        edge = edge->next;
    }

    // Set distance to self as zero
    dist[v] = 0;

    // Create queue and add every vertex in the graph to it 
    // queue priority is based on distance from source
    PQ q = newPQ();
    for (int i = 0; i < paths->noNodes; i += 1) {
        ItemPQ *item = malloc(sizeof(ItemPQ));
        item->key = i;
        item->value = dist[i];
        addPQ(q, *item);
    }

    // Emptying Queue
    while (PQEmpty(q) == 0) {
        // Get item from queue
        ItemPQ vertex = dequeuePQ(q);
        // Get edges from vertex
        adjListNode *edge = outIncident(g, vertex.key);  
        while (edge != NULL) {
            int destination = edge->w;
            int newDistance = edge->weight + dist[vertex.key];
            if (newDistance < dist[destination]) {
                dist[destination] = newDistance;
                ItemPQ *item = malloc(sizeof(ItemPQ));
                item->key = edge->w;
                item->value = newDistance;
                addPQ(q, *item);
            }
            edge = edge->next;
        }
    }
    
    // GETTING PRENODES
    for(int i = 0; i < paths->noNodes; i += 1) {
        edge = inIncident(g, i);
        while (edge != NULL) {
            int distance = edge->weight + dist[edge->w];
            if (distance == dist[i]) {
                if (pred[i] == NULL) {
                    pred[i] = newNode(edge->w);
                } else {
                    PredNode *curr = pred[i];
                    while (curr->next != NULL) {
                        curr = curr->next;
                    }
                    curr->next = newNode(edge->w);
                }
            }
            edge = edge->next;
        }
    }
    
    // Set inital values to 0 if they were infinity
    for(int i = 0; i < paths->noNodes; i += 1) {
        if (dist[i] == INFINITY) {
            dist[i] = 0;
        }
    }
    
    paths->dist = dist;
    paths->pred = pred;
    freePQ(q);
	return *paths;
}

// From testDijkstra.c
void showShortestPaths(ShortestPaths paths) {
    int i = 0;
    printf("Node %d\n",paths.src);
    printf("  Distance\n");
    for (i = 0; i < paths.noNodes; i++) {
            if(i == paths.src)
            printf("    %d : X\n",i);
            else
                printf("    %d : %d\n",i,paths.dist[i]);
    }
    printf("  Preds\n");
    for (i = 0; i < paths.noNodes; i++) {
        int numPreds = 0;
        int preds[paths.noNodes];
        printf("    %d : ",i);
        PredNode *curr = paths.pred[i];
        while (curr != NULL && numPreds < paths.noNodes) {
            preds[numPreds++] = curr->v;
            curr = curr->next;
        }
        
        // Insertion sort
        for (int j = 1; j < numPreds; j++) {
            int temp = preds[j];
            int k = j;
            while (preds[k - 1] > temp && k > 0) {
                preds[k] = preds[k - 1];
                k--;
            }
            preds[k] = temp;
        }
        
        for (int j = 0; j < numPreds; j++) {
            printf("[%d]->", preds[j]);
        }
        printf("NULL\n");
    }
}


void freeShortestPaths(ShortestPaths paths) {
    for(int i = 0; i < paths.noNodes; i += 1) {
        freeList(paths.pred[i]);
    }
    free(paths.pred);
    free(paths.dist);
    // free(paths);
    return;
}
