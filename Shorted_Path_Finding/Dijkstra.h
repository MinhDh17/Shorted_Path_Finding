#pragma once
#include "Algorithm.h"
#include "Graph.h"
#include "Grid.h"
#include <unordered_set>
#include <list>

class Dijkstra : public Algorithm {
private:
	Graph& graph;
	sf::Text Text;
	sf::Font Font;
	Coord Start_Pos;
	Coord End_Pos;
	std::list<Node*> l;
	std::unordered_set<Node*> Open_Set;
	double Node_Distance(Node* a, Node* b);
	bool flag = 0;
	int length = 0;
public:
	Dijkstra(Graph& graph);
	void Visualize_Algorithm(const Coord& Start_Pos, const Coord& End_Pos, const std::vector<Coord>& Obstacles, Grid& Grid, sf::RenderWindow& render_window) override;
    void Build_Path(Grid& Grid) override;
	bool Path_Found() const override;
	int Get_Path_Length() const override;
};