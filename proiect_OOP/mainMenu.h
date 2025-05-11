#pragma once
#define SFML_STATIC
#include "screen.h"
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include <SFML/Graphics/Font.hpp>
#include<filesystem>
#include<memory>

namespace fs = std::filesystem;

//clasa de Main Menu
class MainMenu: public Screen{
public:
    MainMenu(std::function<void(std::unique_ptr<Screen>)> changeScreenFunc);
    void render(sf::RenderWindow &window) override;

private:
    void initText(sf::Text &text, const int charSize, const float lineSpacing, const std::uint32_t style, const sf::Color fillColor,
    const sf::Color outlineClr, const float thickness, const float pozx, const float pozy) override;
    void handleEvents(sf::RenderWindow& window) override;
    std::function<void(std::unique_ptr<Screen>)> requestScreenChange;
    sf::Font font{ fs::path("Type Machine.ttf") };

};