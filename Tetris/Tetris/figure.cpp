#include "figure.h"
#include <time.h> 
#include <stdlib.h>

#define cntTex 5 // кол-во текстур
#define startPos 4 // исходное положение фигуры 
#define zeroPosX 5 // стартовая позиция по х
#define zeroPosY 0 // стартовая позиция по y

void Figure::setConfByDir() 
{
    // виртуальная функция, но в данной реализации она не выполняет никаких действий.
}

Figure::Figure()
{
    dir = 0 ; // начальное положение фигуры
    // случайная текстура
    pos = sf::Vector2i(zeroPosX, zeroPosY) ;
    texidx = rand() % cntTex; // установка случайной текстуры 

    setConfByDir(); // для установки конфигурации фигуры в соответствии с текущим направлением.
}

Figure::Figure(Figure * src) { // копирует поля фигуры из источника в новый объект
    this->dir = src->dir; // копирование направления 
    this->baseconf = src->baseconf; // копирование массива конфигурации 
    this->pos = src->pos ; // копирование позиции  
    this->texidx = src->texidx; // копирование индекса текстуры
}

sf::Vector2i Figure::getBlock(int i) const // позицию блока фигуры по указанному индексу
{
    return sf::Vector2i(pos.x+baseconf[i].x,pos.y+baseconf[i].y) ;
} // вычисляет позицию блока относительно текущей позиции фигуры с учетом смещения из массива конфигурации.

int Figure::getTextureIdx() const
{
    return texidx ; // возвращает индекс текстуры фигуры.
}

int Figure::getCount() const
{ // возвращает количество блоков в фигуре, основываясь на размере массива конфигурации.
    return baseconf.size() ; 
}

Figure* Figure::Clone() //  создает и возвращает копию объекта фигуры с помощью конструктора копирования
{
    return new Figure(*this);
} // создает новый объект Figure, инициализируя его значениями текущего объекта.


// эти методы реализуют команды движения и вращения фигуры
void Figure::Left()
{
    pos.x--;
}

void Figure::Right()
{
    pos.x++;
}

void Figure::Roll()
{
    // Циклическое вращение
    dir++ ;
    if (dir== startPos) dir=0 ; // возвращение в исходное положение
    setConfByDir();
}

void Figure::Down()
{
    pos.y++;
}
