#include "textureManager.h"
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include <SFML/Graphics/Font.hpp>
#include<unordered_map>

//constructorul
TextureManager::TextureManager(){
    this->textures = textures;
}

//getInstance -> functia care ne ajuta sa putem creea unicul obiect de tip TextureManager
TextureManager& TextureManager::getInstance(){
    static TextureManager texture;
    return texture;
}

//load -> functia care populeaza map-ul cu perechi de tipul (nume_element, textura_element)
sf::Texture& TextureManager::load(const std::string& key, const std::string& filename){
    //cand populam map-ul verificam intai daca elementul a fost deja adaugat
    //daca elementul de afla deja in map returnam textura lui
    auto it = this->textures.find(key);
    if(it != this->textures.end())
        return it->second;

    //daca elementul nu este gasit il adaugam
    sf::Texture t;
    if(!t.loadFromFile(filename))
        throw std::runtime_error("Could not load icon: " + filename);
    
    t.setSmooth(true);

    //introducem noul element in map si retinem un iterator care pointeaza catre noul element
    auto [newIt, _] = this->textures.emplace(key, std::move(t));
    return newIt->second;
}