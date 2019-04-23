// PQ ADT interface for Ass2 (COMP2521)

// Library includes.
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// File includes.
#include "PQ.h"

// Structs.
struct PQRep {
	int isEmpty;
	ItemPQ node;
	struct PQRep *next;
};

// Functions.
PQ newPQ() {
	PQ new = malloc(sizeof(PQ));
	assert(new != NULL);
	new->isEmpty = 1;
	new->node = {0};
	new->next = NULL;

	return new;
}

int PQEmpty(PQ pq) {
	assert(pq != NULL);

	return pq->isEmpty;
}

void addPQ(PQ pq, ItemPQ element) {
	assert(pq != NULL);

	// Empty PQ.
	if (pq->isEmpty == 1) {
		pq->node = element;
	}
}

ItemPQ dequeuePQ(PQ pq) {
	ItemPQ temp = {0};
	return temp;
}

void updatePQ(PQ pq, ItemPQ element) {
	//
}

void  showPQ(PQ pq) {
	//
}

void  freePQ(PQ pq) {
	//
}
