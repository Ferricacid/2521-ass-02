// PQ ADT interface for Ass2 (COMP2521)

// Library includes.
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// File includes.
#include "PQ.h"

// Structs.
struct PQRep {
	ItemPQ *node;
	struct PQRep *next;
};

// Functions.
PQ newPQ() {
	PQ new = malloc(sizeof(PQ));
	assert(new != NULL);
	new->node = NULL;
	new->next = NULL;

	return new;
}

int PQEmpty(PQ pq) {
	assert(pq != NULL);

	int isEmpty;

	if (pq->node == NULL) {
		isEmpty = 1;
	}
	else {
		isEmpty = 0;
	}

	return isEmpty;
}

void addPQ(PQ pq, ItemPQ element) {
	assert(pq != NULL);

	// Empty PQ.
	if (pq->node == NULL) {
		pq->node = malloc(sizeof(pq->node))
		assert(pq->node != NULL);
		pq->node->key = element.key;
		pq->node->value = element.value;
		pq->next = NULL;
	}
	// At least one item.
	else {
		PQ curr = pq;
		// Check if exists already.
		while (curr != NULL) {
			if (curr->node->key == element.key) {
				curr->node->value = element.value;
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
		curr->next->node = malloc(sizeof(pq->node));
		curr->next->node->key = element.key;
		curr->next->node->value = element.value;
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
