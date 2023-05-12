#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

using namespace std;

// class that acts like the game engine 
// wrapper class
class Game
{
private:
    // private variables
    sf::RenderWindow* my_window;
    sf::Event my_event;
    sf::VideoMode my_VM;
    sf::Mouse my_mouse;

    // game logic
    int points;

    // papers
    float paper_spawn_timer;
    float paper_spawn_timer_max;
    int max_papers;

    // rocks
    float rock_spawn_timer;
    float rock_spawn_timer_max;
    int max_rocks;

    // scissors
    float scissor_spawn_timer;
    float scissor_spawn_timer_max;
    int max_scissors;


    // game objects
    vector<sf::RectangleShape> papers;
    sf::RectangleShape paper; // rectanlge

    vector<sf::RectangleShape> rocks;
    sf::RectangleShape rock; // square

    vector<sf::CircleShape> scissors;
    sf::CircleShape scissor; // trianlge

    // private functions
    void initVariables();
    void initWindow();
    void initPapersRocksScissors();

public:
    // constructor
    Game();
    // destructor
    ~Game();

    // accessors
    const bool window_is_open() const;

    // functions
    void poll_events();
    void update();
    void render();
    void render_rps();


    void update_paper();
    void spawn_paper();


    void update_rock();
    void spawn_rock();


    void update_scissor();
    void spawn_scissor();


    void paper_vs_rock();
    void rock_vs_scissor();
    void scissor_vs_paper();
};

