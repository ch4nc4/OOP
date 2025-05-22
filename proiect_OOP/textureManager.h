#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include <SFML/Graphics/Font.hpp>
#include<unordered_map>

class TextureManager{ //singleton - avem un singur manager al texturilor pe toata durata jocului
    public:
        //constructor
        sf::Texture& load(const std::string& key, const std::string& filename);
        static TextureManager& getInstance();
    private:
        TextureManager();
        TextureManager(const TextureManager&) = delete;
        TextureManager& operator=(const TextureManager&) = delete;
        std::unordered_map<std::string, sf::Texture> textures;
};