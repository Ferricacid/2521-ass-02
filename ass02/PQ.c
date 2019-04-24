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
	assert(pq != NULL);

	ItemPQ deQueued = {0};

	// If PQ empty, return an zeroed ItemPQ.
	if (pq->isEmpty) {
		return deQueued;
	}

	// If PQ has only one element, return it.
	if (pq->next == NULL) {
		deQueued = {.key = pq->node.key, .value = pq->node.value};
		pq->node.key = 0;
		pq->node.value = 0;
		pq->isEmpty = 1;
		return deQueued;
	}

	// PQ has at least TWO elements.
	// Find lowest the key of the ItemPQ to dequeue.
	int lowestKey = pq->node.key;
	int lowestValue = pq->node.value;
	PQ curr = pq;
	while (curr != NULL) {
		if (curr->node.value < lowestValue) {
			lowestKey = curr->node.key;
			lowestValue = curr->node.value;
		}
		curr = curr->next;
	}
	// Locate the key, find prev and next.
	PQ prev;
	PQ deQueue;
	PQ next;
	curr = pq;
	while (curr != NULL) {
		if (curr->node.key == lowestKey) {
			deQueue = curr;
		}
		curr = curr->next;
	}
	prev = deQueue;
	next = deQueue;
	curr = pq;
	while (curr->next != NULL) {
		if (curr->next->node.key == lowestKey) {
			prev = curr;
		}
		curr = curr->next;
	}

	return deQueued;
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
