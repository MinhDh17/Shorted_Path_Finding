#include "Graph.h"
#include <iostream>
#include <utility>

Graph::Graph(std::pair<int, int> Count_Tiles) {
	int X_Tiles = Count_Tiles.first;
	int Y_Tiles = Count_Tiles.second;
	this->X_Tiles = X_Tiles;
	this->Y_Tiles = Y_Tiles;

	for (int i = 0; i < X_Tiles; i++) {
		for (int j = 0; j < Y_Tiles; j++) {
			node.emplace_back(i, j);
		}
	}
	if (node.size() != X_Tiles * Y_Tiles) {
		return;
	}

	for (int x = 0; x < X_Tiles; x++) {
		for (int y = 0; y < Y_Tiles; y++) {
			if (y > 0) {
				node[x * X_Tiles + y].Nearby.emplace_back(&node[x * X_Tiles + (y - 1)]); //trên
			}

			if (y < X_Tiles - 1) {
				node[x * X_Tiles + y].Nearby.emplace_back(&node[x * X_Tiles + (y + 1)]); //dưới
			}

			if (x > 0) {
				node[x * X_Tiles + y].Nearby.emplace_back(&node[(x - 1) * X_Tiles + y]); //trái
			}

			if (x < X_Tiles - 1) {
				node[x * X_Tiles + y].Nearby.emplace_back(&node[(x + 1) * X_Tiles + y]); //phải
			}
		}
	}
}

Node& Graph::Get_Node(const Coord& pos) {
	//nút nằm trong phạm vi
	if (pos.x * X_Tiles + pos.y >= X_Tiles * Y_Tiles || pos.x * X_Tiles + pos.y < 0) {
		exit(1);
	}
	return node[pos.x * X_Tiles + pos.y];
}

void Graph::Reset_Graph() {
	for (Node& x : node) {
		x.Visited = 0;
		x.Parent = nullptr;
		x.Have_Obstacle = 0;
		x.g_Cost = INFINITY;
		x.h_Cost = INFINITY;
		x.f_Cost = INFINITY;
	}
}