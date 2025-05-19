#pragma once

// #define SFML_STATIC
#include "alchemyTable.h"
#include "screen.h"
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>
#include<memory>
#include<functional>

class Game{
public:
    Game();
    void run();
    void changeScreen(std::unique_ptr<Screen> newScreen);
    // const bool running()const;

private:
    sf::RenderWindow window;
    std::unique_ptr<Screen> currentScreen;
    sf::Music gameSoundtrack;

protected:
     AlchemyTable& initTable;
};