#pragma once
#include "Graph.h"
#include "Grid.h"
#include <vector>

class Algorithm {
public: 
	virtual void Visualize_Algorithm(const Coord& Start_Pos, const Coord& End_Pos, const std::vector<Coord>& Obstacles, Grid& grid, sf::RenderWindow& render_window) = 0;
	virtual void Build_Path(Grid& grid) = 0;
	virtual bool Path_Found() const = 0;
	virtual int Get_Path_Length() const = 0;
};