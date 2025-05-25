#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include <SFML/Graphics/Font.hpp>
#include<memory>
#include<iostream>
#include<functional>
#include "gamePlay.h"
#include "screen.h"
#include "game.h"
#include "displayableElem.h"
#include "mainMenu.h"


//constructorul
GamePlay::GamePlay(sf::RenderWindow& window, AlchemyTable& table, TextureManager& texture, DataManager& data): 
Screen(window, table, texture, data),
countDiscovered(font, "Discovered: 0 / 246"),
questionMark(font, "?"),
plus(font, "+"),
returnSign(glyphFont, L"\u21BB"),
bottleSprite(alchemyBottle),
infoTitle(font, "Gameplay info"),
plusBtn(font, "-> Press (+) to add element"),
retBtn(font, "-> Press arrow button to delete last element"),
mainBtn(font, "-> Press alchemy bottle to return to Main Menu"),
mergeElem(font, "***drag elements in order to merge them together***"){
    //setam fonturile
    if(!font.openFromFile("assets/fonts/Type Machine.ttf")){
        throw std::runtime_error("Failed to load font\n");
    }
    else{
        sf::Font initFont("assets/fonts/Type Machine.ttf");
        this->font = initFont;
    }

    if(!glyphFont.openFromFile("assets/fonts/arial unicode ms.otf")){
        throw std::runtime_error("Failed to load font\n");
    }
    else{
        sf::Font initFont("assets/fonts/arial unicode ms.otf");
        this->glyphFont = initFont;
    }

    //setam textura butonului Main Menu 
    if (!this->alchemyBottle.loadFromFile("assets/images/potion.png")) {
        std::cerr << "Failed to load texture.png\n";
    }
    else{
        this->bottleSprite.setTextureRect(sf::IntRect({0, 0}, sf::Vector2i(this->alchemyBottle.getSize())));
    }

    //adaugam primele elemente pe tabla: Fire, Water, Earth, Air
    this->data.initBaseElements();

}

//destructorul

GamePlay::~GamePlay(){
    delete this->dragged;
}

// -- adaugam elementele vizuale ale Game Play --

void GamePlay::render(){
    this->window.clear(sf::Color::Black);

    this->data.drawAll(this->window);

    std::string currentDiscovered = "";
    currentDiscovered = "Discovered: " + std::to_string(this->nrDiscovered);
    currentDiscovered = currentDiscovered +  " / 246";  
    this->countDiscovered.setString(currentDiscovered);
    initText(this->countDiscovered, 28, 2, sf::Text::Regular, sf::Color::Green, sf::Color::Black, 0.2, 325, 50);
    this->window.draw(this->countDiscovered);


    this->alchemyBottle.setSmooth(true);
    float scaleFactor = 85.f/512.f;
    this->bottleSprite.setScale({scaleFactor, scaleFactor});
    // this->bottleSprite.setTexture(this->alchemyBottle);
    this->bottleSprite.setPosition({780.f, 50.f});
    this->window.draw(bottleSprite);

    this->gameInfo.setSize({75.f, 75.f});
    this->gameInfo.setOutlineColor(sf::Color::Green);
    this->gameInfo.setOutlineThickness(0.9);
    this->gameInfo.setFillColor(sf::Color::Black);
    this->gameInfo.setPosition({140.f, 650.f});
    this->window.draw(this->gameInfo);


    initText(this->questionMark, 38, 0, sf::Text::Regular, sf::Color::Green, sf::Color::Green, 0.1, 165, 660);
    this->window.draw(this->questionMark);

    this->addElem.setSize({75.f, 75.f});
    this->addElem.setOutlineColor(sf::Color::Green);
    this->addElem.setOutlineThickness(0.9);
    this->addElem.setFillColor(sf::Color::Black);
    this->addElem.setPosition({460.f, 650.f});
    this->window.draw(this->addElem);

    initText(this->plus, 42, 0, sf::Text::Regular, sf::Color::Green, sf::Color::Green, 0.7, 485, 660);
    this->window.draw(this->plus);

    this->deleteLastElem.setSize({75.f, 75.f});
    this->deleteLastElem.setOutlineColor(sf::Color::Green);
    this->deleteLastElem.setOutlineThickness(0.9);
    this->deleteLastElem.setFillColor(sf::Color::Black);
    this->deleteLastElem.setPosition({780.f, 650.f});
    this->window.draw(this->deleteLastElem);

    initText(this->returnSign, 38, 0, sf::Text::Regular, sf::Color::Green, sf::Color::Green, 0.7, 805, 660);
    this->window.draw(this->returnSign);

    this->infoRect.setSize({650.f, 400.f});
    this->infoRect.setOutlineColor(sf::Color::Green);
    this->infoRect.setOutlineThickness(0.9);
    this->infoRect.setFillColor(sf::Color(0, 255, 0, 180));

    float pozx = this->infoRect.getPosition().x;
    float pozy = this->infoRect.getPosition().y;

    initText(this->infoTitle, 28, 2, sf::Text::Bold, sf::Color::Black, sf::Color::Black, 0.2, pozx + 200, pozy + 25);

    initText(this->plusBtn, 20, 2, sf::Text::Regular, sf::Color::Black, sf::Color::Black, 0.2, pozx + 50, pozy + 75);

    initText(this->retBtn, 20, 2, sf::Text::Regular, sf::Color::Black, sf::Color::Black, 0.2, pozx + 50, pozy + 125);

    initText(this->mainBtn, 20, 2, sf::Text::Regular, sf::Color::Black, sf::Color::Black, 0.2, pozx + 50, pozy + 175);

    initText(this->mergeElem, 20, 2, sf::Text::Regular, sf::Color::Black, sf::Color::Black, 0.2, pozx + 50, pozy + 375);

    if(this->showInfoBox){
        this->window.draw(this->infoRect);
        this->window.draw(this->infoTitle);
        this->window.draw(this->plusBtn);
        this->window.draw(this->retBtn);
        this->window.draw(this->mainBtn);
        this->window.draw(this->mergeElem);
    }

    this->window.display();
}

// -- am adaugat elementele vizuale ale Game Play --


// -- functii pentru event handling -- 

void GamePlay::onClose(const sf::Event::Closed& ev){
    this->window.close();
}

void GamePlay::onKeyPressed(const sf::Event::KeyPressed& ev){
    if(ev.scancode == sf::Keyboard::Scancode::Escape){
        this->window.close();
    }
}

void GamePlay::onMousePressed(const sf::Event::MouseButtonPressed& ev, std::unique_ptr<Screen>& next){
    if(ev.button != sf::Mouse::Button::Left)
        return;
    
    sf::Vector2f worldPos = this->window.mapPixelToCoords(ev.position);

    if(this->showInfoBox)
    {
        if (!this->infoRect.getGlobalBounds().contains(worldPos)) {
            this->showInfoBox = false;
        }
    }

    for(auto& [name, tex] : this->data.updatedElemOnTable){
        for(auto& elem : tex){
            if(elem.sprite.getGlobalBounds().contains(worldPos)){
                this->dragging = true;
                this->dragged = &elem;
                this->dragOffset = worldPos - elem.sprite.getPosition();
                return;
            }
        }
    }

    if(this->gameInfo.getGlobalBounds().contains(worldPos)){
        auto ws = this->window.getSize();
        auto rs = this->infoRect.getSize();
        this->infoRect.setPosition({
             (ws.x - rs.x) / 2.f,
             (ws.y - rs.y) / 2.f
        });

        this->showInfoBox = true;
    }

    if(this->bottleSprite.getGlobalBounds().contains(worldPos)){
         try{
        //     changeScreen(std::make_unique<MainMenu>(
        //         this->window,
        //         this->table,
        //         this->texture,
        //         this->data,
        //         [this](std::unique_ptr<Screen> newScreen) { this->changeScreen(std::move(newScreen));}
        //     ));
            next = std::make_unique<MainMenu>(window, table, texture, data);
            std::cout << "Successfully returned to main menu !!!" << '\n';
            return;
        }
        catch(std::exception& e){
            std::cerr << "[Game] Failed to return to main menu: " << e.what() << "\n";
            std::exit(1);
        }
        return;
    }
    
}

void GamePlay::onMouseMoved(const sf::Event::MouseMoved& ev){
    if(!this->dragging || !this->dragged){
        return;
    }
    sf::Vector2f worldPos = this->window.mapPixelToCoords(ev.position);
    this->dragged->sprite.setPosition(worldPos - this->dragOffset);
}

void GamePlay::onMouseReleased(const sf::Event::MouseButtonReleased& ev){
    if(ev.button == sf::Mouse::Button::Left && this->dragging){
        this->dragging = false;
        dragged = nullptr;
    }
}

std::unique_ptr<Screen> GamePlay::handleEvents(){
    std::unique_ptr<Screen> next = nullptr;

    this->window.handleEvents(
        [this](const sf::Event::Closed& ev){ onClose(ev); },
        [this](const sf::Event::KeyPressed& ev){ onKeyPressed(ev); },
        [this, &next](const sf::Event::MouseButtonPressed& ev){
             onMousePressed(ev, next); },
        [this](const sf::Event::MouseMoved& ev){ onMouseMoved(ev); },
        [this](const sf::Event::MouseButtonReleased& ev){ onMouseReleased(ev); }
    );

    return next;
}

// -- sfarsit functii pentru event handling --

void GamePlay::update(){
    //in update vom detecta constant coliziunile intre elemente
    //pentru fiecare element din tabla verificam coliziuni intre instantele lui
    //si instantele urmatoarelor elemente de pe tabla

    //de fiecare data resetam lista de elemente de combinat
    while(!this->toCombine.empty()){
        this->toCombine.pop();
    }
    int size_t = this->data.updatedElemOnTable.size();
    map<string, vector<DisplayableElem>>::iterator it;
    for(it = this->data.updatedElemOnTable.begin(); it != this->data.updatedElemOnTable.end(); ++it){
         map<string, vector<DisplayableElem>>::iterator it2 = std::next(it);
         auto& firstElemInst = it->second;

         for(; it2 != this->data.updatedElemOnTable.end(); ++it2){
            auto& secElemInst = it2->second;
            checkColisions(firstElemInst, secElemInst, this->toCombine);
         }
    }

    //dupa ce am gasit si retinut posibilele combinari de elemente
    //combinam elementele
    //parcurgem lista de coliziuni
    while(!this->toCombine.empty()){
        DisplayableElem* A = this->toCombine.front().first;
        DisplayableElem* B = this->toCombine.front().second;

        //pentru fiecare coliziune verificam
        //daca in lista de retete combinatia are loc intre primul si al doilea element sau invers
        //in orice caz retinem rezultatul retetei
        std::string recipeRes;
        try{
            recipeRes = this->table.resElem(*((*(A)).elem), *((*(B)).elem)).getName();
        }
        catch(std::exception& e){
            cout << e.what() << '\n';
        }

        cout << (*(A)).elem->getName() << " + " << (*(B)).elem->getName() << " = " << recipeRes << '\n';
        //dupa ce am gasit rezultatul retetei
        //eliminam cele doua elemente combinate de pe tabla
        this->data.eraseElem(A);
        this->data.eraseElem(B);

        //si adaugam noul element la pozitia unde a avut loc coliziunea
        sf::Vector2f pos = ((*(A)).sprite.getPosition() + (*(B)).sprite.getPosition()) / 2.f;
        try{
            DisplayableElem newElem(
                this->table.getElemByName(recipeRes),
                this->texture,
                static_cast<int>(pos.x),
                static_cast<int>(pos.y)
                );
            this->data.addDiscovered(newElem);  
        }
        catch(std::exception& e){
            cerr << "couldn't create displayable" << " " << e.what() << '\n';
        }
        
        this->toCombine.pop();
    }
    
}

void GamePlay::checkColisions(vector<DisplayableElem>& v1,
     vector<DisplayableElem>& v2, queue<pair<DisplayableElem*, 
     DisplayableElem*>>& q){
        for(int i = 0; i < v1.size(); i++){
            auto boundsA = v1[i].sprite.getGlobalBounds();

            for(int j = 0; j < v2.size(); j++){
                auto boundsB = v2[j].sprite.getGlobalBounds();

                if(boundsA.findIntersection(boundsB)){
                    //daca doua elemente e intersecteaza si formeaza o reteta
                    //atunci adaugam perechea in coada de combinari
                    if(this->table.canCombine(*(v1[i].elem), *(v2[j].elem)))
                        q.push({&v1[i], &v2[j]});
                    else if(this->table.canCombine(*(v2[j].elem), *(v1[i].elem)))
                        q.push({&v2[j], &v1[i]});
                }

            }
        }

}


// personalizarea textului care apare pe screen
void GamePlay::initText(sf::Text &text, const int charSize, const float lineSpacing, const std::uint32_t style, const sf::Color fillColor,
    const sf::Color outlineClr, const float thickness, float pozx, float pozy){
    text.setCharacterSize(charSize);
    text.setLineSpacing(lineSpacing);
    text.setStyle(style);
    text.setFillColor(fillColor);
    text.setOutlineColor(outlineClr);
    text.setOutlineThickness(thickness);
    text.setPosition({pozx, pozy});
}


