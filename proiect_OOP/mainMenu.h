#pragma once
#include "screen.h"
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include <SFML/Graphics/Font.hpp>
#include<filesystem>
#include<functional>
#include<memory>

namespace fs = std::filesystem;

//clasa de Main Menu
class MainMenu: public Screen{
public:
    MainMenu(sf::RenderWindow& window, std::function<void(std::unique_ptr<Screen>)> changeScreen);
    void render() override;

private:
    void handleEvents() override;
    // void update() override;
    std::function<void(std::unique_ptr<Screen>)> requestScreenChange;
    void initText(sf::Text &text, const int charSize, const float lineSpacing, const std::uint32_t style, const sf::Color fillColor,
        const sf::Color outlineClr, const float thickness, const float pozx, const float pozy) override;
    void onClose(const sf::Event::Closed& ev);
    void onKeyPressed(const sf::Event::KeyPressed& ev);

    sf::Font font;
};