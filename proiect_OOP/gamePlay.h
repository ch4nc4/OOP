#pragma once
#include "screen.h"
#include "game.h"
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include <SFML/Graphics/Font.hpp>
#include<filesystem>
#include<functional>
#include<memory>

//aici se joaca de fapt jocul
class GamePlay: public Screen{
    public:
        //constructorul
        GamePlay(sf::RenderWindow& window, 
                AlchemyTable& table,
                std::function<void(std::unique_ptr<Screen>)> changeScreen);
        //clasele virtuale ale lui Screen
        void render() override;
        void update() override;

    private:
        //functia de schimbare a ecranului si alte functii virtuale ale Screen
        void handleEvents() override;
        std::function<void(std::unique_ptr<Screen>)> requestScreenChange;
        void initText(sf::Text &text, const int charSize, const float lineSpacing, const std::uint32_t style, const sf::Color fillColor,
            const sf::Color outlineClr, const float thickness, const float pozx, const float pozy) override;

        //functii pentru event handling
        void onClose(const sf::Event::Closed& ev);
        void onKeyPressed(const sf::Event::KeyPressed& ev);

        //UI elements
        sf::Font font;
        sf::Font glyphFont;

        //va fi afisat cate elemente au fost descoperite in sesiunea curenta
        sf::Text countDiscovered;
        int nrDiscovered = 0;

        //in coltul dreapta sus al ecranului va fi un buton care duce jucatorul inapoi in Main Menu
        sf::Texture alchemyBottle;
        sf::Sprite bottleSprite;
        sf::RectangleShape test;

        //in josul ecranului vor fi 3 butoane: gameInfo, addElem si deleteLastElem
        sf::RectangleShape gameInfo;
        sf::RectangleShape addElem;
        sf::RectangleShape deleteLastElem;
        sf::Text questionMark;
        sf::Text plus;
        sf::Text returnSign;

};