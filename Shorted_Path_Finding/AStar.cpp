#include "AStar.h"
#include <iostream>
#include <thread>

AStar::AStar(Graph& graph)
	:graph(graph)
{
	if (!Font.loadFromFile("../font/RadleySans-ZVYBK.ttf")) {}
	Text.setFont(Font);
	Text.setString("Visualizing A*...");
	Text.setPosition(sf::Vector2f(500, 645));
	Text.setFillColor(sf::Color::Black);
	Text.setOutlineColor(sf::Color::White);
	Text.setOutlineThickness(2);
	Text.setCharacterSize(30);
}

void AStar::Visualize_Algorithm(const Coord& Start_Pos, const Coord& End_Pos, const std::vector<Coord>& Obstacles, Grid& Grid, sf::RenderWindow& render_window) {
	for (const Coord& x : Obstacles) {
		graph.Get_Node(x).Have_Obstacle = true;
	}

	this->Start_Pos = Start_Pos;
	this->End_Pos = End_Pos;

	auto f_Cost_Comparator = [](Node* Left_Node, Node* Right_Node) {
		return Left_Node->f_Cost < Right_Node->f_Cost;
	};

	Node* Start_Node = &(graph.Get_Node(Start_Pos));
	Start_Node->g_Cost = 0;
	Node* End_Node = &(graph.Get_Node(End_Pos));
	Start_Node->h_Cost = Node_Distance(Start_Node, End_Node);
	l.emplace_back(Start_Node);

	while (!l.empty() && !flag) {
		l.sort(f_Cost_Comparator);
		Node* Current = l.front();
		l.pop_front();
		Current->Visited = true;
		Grid.Set_Color_Visited(Current->Node_Pos);

		if (Current->Node_Pos == End_Pos) {
			flag = true;
		}

		Grid.Draw_Grid();
		render_window.draw(Text);
		render_window.display();

		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		for (Node* &Neighbor : Current->Nearby) {
			if (Neighbor->Visited || Neighbor->Have_Obstacle) {
				continue;
			}

			else {
				double e_gCost = Current->g_Cost + Node_Distance(Current, Neighbor);
				if (e_gCost < Neighbor->g_Cost) {			
					Neighbor->Parent = Current;
					Neighbor->g_Cost = e_gCost;
					Neighbor->h_Cost = Node_Distance(Neighbor, End_Node);
					Neighbor->f_Cost = Neighbor->g_Cost + Neighbor->h_Cost;

					auto x = Open_Set.find(Neighbor);
					if (x == Open_Set.end()) {		
						Grid.Set_Color_Visiting(Neighbor->Node_Pos);
						l.emplace_back(Neighbor);
						Open_Set.insert(Neighbor);
					}
				}
			}
		}
	}
}

void AStar::Build_Path(Grid& Grid) {
	Node* Path = &graph.Get_Node(End_Pos);

	if (Path != nullptr) {
		while (Path->Parent != nullptr) {
			Grid.Set_Color_Path(Path->Node_Pos, Path->Parent->Node_Pos);
			Path = Path->Parent;
			length++;
		}
	}
}

double AStar::Node_Distance(Node* a, Node* b)
{
	int x = (a->Node_Pos.x - b->Node_Pos.x);
	int y = (a->Node_Pos.y - b->Node_Pos.y);
	return sqrt((x * x) + (y * y));				
}

bool AStar::Path_Found() const {
	return flag;
}

int AStar::Get_Path_Length() const {
	return length;
}