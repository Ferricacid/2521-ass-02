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
	ODC.values = malloc(sizeof(int) * ODC.noNodes);
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
	IDC.values = malloc(sizeof(int) * IDC.noNodes);
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
	NodeValues IDC = outDegreeCentrality(g);
	NodeValues DC = {0};
	
	DC.noNodes = numVerticies(g);
	DC.values = malloc(sizeof(int) * DC.noNodes);
	assert(DC.values != NULL);

	for (v = 0; v < DC.noNodes; v++) {
		DC.values[v] = ODC.values[v] + IDC.values[v];
	}

	return DC;
}

NodeValues closenessCentrality(Graph g) {
	assert(g != NULL);

	int v = 0;
	int sum_shortest = 0;
	int v_other = 0;
	NodeValues CC = {0};
	
	CC.noNodes = numVerticies(g);
	CC.values = malloc(sizeof(int) * CC.noNodes);
	assert(CC.values != NULL);

	for (v = 0; v < CC.noNodes; v++) {
		ShortestPaths paths = dijkstra(g, v);
		sum_shortest = 0;
		for (v_other = 0; v < paths.noNodes; v_other++) {
			sum_shortest += paths.dist[v_other];
		}
		if (sum_shortest != 0) {
			CC.values[v] = ((paths.noNodes - 1) / (CC.noNodes)) * ((paths.noNodes - 1) / sum_shortest);
		}
		else {
			CC.values[v] = 0;
		}
		freeShortestPaths(paths);
	}
	
	return CC;
}

NodeValues betweennessCentrality(Graph g) {
	assert(g != NULL);

	NodeValues BC = {0};

	BC.noNodes = numVerticies(g);
	BC.values = malloc(sizeof(int) * BC.noNodes);
	assert(BC.values != NULL);

	return BC;
}

NodeValues betweennessCentralityNormalised(Graph g) {
	assert(g != NULL);

	int v = 0;
	NodeValues BCN = {0};
	NodeValues BC = betweennessCentrality(g);

	BCN.noNodes = numVerticies(g);
	BCN.values = malloc(sizeof(int) * BCN.noNodes);
	assert(BN.values != NULL);

	for (v = 0; v < BN.noNodes; v++) {
		BCN.values[v] = (1 / ((BCN.noNodes  - 1) * (BCN.noNodes - 2))) * BC.values[v];
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
