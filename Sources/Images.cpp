//
// Created by Bartłomiej Binda on 13/05/2019.
//

#include "../Headers/Images.hpp"

//////////////////////////////////////////////////////////////////////
TextManager::TextManager()
{
}

//////////////////////////////////////////////////////////////////////
TextManager::~TextManager()
{
    /* Usuwamy każdą teksturę. */
    for (auto textureData : text_map) delete (textureData.second);
}

//////////////////////////////////////////////////////////////////////
sf::Texture* TextManager::Load(const std::string &textureName, const std::string &texturePath) {
    /* Spróbujmy pobrać teksture z menedżera */
    sf::Texture *result = TextManager::Get(textureName);

    /* Jezeli istnieje juz tekstura o takiej nazwie */
    if (result)
        /*	Używamy jej do wczytania nowej tekstury.
            Nowa tekstura zamieni starą.
        */
        result->loadFromFile(texturePath);
    else {
        /*	Jeśli jednak tekstura jeszcze nie istaniała
            to musimy ją utworzyć od podstaw.
            Tworzymy nową teksture.
        */
        result = new sf::Texture();
        /* Wczytujemy ją z pliku. */
        result->loadFromFile(texturePath);
        /* Następnie zapisujemy ją w kontenerze.*/
        Instance().text_map[textureName] = result;
    }

    /* Tekstura wynikowa jest wskazywana wlasnie przez result. Zwracamy ją */
    return result;
}

//////////////////////////////////////////////////////////////////////
bool TextManager::Unload(const std::string &textureName) {
    /*	By uniknąć kilkukrotniego wywołania funkcji Instance()
        tworzymy referencje na tą instancję.
    */
    auto &instance = Instance();

    /* Szukamy tekstury w kontenerze. Funkcja find zwraca iterator. */
    auto textureIt = instance.text_map.find(textureName);

    /* Jeśli iterator wskazuje na koniec kontenera to nie znaleziono tekstury.*/
    if (textureIt == instance.text_map.end())
        return false;

    else {
        /*	Tekstura została znaleziona. Należy usunąć ją za pomocą jej wskaźnika,
            który znajduje się pod textureIt->second.
        */
        delete (textureIt->second);
        /*	Iterator wskazuje dokładnie na teksturę, którą chcemy usunąć z kontenera.
            Robimy to za pomocą metody erase.
        */
        instance.text_map.erase(textureIt);

        /* Tekstura została zwolniona, zwracamy prawdę. */
        return true;
    }
}

//////////////////////////////////////////////////////////////////////
std::size_t TextManager::Cleanup() {
    /*	By uniknąć kilkukrotniego wywołania funkcji Instance()
        tworzymy referencje na tą instancję.
    */
    auto &instance = Instance();

    /*	Pobieramy ilość tekstur do usunięcia. */
    std::size_t textureCount = instance.text_map.size();

    /*	Usuwamy każdą teksture. */
    for (auto textureData : instance.text_map)
        delete (textureData.second);

    /*	Zwracamy ilość tekstur */
    return textureCount;
}

//////////////////////////////////////////////////////////////////////
sf::Texture * TextManager::Get(const std::string &textureName) {
    /*	By uniknąć kilkukrotniego wywołania funkcji Instance()
        tworzymy referencje na tą instancję.
    */
    auto &instance = Instance();

    /* Szukamy tekstury w kontenerze. Funkcja find zwraca iterator. */
    auto text = instance.text_map.find(textureName);

    /* Jeśli iterator wskazuje na koniec kontenera to nie znaleziono tekstury.*/
    if (text == instance.text_map.end())
        return nullptr;

    /* Tekstura została znaleziona. Zwracamy ją. */
    return text->second;
}