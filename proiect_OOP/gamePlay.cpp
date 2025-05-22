#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include <SFML/Graphics/Font.hpp>
#include<memory>
#include<iostream>
#include<functional>
#include "gamePlay.h"
#include "screen.h"
#include "game.h"
#include "displayableElem.h"


//constructorul
GamePlay::GamePlay(sf::RenderWindow& window, AlchemyTable& table, TextureManager& texture, DataManager& data, std::function<void(std::unique_ptr<Screen>)> changeScreen): 
Screen(window, table, texture, data, std::move(changeScreen)),
requestScreenChange(std::move(changeScreen)),
countDiscovered(font, "Discovered: 0 / 246"),
questionMark(font, "?"),
plus(font, "+"),
returnSign(glyphFont, L"\u21BB"),
bottleSprite(alchemyBottle){
    //setam fonturile
    if(!font.openFromFile("assets/fonts/Type Machine.ttf")){
        throw std::runtime_error("Failed to load font\n");
    }
    else{
        sf::Font initFont("assets/fonts/Type Machine.ttf");
        this->font = initFont;
    }

    if(!glyphFont.openFromFile("assets/fonts/arial unicode ms.otf")){
        throw std::runtime_error("Failed to load font\n");
    }
    else{
        sf::Font initFont("assets/fonts/arial unicode ms.otf");
        this->glyphFont = initFont;
    }

    //setam textura butonului Main Menu 
    if (!this->alchemyBottle.loadFromFile("assets/images/potion.png")) {
        std::cerr << "Failed to load texture.png\n";
    }
    else{
        this->bottleSprite.setTextureRect(sf::IntRect({0, 0}, sf::Vector2i(this->alchemyBottle.getSize())));
    }

    //adaugam primele elemente pe tabla: Fire, Water, Earth, Air
    this->data.initBaseElements();

}

// -- adaugam elementele vizuale ale Game Play --

void GamePlay::render(){
    this->window.clear(sf::Color::Black);

    this->data.drawAll(this->window);

    std::string currentDiscovered = "";
    currentDiscovered = "Discovered: " + std::to_string(this->nrDiscovered);
    currentDiscovered = currentDiscovered +  " / 246";  
    this->countDiscovered.setString(currentDiscovered);
    initText(this->countDiscovered, 28, 2, sf::Text::Regular, sf::Color::Green, sf::Color::Black, 0.2, 325, 50);
    this->window.draw(this->countDiscovered);


    this->alchemyBottle.setSmooth(true);
    float scaleFactor = 85.f/512.f;
    this->bottleSprite.setScale({scaleFactor, scaleFactor});
    // this->bottleSprite.setTexture(this->alchemyBottle);
    this->bottleSprite.setPosition({780.f, 50.f});
    this->window.draw(bottleSprite);

    this->gameInfo.setSize({75.f, 75.f});
    this->gameInfo.setOutlineColor(sf::Color::Green);
    this->gameInfo.setOutlineThickness(0.9);
    this->gameInfo.setFillColor(sf::Color::Black);
    this->gameInfo.setPosition({140.f, 650.f});
    this->window.draw(this->gameInfo);

    initText(this->questionMark, 38, 0, sf::Text::Regular, sf::Color::Green, sf::Color::Green, 0.1, 165, 660);
    this->window.draw(this->questionMark);

    this->addElem.setSize({75.f, 75.f});
    this->addElem.setOutlineColor(sf::Color::Green);
    this->addElem.setOutlineThickness(0.9);
    this->addElem.setFillColor(sf::Color::Black);
    this->addElem.setPosition({460.f, 650.f});
    this->window.draw(this->addElem);

    initText(this->plus, 42, 0, sf::Text::Regular, sf::Color::Green, sf::Color::Green, 0.7, 485, 660);
    this->window.draw(this->plus);

    this->deleteLastElem.setSize({75.f, 75.f});
    this->deleteLastElem.setOutlineColor(sf::Color::Green);
    this->deleteLastElem.setOutlineThickness(0.9);
    this->deleteLastElem.setFillColor(sf::Color::Black);
    this->deleteLastElem.setPosition({780.f, 650.f});
    this->window.draw(this->deleteLastElem);

    initText(this->returnSign, 38, 0, sf::Text::Regular, sf::Color::Green, sf::Color::Green, 0.7, 805, 660);
    this->window.draw(this->returnSign);

    this->window.display();
}

// -- am adaugat elementele vizuale ale Game Play --


// -- functii pentru event handling -- 

void GamePlay::onClose(const sf::Event::Closed& ev){
    this->window.close();
}

void GamePlay::onKeyPressed(const sf::Event::KeyPressed& ev){
    if(ev.scancode == sf::Keyboard::Scancode::Escape){
        this->window.close();
    }
}

void GamePlay::handleEvents(){
    this->window.handleEvents(
        [this](const sf::Event::Closed& ev){ onClose(ev); },
        [this](const sf::Event::KeyPressed& ev){ onKeyPressed(ev); }
    );
}


// personalizarea textului care apare pe screen
void GamePlay::initText(sf::Text &text, const int charSize, const float lineSpacing, const std::uint32_t style, const sf::Color fillColor,
    const sf::Color outlineClr, const float thickness, float pozx, float pozy){
    text.setCharacterSize(charSize);
    text.setLineSpacing(lineSpacing);
    text.setStyle(style);
    text.setFillColor(fillColor);
    text.setOutlineColor(outlineClr);
    text.setOutlineThickness(thickness);
    text.setPosition({pozx, pozy});
}

void GamePlay::update(){
    
}
