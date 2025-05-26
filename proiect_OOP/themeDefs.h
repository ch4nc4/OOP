#pragma once
#include<SFML/Graphics.hpp>
#include "themeBase.h"

class LightTheme : public ThemeBase{
    public:
        inline static constexpr sf::Color Background     {0, 255, 0, 255};
        inline static constexpr sf::Color ButtonFill     {0, 255, 0, 255};
        inline static constexpr sf::Color ButtonOutline  {0, 0, 0, 255};
        inline static constexpr sf::Color Text           {0, 0, 0, 255};
        inline static constexpr sf::Color TextOutline    {0, 0, 0, 255};

        static void styleButton(sf::RectangleShape& btn);
};

class DarkTheme : public ThemeBase{
    public:
        inline static constexpr sf::Color Background     {0, 0, 0, 255};
        inline static constexpr sf::Color ButtonFill     {0, 0, 0, 255};
        inline static constexpr sf::Color ButtonOutline  {0, 255, 0, 255};
        inline static constexpr sf::Color Text           {0, 255, 0, 255};
        inline static constexpr sf::Color TextOutline    {0, 0, 0, 255};


        static void styleButton(sf::RectangleShape& btn);
};

template<typename TTheme>
void styleAllButtons(std::vector<sf::RectangleShape*>& buttons) {
    for (auto* btn : buttons) {
        TTheme::styleButton(*btn);
    }
}



