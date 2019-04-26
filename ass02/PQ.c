// PQ ADT interface for Ass2 (COMP2521)

// Library includes.
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// File includes.
#include "PQ.h"

// Constants.
#define EMPTY_NODE -1

// Structs.
struct PQRep {
	ItemPQ node;
	struct PQRep *next;
};

// Functions.
PQ newPQ() {
	PQ new = malloc(sizeof(PQ));
	assert(new != NULL);
	new->node.key = EMPTY_NODE;
	new->node.value = 0;
	new->next = NULL;
	return new;
}

int PQEmpty(PQ pq) {
	assert(pq != NULL);

	int isEmpty = 0;

	if (pq->node.key == EMPTY_NODE) {
		isEmpty = 1;
	}

	return isEmpty;
}

void addPQ(PQ pq, ItemPQ element) {
	assert(pq != NULL);
	assert(element.key != -1); // FUNCTION ASSUMES A KEY CANNOT BE NEGATIVE (SPECIFICALLY -1).

	PQ curr = pq;

	if (pq->node.key == EMPTY_NODE) {
		pq->node.key = element.key;
		pq->node.value = element.value;
	}
	else {
		curr = pq;
		while (curr != NULL) {
			if (curr->node.key == element.key) {
				curr->node.value = element.value;
				return;
			}
			curr = curr->next;
		}

		curr = pq;
		while (curr->next != NULL) {
			curr = curr->next;
		}
		curr->next = newPQ();
		curr->next->node.key = element.key;
		curr->next->node.value = element.value;
	}

	curr = pq;
	while (curr != NULL) {
		printf("> %d-%d\n", curr->node.key, curr->node.value);
	}
}

ItemPQ dequeuePQ(PQ pq) {
	assert(pq != NULL);

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
