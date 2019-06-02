//
// Created by Bartłomiej Binda on 13/05/2019.
//

#ifndef SFML_IMAGES_HPP
#define SFML_IMAGES_HPP

#include <SFML/Graphics.hpp>

#include <unordered_map>

// Klasa do zarządzania teksturami

class TextManager {
public:
    typedef std::unordered_map<std::string, sf::Texture *> text_um;

    //	Destruktor - zwalnia cala pamiec, wszystkie pozostale tekstury
    ~TextManager();

    //  Menedzer tekstur to singleton, zabraniamy kopiowania tego obiektu.

    TextManager(const TextManager &Next) = delete;
    void operator=(const TextManager &Next) = delete;

    /*	Statyczna metoda, ktora laduje teksture do pamieci i ustawia ją pod kluczem
    podanym w [textureName]. Jeśli textura o tej nazwie już istniała, to zamieniamy ją.
    Robimy to w taki sposób, by nie "psuć" spritów, które już korzystają z tamtej tekstury.
*/
    static sf::Texture* Load(const std::string &textureName, const std::string &texturePath);

/*	Usuwa teksture o podanej nazwie [textureName] z pamięci.
*/
    static bool Unload(const std::string &textureName);

/*	Usuwa wszystkie tekstury z pamięci.
    Zwraca ilość usuniętych tekstur.
*/
    static std::size_t Cleanup();

/*	Pobiera teksture ze zbioru, jednak gdy jeszcze nie została ona wczytana
    to zwróci nullptr.
*/
    static sf::Texture* Get(const std::string &textureName);

/*	Sprawdza czy tekstura znajduje się w zasobach.
*/
    inline static bool Exists(const std::string &textureName) { return TextManager::Get(textureName) != nullptr; }

private:
    /*	Konstruktor menedzera tekstur.
        Jest prywatny ze względu na to, że cała klasa jest singletonem.
    */
    TextManager();

    /*	Tworzy pojedynczą instancję klasy TextManager i ją zwraca.
        Ta metoda jest prywatna, ze względu na to, że zostawiamy zarządzanie
        klasą metodom statycznym.
    */
    inline static TextManager& Instance() {
        static TextManager instance;
        return instance;
    }

    text_um	text_map;		// Zbiór tekstur.
};

#endif //SFML_IMAGES_HPP
