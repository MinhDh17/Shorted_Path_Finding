#pragma once
#include <vector>
#include <utility>
//tọa độ
struct Coord {
	int x;
	int y;
	bool operator == (const Coord& other) const {
		if (x == other.x && y == other.y) return true;
		return false;
	}
	bool operator != (const Coord& other) const {
		if (x != other.x || y != other.y) return true;
		return false;
	}
};

//nút trong đồ thị
struct Node {
	Node(int x, int y) : Node_Pos({ x, y }) {}
	Coord Node_Pos;
	bool Visited = 0;
	Node* Parent = nullptr;     
	bool Have_Obstacle = 0;

	double g_Cost = INFINITY; //điểm bắt đầu -> nút htại
	double h_Cost = INFINITY; //nút htại -> đích 
	double f_Cost;            
	std::vector<Node*> Nearby;
};

//Đồ thị
class Graph {
private:
	std::vector<Node> node;
	int X_Tiles;  
	int Y_Tiles;  
public:
	Graph(std::pair<int, int> Count_Tiles); //khởi tạo
	Node& Get_Node(const Coord& pos); //trả về nút dựa trên pos
	void Reset_Graph();
};