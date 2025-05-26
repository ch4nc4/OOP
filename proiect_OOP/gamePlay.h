#pragma once
#include "screen.h"
#include "game.h"
#include "themeBase.h"
#include "themeDefs.h"
#include "gamePlay.h"
#include "displayableElem.h"
#include "mainMenu.h"
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include <SFML/Graphics/Font.hpp>
#include<filesystem>
#include<functional>
#include<memory>
#include<queue>
#include<concepts>

//aici se joaca de fapt jocul
template<typename TTheme>
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

        //variabila care retine ca am apasat '+'
        bool showAddBox = false;

        //pop-up generat de apasarea butonului '+'
        sf::RectangleShape addRect;
        sf::Text addTitle;
        int popupCols = 5;
        float cellSize = 100.f;
        float cellPadding = 50.f;

        //buton de intoarcere la gamePlay
        sf::RectangleShape btn;
        sf::Text arrow;

        //variabila care retine ca am apasat arrow
        bool deleteElem = false;   
        
        std::vector<sf::RectangleShape*> allBtns = {
            &gameInfo,
            &addElem,
            &deleteLastElem
        }; 
};




//constructorul
template<typename TTheme>
GamePlay<TTheme>::GamePlay(sf::RenderWindow& window, AlchemyTable& table, TextureManager& texture, DataManager& data): 
Screen(window, table, texture, data),
countDiscovered(font, "Discovered: 0 / 250"),
questionMark(font, "?"),
plus(font, "+"),
returnSign(glyphFont, L"\u21BB"),
bottleSprite(alchemyBottle),
infoTitle(font, "Gameplay info"),
plusBtn(font, "-> Press (+) to add element"),
retBtn(font, "-> Press arrow button to delete last element"),
mainBtn(font, "-> Press alchemy bottle to return to Main Menu"),
mergeElem(font, "***drag elements in order to merge them together***"),
addTitle(font, "Add new element"),
arrow(glyphFont, L"\u21BB"){
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
    if constexpr (std::is_same_v<TTheme, LightTheme>){
        if (!this->alchemyBottle.loadFromFile("assets/images/potion_light.png")) {
            std::cerr << "Failed to load texture.png\n";
        }
        else{
            this->bottleSprite.setTextureRect(sf::IntRect({0, 0}, sf::Vector2i(this->alchemyBottle.getSize())));
        }
    }
    else if constexpr (std::is_same_v<TTheme, DarkTheme>){
        if (!this->alchemyBottle.loadFromFile("assets/images/potion.png")) {
            std::cerr << "Failed to load texture.png\n";
        }
        else{
            this->bottleSprite.setTextureRect(sf::IntRect({0, 0}, sf::Vector2i(this->alchemyBottle.getSize())));
        }
    }

    //adaugam primele elemente pe tabla: Fire, Water, Earth, Air
    if(this->data.clickedNewGame)
        this->data.initBaseElements();

}

//destructorul
template<typename TTheme>
GamePlay<TTheme>::~GamePlay(){
    delete this->dragged;
}

// -- adaugam elementele vizuale ale Game Play --
template<typename TTheme>
void GamePlay<TTheme>::render(){
    this->window.clear(TTheme::Background);

    this->data.drawAll(this->window);
    styleAllButtons<TTheme>(this->allBtns);

    std::string currentDiscovered = "";
    currentDiscovered = "Discovered: " + std::to_string(this->data.discovered.size());
    currentDiscovered = currentDiscovered +  " / 250";  
    this->countDiscovered.setString(currentDiscovered);
    initText(this->countDiscovered, 28, 2, sf::Text::Regular, TTheme::Text, sf::Color::Black, 0.2, 325, 50);
    this->window.draw(this->countDiscovered);


    this->alchemyBottle.setSmooth(true);
    float scaleFactor = 85.f/512.f;
    this->bottleSprite.setScale({scaleFactor, scaleFactor});
    this->bottleSprite.setPosition({780.f, 50.f});
    this->window.draw(bottleSprite);

    this->gameInfo.setSize({75.f, 75.f});
    this->gameInfo.setPosition({140.f, 650.f});
    this->window.draw(this->gameInfo);


    initText(this->questionMark, 38, 0, sf::Text::Regular, TTheme::Text, TTheme::TextOutline, 0.1, 165, 660);
    this->window.draw(this->questionMark);

    this->addElem.setSize({75.f, 75.f});
    this->addElem.setPosition({460.f, 650.f});
    this->window.draw(this->addElem);

    initText(this->plus, 42, 0, sf::Text::Regular, TTheme::Text, TTheme::TextOutline, 0.7, 485, 660);
    this->window.draw(this->plus);

    this->deleteLastElem.setSize({75.f, 75.f});
    this->deleteLastElem.setPosition({780.f, 650.f});
    this->window.draw(this->deleteLastElem);

    initText(this->returnSign, 38, 0, sf::Text::Regular, TTheme::Text, TTheme::TextOutline, 0.7, 805, 660);
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

    initText(this->mergeElem, 20, 2, sf::Text::Regular, sf::Color::Black, sf::Color::Black, 0.2, pozx + 50, pozy + 250);

    if(this->showInfoBox){
        this->window.draw(this->infoRect);
        this->window.draw(this->infoTitle);
        this->window.draw(this->plusBtn);
        this->window.draw(this->retBtn);
        this->window.draw(this->mainBtn);
        this->window.draw(this->mergeElem);
    }

    this->addRect.setOutlineColor(sf::Color::Black);
    this->addRect.setOutlineThickness(0.9);
    this->addRect.setFillColor(sf::Color(0, 255, 0, 180));

    initText(this->addTitle, 38, 2, sf::Text::Italic, sf::Color::Black, sf::Color::Black, 0.2, 300, 50);

    if(this->showAddBox){
        //desenam elementele ecranului Add Elements
        this->window.draw(this->addRect);
        this->window.draw(this->addTitle);

        //copiem discovered elems intr-un vector pentru a itera prin ele
        std::vector<std::string> elems(
            this->data.discovered.begin(),
            this->data.discovered.end());

        //apoi pentru fiecare element de afisat ii calculam linia si coloana pe ecran
        for(int i = 0; i < elems.size(); i++){
            int row = i / this->popupCols;
            int col = i % this->popupCols;

            float startX =  (window.getSize().x 
                             - popupCols * cellSize 
                             - (popupCols-1)*cellPadding) * 0.5f;
            float startY =  (window.getSize().y * 0.2f);

            sf::Vector2f cellPos = {
                startX + col*(cellSize+cellPadding),
                startY + row*(cellSize+cellPadding)
            };

            sf::RectangleShape box({cellSize, cellSize});
            box.setPosition(cellPos);
            box.setFillColor(sf::Color(0, 0, 0, 180));
            box.setOutlineColor(sf::Color::Black);
            box.setOutlineThickness(2.f);
            this->window.draw(box);

            const sf::Texture& tex = texture.load(elems[i], "assets/icons/" + elems[i] + ".png");
            sf::Sprite icon(tex);

            float iconMaxW = cellSize * 0.6f;
            float iconMaxH = cellSize * 0.6f;
            auto ts = tex.getSize();
            float scale = std::min(iconMaxW/ts.x, iconMaxH/ts.y);
            icon.setScale({scale, scale});

            auto iconBounds = icon.getGlobalBounds();
            icon.setPosition({
                cellPos.x + (cellSize - iconBounds.size.x) * 0.5f,
                cellPos.y 
            });

            this->window.draw(icon);

            sf::Text label(font, elems[i]);
            int posLabelx = icon.getPosition().x - 5;
            int posLabely = icon.getPosition().y + cellSize / 2 + 13;
            this->initText(label, 14, 2, sf::Text::Regular, sf::Color::Green, sf::Color::Black, 0.2, posLabelx, posLabely);

            this->window.draw(label);
        }

        this->btn.setSize({75.f, 75.f});
        this->btn.setOutlineColor(sf::Color::Black);
        this->btn.setOutlineThickness(2);
        this->btn.setFillColor(sf::Color(0, 0, 0, 180));
        this->btn.setPosition({50.f, 40.f});
        this->window.draw(this->btn);

        initText(this->arrow, 38, 0, sf::Text::Regular, sf::Color::Green, sf::Color::Black, 1, 75, 50);
        this->window.draw(this->arrow);

    }

    this->window.display();
}

// -- am adaugat elementele vizuale ale Game Play --


// -- functii pentru event handling -- 
template<typename TTheme>
void GamePlay<TTheme>::onClose(const sf::Event::Closed& ev){
    this->window.close();
}

template<typename TTheme>
void GamePlay<TTheme>::onKeyPressed(const sf::Event::KeyPressed& ev){
    if(ev.scancode == sf::Keyboard::Scancode::Escape){
        this->window.close();
    }
}

template<typename TTheme>
void GamePlay<TTheme>::onMousePressed(const sf::Event::MouseButtonPressed& ev, std::unique_ptr<Screen>& next){
    if(ev.button != sf::Mouse::Button::Left)
        return;
    
    sf::Vector2f worldPos = this->window.mapPixelToCoords(ev.position);

    if(this->showInfoBox){
        if (!this->infoRect.getGlobalBounds().contains(worldPos)) {
            this->showInfoBox = false;
        }
    }

    if(this->showAddBox){
        if(this->arrow.getGlobalBounds().contains(worldPos)){
            this->showAddBox = false;
        }

        std::vector<std::string> elems(
            this->data.discovered.begin(),
            this->data.discovered.end());

        for(int i = 0; i < elems.size(); i++){
            int r = i / this->popupCols;
            int c = i % this->popupCols;

            float stX =  (window.getSize().x 
                             - popupCols * cellSize 
                             - (popupCols-1)*cellPadding) * 0.5f;
            float stY =  (window.getSize().y * 0.2f);

            sf::Vector2f cellPos = {
                stX + c*(cellSize + cellPadding),
                stY + r*(cellSize + cellPadding)
            };

            sf::FloatRect cellRect(cellPos, {cellSize,cellSize});

            if(cellRect.contains(worldPos)){
                std::string name = elems[i];
                int  x = this->data.xDist(this->data.rng);
                int  y = this->data.yDist(this->data.rng);

                DisplayableElem added(this->table.getElemByName(elems[i]),
                                     this->texture,
                                    x,y);
                this->data.addDiscovered(added);
            }
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

    auto ws = this->window.getSize();
    if(this->gameInfo.getGlobalBounds().contains(worldPos)){
        auto rs = this->infoRect.getSize();
        this->infoRect.setPosition({
             (ws.x - rs.x) / 2.f,
             (ws.y - rs.y) / 2.f
        });

        this->showInfoBox = true;
    }

    if(this->addElem.getGlobalBounds().contains(worldPos)){
        this->addRect.setSize(sf::Vector2f(this->window.getSize()));
        this->showAddBox = true;
    }

    if(this->bottleSprite.getGlobalBounds().contains(worldPos)){
         try{
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

template<typename TTheme>
void GamePlay<TTheme>::onMouseMoved(const sf::Event::MouseMoved& ev){
    if(!this->dragging || !this->dragged){
        return;
    }
    sf::Vector2f worldPos = this->window.mapPixelToCoords(ev.position);
    this->dragged->sprite.setPosition(worldPos - this->dragOffset);
}

template<typename TTheme>
void GamePlay<TTheme>::onMouseReleased(const sf::Event::MouseButtonReleased& ev){
    if(ev.button == sf::Mouse::Button::Left && this->dragging){
        this->dragging = false;
        dragged = nullptr;
    }
}

template<typename TTheme>
std::unique_ptr<Screen> GamePlay<TTheme>::handleEvents(){
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

template<typename TTheme>
void GamePlay<TTheme>::update(){
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
            recipeRes = (*((*(A)).elem) + *((*(B)).elem)).getName(); //folosim operatorul + pe elemente
            std::cout << recipeRes << '\n';
            // recipeRes = this->table.resElem(*((*(A)).elem), *((*(B)).elem)).getName();
        }
        catch(std::exception& e){
            cout << e.what() << '\n';
        }

        //dupa ce am gasit rezultatul retetei
        //eliminam cele doua elemente combinate de pe tabla
        //si adaugam noul element la pozitia unde a avut loc coliziunea
        sf::Vector2f pos = ((*(A)).sprite.getPosition() + (*(B)).sprite.getPosition()) / 2.f;

        this->data.eraseElem(A);
        this->data.eraseElem(B);
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

template<typename TTheme>
void GamePlay<TTheme>::checkColisions(vector<DisplayableElem>& v1,
     vector<DisplayableElem>& v2, queue<pair<DisplayableElem*, 
     DisplayableElem*>>& q){

        for(int i = 0; i < v1.size(); i++){
            auto boundsA = v1[i].sprite.getGlobalBounds();

            for(int j = 0; j < v2.size(); j++){
                auto boundsB = v2[j].sprite.getGlobalBounds();

                if(boundsA.findIntersection(boundsB)){

                    //daca doua elemente e intersecteaza si formeaza o reteta
                    //atunci adaugam perechea in coada de combinari
                    if(this->table.canCombine(*(v1[i].elem), *(v2[j].elem))){
                        q.push({&v1[i], &v2[j]});

                        std:string res = (*(v1[i].elem) + *(v2[j].elem)).getName();
                        std::cout << v1[i].elem->getName() << " + " << v2[j].elem->getName() << " = " << res << '\n';
                    }
                    else if(this->table.canCombine(*(v2[j].elem), *(v1[i].elem)))
                        q.push({&v2[j], &v1[i]});
                }

            }
        }

}


// personalizarea textului care apare pe screen
template<typename TTheme>
void GamePlay<TTheme>::initText(sf::Text &text, const int charSize, const float lineSpacing, const std::uint32_t style, const sf::Color fillColor,
    const sf::Color outlineClr, const float thickness, float pozx, float pozy){
    text.setCharacterSize(charSize);
    text.setLineSpacing(lineSpacing);
    text.setStyle(style);
    text.setFillColor(fillColor);
    text.setOutlineColor(outlineClr);
    text.setOutlineThickness(thickness);
    text.setPosition({pozx, pozy});
}
