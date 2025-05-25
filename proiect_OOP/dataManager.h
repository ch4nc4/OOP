#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include <SFML/Graphics/Font.hpp>
#include<memory>
#include<iostream>
#include<functional>
#include<set>
#include<random>
#include<stack>
#include "textureManager.h"
#include "displayableElem.h"
#include "alchemyTable.h"


class DataManager{
    public:
    DataManager(AlchemyTable& table, TextureManager& textures);

    //apelat la inceputul jocului pentru a plasa pe tabla cele 4 elemente : fire, water, air, earth
    void initBaseElements();

    //cand se adauga un element
    void addDiscovered(DisplayableElem display);

    //adaugam in window elementele gasite 
    void drawAll(sf::RenderWindow& window);

    // void updateElems();

    //cand stergem un element de pe tabla
    void eraseElem(DisplayableElem* del);

private:
    AlchemyTable& table;            
    TextureManager& texture;
    
public:

    //membrii care ajuta cu pozitionarea random a elementelor pe tabla cand sunt adaugate
    std::mt19937   rng{std::random_device{}()};
    sf::IntRect tableArea;
    std::uniform_real_distribution<float> xDist{100.f, 800.f};
    std::uniform_real_distribution<float> yDist{100.f, 600.f};

    //numele tuturor elementelor gasite
    std::set<std::string> discovered; 
    //cate elemente din fiecare se afla pe tabla       
    std::map<std::string,int> tableMultipliers;  

    //elementele curente de pe tabla
    // std::map<std::string, std::stack<DisplayableElem>> currentElem;
    //tot elementele curente dar mai usor de desenat (nu foloseste stack)
    std::map<std::string, vector<DisplayableElem>> updatedElemOnTable;


};
