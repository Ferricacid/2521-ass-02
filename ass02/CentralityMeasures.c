// Graph ADT interface for Ass2 (COMP2521)
#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

NodeValues outDegreeCentrality(Graph g) {
	assert(g != NULL);

	int v = 0;
	NodeValues ODC = {0};
	AdjList out = {0};

	ODC.noNodes = numVerticies(g);
	ODC.values = malloc(sizeof(double) * ODC.noNodes);
	assert(ODC.values != NULL);

	for (v = 0; v < ODC.noNodes; v++) {
		ODC.values[v] = 0;
		out = outIncident(g, v);
		while (out != NULL) {
			ODC.values[v]++;
			out = out->next;
		}
	}

	return ODC;
}
NodeValues inDegreeCentrality(Graph g) {
	assert(g != NULL);

	int v = 0;
	NodeValues IDC = {0};
	AdjList in = {0};

	IDC.noNodes = numVerticies(g);
	IDC.values = malloc(sizeof(double) * IDC.noNodes);
	assert(IDC.values != NULL);

	for (v = 0; v < IDC.noNodes; v++) {
		IDC.values[v] = 0;
		in = inIncident(g, v);
		while(in != NULL) {
			IDC.values[v]++;
			in = in->next;
		}
	}

	return IDC;
}
NodeValues degreeCentrality(Graph g) {
	assert(g != NULL);

	int v = 0;
	NodeValues ODC = outDegreeCentrality(g);
	NodeValues IDC = inDegreeCentrality(g);
	NodeValues DC = {0};
	
	DC.noNodes = numVerticies(g);
	DC.values = malloc(sizeof(double) * DC.noNodes);
	assert(DC.values != NULL);

	for (v = 0; v < DC.noNodes; v++) {
		DC.values[v] = ODC.values[v] + IDC.values[v];
	}

	return DC;
}

NodeValues closenessCentrality(Graph g) {
	assert(g != NULL);

	int u = 0;
	int v = 0;
	int cc_n = 0;
	int cc_N = 0;
	int sum_d = 0;

	NodeValues CC = {0};
	
	CC.noNodes = numVerticies(g);
	CC.values = malloc(sizeof(double) * CC.noNodes);
	assert(CC.values != NULL);

	for (u = 0; u < CC.noNodes; u++) {
		ShortestPaths paths = dijkstra(g, u);

		cc_n = 1;
		for (v = 0; v < paths.noNodes; v++) {
			if (paths.dist[v] > 0) {
				cc_n++;
			}
		}

		cc_N = paths.noNodes;

		sum_d = 0;
		for (v = 0; v < paths.noNodes; v++) {
			if (paths.dist[v] > 0) {
				sum_d += paths.dist[v];
			}
		}

		if ((sum_d == 0) || ((cc_N - 1) == 0)) {
			CC.values[u] = 0;
		}
		else {
			CC.values[u] = (((double)cc_n - 1) / ((double)cc_N - 1)) * (((double)cc_n - 1) / (double)sum_d);
		}

		freeShortestPaths(paths);
	}
	
	return CC;
}

NodeValues betweennessCentrality(Graph g) {
	assert(g != NULL);

	int v = 0;
	int s = 0;
	int t = 0;
	int num_paths = 0;
	int v_appearances = 0;
	ItemPQ add = {0};
	ItemPQ view = {0};
	PredNode *curr = NULL;

	ItemPQ subView = {0};

	NodeValues BC = {0};
	BC.noNodes = numVerticies(g);
	BC.values = malloc(sizeof(double) * BC.noNodes);
	assert(BC.values != NULL);

	for (v = 0; v < BC.noNodes; v++) {
		// printf("vertex %d\n", v);
		BC.values[v] = 0;

		for(s = 0; s < BC.noNodes; s++) {
			// printf("src %d\n", s);
			ShortestPaths dijPaths = dijkstra(g, s);
			for (t = 0; t < BC.noNodes; t++) {
				if (((s != t) && (s != v) && (t != v)) && (dijPaths.dist[t] > 0)) {
					// printf("%d -> %d\n", s, t);
					num_paths = 0;
					v_appearances = 0;

					PQ toDo = newPQ();
					add.key = t;
					add.value = dijPaths.dist[t];
					addPQ(toDo, add);

					// printf("now:\n");
					// showPQ(toDo);

					while (PQEmpty(toDo) != 1) {
						view = dequeuePQ(toDo);
						if (view.key == s) {
							num_paths++;
						}
						else if (view.key == v) {
							PQ subToDo = newPQ();
							add.key = v;
							add.value = dijPaths.dist[v];
							// printf("> view.key %d\n", view.key);
							// printf("->%d %d\n", add.key, add.value);
							addPQ(subToDo, add);
							while (PQEmpty(subToDo) != 1) {
								subView = dequeuePQ(subToDo);
								if (subView.key == s) {
									v_appearances++;
								}
								curr = dijPaths.pred[subView.key];
								while (curr != NULL) {
									add.key = curr->v;
									add.value = dijPaths.dist[v];
									addPQ(subToDo, add);
									curr = curr->next;
									// printf(">\n");
								}
							}
							freePQ(subToDo);
						}
						// else if view.key == v, find num_paths from v and add to v_apperances
						curr = dijPaths.pred[view.key];
						while (curr != NULL) {
							add.key = curr->v;
							add.value = dijPaths.dist[v];
							addPQ(toDo, add);
							curr = curr->next;
						}
					}

					freePQ(toDo);

					if (num_paths > 0) {
						// printf("v_apperances = %d , num_paths = %d\n", v_appearances, num_paths);
						BC.values[v] += (float) v_appearances / (float) num_paths;
					}
				}
			}
			freeShortestPaths(dijPaths);
		}
		// printf("\n");
	}

	return BC;
}

NodeValues betweennessCentralityNormalised(Graph g) {
	assert(g != NULL);

	int v = 0;
	NodeValues BCN = {0};
	NodeValues BC = betweennessCentrality(g);

	BCN.noNodes = numVerticies(g);
	BCN.values = malloc(sizeof(double) * BCN.noNodes);
	assert(BCN.values != NULL);
	
	for (v = 0; v < BCN.noNodes; v++) {
		BCN.values[v] = (1 / (((float) BCN.noNodes  - 1) * ((float) BCN.noNodes - 2))) * (float) BC.values[v];
	}
	
	return BCN;
}

void showNodeValues(NodeValues values) {
	int v = 0;

	for (v = 0; v < values.noNodes; v++) {
		printf("%d: %f\n", v, values.values[v]);
	}
}

void freeNodeValues(NodeValues values) {
	free(values.values);
}
