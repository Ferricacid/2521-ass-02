// Dijkstra ADT interface for Ass2 (COMP2521)

// Library includes.

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

// File includes.
#include "Dijkstra.h"
#include "PQ.h"

// DEFINE
#define INFINITE 32767

static void freeList(PredNode *head) {
    PredNode *temp = head;
    while (head != NULL) {
        head = head->next;
        free(temp);
        temp = head;
    }
    // head = NULL;
}
/*
static predNode addToList(PredNode *head, Vertex v) {
    PredNode *new = malloc(sizeof(PredNode));
    new->v = v;
    new->next = NULL;
    if (head == NULL) {
        head = new;
    } else {
        while (head->next != NULL) {
            head = head->next;
        }
        head->next = new;
    }
    
}
*/

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

    for (int i = 0; i < numVerticies(g); i += 1) {
        dist[i] = INFINITE;
        pred[i] = NULL;
    }
    adjListNode *edge = outIncident(g, v);
        
    while (edge != NULL) {
        dist[edge->w] = edge->weight;
        edge = edge->next;
    }
    // Set distance to self as zero
    dist[v] = 0;

    // New Queue
    PQ q = newPQ();
    for (int i = 0; i < paths->noNodes; i += 1) {
        ItemPQ *item = malloc(sizeof(ItemPQ));
        item->key = i;
        item->value = dist[i];
        addPQ(q, *item);
    }
    //showPQ(q);



    while (PQEmpty(q) == 0) {
        
        
        //printf("Initial Queue: \n");
        //showPQ(q);
        
        ItemPQ vertex = dequeuePQ(q);
        //printf("After dequeuePQ: \n");
        //showPQ(q);
        //printf("Exploring Node %d...\n", vertex.key);


        adjListNode *edge = outIncident(g, vertex.key);
        

        while (edge != NULL) {
            /*
            printf("Current Distance Array: ");
            for (int i = 0; i < paths->noNodes; i += 1) {
                printf("%d, ", dist[i]);
            }
            printf("\n");
            showPQ(q);
            */
            // printf("%d, ", edge->w);
            int destination = edge->w;
            int newDistance = edge->weight + dist[vertex.key];
            //printf("%d, %d\n", destination, newDistance);
            if (newDistance < dist[destination]) {
                dist[destination] = newDistance;
                
                ItemPQ *item = malloc(sizeof(ItemPQ));
                item->key = edge->w;
                item->value = newDistance;
                
                addPQ(q, *item);
                
                // showPQ(q);
            }
            //showPQ(q);

            //printf("%d, ", edge->w);
            edge = edge->next;
        }
        //printf("\n");
        

    }
    

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
    
    // Set inital values to zero
    // for
    for(int i = 0; i < paths->noNodes; i += 1) {
        if (dist[i] == INFINITE) {
            dist[i] = 0;
        }
    }
    
    paths->dist = dist;
    paths->pred = pred;
    freePQ(q);
	return *paths;

}

void showShortestPaths(ShortestPaths paths) {

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
