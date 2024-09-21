#pragma once
#include "Algorithm.h"
#include "BFS.h"
#include "Dijkstra.h"
#include "AStar.h"

class All_Algorithm {
public:
	static Algorithm* Create(const std::string& algorithm, Graph& graph) {
		if (algorithm == "BFS") {
			return new BFS(graph);
		}

		else if (algorithm == "Dijkstra") {
			return new Dijkstra(graph);
		}

		else if (algorithm == "A*") {
			return new AStar(graph);
		}

		else return nullptr;
	}
};