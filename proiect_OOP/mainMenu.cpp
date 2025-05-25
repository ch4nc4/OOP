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
#include "gamePlay.h"

static sf::Clock frameClock;


//constructor
MainMenu::MainMenu(sf::RenderWindow& window, AlchemyTable& table, TextureManager& textureMng, DataManager& data): 
Screen(window, table, textureMng, data),
welcomeMsg(font, "Welcome Alchemist!"),
welcomeMsg2(font, "let's start the experiments"),
newGame(font, "New game"),
gameTheme(font, "Set game theme"),
darkTheme(font, "Dark"),
lightTheme(font, "Light"){
    
    // std::cout << "!!!";
    if(!font.openFromFile("assets/fonts/Type Machine.ttf")){
        throw std::runtime_error("Failed to load font");
    }
    else{
        sf::Font initFont("assets/fonts/Type Machine.ttf");
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
    // sf::Text welcomeMsg(this->font, "Welcome alchemist!");
    initText(this->welcomeMsg, 48, 2, sf::Text::Bold, sf::Color::Green, sf::Color::Black, 0.2, 100, 100);
    this->window.draw(this->welcomeMsg);

    // sf::Text welcomeMsg2(this->font, "let's start the experiments");
    initText(this->welcomeMsg2, 40, 1, sf::Text::Regular, sf::Color::Green, sf::Color::Black, 0.2, 150, 150);
    this->window.draw(this->welcomeMsg2);

    // sf::RectangleShape newGameBtn({400.f, 100.f});
    this->newGameBtn.setSize({400.f, 100.f});
    this->newGameBtn.setOutlineColor(sf::Color::Green);
    this->newGameBtn.setOutlineThickness(0.8);
    this->newGameBtn.setFillColor(sf::Color::Black);
    this->newGameBtn.setPosition({125.f, 275.f});
    this->window.draw(this->newGameBtn);
   

    // sf::Text newGame(this->font, "Start new game");
    initText(this->newGame, 38, 1, sf::Text::Regular, sf::Color::Green, sf::Color::Black, 0.2, 150, 300);
    this->window.draw(this->newGame);

    // sf::RectangleShape setThemeBtn({400.f, 100.f});
    this->setThemeBtn.setSize({400.f, 100.f});
    this->setThemeBtn.setOutlineColor(sf::Color::Green);
    this->setThemeBtn.setOutlineThickness(0.8);
    this->setThemeBtn.setFillColor(sf::Color::Black);
    this->setThemeBtn.setPosition({125.f, 425.f});
    this->window.draw(this->setThemeBtn);

    // sf::Text gameTheme(this->font, "Set game theme");
    initText(this->gameTheme, 38, 1, sf::Text::Regular, sf::Color::Green, sf::Color::Black, 0.2, 150, 450);
    this->window.draw(this->gameTheme);

    if(this->buttonClicked){
        // la apasarea butonului "Set game theme" jucatorului ii sunt oferite variantele cromatice
        this->setDarkTheme.setSize({150.f, 80.f});
        this->setDarkTheme.setOutlineColor(sf::Color::Green);
        this->setDarkTheme.setOutlineThickness(0.8);
        this->setDarkTheme.setFillColor(sf::Color::Green);
        this->setDarkTheme.setPosition({80.f, 600.f});
        this->window.draw(this->setDarkTheme);

        initText(this->darkTheme, 28, 1, sf::Text::Italic, sf::Color::Black, sf::Color::Black, 0.1, 105, 625);
        this->window.draw(darkTheme);

        this->setLightTheme.setSize({150.f, 80.f});
        this->setLightTheme.setOutlineColor(sf::Color::Green);
        this->setLightTheme.setOutlineThickness(0.8);
        this->setLightTheme.setFillColor(sf::Color::Black);
        this->setLightTheme.setPosition({455.f, 600.f});
        this->window.draw(this->setLightTheme);

        initText(this->lightTheme, 28, 1, sf::Text::Italic, sf::Color::Green, sf::Color::Black, 0.1, 480, 625);
        this->window.draw(lightTheme);

    }

    this->window.display();
}

// -- am adaugat elementele vizuale ale Main Menu --

// -- functii pentru event handling --

void MainMenu::onClose(const sf::Event::Closed& ev){
    this->window.close();
}

void MainMenu::onKeyPressed(const sf::Event::KeyPressed& ev){
    if(ev.scancode == sf::Keyboard::Scancode::Escape){
        this->window.close();
    }
}

void MainMenu::onMousePressed(const sf::Event::MouseButtonPressed& ev,
      std::unique_ptr<Screen>& next,
      const sf::RectangleShape& shape1,
       const sf::RectangleShape& shape2){
    // raportam pozitia click-ului la intregul screen al desktopului
     sf::Vector2f worldPos = window.mapPixelToCoords(ev.position);

     // luam intervalul in care se afla punctele incluse in dreptunghi
     sf::FloatRect gameBtnBounds = shape1.getGlobalBounds();

     // verificam daca click-ul a avut loc in acel interval
     if(gameBtnBounds.contains(worldPos)){
        std::cout << "Loading new game..." << '\n';
        // daca am apasat pe "Start new game" atunci incepe un nou joc si trecem pe Game window
        try{
            // this->changeScreen(std::make_unique<GamePlay>(
            //     this->window,
            //     this->table,
            //     this->texture,
            //     this->data,
            //     [this](std::unique_ptr<Screen> newScreen) { this->changeScreen(std::move(newScreen));}
            // ));
            next = std::make_unique<GamePlay>(window, table, texture, data);
            std::cout << "Game window successfully created !!!" << '\n';
            return;
        }
        catch(std::exception& e){
            std::cerr << "[Game] Failed to create Game window: " << e.what() << "\n";
            std::exit(1);
        }
        
     }

     // analog pentru butonul de setare a temei jocului
     sf::FloatRect themeBtnBounds = shape2.getGlobalBounds();

     if(themeBtnBounds.contains(worldPos)){
        std::cout << "Loading game customization window..." << '\n';
        //daca am apasat pe "Set game theme" atunci apar doua butoane cu care putem seta cromatica jocului
        this->buttonClicked = true;
     }

}

std::unique_ptr<Screen> MainMenu::handleEvents(){
    //aici pastram urmatorul screen cerut de evenimente
    std::unique_ptr<Screen> next = nullptr;

    this->window.handleEvents(
        [this](const sf::Event::Closed& ev){ onClose(ev); },
        [this](const sf::Event::KeyPressed& ev){ onKeyPressed(ev); },
        [this, &next](const sf::Event::MouseButtonPressed& ev){
             onMousePressed(ev, next, this->newGameBtn, this->setThemeBtn); }
    );
    return next;
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
