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
#include<queue>

//aici se joaca de fapt jocul
class GamePlay: public Screen{
    public:
        //constructorul
        GamePlay(sf::RenderWindow& window, 
                AlchemyTable& table,
                TextureManager& texture,
                DataManager& data);
        ~GamePlay() override;
        //clasele virtuale ale lui Screen
        void render() override;
        void update() override;

    private:
        //functia de schimbare a ecranului si alte functii virtuale ale Screen
        std::unique_ptr<Screen> handleEvents() override;
        void initText(sf::Text &text, const int charSize, const float lineSpacing, const std::uint32_t style, const sf::Color fillColor,
            const sf::Color outlineClr, const float thickness, const float pozx, const float pozy) override;

        //functii pentru event handling
        void onClose(const sf::Event::Closed& ev);
        void onKeyPressed(const sf::Event::KeyPressed& ev);
        void onMousePressed(const sf::Event::MouseButtonPressed& ev, std::unique_ptr<Screen>& next);
        void onMouseMoved(const sf::Event::MouseMoved& ev);
        void onMouseReleased(const sf::Event::MouseButtonReleased& ev);


        //functie pentru gasirea coliziunilor intre elemente
        void checkColisions(vector<DisplayableElem>& v1, 
            vector<DisplayableElem>& v2,
             queue<pair<DisplayableElem*, DisplayableElem*>>& q);

        // membrii care ajuta la element dragging
        bool dragging = false;
        DisplayableElem* dragged = nullptr;
        sf::Vector2f dragOffset;

        //membrii care ajuta la combinarea elementelor
        //pe masura ce gasim posibile combinatii intre elemente le retinem
        //trebuie sa retinem pointeri catre displayable pentru ca vom vrea sa eliminam aceste elemente
        //si ele putand fi mutate => nu le putem stii pozitia exacta niciodata
        queue<pair<DisplayableElem*, DisplayableElem*>> toCombine;

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

        //variabila care retine daca am apasat butonul '?'
        bool showInfoBox = false;

        //pop-up generat de apasarea butonului '?'
        sf::RectangleShape infoRect;
        sf::Text infoTitle;
        sf::Text plusBtn;
        sf::Text retBtn;
        sf::Text mainBtn;
        sf::Text mergeElem;

};