#include "figurecube.h"

void FigureCube::setConfByDir()
{
    baseconf.clear(); // Очищаем текущую конфигурацию
    // Устанавливаем конфигурацию для фигуры Куб
    // Куб состоит из четырех блоков, расположенных в квадрате
    baseconf.push_back(sf::Vector2i(0,0));
    baseconf.push_back(sf::Vector2i(1,0));
    baseconf.push_back(sf::Vector2i(0,1));
    baseconf.push_back(sf::Vector2i(1,1));
}

FigureCube::FigureCube()://Конструктор вызывает конструктор базового класса Figure() и затем вызывает функцию setConfByDir() для установки конфигурации фигуры "Куб".
    Figure()
{
    setConfByDir();
}

FigureCube::FigureCube(Figure* src) : Figure(src)
{// Конструктор вызывает конструктор базового класса Figure(Figure* src) для копирования данных из исходного объекта src в новый объект FigureCube.
}

Figure* FigureCube::Clone()
{//создает и возвращает новый объект FigureCube, который является копией текущего объекта.
    return new FigureCube(*this);
}