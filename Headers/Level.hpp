//
// Created by Bartłomiej Binda on 21/05/2019.
//

#ifndef SFML_LEVEL_H
#define SFML_LEVEL_H

#include <iostream>
#include "../Headers/Entity.hpp"
#include "../Headers/block.hpp"

class Level
{
public:
    typedef std::vector<Entity *> Vunits;

    /*	Konstruktor klasy poziomu.
    */
    Level();
    /*	Destruktor klasy poziomu.
        Dba o poprawne zwolnienie pozostałych zasobów
    */
    ~Level();

    /*	Dodaje aktora do poziomu.
        Jeśli aktor pozostanie do czasu destrukcji obiektu poziomu
        to automatycznie zostanie zniszczony przez jego destruktor.
        Zwraca prawdę jeśli aktora jeszcze nie było w tym poziomie.
    */
    bool Add(Entity *unit);
    /*	Usuwa aktora ze poziomu.
        Nie zwalnia go z pamięci.
        Zwraca prawdę jeśli aktor był w tym poziomie.
    */
    bool Remove(Entity *unit);
    /*	Zwraca prawdę jeśli podany aktor jest juz w tym poziomie.
    */
    bool Exists(Entity *unit) const;
    /*	Usuwa wszystkich aktorów ze sceny
        i zwraca ich ilość przed usunięciem.
    */
    std::size_t Cleanup();
    /*	Uaktualnia wszystkich aktorów z poziomu.
    */
    void Update(const float &deltaTime);
    /*	Wyświetla wszystkich aktorów w tym poziomie.
    */
    void Draw();
    /* Zwraca ilość aktorów znajdujących się na tym levelu. */
    inline std::size_t Count() const { return units.size(); }
private:
    Vunits units;		// Aktorzy na scenie.
};

void setMap(Level *currentLevel);

#endif //SFML_LEVEL_H
