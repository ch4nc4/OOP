#define SFML_STATIC
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
Game::Game() : window(sf::VideoMode({800,600}), "Alchemy"){
    //primul lucru pe care il facem este sa initializam jocul
    try{
        this->initTable.verifInitGame();
        this->initTable.initGame("elements", "recipes");
    }
    catch(const std::exception& e){
        std::cerr << "Caught exception: " << e.what() << '\n';
    }

    //apoi setam currentScreen
    changeScreen(std::make_unique<MainMenu>(
        [this](std::unique_ptr<Screen> newScreen) { this->changeScreen(std::move(newScreen));}
    ));
};

//functia de rulare a jocului
void Game::run(){
    while(this->window.isOpen()){
        this->currentScreen->handleEvents(this->window);
        this->currentScreen->update();
        this->currentScreen->render(window);
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