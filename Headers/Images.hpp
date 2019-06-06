//
// Created by Bartłomiej Binda on 13/05/2019.
//

#ifndef SFML_IMAGES_HPP
#define SFML_IMAGES_HPP

#include <SFML/Graphics.hpp>

#include <unordered_map>

/// Class to manage textures
class TextManager {
public:
    /** typedef for our texture container */
    typedef std::unordered_map<std::string, sf::Texture *> text_um;
    /** Destructor. Deletes all the textures (cleaning up) */
    ~TextManager();
    /** TextManager is singleton, we forbid coppying it */
    TextManager(const TextManager &Next) = delete;
    void operator=(const TextManager &Next) = delete;
      /** Loads textures and sets them by key Value (textureName). If there already exists one we change it. */
    static sf::Texture* Load(const std::string &textureName, const std::string &texturePath);
    /** Removes texture by name from text_map */
    static bool Unload(const std::string &textureName);
    /** Removes all textures. returns the number of removed elements */
    static std::size_t Cleanup();
    /** Gets a texture by name, if it hasn't been loaded before it returns nullptr */
    static sf::Texture* Get(const std::string &textureName);
    /** Checks whether the Texture has been loaded before */
    inline static bool Exists(const std::string &textureName) { return TextManager::Get(textureName) != nullptr; }

private:
    /** Private constructor because it's a singletone class. */
    TextManager();
    /** Creates a single instance of TextManager. It's private, because we manage Textures with static methods. */
    inline static TextManager& Instance() {
        static TextManager instance;
        return instance;
    }
    /** container for our textures */
    text_um	text_map;		// Zbiór tekstur.
};

#endif //SFML_IMAGES_HPP
