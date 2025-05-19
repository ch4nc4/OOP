#pragma once
#include<SFML/Graphics.hpp>
#include<functional>
#include "alchemyTable.h"

class Screen{
public:

    Screen(sf::RenderWindow& window, AlchemyTable& table, std::function<void(std::unique_ptr<Screen>)> changeScreen)
    : window(window), table(table), changeScreen(std::move(changeScreen)){};
    virtual ~Screen() = default;
    virtual void handleEvents() = 0;
    virtual void render() = 0;
    virtual void update() = 0;
    virtual void initText(sf::Text &text, const int charSize, const float lineSpacing, const std::uint32_t style, const sf::Color fillColor,
        const sf::Color outlineClr, const float thickness, const float pozx, const float pozy) = 0;

protected:
        sf::RenderWindow& window;
        AlchemyTable &table;
        std::function<void(std::unique_ptr<Screen>)> changeScreen;
};