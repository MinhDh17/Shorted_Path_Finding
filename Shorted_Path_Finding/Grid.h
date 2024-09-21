#pragma once
#include <SFML\Graphics.hpp>
#include "Graph.h"

class Grid {
private:
	std::vector<sf::RectangleShape> Map; //các ô hcn
	std::vector<Coord> Obstacles; //lưu trữ vị trí tường
	const sf::Mouse& mouse;
	sf::RenderWindow& render_window;
	//32
	const int Tile_size = 32;
	const int Thickness = 1;

	const int Map_Width;
	const int Map_Height;

	int Number_X_Tiles;
	int Number_Y_Tiles;

	Coord Start_Pos;
	Coord End_Pos;
    
	Coord Prev_Mouse_Pos = { -1, -1 };

	sf::Color Tile_Color = sf::Color(18, 33, 153);

	sf::Color Obstacle_Color = sf::Color::Black;
	sf::Color Start_Color = sf::Color::Green;
	sf::Color End_Color = sf::Color::Red;
	sf::Color Visited_Color = sf::Color::Blue;
	sf::Color Visiting_Color = sf::Color::Cyan;

	std::vector<sf::Vertex> Vertices;

	bool Change_Start_Pos = 0;
	bool Change_End_Pos = 0;

	void Update_Start_Pos(const Coord& pos);
	void Update_End_Pos(const Coord& pos);
	sf::Color Get_Color(const Coord& pos) const;
	void Set_Color(const Coord& pos, const sf::Color& color);
	bool Check_Out(int x, int y);

public:
	Grid(int width, int height, const sf::Mouse& mouse, sf::RenderWindow& render_window);
	void Draw_Grid();
	void Draw_Path();
	void Set_Obstacle();
	void Set_Start();
	void Set_End();
	void Set_Color_Visiting(const Coord& pos);
	void Set_Color_Visited(const Coord& pos);
	void Set_Color_Path(const Coord& pos_1, const Coord& pos_2);
	void Reset_Grid();
	void Clear_Obstacles();

	std::vector<Coord> Get_Obstacle_Pos() const;
	std::pair<int, int> Get_Tiles() const;

	Coord Get_Start_Pos() const; //tọa độ điểm bắt đầu
	Coord Get_End_Pos() const;   //tọa độ điểm kết thúc
};