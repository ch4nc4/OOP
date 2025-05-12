// #define SFML_STATIC
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include <SFML/Graphics/Font.hpp>
#include<memory>
#include<iostream>
#include<functional>
#include "mainMenu.h"
#include "screen.h"

static sf::Clock frameClock;


//constructor
MainMenu::MainMenu(sf::RenderWindow& window, std::function<void(std::unique_ptr<Screen>)> changeScreen): 
Screen(window, std::move(changeScreen)),
requestScreenChange(std::move(changeScreen)){
    
    std::cout << "!!!";
    if(!font.openFromFile("Type Machine.ttf")){
        throw std::runtime_error("Failed to load font");
    }
    else{
        sf::Font initFont("Type Machine.ttf");
        this->font = initFont;
    }
}

//adaugam elementele vizuale ale MainMenu

void MainMenu::render(){
    //dam clear la window si adaugam background negru
    this->window.clear(sf::Color::Black);

    //desenam bulele
    for (auto& b : bubbles)
        window.draw(b.getShape());

    //adaugam elementele vizuale (UI)
    sf::Text welcomeMsg(this->font, "Welcome alchemist!");
    initText(welcomeMsg, 48, 2, sf::Text::Bold, sf::Color::Green, sf::Color::Black, 0.2, 100, 100);
    this->window.draw(welcomeMsg);

    sf::Text welcomeMsg2(this->font, "let's start the experiments");
    initText(welcomeMsg2, 40, 1, sf::Text::Regular, sf::Color::Green, sf::Color::Black, 0.2, 150, 150);
    this->window.draw(welcomeMsg2);

    sf::Text newGame(this->font, "Start new game");
    initText(newGame, 38, 1, sf::Text::Regular, sf::Color::Green, sf::Color::Black, 0.2, 150, 300);
    this->window.draw(newGame);

    sf::Text gameTheme(this->font, "Set game theme");
    initText(gameTheme, 38, 1, sf::Text::Regular, sf::Color::Green, sf::Color::Black, 0.2, 150, 400);
    this->window.draw(gameTheme);

    this->window.display();
}

// -- functii pentru event handling --

void MainMenu::onClose(const sf::Event::Closed& ev){
    this->window.close();
}

void MainMenu::onKeyPressed(const sf::Event::KeyPressed& ev){
    if(ev.scancode == sf::Keyboard::Scancode::Escape){
        window.close();
    }
}

void MainMenu::handleEvents(){
    this->window.handleEvents(
        [this](const sf::Event::Closed&   ev){ onClose(ev); },
        [this](const sf::Event::KeyPressed& ev){ onKeyPressed(ev); }
    );
}

// -- sfarsitul functiilor pentru event handling


// -- functii pentru crearea si propagarea bulelor --

MainMenu::Bubble::Bubble(float x, float radius, float speed):
shape(radius), speed(speed){
    this->shape.setPosition({x, 600.f + radius*2});   
    this->shape.setFillColor(sf::Color::Black);
    this->shape.setOutlineColor(sf::Color(0,200,0,200));
    this->shape.setOutlineThickness(0.8);
}

void MainMenu::spawnBubble(){
    float x      = xDist(rng);
    float r      = radiusDist(rng);
    float speed  = speedDist(rng);
    Bubble newBubble(x, r, speed);
    this->bubbles.push_back(newBubble);
}

void MainMenu::update(){
    // in primul rand tratam evenimentele
    this->handleEvents();

    //apoi cream bulele
    if (this->bubbleClock.getElapsedTime().asSeconds() > 0.2f) {
        spawnBubble();
        this->bubbleClock.restart();
    }

    float dt = this->frameClock.restart().asSeconds();  
  
    //bulele se propaga in sus si dispar la inceputul ecranului
    for (auto it = bubbles.begin(); it != bubbles.end(); ) {
        it->getShape().move({0.f, -it->getSpeed() * dt});
        if (it->getShape().getPosition().y + it->getShape().getRadius() * 2 < 0.f)
            it = bubbles.erase(it);
        else
            ++it;
    }

}

// -- sfarsit functii pentru crearea si propagarea bulelor --

// personalizarea textului care apare pe screen
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
