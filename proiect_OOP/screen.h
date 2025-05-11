#pragma once
#define SFML_STATIC
#include<SFML/Graphics.hpp>

class Screen{
public:
    virtual ~Screen() = default;
    virtual void handleEvents(sf::RenderWindow& window) = 0;
    virtual void update() = 0;
    virtual void render(sf::RenderWindow &window) = 0;
    virtual void initText(sf::Text &text, const int charSize, const float lineSpacing, const std::uint32_t style, const sf::Color fillColor,
        const sf::Color outlineClr, const float thickness, const float pozx, const float pozy) = 0;
};