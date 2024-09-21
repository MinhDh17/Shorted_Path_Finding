#include "BFS.h"
#include <iostream>
#include <thread>

BFS::BFS(Graph& graph)
	:graph(graph) {
	if (!Font.loadFromFile("../font/RadleySans-ZVYBK.ttf")) {}
	Text.setFont(Font);
	Text.setString("Visualizing BFS...");
	Text.setPosition(sf::Vector2f(500, 645));
	Text.setFillColor(sf::Color::Black);
	Text.setOutlineColor(sf::Color::White);
	Text.setOutlineThickness(2);
	Text.setCharacterSize(30);
}

void BFS::Visualize_Algorithm(const Coord& Start_Pos, const Coord& End_Pos, const std::vector<Coord>& Obstacles, Grid& Grid, sf::RenderWindow& render_window) {
	for (const Coord& x : Obstacles) {
		graph.Get_Node(x).Have_Obstacle = true;
	}

	this->End_Pos = End_Pos;
	this->Start_Pos = Start_Pos;

	Node* Start_Node = &(graph.Get_Node(Start_Pos));
	q.push(Start_Node);
	Start_Node->Visited = true;

	while (!q.empty() && !flag) {
		Node* Current_Node = q.front();
		q.pop();
		Grid.Set_Color_Visited(Current_Node->Node_Pos);

		Grid.Draw_Grid();
		render_window.draw(Text);
		render_window.display();

		if (Current_Node->Node_Pos == End_Pos) {
			flag = true;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		for (Node* &x : Current_Node->Nearby) {
			if (!x->Visited) {
				if (x->Have_Obstacle) {
					continue;
				}

				else {
					x->Parent = Current_Node;
					q.push(x);
					x->Visited = true;
					Grid.Set_Color_Visiting(x->Node_Pos);
				}
			}
		}
	}
	return;
}

void BFS::Build_Path(Grid& Grid) {
	length = 0;
	Node* Path = &(graph.Get_Node(End_Pos));

	if (Path != nullptr) {
		while (Path->Parent != nullptr) {
			Grid.Set_Color_Path(Path->Node_Pos, Path->Parent->Node_Pos);
			Path = Path->Parent;
			length++;
		}
	}
}

bool BFS::Path_Found() const {
	return flag;
}

int BFS::Get_Path_Length() const {
	return length;
}