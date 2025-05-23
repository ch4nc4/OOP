#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include <SFML/Graphics/Font.hpp>
#include<memory>
#include<iostream>
#include<functional>
#include<set>
#include<stack>
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
        addDiscovered(name);            
    }
}

void DataManager::addDiscovered(const std::string& name) {
    int x = xDist(rng);
    int y = yDist(rng);
   
    std::cout << "generating sprites at pos: "  << x << " " << y << '\n';
    if (this->updatedElemOnTable.find(name) == this->updatedElemOnTable.end()){
        try{
            DisplayableElem newElem(table.getElemByName(name), texture,x,y);
            // this->currentElem[name].emplace(newElem);  
            this->updatedElemOnTable[name].emplace_back(newElem);  
        }
        catch(std::exception& e){
            std::cout << "couldn't create displayable" << e.what() << '\n';
        }
    }
    
    tableMultipliers[name] += 1;

}

void DataManager::eraseElem(const std::string & name, int pozx, int pozy){
    for(auto it = updatedElemOnTable[name].begin(); it != updatedElemOnTable[name].end(); ++it){
        //cautam in aparitiile elementului pe tabla
        sf::Vector2f posErase = {static_cast<float>(pozx), static_cast<float>(pozy)};

        //cand am gasit elementul "name" la pozitia {pozx, pozy}
        if(it->sprite.getPosition() == posErase){
            updatedElemOnTable[name].erase(it);
            return;
        }

    }   
}

void DataManager::drawAll(sf::RenderWindow& window){
    // std::cout << "drawing alchemy elements...\n";
    // for(auto& [name, elemDisplay] : updatedElemOnTable){
    //         std::cout << "!!!";
    //    for(auto& t: elemDisplay){
    //     std::cout << "!!!";
    //     t.draw(window);
    //    }
    // }
    // std::cout << "drawing elems...\n";
    // std::cout << updatedElemOnTable.size() << '\n';
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