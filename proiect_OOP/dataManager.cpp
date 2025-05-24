#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include <SFML/Graphics/Font.hpp>
#include<memory>
#include<iostream>
#include<functional>
#include<set>
#include<algorithm>
#include "textureManager.h"
#include "displayableElem.h"
#include "alchemyTable.h"
#include "dataManager.h"



DataManager::DataManager(AlchemyTable& table, TextureManager& texture)
: table(table),
 texture(texture),
 rng({std::random_device{}()}),
 tableArea({100, 100}, {600, 400}){}
//  xDist(
//     tableArea.position.x,
//     tableArea.position.x + tableArea.size.x - 75
//   ),
//  yDist(
//     tableArea.position.y,
//     tableArea.position.y + tableArea.size.y - 75
//   )

void DataManager::initBaseElements() {
    static const std::vector<std::string> base = {"Fire","Water","Earth","Air"};
    for (int i = 0; i < base.size(); i++) {
        std::string name = base[i];
        tableMultipliers[name] = 1;          
        discovered.insert(name); 

        int x, y;
        if(name == "Fire"){
            x = 100;
            y = 200;
        }
        else if(name == "Water"){
            x = 200;
            y = 200;
        }
        else if(name == "Earth"){
            x = 400;
            y = 100;
        }
        else if(name == "Air"){
            x = 300;
            y = 250;
        }
   
        std::cout << "generating sprites at pos: "  << x << " " << y << '\n';
        try{
            DisplayableElem newElem(table.getElemByName(name), texture,x,y);
            this->discovered.insert(name);  
            this->updatedElemOnTable[name].emplace_back(newElem);  
        }
        catch(std::exception& e){
            std::cout << "couldn't create displayable" << e.what() << '\n';
        }
        
        tableMultipliers[name] += 1;
            // addDiscovered(name);            
    }
}

void DataManager::addDiscovered(DisplayableElem display) {
    std::string name = display.elem->getName();
   
    try{
        this->discovered.insert(name);  
        this->updatedElemOnTable[name].emplace_back(display);  
    }
    catch(std::exception& e){
        std::cout << "couldn't update element table" << e.what() << '\n';
    }
 
    tableMultipliers[name] += 1;

}

void DataManager::eraseElem(DisplayableElem* del){
    const std::string name = (*(del)).elem->getName();

    auto& inst = this->updatedElemOnTable[name];

    //elimin am orice element care are adresa echivalenta cu cea a lui del
     inst.erase(
      std::remove_if(
        inst.begin(), inst.end(),
        [del](DisplayableElem& e){
            return &e == del;
        }
      ),
      inst.end()
    );
    // int pozx;
    // int pozy;
  
    // auto pos = (*(del)).sprite.getPosition();
    // pozx = pos.x;
    // pozy = pos.y;
    // for(auto it = updatedElemOnTable[name].begin(); it != updatedElemOnTable[name].end(); ++it){
    //     //cautam in aparitiile elementului pe tabla
    //     sf::Vector2f posErase = {static_cast<float>(pozx), static_cast<float>(pozy)};

    //     //cand am gasit elementul "name" la pozitia {pozx, pozy}
    //     if(it->sprite.getPosition() == posErase){
    //         updatedElemOnTable[name].erase(it);
    //         return;
    //     }

    // }   
}

void DataManager::drawAll(sf::RenderWindow& window){
    for (auto it = updatedElemOnTable.begin(); it != updatedElemOnTable.end(); ++it) {
        const std::string& name = it->first;
        auto& elems   = it->second;
        for (size_t i = 0; i < elems.size(); ++i) {
            elems[i].draw(window);
        }
    }

}

// void DataManager::updateElems(){

// }