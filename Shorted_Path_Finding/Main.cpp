#include <SFML/Graphics.hpp>
#include <chrono>
#include "Grid.h"
#include "Graph.h"
#include "Algorithm.h"
#include "All_Algorithm.h"
int main()
{ 
    sf::RenderWindow window(sf::VideoMode(800, 800), "Shorted_Path_Finding");
    window.setFramerateLimit(60);
    sf::Mouse mouse;
    

    Grid grid(640, 640, mouse, window);
    Graph graph(grid.Get_Tiles());

    bool Visualize = false;

    sf::Font font;
    std::string Choose = "Algorithm: ";
    std::string command1 = "Clear obstacle: Press 'O'";
    std::string command2 = "Clear search: Press 'R'";
    std::string command3 = "Visualize: Press 'V'";
    std::string command4 = "Press 1,2,3 to choose algorithm";
    std::string algorithm;
    std::string result;
    std::string step;
    
    sf::Text text;
    sf::Text Algorithm_text;
    sf::Text result_text;
    sf::Text step_text;
    sf::Text command1_text;
    sf::Text command2_text;
    sf::Text command3_text;
    sf::Text command4_text;
    
    sf::RectangleShape Right_Background;
    sf::RectangleShape Bottom_Background;
    sf::RectangleShape Map_Background;

    sf::RectangleShape button_bfs;
    sf::RectangleShape button_dijkstra;
    sf::RectangleShape button_Astar;

    sf::Text button_bfs_text;
    sf::Text button_dijkstra_text;
	sf::Text button_Astar_text;

    if (!font.loadFromFile("../font/RadleySans-ZVYBK.ttf")) {

    }

    text.setFont(font);
    text.setString(Choose);
    text.setPosition(sf::Vector2f(652, 300));
    text.setFillColor(sf::Color::Black);
    text.setOutlineColor(sf::Color::White);
    text.setOutlineThickness(2);
    text.setCharacterSize(30);

    Algorithm_text.setFont(font);
    Algorithm_text.setString(algorithm);
    Algorithm_text.setPosition(sf::Vector2f(655, 340));
    Algorithm_text.setFillColor(sf::Color::Black);
    Algorithm_text.setOutlineColor(sf::Color::White);
    Algorithm_text.setOutlineThickness(2);
    Algorithm_text.setCharacterSize(30);

    result_text.setFont(font);
    result_text.setString(result);
    result_text.setPosition(sf::Vector2f(500, 645));
    result_text.setFillColor(sf::Color::Black);
    result_text.setOutlineColor(sf::Color::White);
    result_text.setOutlineThickness(2);
    result_text.setCharacterSize(40);

    step_text.setFont(font);
    step_text.setString(step);
    step_text.setPosition(sf::Vector2f(500, 690));
    step_text.setFillColor(sf::Color::Black);
    step_text.setOutlineColor(sf::Color::White);
    step_text.setOutlineThickness(2);
    step_text.setCharacterSize(40);

    command1_text.setFont(font);
    command1_text.setString(command1);
    command1_text.setPosition(sf::Vector2f(10, 640));
    command1_text.setFillColor(sf::Color::Black);
    command1_text.setOutlineColor(sf::Color::White);
    command1_text.setOutlineThickness(2);
    command1_text.setCharacterSize(30);

    command2_text.setFont(font);
    command2_text.setString(command2);
    command2_text.setPosition(sf::Vector2f(10, 680));
    command2_text.setFillColor(sf::Color::Black);
    command2_text.setOutlineColor(sf::Color::White);
    command2_text.setOutlineThickness(2);
    command2_text.setCharacterSize(30);

    command3_text.setFont(font);
    command3_text.setString(command3);
    command3_text.setPosition(sf::Vector2f(10, 720));
    command3_text.setFillColor(sf::Color::Black);
    command3_text.setOutlineColor(sf::Color::White);
    command3_text.setOutlineThickness(2);
    command3_text.setCharacterSize(30);

    command4_text.setFont(font);
    command4_text.setString(command4);
    command4_text.setPosition(sf::Vector2f(10, 760));
    command4_text.setFillColor(sf::Color::Black);
    command4_text.setOutlineColor(sf::Color::White);
    command4_text.setOutlineThickness(2);
    command4_text.setCharacterSize(30);

    Right_Background.setSize(sf::Vector2f(160, 800));
    Right_Background.setFillColor(sf::Color(200, 200, 200)); 
    Right_Background.setPosition(640, 0);

    Bottom_Background.setSize(sf::Vector2f(640, 160));
    Bottom_Background.setFillColor(sf::Color(200, 200, 200)); 
    Bottom_Background.setPosition(0, 640);

    button_bfs.setSize(sf::Vector2f(120, 60));
    button_bfs.setFillColor(sf::Color::White);
    button_bfs.setPosition(660, 20);
    button_bfs.setOutlineColor(sf::Color::Black);
    button_bfs.setOutlineThickness(-2);

    button_dijkstra.setSize(sf::Vector2f(120, 60));
    button_dijkstra.setFillColor(sf::Color::White);
    button_dijkstra.setPosition(660, 120);
    button_dijkstra.setOutlineColor(sf::Color::Black);
    button_dijkstra.setOutlineThickness(-2);

    button_Astar.setSize(sf::Vector2f(120, 60));
    button_Astar.setFillColor(sf::Color::White);
    button_Astar.setPosition(660, 220);
    button_Astar.setOutlineColor(sf::Color::Black);
    button_Astar.setOutlineThickness(-2);

    button_bfs_text.setFont(font);
    button_bfs_text.setString("BFS");
    button_bfs_text.setCharacterSize(30);
    button_bfs_text.setFillColor(sf::Color::Black);
    button_bfs_text.setPosition(695, 30);

    button_dijkstra_text.setFont(font);
    button_dijkstra_text.setString("Dijkstra");
    button_dijkstra_text.setCharacterSize(30);
    button_dijkstra_text.setFillColor(sf::Color::Black);
    button_dijkstra_text.setPosition(665, 130);

    button_Astar_text.setFont(font);
    button_Astar_text.setString("A*");
    button_Astar_text.setCharacterSize(30);
    button_Astar_text.setFillColor(sf::Color::Black);
    button_Astar_text.setPosition(710, 230);

    Algorithm* algo = nullptr;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (!Visualize) {   

				if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
					grid.Set_Start();
					grid.Set_End();
				}

                grid.Set_Obstacle();
            }
            
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Num1) {
                    algorithm = "BFS";
                    Algorithm_text.setString(algorithm);
                    if (algo != nullptr) {
                        delete algo;
                    }
                    algo = All_Algorithm::Create("BFS", graph);
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Num2) {
                    algorithm = "Dijkstra";
                    Algorithm_text.setString(algorithm);
                    if (algo != nullptr) {
                        delete algo;
                    }
                    algo = All_Algorithm::Create("Dijkstra", graph);
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Num3) {
                    algorithm = "A*";
                    Algorithm_text.setString(algorithm);
                    if (algo != nullptr) {
                        delete algo;
                    }
                    algo = All_Algorithm::Create("A*", graph);
                }
            }

            if (algo != nullptr) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
                    Visualize = true;
                }
            }
            
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::R) {
                    grid.Reset_Grid();
                    graph.Reset_Graph();
                    algorithm = "";
                    Algorithm_text.setString(algorithm);
                    result = "";
                    step = "";
                    result_text.setString(result);
                    step_text.setString(step);
                    delete algo;
                    algo = nullptr;
                    Visualize = false;
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::O) {
                    grid.Clear_Obstacles();
                }
            }

            if (Visualize) {
                Coord Start_Pos = grid.Get_Start_Pos();
                Coord End_Pos = grid.Get_End_Pos();
                std::vector<Coord> Obstacles = grid.Get_Obstacle_Pos();
                algo->Visualize_Algorithm(Start_Pos, End_Pos, Obstacles, grid, window);
                algo->Build_Path(grid);
                
                if (algo->Path_Found()) {
                    result = "Finding Success!";
                    step = "Step: " + std::to_string(algo->Get_Path_Length());
                }
                else {
                    result = "Can't find path!";
                }
                result_text.setString(result);
                step_text.setString(step);
                Visualize = false;
            }
        }
        window.clear();

        window.draw(Right_Background);
        window.draw(Bottom_Background);
        window.draw(text);
        window.draw(Algorithm_text);
        window.draw(result_text);
        window.draw(step_text);

        window.draw(command1_text);
        window.draw(command2_text);
        window.draw(command3_text);
        window.draw(command4_text);
       
        window.draw(button_bfs);
        window.draw(button_bfs_text);
        window.draw(button_dijkstra);
        window.draw(button_dijkstra_text);
        window.draw(button_Astar);
        window.draw(button_Astar_text);

        grid.Draw_Grid();
        grid.Draw_Path();

        window.display();

    }
    return 0;
}