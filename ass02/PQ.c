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

	ItemPQ empty = {0};
	new->isEmpty = 1;
	new->node = empty;
	new->next = NULL;

	return new;
}

int PQEmpty(PQ pq) {
	assert(pq != NULL);
	
	return pq->isEmpty;
}

void addPQ(PQ pq, ItemPQ element) {
	assert(pq != NULL);

	ItemPQ new = {.key = element.key, .value = element.value};

	// Empty PQ.
	if (pq->isEmpty) {
		pq->node = new;
		pq->isEmpty = 0;
		pq->next = NULL;
	}
	// At least one item.
	else {
		PQ curr = pq;
		// Check if exists already.
		while (curr != NULL) {
			if (curr->node.key == element.key) {
				curr->node.value = element.value;
				return;
			}
			curr = curr->next;
		}

		// Not in PQ, add to end.
		curr = pq;
		while (curr->next != NULL) {
			curr = curr->next;
		}
		curr->next = newPQ();
		curr->next->node = new;
		curr->next->isEmpty = 0;
		curr->next->next = NULL;
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
