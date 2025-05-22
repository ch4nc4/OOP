#include "alchemyTable.h"
#include "textureManager.h"
#include "displayableElem.h"
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include <SFML/Graphics/Font.hpp>
#include<iostream>
#include<unordered_map>

//constructorul
DisplayableElem::DisplayableElem(AlchemyTable::Element& element, TextureManager& texture, int pozx, int pozy):
elem(element),
iconPath("assets\\icons\\" + element.getName() + ".png"),
sprite(texture.load(element.getName(),
        iconPath)){
    std::cout << "Creating displayable: " << this->elem.getName() << '\n';
    std::cout << "Searching for texture in: " << this->iconPath << '\n';

    const sf::Texture& tex = this->sprite.getTexture();

    sprite.setTextureRect(sf::IntRect({0, 0}, sf::Vector2i(tex.getSize())));
    float scaleFactor = 200.f/512.f;
    sprite.setScale({scaleFactor, scaleFactor});
    sprite.setPosition({float(pozx), float(pozy)});

}

void DisplayableElem::draw(sf::RenderWindow& window){
    try{
        window.draw(this->sprite);
    }
    catch(std::exception& e){
        std::cout << "couldn't draw element" << e.what() << '\n';
    }
}