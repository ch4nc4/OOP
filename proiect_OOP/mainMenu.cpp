#define SFML_STATIC
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include <SFML/Graphics/Font.hpp>
#include<memory>
#include<iostream>
#include "mainMenu.h"
#include "screen.h"


//constructor
MainMenu::MainMenu(std::function<void(std::unique_ptr<Screen>)> changeScreenFunc): requestScreenChange(std::move(changeScreenFunc)){
    this->font = font;
}

//adaugam elementele vizuale ale MainMenu

void MainMenu::render(sf::RenderWindow &window){
    //dam clear la window si adaugam background negru
    window.clear(sf::Color::Black);

    //adaugam elementele vizuale (UI)
    sf::Text welcomeMsg(this->font, "Welcome alchemist!");
    initText(welcomeMsg, 48, 2, std::uint32_t("Bold"), sf::Color::Green, sf::Color::Black, 0.2, 100, 100);
    window.draw(welcomeMsg);

    sf::Text welcomeMsg2(this->font, "let's start the experiments");
    initText(welcomeMsg2, 40, 1, std::uint32_t("Regular"), sf::Color::Green, sf::Color::Black, 0.2, 120, 120);
    window.draw(welcomeMsg2);

    sf::Text newGame(this->font, "Start new game");
    initText(newGame, 38, 1, std::uint32_t("Regular"), sf::Color::Green, sf::Color::Black, 0.2, 120, 160);
    window.draw(newGame);

    sf::Text gameTheme(this->font, "Set game theme");
    initText(gameTheme, 38, 1, std::uint32_t("Regular"), sf::Color::Green, sf::Color::Black, 0.2, 120, 180);
    window.draw(gameTheme);

    window.display();
}

//customize the UI text
void MainMenu::initText(sf::Text &text, const int charSize, const float lineSpacing, const std::uint32_t style, const sf::Color fillColor,
    const sf::Color outlineClr, const float thickness, float pozx, float pozy){
    text.setCharacterSize(charSize);
    text.setLineSpacing(lineSpacing);
    text.setStyle(style);
    text.setFillColor(fillColor);
    text.setOutlineColor(outlineClr);
    text.setOutlineThickness(thickness);
    text.setPosition({pozx, pozy});
}
