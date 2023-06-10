#include "figureline.h"

void FigureLine::setConfByDir()
{
    baseconf.clear(); // Очищаем текущую конфигурацию
    // Устанавливаем конфигурацию для фигуры "Линия"
    // Фигура "Линия" имеет 4 возможных ориентации (dir = 0, 1, 2, 3)
    // В зависимости от ориентации (dir), определенные блоки добавляются в конфигурацию
    if ((dir==0)||(dir==2)) {
        baseconf.push_back(sf::Vector2i(0,0));
        baseconf.push_back(sf::Vector2i(0,1));
        baseconf.push_back(sf::Vector2i(0,2));
        baseconf.push_back(sf::Vector2i(0,3));
    }
    else {
        baseconf.push_back(sf::Vector2i(-1,0));
        baseconf.push_back(sf::Vector2i(0,0));
        baseconf.push_back(sf::Vector2i(1,0));
        baseconf.push_back(sf::Vector2i(2,0));
    }
}

FigureLine::FigureLine():
    Figure() // Конструктор вызывает конструктор базового класса Figure() и затем вызывает функцию setConfByDir() для установки конфигурации фигуры "Линия".
{
    setConfByDir();
}

FigureLine::FigureLine(Figure* src) : Figure(src)
{// Конструктор вызывает конструктор базового класса Figure(Figure* src) для копирования данных из исходного объекта src в новый объект FigureLine.
}

Figure* FigureLine::Clone()
{ // создает и возвращает новый объект FigureLine, который является копией текущего объекта.
    return new FigureLine(*this);
}
