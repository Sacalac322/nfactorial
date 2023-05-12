#include "Game.h"


// private functions
void Game::initVariables()
{
    this->my_window = nullptr;
    srand(static_cast<unsigned>(time(NULL)));


    // game logic
    points = 0;
    // paper
    this->paper_spawn_timer_max = 10.0f;
    this->paper_spawn_timer = this->paper_spawn_timer_max;
    this->max_papers = (rand() % (30 - 10 + 1) + 10);


    // rock
    this->rock_spawn_timer_max = 10.0f;
    this->rock_spawn_timer = this->rock_spawn_timer_max;
    this->max_rocks = (rand() % (30 - 10 + 1) + 10);

    // scissor
    this->scissor_spawn_timer_max = 10.0f;
    this->scissor_spawn_timer = this->scissor_spawn_timer_max;
    this->max_scissors = (rand() % (30 - 10 + 1) + 10);
}

void Game::initWindow()
{
    this->my_VM.width = 400;
    this->my_VM.height = 600;
    this->my_window = new sf::RenderWindow(this->my_VM, "Simulation", sf::Style::Titlebar | sf::Style::Close);
    this->my_window->setFramerateLimit(60);
}

void Game::initPapersRocksScissors()
{
    // paper
    this->paper.setSize(sf::Vector2f(10.0f, 20.0f));
    this->paper.setFillColor(sf::Color::Cyan);
    this->paper.setOutlineColor(sf::Color::White);
    this->paper.setOutlineThickness(1.0f);


    // rock
    this->rock.setSize(sf::Vector2f(10.0f, 10.0f));
    this->rock.setFillColor(sf::Color::White);
    this->rock.setOutlineColor(sf::Color::White);
    this->rock.setOutlineThickness(1.0f);

    // scissor
    this->scissor.setRadius(10.0f);
    this->scissor.setPointCount(3);
    this->scissor.setFillColor(sf::Color::Green);
    this->scissor.setOutlineColor(sf::Color::White);
    this->scissor.setOutlineThickness(1.0f);
}



// constructors and desturctors
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initPapersRocksScissors();
}

Game::~Game()
{
    delete this->my_window;
}


const bool Game::window_is_open() const
{
    return this->my_window->isOpen();
}



// functions
void Game::poll_events()
{
    while (this->my_window->pollEvent(this->my_event)) {
        switch (this->my_event.type) {
        case sf::Event::Closed:
            this->my_window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->my_event.key.code == sf::Keyboard::Escape) this->my_window->close();
            break;
        }

    }
}
	
void Game::update()
{
    this->poll_events();
    this->update_paper();
    this->update_rock();
    this->update_scissor();
    cout << "papers (cyan rectangles): " << this->papers.size() << ", rocks (white squares): " << this->rocks.size()
        << ", scissors (green triangles): " << this->scissors.size() 
        << ". Overall: " << this->papers.size() + this->rocks.size() + this->scissors.size()
        << "\n";
    this->paper_vs_rock();
    this->rock_vs_scissor();
    this->scissor_vs_paper();


    if (this->papers.size() > 0 and this->rocks.size() == 0 and this->scissors.size() == 0)
    {
        this->my_window->close();
        cout << "Papers win (cyan rectangles)!!!\n";
    }
    else if (this->papers.size() == 0 and this->rocks.size() > 0 and this->scissors.size() == 0)
    {
        this->my_window->close();
        cout << "Rocks win (white squares)!!!\n";
    }
    else if (this->papers.size() == 0 and this->rocks.size() == 0 and this->scissors.size() > 0)
    {
        this->my_window->close();
        cout << "Scissors win (green triangles)!!!\n";
    }
}

void Game::render()
{
   // clears an old frame
   // renders a new frame
   // display a new frame in window


    this->my_window->clear();
    this->render_rps();
    this->my_window->display();
}

void Game::render_rps()
{
    // rendering all papers
    for (auto& e : this->papers) {
        this->my_window->draw(e);
    }

    // rendering all rocks
    for (auto& e : this->rocks) {
        this->my_window->draw(e);
    }

    // rendering all rocks
    for (auto& e : this->scissors) {
        this->my_window->draw(e);
    }
}

void Game::update_paper()
{
    /*
        @return void
        updating the timer for paper spawning
        moves the papers randomly
    */
    if (this->papers.size() < this->max_papers) {
        if (this->paper_spawn_timer >= this->paper_spawn_timer_max) {
            this->paper_spawn_timer = 0.0f;
            this->spawn_paper();
        }
        else 
            this->paper_spawn_timer += 1.0f;
    }


    // move the papers
    for (int e = 0; e < papers.size(); e++) {
        papers[e].move((float)((rand() % 9) + (-4)), (float)((rand() % 9) + (-4)));

        if (papers[e].getPosition().x < 0.f) 
            papers[e].setPosition(0.f, papers[e].getPosition().y); // left collision
        if (papers[e].getPosition().y < 0.f) 
            papers[e].setPosition(papers[e].getPosition().x, 0.f); // top collision
        if (papers[e].getPosition().x + papers[e].getGlobalBounds().width > this->my_VM.width) // right collision
            papers[e].setPosition(this->my_VM.width - papers[e].getGlobalBounds().width, papers[e].getPosition().y);
        if (papers[e].getPosition().y + papers[e].getGlobalBounds().height > this->my_VM.height) // bot collision
            papers[e].setPosition(papers[e].getPosition().x, this->my_VM.height - papers[e].getGlobalBounds().height);
    }
}

void Game::spawn_paper()
{
    /*
        @return void
         
         spawns enemies and sets their colors and positions
         - sets a random position
         - sets a random color
         - add enemy to the vector
    */
    this->paper.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->my_window->getSize().x - this->paper.getSize().x)),
        0.0f
    );

    //this->paper.setFillColor(sf::Color::Green);
    this->papers.push_back(this->paper);
}

void Game::update_rock()
{
    /*
        @return void
        updating the timer for rock spawning
        moves the rocks randomly
    */
    if (this->rocks.size() < this->max_rocks) {
        if (this->rock_spawn_timer >= this->rock_spawn_timer_max) {
            this->rock_spawn_timer = 0.0f;
            this->spawn_rock();
        }
        else
            this->rock_spawn_timer += 1.0f;
    }


    // move the rocks
    for (int i = 0; i < rocks.size(); i++) {
        rocks[i].move((float)((rand() % 9) + (-4)), (float)((rand() % 9) + (-4)));

        if (rocks[i].getPosition().x < 0.f) 
            rocks[i].setPosition(0.f, rocks[i].getPosition().y); // left collision
        if (rocks[i].getPosition().y < 0.f)
            rocks[i].setPosition(rocks[i].getPosition().x, 0.f); // top collision
        if (rocks[i].getPosition().x + rocks[i].getGlobalBounds().width > this->my_VM.width) // right collision
            rocks[i].setPosition(this->my_VM.width - rocks[i].getGlobalBounds().width, rocks[i].getPosition().y);
        if (rocks[i].getPosition().y + rocks[i].getGlobalBounds().height > this->my_VM.height) // bot collision
            rocks[i].setPosition(rocks[i].getPosition().x, this->my_VM.height - rocks[i].getGlobalBounds().height);
    }

}

void Game::spawn_rock()
{
    this->rock.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->my_window->getSize().x - this->rock.getSize().x)),
        250.0f
    );

    //this->paper.setFillColor(sf::Color::Green);
    this->rocks.push_back(this->rock);
}

void Game::update_scissor()
{
    /*
        @return void
        updating the timer for rock spawning
        moves the rocks randomly
    */
    if (this->scissors.size() < this->max_scissors) {
        if (this->scissor_spawn_timer >= this->scissor_spawn_timer_max) {
            this->scissor_spawn_timer = 0.0f;
            this->spawn_scissor();
        }
        else
            this->scissor_spawn_timer += 1.0f;
    }


    // move the papers
    for (int i = 0; i < scissors.size(); i++) {
        scissors[i].move((float)((rand() % 9) + (-4)), (float)((rand() % 9) + (-4)));

        if (scissors[i].getPosition().x < 0.f)
            scissors[i].setPosition(0.f, scissors[i].getPosition().y); // left collision
        if (scissors[i].getPosition().y < 0.f)
            scissors[i].setPosition(scissors[i].getPosition().x, 0.f); // top collision
        if (scissors[i].getPosition().x + scissors[i].getGlobalBounds().width > this->my_VM.width) // right collision
            scissors[i].setPosition(this->my_VM.width - scissors[i].getGlobalBounds().width, scissors[i].getPosition().y);
        if (scissors[i].getPosition().y + scissors[i].getGlobalBounds().height > this->my_VM.height) // bot collision
            scissors[i].setPosition(scissors[i].getPosition().x, this->my_VM.height - scissors[i].getGlobalBounds().height);
        // TODO:
        //      check here!!!

    }
}

void Game::spawn_scissor()
{
    this->scissor.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->my_window->getSize().x - this->scissor.getRadius())),
        500.0f
    );
    this->scissors.push_back(this->scissor);
}

void Game::paper_vs_rock()
{
    for (int i = 0; i < papers.size(); i++) {
        for (int j = 0; j < rocks.size(); j++) {
            if (papers[i].getGlobalBounds().intersects(rocks[j].getGlobalBounds())) {
                this->paper.setPosition(rocks[j].getPosition());
                rocks.erase(rocks.begin() + j);
                this->papers.push_back(this->paper);
                max_papers++;
                max_rocks--;
            }
        }
    }
}

void Game::rock_vs_scissor()
{
    for (int i = 0; i < rocks.size(); i++) {
        for (int j = 0; j < scissors.size(); j++) {
            if (rocks[i].getGlobalBounds().intersects(scissors[j].getGlobalBounds())) {
                this->rock.setPosition(scissors[j].getPosition());
                this->scissors.erase(scissors.begin() + j);
                this->max_scissors--;
                this->rocks.push_back(this->rock);
                this->max_rocks++;
            }
        }
    }
}

void Game::scissor_vs_paper()
{
    for (int i = 0; i < scissors.size(); i++) {
        for (int j = 0; j < papers.size(); j++) {
            if (scissors[i].getGlobalBounds().intersects(papers[j].getGlobalBounds())) {
                this->scissor.setPosition(papers[j].getPosition());
                this->papers.erase(papers.begin() + j);
                this->max_papers--;
                this->scissors.push_back(this->scissor); 
                this->max_scissors++;
            }
        }
    }
}
