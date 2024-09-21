#include <iostream>
#include "Grid.h"

Grid::Grid(int width, int height, const sf::Mouse& mouse, sf::RenderWindow& render_window) : Map_Width(width), Map_Height(height), mouse(mouse), render_window(render_window) {
	//Tính số ô theo trục x,y
	Number_X_Tiles = (width) / Tile_size;
	Number_Y_Tiles = (height) / Tile_size;

	Start_Pos = { 0, 0 };
	End_Pos = { Number_X_Tiles - 1, Number_Y_Tiles - 1 };

	for (int i = 0; i < Number_X_Tiles * Number_Y_Tiles; i++) {
		Map.emplace_back(sf::Vector2f(Tile_size, Tile_size));
	}

	for (int x = 0; x < Number_X_Tiles; x++) {
		for (int y = 0; y < Number_Y_Tiles; y++) {
			Map[x * Number_X_Tiles + y].setPosition(sf::Vector2f(x * Tile_size, y * Tile_size));
			Map[x * Number_X_Tiles + y].setFillColor(Tile_Color);
			Map[x * Number_X_Tiles + y].setOutlineColor(sf::Color(52, 61, 70));
			Map[x * Number_X_Tiles + y].setOutlineThickness(-Thickness);
		}
	}

	Map[Start_Pos.x * Number_X_Tiles + Start_Pos.y].setFillColor(Start_Color);
	Map[End_Pos.x * Number_X_Tiles + End_Pos.y].setFillColor(End_Color);
}

void Grid::Draw_Grid() {
	for (const sf::RectangleShape& Tile : Map) {
		render_window.draw(Tile);
	}
}

void Grid::Draw_Path() {
	if (Vertices.size() > 0) {
		render_window.draw(&Vertices[0], Vertices.size(),sf::Lines);
	}
}

void Grid::Set_Obstacle() {
	int Mouse_x = mouse.getPosition(render_window).x;
	int Mouse_y = mouse.getPosition(render_window).y;

	Coord Mouse_Pos = { Mouse_x / Tile_size, Mouse_y / Tile_size };

	if (Mouse_x < 0 || Mouse_x >= 640 || Mouse_y < 0 || Mouse_y >= 640) {
		return;
	}

	if (Get_Color(Mouse_Pos) == Start_Color || Get_Color(Mouse_Pos) == End_Color) return;

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		Prev_Mouse_Pos = { -1, -1 }; 
		return;
	}

	if (Prev_Mouse_Pos.x == -1 && Prev_Mouse_Pos.y == -1) {
		Prev_Mouse_Pos = Mouse_Pos;
		if (Get_Color(Mouse_Pos) != Start_Color && Get_Color(Mouse_Pos) != End_Color) {
			Set_Color(Mouse_Pos, Obstacle_Color);
			Obstacles.emplace_back(Mouse_Pos);
		}
		return;
	}

	int dx = abs(Mouse_Pos.x - Prev_Mouse_Pos.x);
	int dy = abs(Mouse_Pos.y - Prev_Mouse_Pos.y);

	int sx = Prev_Mouse_Pos.x < Mouse_Pos.x ? 1 : -1;
	int sy = Prev_Mouse_Pos.y < Mouse_Pos.y ? 1 : -1;
	int err = dx - dy;

	Coord Current = Prev_Mouse_Pos;
	while (1) {
		if (Get_Color(Current) != Start_Color && Get_Color(Current) != End_Color) {
			Set_Color(Current, Obstacle_Color);
			Obstacles.emplace_back(Current);
		}
		if (Current.x == Mouse_Pos.x && Current.y == Mouse_Pos.y) break;

		int e2 = 2 * err;
		if (e2 > -dy) {
			err -= dy;
			Current.x += sx;
		}
		if (e2 < dx) {
			err += dx;
			Current.y += sy;
		}

	}
	Prev_Mouse_Pos = Mouse_Pos;
}

void Grid::Set_Start() {
	int Mouse_x = mouse.getPosition(render_window).x;
	int Mouse_y = mouse.getPosition(render_window).y;

	if (Mouse_x < 0 || Mouse_x >= 640 || Mouse_y < 0 || Mouse_y >= 640) {
		return;
	}

	int x = (int)(Mouse_x / Tile_size);
	int y = (int)(Mouse_y / Tile_size);

	if (Check_Out(x, y)) return;

	Coord Pre_Start_Pos;
	Coord Mouse_Pos = { x, y };

	if (Get_Color(Mouse_Pos) == Start_Color) {
		Change_Start_Pos = true;
		Pre_Start_Pos = { x, y };
	}

	while (Change_Start_Pos) {
		int Mouse_x = mouse.getPosition(render_window).x;
		int Mouse_y = mouse.getPosition(render_window).y;
		int x = (int)(Mouse_x / Tile_size);
		int y = (int)(Mouse_y / Tile_size);

		Coord New_Start_Pos = { x, y };

		if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {

			if (Get_Color(New_Start_Pos) == Obstacle_Color) {
				continue;
			}

			if (Get_Color(New_Start_Pos) == End_Color) {	
				Change_End_Pos = false;			
				continue;
			}

			if (Get_Color(New_Start_Pos) == Tile_Color) {		
				Set_Color(New_Start_Pos, Start_Color);		
				Update_Start_Pos(New_Start_Pos);				
				Set_Color(Pre_Start_Pos, Tile_Color);	
				Change_Start_Pos = false;
				break;
			}
		}
	}
}

void Grid::Set_End() {
	int Mouse_x = mouse.getPosition(render_window).x;
	int Mouse_y = mouse.getPosition(render_window).y;

	if (Mouse_x < 0 || Mouse_x >= 640 || Mouse_y < 0 || Mouse_y >= 640) {
		return;
	}

	int x = (int)(Mouse_x / Tile_size);
	int y = (int)(Mouse_y / Tile_size);

	if (Check_Out(x, y)) return;

	Coord Pre_End_Pos;
	Coord Mouse_Pos = { x, y };

	if (Get_Color(Mouse_Pos) == End_Color) {
		Change_End_Pos = true;
		Pre_End_Pos = { x, y };
	}

	while (Change_End_Pos) {
		int Mouse_x = mouse.getPosition(render_window).x;
		int Mouse_y = mouse.getPosition(render_window).y;
		int x = (int)(Mouse_x / Tile_size);
		int y = (int)(Mouse_y / Tile_size);

		Coord New_End_Pos = { x, y };

		if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {

			if (Get_Color(New_End_Pos) == Obstacle_Color) {
				continue;
			}

			if (Get_Color(New_End_Pos) == Start_Color) {	
				Change_Start_Pos = false;			
				continue;
			}

			if (Get_Color(New_End_Pos) == Tile_Color) {		
				Set_Color(New_End_Pos, End_Color);		
				Update_End_Pos(New_End_Pos);				
				Set_Color(Pre_End_Pos, Tile_Color);	
				Change_End_Pos = false;
				break;
			}
		}
	}
}

void Grid::Set_Color_Visiting(const Coord& pos) {
	if (pos == Start_Pos || pos == End_Pos) return;
	Set_Color(pos, Visiting_Color);
}

void Grid::Set_Color_Visited(const Coord& pos) {
	if (pos == Start_Pos || pos == End_Pos) return;
	Set_Color(pos, Visited_Color);
}

void Grid::Set_Color_Path(const Coord& pos_1, const Coord& pos_2) {
	if (pos_1 != Start_Pos && pos_1 != End_Pos) {
		Set_Color(pos_1, sf::Color(212, 175, 55));
	}
	if (pos_2 != Start_Pos && pos_2 != End_Pos) {
		Set_Color(pos_2, sf::Color(212, 175, 55));
	}
}

void Grid::Reset_Grid() {
	for (sf::RectangleShape &Tile : Map) {
		if (Tile.getFillColor() == Obstacle_Color) continue;
		Tile.setFillColor(Tile_Color);
	}

	Set_Color(Start_Pos, Start_Color);
	Set_Color(End_Pos, End_Color);
	Vertices.clear();
}

void Grid::Clear_Obstacles() {
	for (sf::RectangleShape &Tile : Map) {
		if (Tile.getFillColor() == Obstacle_Color) {
			Tile.setFillColor(Tile_Color);
		}
	}
	Obstacles.clear();
}

std::vector<Coord> Grid::Get_Obstacle_Pos() const {
	return Obstacles;
}

std::pair<int, int> Grid::Get_Tiles() const {
	return std::make_pair(Number_X_Tiles, Number_Y_Tiles);
}

Coord Grid::Get_Start_Pos() const {
	return Start_Pos;
}

Coord Grid::Get_End_Pos() const {
	return End_Pos;
}

void Grid::Update_Start_Pos(const Coord& pos) {
	Start_Pos.x = pos.x;
	Start_Pos.y = pos.y;
}

void Grid::Update_End_Pos(const Coord& pos) {
	End_Pos.x = pos.x;
	End_Pos.y = pos.y;
}

sf::Color Grid::Get_Color(const Coord& pos) const {
	return Map[pos.x * Number_X_Tiles + pos.y].getFillColor();
}

void Grid::Set_Color(const Coord& pos, const sf::Color& color) {
	Map[pos.x * Number_X_Tiles + pos.y].setFillColor(color);
}

bool Grid::Check_Out(int x, int y) {
	if (x < 0 || y < 0 || x >= Map_Width || y >= Map_Height) return 1;
	return 0;
}
