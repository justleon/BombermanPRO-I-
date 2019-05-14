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
    for (auto textureData : m_textures)
    {
        delete (textureData.second);
    }
}

//////////////////////////////////////////////////////////////////////
sf::Texture* TextManager::Load(const std::string &textureName, const std::string &texturePath)
{
    /* Spróbujmy pobrać teksture z menedżera */
    sf::Texture *result = TextManager::Get(textureName);

    /* Jezeli istnieje juz tekstura o takiej nazwie */
    if (result)
    {
        /*	Używamy jej do wczytania nowej tekstury.
            Nowa tekstura zamieni starą.
        */
        result->loadFromFile(texturePath);
    }
    else
    {
        /*	Jeśli jednak tekstura jeszcze nie istaniała
            to musimy ją utworzyć od podstaw.
            Tworzymy nową teksture.
        */
        result = new sf::Texture();
        /* Wczytujemy ją z pliku. */
        result->loadFromFile(texturePath);
        /* Następnie zapisujemy ją w kontenerze.*/
        Instance().m_textures[textureName] = result;
    }

    /* Tekstura wynikowa jest wskazywana wlasnie przez result. Zwracamy ją */
    return result;
}

//////////////////////////////////////////////////////////////////////
bool TextManager::Unload(const std::string &textureName)
{
    /*	By uniknąć kilkukrotniego wywołania funkcji Instance()
        tworzymy referencje na tą instancję.
    */
    auto &instance = Instance();

    /* Szukamy tekstury w kontenerze. Funkcja find zwraca iterator. */
    auto textureIt = instance.m_textures.find(textureName);

    /* Jeśli iterator wskazuje na koniec kontenera to nie znaleziono tekstury.*/
    if (textureIt == instance.m_textures.end())
    {
        return false;
    }
    else
    {
        /*	Tekstura została znaleziona. Należy usunąć ją za pomocą jej wskaźnika,
            który znajduje się pod textureIt->second.
        */
        delete (textureIt->second);
        /*	Iterator wskazuje dokładnie na teksturę, którą chcemy usunąć z kontenera.
            Robimy to za pomocą metody erase.
        */
        instance.m_textures.erase(textureIt);

        /* Tekstura została zwolniona, zwracamy prawdę. */
        return true;
    }
}

//////////////////////////////////////////////////////////////////////
std::size_t TextManager::Cleanup()
{
    /*	By uniknąć kilkukrotniego wywołania funkcji Instance()
        tworzymy referencje na tą instancję.
    */
    auto &instance = Instance();

    /*	Pobieramy ilość tekstur do usunięcia. */
    std::size_t textureCount = instance.m_textures.size();

    /*	Usuwamy każdą teksture. */
    for (auto textureData : instance.m_textures)
    {
        delete (textureData.second);
    }

    /*	Zwracamy ilość tekstur */
    return textureCount;
}

//////////////////////////////////////////////////////////////////////
sf::Texture * TextManager::Get(const std::string &textureName)
{
    /*	By uniknąć kilkukrotniego wywołania funkcji Instance()
        tworzymy referencje na tą instancję.
    */
    auto &instance = Instance();

    /* Szukamy tekstury w kontenerze. Funkcja find zwraca iterator. */
    auto textureIt = instance.m_textures.find(textureName);

    /* Jeśli iterator wskazuje na koniec kontenera to nie znaleziono tekstury.*/
    if (textureIt == instance.m_textures.end())
    {
        return nullptr;
    }

    /* Tekstura została znaleziona. Zwracamy ją. */
    return textureIt->second;
}

/*
void image_manager::add_resource_directory( const std::string& directory )
{
    // Check whether the path already exists
    for( std::vector<std::string>::const_iterator it  = resource_directories_.begin();
         it != resource_directories_.end();
         ++it )
    {
        // The path exists. So it isn't necessary to add id once more.
        if( directory == (*it) )
            return;
    }

    // insert the directory
    resource_directories_.push_back( directory );
}

const sf::Image& image_manager::get_image( const std::string& filename )
{
    // Check, whether the image already exists
    for( std::map<std::string, sf::Image>::const_iterator it = images_.begin();
         it != images_.end();
         ++it)
    {
        if( filename == it->first )
        {
            std::cout << "DEBUG_MESSAGE: " << filename << " using existing image.\n";
            return it->second;
        }
    }

    // The image doesen't exists. Create it and save it.
    sf::Image image;

    // Search project's main directory
    if( image.LoadFromFile( filename ) )
    {
        images_[filename] = image;
        std::cout << "DEBUG_MESSAGE: " << filename << " loading image.\n";
        return images_[filename];
    }

    // If the image has still not been found, search all registered directories
    for( std::vector< std::string >::iterator it = resource_directories_.begin();
         it != resource_directories_.end();
         ++it )
    {
        if( image.LoadFromFile( (*it) + filename ) )
        {
            images_[filename] = image;
            std::cout << "DEBUG_MESSAGE: " << filename << " loading image.\n";
            return images_[filename];
        }

    }

    std::cout << "GAME_ERROR: Image was not found. It is filled with an empty image.\n";
    images_[filename] = image;
    return images_[filename];
}

void image_manager::delete_image( const sf::Image& image )
{
    for( std::map<std::string, sf::Image>::const_iterator it = images_.begin();
         it != images_.end();
         ++it)
    {
        // compare the adresses
        if( &image == &it->second )
        {
            images_.erase( it );
            return;
        }
    }
}

void image_manager::delete_image( const std::string& filename )
{
    std::map<std::string, sf::Image>::const_iterator it = images_.find( filename );
    if( it != images_.end() )
        images_.erase( it );
}

*/
