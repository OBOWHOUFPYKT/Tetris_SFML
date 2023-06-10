#include "figure4.h"

void Figure4::setConfByDir()
{
    baseconf.clear(); // ќчищаем текущую конфигурацию

    // ¬ зависимости от значени€ переменной dir (направление поворота фигуры) определ€ем конфигурацию фигуры
    if (dir==0) {
        // Ќаправление 0: горизонтальна€ лини€
        baseconf.push_back(sf::Vector2i(0,0));
        baseconf.push_back(sf::Vector2i(-1,0));
        baseconf.push_back(sf::Vector2i(1,0));
        baseconf.push_back(sf::Vector2i(0,1));
    }
    if (dir==1) {
        // Ќаправление 1: вертикальна€ лини€
        baseconf.push_back(sf::Vector2i(0,-1));
        baseconf.push_back(sf::Vector2i(0,0));
        baseconf.push_back(sf::Vector2i(0,1));
        baseconf.push_back(sf::Vector2i(1,0));
    }
    if (dir==2) {
        // Ќаправление 2: горизонтальна€ лини€
        baseconf.push_back(sf::Vector2i(0,0));
        baseconf.push_back(sf::Vector2i(-1,0));
        baseconf.push_back(sf::Vector2i(1,0));
        baseconf.push_back(sf::Vector2i(0,-1));
    }
    if (dir==3) {
        // Ќаправление 3: вертикальна€ лини€
        baseconf.push_back(sf::Vector2i(0,-1));
        baseconf.push_back(sf::Vector2i(0,0));
        baseconf.push_back(sf::Vector2i(0,1));
        baseconf.push_back(sf::Vector2i(-1,0));
    }
}

Figure4::Figure4(): // вл€етс€ конструктором по умолчанию
    Figure()
{
    setConfByDir(); // установить конфигурацию фигуры в соответствии с текущим значением dir.
}

Figure4::Figure4(Figure * src) : Figure(src) // конструктор копировани€ класса Figure4.
{ // вызывает конструктор копировани€ базового класса Figure, чтобы скопировать пол€ фигуры из объекта src.
}

Figure* Figure4::Clone() // €вл€етс€ виртуальным методом из базового класса Figure.
{
    return new Figure4(*this); // возвращает указатель на новый объект Figure4, созданный с использованием конструктора копировани€ Figure4(*this).
}