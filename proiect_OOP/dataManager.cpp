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
    try{
        DisplayableElem newElem(table.getElemByName(name), texture,x,y);
         currentElem[name].push(newElem);  
        updatedElemOnTable[name].push_back(newElem);  
    }
    catch(std::exception& e){
        std::cout << "couldn't create displayable" << e.what() << '\n';
    }
    
    tableMultipliers[name] += 1;

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