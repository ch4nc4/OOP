// #define SFML_STATIC
#include "screen.h"
#include "alchemyTable.h"
#include "game.h"
#include "mainMenu.h"
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<memory>
#include<exception>
#include<iostream>

// --- public functions of Game class ---

//Constructor
Game::Game() : window(sf::VideoMode({1000,800}), "Alchemy"), initTable(AlchemyTable::getInstance()), 
textureMng(TextureManager::getInstance()),
data(initTable, textureMng){
    //primul lucru pe care il facem este sa initializam jocul
    cout << "entered game constructor successfully" << '\n';
    try{
        this->initTable.verifInitGame();
        this->initTable.initGame("assets/elements.txt", "assets/recipes.txt");
    }
    catch(const std::exception& e){
        std::cerr << "Caught exception: " << e.what() << '\n';
    }
    cout << "game initiated correctly" << '\n';

    //apoi initializam soundtrack-ul jocului
    if(!this->gameSoundtrack.openFromFile("assets/Alchemy_soundtrack.wav")){
         throw std::runtime_error("Couldn't load game soundtrack");
    }
    else{
       std::cout << "Soundtrack successfully loaded" << '\n';
    }

    //si pornim rularea soundtrack-ului
    this->gameSoundtrack.setVolume(30.f);
    this->gameSoundtrack.setLooping(true);
    this->gameSoundtrack.play();

    //apoi setam currentScreen
    try{
        changeScreen(std::make_unique<MainMenu>(
            this->window,
            this->initTable,
            this->textureMng,
            this->data,
            [this](std::unique_ptr<Screen> newScreen) { this->changeScreen(std::move(newScreen));}
        ));
    }
    catch(std::exception& e){
        std::cerr << "[Game] Failed to create MainMenu: " << e.what() << "\n";
        std::exit(1);
    }

};

//functia de rulare a jocului
void Game::run(){
    while(this->window.isOpen()){
        if (!this->currentScreen) {
            std::cerr << "Error: currentScreen is nullptr!\n";
            break;
        }
        this->currentScreen->handleEvents();
        this->currentScreen->update();
        this->currentScreen->render();
    }
}

//functia care verifica daca jocul ruleaza
/*const bool Game::running()const{
    return this->window.isOpen();
}*/

//functia care face switch intre windows
void Game::changeScreen(std::unique_ptr<Screen> newScreen){
    currentScreen = std::move(newScreen);
}