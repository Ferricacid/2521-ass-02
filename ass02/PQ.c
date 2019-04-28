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
	new->node.key = 0;
	new->node.value = EMPTY_NODE;
	// define a pq as empty if its head node has a value of EMPTY_NODE
	new->next = NULL;
	return new;
}

int PQEmpty(PQ pq) {
	assert(pq != NULL);

	int isEmpty = 0;

	if (pq->node.value == EMPTY_NODE) {
		isEmpty = 1;
	}

	return isEmpty;
}

void addPQ(PQ pq, ItemPQ element) {
	assert(pq != NULL);

	PQ curr = pq;

	if (pq->node.value == EMPTY_NODE) {
		// pq is empty, replace its key-value.
		pq->node.key = element.key;
		pq->node.value = element.value;
	}
	else {
		// if element key is already in pq, update its value.
		curr = pq;
		while (curr != NULL) {
			if (curr->node.key == element.key) {
				curr->node.value = element.value;
				return;
			}
			curr = curr->next;
		}

		// otherwise normal case, go to end of pq and add the
		// key-value.
		curr = pq;
		while (curr->next != NULL) {
			curr = curr->next;
		}
		curr->next = newPQ();
		curr->next->node.key = element.key;
		curr->next->node.value = element.value;
	}
}

ItemPQ dequeuePQ(PQ pq) {
	assert(pq != NULL);

	ItemPQ pop = {0};

	PQ curr = pq;
	PQ temp = pq;
	PQ prev = pq;

	// if pq is empty, return a zeroed ItemPQ.
	if (pq->node.value != EMPTY_NODE) {
		// at least one node.
		if (pq->next == NULL) {
			// only one node. extract its key-value
			// and reset it to empty node values.
			pop.key = pq->node.key;
			pop.value = pq->node.value;
			pq->node.key = 0;
			pq->node.value = EMPTY_NODE;
		}
		else {
			// at least two nodes.
			pop.key = pq->node.key;
			pop.value = pq->node.value;
			curr = pq;
			while (curr != NULL) {
				// store key-value of lowest value node which is also
				// closest to the head (this will be dequeued).
				if (curr->node.value < pop.value) {
					pop.key = curr->node.key;
					pop.value = curr->node.value;
				}
				curr = curr->next;
			}

			// pop now stores the key and value of what we want to
			// dequeue.

			if (pq->node.key == pop.key) {
				// if the head is to be dequeued. 
				curr = pq;
				prev = pq;
				// move all item key-value pairs 'up' the queue by one
				// the head will be replcaed by the data of its next
				// and so on
				while (curr->next != NULL) {
					curr->node.key = curr->next->node.key;
					curr->node.value = curr->next->node.value;
					prev = curr;
					curr = curr->next;
				}
				// remove the last node which is now redundant.
				prev->next = NULL;
				free(curr);
				return pop;
			}

			// if a non-head node is to be dequeued, do similar
			// as above
			curr = pq;
			while (curr->next != NULL) {
				if (curr->next->node.key == pop.key) {
					temp = curr->next;
					curr->next = curr->next->next;
					free(temp);
					break;
				}
				curr = curr->next;
			}
		}
	}

	return pop;
}

void updatePQ(PQ pq, ItemPQ element) {
	assert(pq != NULL);

	PQ curr = pq;

	while (curr != NULL) {
		if (curr->node.key == element.key) {
			curr->node.value = element.value;
			break;
		}
		curr = curr->next;
	}
}

void showPQ(PQ pq) {
	assert(pq != NULL);

	PQ curr = pq;

	while (curr != NULL) {
		printf("> Key: %d | Value: %d", curr->node.key, curr->node.value);
		if (curr->node.key == EMPTY_NODE) {
			printf(" (EMPTY NODE)");
		}
		printf("\n");
		curr = curr->next;
	}
}

void freePQ(PQ pq) {
	assert(pq != NULL);

	if (pq->next == NULL) {
		free(pq);
		return;
	}

	PQ curr = pq;
	PQ prev = pq;

	while (curr->next != NULL) {
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	free(curr);
}
