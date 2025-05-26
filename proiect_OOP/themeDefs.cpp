#include "themeDefs.h"
#include<SFML/Graphics.hpp>

void LightTheme::styleButton(sf::RectangleShape& btn) {
        btn.setFillColor      (LightTheme::ButtonFill);
        btn.setOutlineColor   (LightTheme::ButtonOutline);
        btn.setOutlineThickness(2.f);
};

void DarkTheme::styleButton(sf::RectangleShape& btn) {
        btn.setFillColor      (DarkTheme::ButtonFill);
        btn.setOutlineColor   (DarkTheme::ButtonOutline);
        btn.setOutlineThickness(2.f);
};

