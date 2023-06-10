#include "figureg.h"

void FigureG::setConfByDir()
{
    baseconf.clear(); // Очищаем текущую конфигурацию

    // Устанавливаем конфигурацию для фигуры "Г"
    // Фигура "Г" имеет 4 возможных ориентации (dir = 0, 1, 2, 3)
    // В зависимости от ориентации (dir), определенные блоки добавляются в конфигурацию
    if (dir==0) {
        baseconf.push_back(sf::Vector2i(1,0));
        baseconf.push_back(sf::Vector2i(0,0));
        baseconf.push_back(sf::Vector2i(0,1));
        baseconf.push_back(sf::Vector2i(0,2));
    }
    if (dir==1) {
        baseconf.push_back(sf::Vector2i(1,1));
        baseconf.push_back(sf::Vector2i(0,1));
        baseconf.push_back(sf::Vector2i(-1,1));
        baseconf.push_back(sf::Vector2i(-1,0));
    }
    if (dir==2) {
        baseconf.push_back(sf::Vector2i(1,2));
        baseconf.push_back(sf::Vector2i(0,0));
        baseconf.push_back(sf::Vector2i(0,1));
        baseconf.push_back(sf::Vector2i(0,2));
    }
    if (dir==3) {
        baseconf.push_back(sf::Vector2i(1,0));
        baseconf.push_back(sf::Vector2i(0,0));
        baseconf.push_back(sf::Vector2i(-1,0));
        baseconf.push_back(sf::Vector2i(-1,1));
    }
}

FigureG::FigureG()://Конструктор вызывает конструктор базового класса Figure() и затем вызывает функцию setConfByDir() для установки конфигурации фигуры "Г".
    Figure()
{
    setConfByDir();
}

FigureG::FigureG(Figure* src) : Figure(src)
{// Конструктор вызывает конструктор базового класса Figure(Figure* src) для копирования данных из исходного объекта src в новый объект FigureG.
}

Figure* FigureG::Clone()
{// создает и возвращает новый объект FigureG, который является копией текущего объекта.
    return new FigureG(*this);
}