#pragma once
#include "alchemyTable.h"
#include "textureManager.h"
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include <SFML/Graphics/Font.hpp>
#include<unordered_map>

class DisplayableElem{
    public:
        //constructor: initializam displayableElem cu elementul de afisat, manager-ul de texturi, pozitia la care sa se afle
        DisplayableElem(AlchemyTable::Element& element,
                        TextureManager& texture,
                        int pozx,
                        int pozy);
        void draw(sf::RenderWindow& window);
    private:
        AlchemyTable::Element& elem;
        std::string iconPath;
        sf::Sprite sprite;
};