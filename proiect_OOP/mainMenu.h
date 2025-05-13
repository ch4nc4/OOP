#pragma once
#include "screen.h"
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include <SFML/Graphics/Font.hpp>
#include<filesystem>
#include<functional>
#include<memory>
#include<random>

namespace fs = std::filesystem;

//clasa de Main Menu        
class MainMenu: public Screen{

    class Bubble{
        sf::CircleShape shape;
        float speed;   // pixels per second
    
        public:
            Bubble(float x, float radius, float speed);

            sf::CircleShape& getShape(){
                return this->shape;
            }

            float getSpeed(){
                return this->speed;
            }
    };
    public:
        MainMenu(sf::RenderWindow& window, std::function<void(std::unique_ptr<Screen>)> changeScreen);
        void render() override;
        void update() override;

    private:
        //membrii privati ce ajuta la propagarea bulelor
        std::vector<Bubble> bubbles;
        sf::Clock bubbleClock; 
        sf::Clock frameClock;  
        std::mt19937 rng{std::random_device{}()};
        std::uniform_real_distribution<float>  xDist{0.f, 800.f};
        std::uniform_real_distribution<float>  radiusDist{5.f, 20.f};
        std::uniform_real_distribution<float>  speedDist{50.f, 150.f};

        //functia de creare a bulelor
        void spawnBubble();

        void handleEvents() override;
        std::function<void(std::unique_ptr<Screen>)> requestScreenChange;
        void initText(sf::Text &text, const int charSize, const float lineSpacing, const std::uint32_t style, const sf::Color fillColor,
            const sf::Color outlineClr, const float thickness, const float pozx, const float pozy) override;

        //functii pentru event handling
        void onClose(const sf::Event::Closed& ev);
        void onKeyPressed(const sf::Event::KeyPressed& ev);
        void onMousePressed(const sf::Event::MouseButtonPressed& ev);

        //UI elements
        sf::Text welcomeMsg;
        sf::Text welcomeMsg2;
        sf::RectangleShape newGameBtn;
        sf::Text newGame;
        sf::RectangleShape setThemeBtn;
        sf::Text gameTheme;
        sf::Font font;
};