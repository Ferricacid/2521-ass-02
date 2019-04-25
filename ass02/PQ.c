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
	// PQ before = pq;
	// PQ after = pq;

	if (pq->node.key == EMPTY_NODE) { // No nodes, replace its key-value.
		printf("> CASE: EMPTY NODE\n");
		pq->node.key = element.key;
		pq->node.value = element.value;
	}
	else { // At least the first node.
		while (curr != NULL) { // check if key already in PQ.
			if (curr->node.key == element.key) {
				printf("> CASE: KEY ALREADY IN PQ\n");
				curr->node.value = element.value;
				return;
			}
			curr = curr->next;
		}
		// Key is not in PQ.
		if (element.value < pq->node.value) {
			// Add before the pq.
			printf("> pq->node.key = %d , pq->node.value = %d\n", pq->node.key, pq->node.value);
			curr = pq;
			while (curr != NULL) {
				printf("> key = %d , value = %d\n", curr->node.key, curr->node.value);
				curr = curr->next;
			}
			printf("> Operating ..\n");
			// after = pq;
			PQ newHead = newPQ();
			newHead->node.key = element.key;
			newHead->node.value = element.value;
			newHead->next = pq;
			// // swap
			pq = newHead;
			//
			curr = pq;
			while (curr != NULL) {
				printf("> key = %d , value = %d\n", curr->node.key, curr->node.value);
				curr = curr->next;
			}
		}
		// while (curr->next != NULL) {
		// 	curr = curr->next;
		// }
		// else if (element.value >= curr->node.value) {
		// 	// Add after the curr.
		// 	curr->next = newPQ();
		// 	curr->next->node.key = element.key;
		// 	curr->next->node.value = element.value;
		// }
		// else {
		// 	// Lies in-between two PQ's.
		// 	after = before->next;
		// 	while (after ->next != NULL) {
		// 		if ((element.value < after->node.value) && (element.value >= before->node.value)) {
		// 			before->next = newPQ();
		// 			before->next->node.key = element.key;
		// 			before->next->node.value = element.value;
		// 			before->next->next = after;
		// 			return;
		// 		}
		// 		before = after;
		// 		after = after->next;
		// 	}
		// }
	}
	printf("\n");
}

ItemPQ dequeuePQ(PQ pq) {
	assert(pq != NULL);

	PQ curr = pq;
	ItemPQ temp = {0};

	if (pq->node.key == EMPTY_NODE) { // No nodes, do nothing (nothing to dequeue).
		;
	}
	else { // At least one node.
		temp.key = pq->node.key;
		temp.value = pq->node.value;
		if (pq->next == NULL) { // Only one node, replace its key-value.
			pq->node.key = EMPTY_NODE;
			pq->node.value = 0;
		}
		else { // More nodes, replace pq with pq->next.
			pq = pq->next;
			free(curr);
		}
	}
	
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
