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
        //destructor: dezalocam memoria alocata pointerului element
        // ~DisplayableElem();
        void draw(sf::RenderWindow& window);
        AlchemyTable::Element* elem;
    private:
        std::string iconPath;
    public:
        sf::Sprite sprite;
        
};