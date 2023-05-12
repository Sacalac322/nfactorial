#include "Game.h"




int main()
{
    cout << "Start of the game!\n";
    Game rps;
    sf::SoundBuffer my_buffer;
    sf::Sound my_sound;
    if (!my_buffer.loadFromFile("music.wav")) 
    {
        cout << "Music error!\n";
    }
    my_sound.setBuffer(my_buffer);
    my_sound.play();


    srand(static_cast<unsigned>(time(NULL)));

    // game loop
    while (rps.window_is_open()) 
    {
        // update
        rps.update();
        // render
        rps.render();
    }


    cout << "The game is successfully finished!\n";
    return 0;
}


