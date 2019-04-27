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
}

ItemPQ dequeuePQ(PQ pq) {
	assert(pq != NULL);

	ItemPQ pop = {0};

	PQ curr = pq;
	PQ temp = pq;
	PQ prev = pq;

	if (pq->node.key != EMPTY_NODE) {
		// printf("> Checkpoint 1 ..\n");
		if (pq->next == NULL) {
			// printf("> Checkpoint 2-1 ..\n");
			pop.key = pq->node.key;
			pop.value = pq->node.value;
			pq->node.key = EMPTY_NODE;
			pq->node.value = 0;
		}
		else {
			// printf("> Checkpoint 2-2 ..\n");
			pop.key = pq->node.key;
			pop.value = pq->node.value;
			curr = pq;
			while (curr != NULL) {
				if (curr->node.value < pop.value) {
					pop.key = curr->node.key;
					pop.value = curr->node.value;
				}
				curr = curr->next;
			}

			//
			if (pq->node.key == pop.key) {
				curr = pq;
				prev = pq;
				while (curr->next != NULL) {
					curr->node.key = curr->next->node.key;
					curr->node.value = curr->next->node.value;
					prev = curr;
					curr = curr->next;
				}
				prev->next = NULL;
				free(curr);
				return pop;
				// at least two items.
				// move all item values down queue.
			}
			//

			// printf("> Checkpoint 3 ..\n");
			curr = pq;
			while (curr->next != NULL) {
				if (curr->next->node.key == pop.key) {
					// FREE curr->next
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
