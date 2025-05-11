#define SFML_STATIC
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<memory>

namespace fs = std::filesystem;

class GameUI {
    sf::Font font;
    sf::Text welcomeMsg;
    std::string str;
    int size;
    float pozx;
    float pozy;

public:
    GameUI(sf::Font &font, sf::Text &welcomeMsg_, std::string str, int size, float pozx, float pozy) : welcomeMsg(welcomeMsg_){
        sf::Font font{ fs::path("Type Machine.ttf") };
        sf::Text text(this->font);
        this->font = font;
        this-> str = str;
        this-> size = size;
        this-> pozx = pozx;
        this-> pozy = pozy;
    }

    void initText(sf::Text& text, const sf::Font& font, const std::string& str, const int& size, const float& pozx, const float& pozy) {
        text.setString(str);
        text.setCharacterSize(size);
        text.setFillColor(sf::Color::Green);
        text.setPosition({pozx, pozy});
    }
};
