// PQ ADT interface for Ass2 (COMP2521)

// Library includes.
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// File includes.
#include "PQ.h"

// Structs.
struct PQRep {
	ItemPQ node;
	struct PQRep *next;
};

// Functions.
PQ newPQ() {
	PQ new = malloc(sizeof(PQ));
	assert(new != NULL);
	new.node = NULL;
	new->next = NULL;

	return new;
}

int PQEmpty(PQ pq) {
	assert(pq != NULL);

	int isEmpty;

	if (pq.node == NULL) {
		isEmpty = 1;
	}
	else {
		isEmpty 0;
	}

	return isEmpty;
}

void addPQ(PQ pq, ItemPQ element) {
	assert(pq != NULL);

	// Empty PQ.
	if (pq.node == NULL) {
		pq.node = element;
	}
}

ItemPQ dequeuePQ(PQ pq) {
	return NULL;
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
