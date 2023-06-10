#include "figure.h"
#include <time.h> 
#include <stdlib.h>

#define cntTex 5 // ���-�� �������
#define startPos 4 // �������� ��������� ������ 
#define zeroPosX 5 // ��������� ������� �� �
#define zeroPosY 0 // ��������� ������� �� y

void Figure::setConfByDir() 
{
    // ����������� �������, �� � ������ ���������� ��� �� ��������� ������� ��������.
}

Figure::Figure()
{
    dir = 0 ; // ��������� ��������� ������
    // ��������� ��������
    pos = sf::Vector2i(zeroPosX, zeroPosY) ;
    texidx = rand() % cntTex; // ��������� ��������� �������� 

    setConfByDir(); // ��� ��������� ������������ ������ � ������������ � ������� ������������.
}

Figure::Figure(Figure * src) { // �������� ���� ������ �� ��������� � ����� ������
    this->dir = src->dir; // ����������� ����������� 
    this->baseconf = src->baseconf; // ����������� ������� ������������ 
    this->pos = src->pos ; // ����������� �������  
    this->texidx = src->texidx; // ����������� ������� ��������
}

sf::Vector2i Figure::getBlock(int i) const // ������� ����� ������ �� ���������� �������
{
    return sf::Vector2i(pos.x+baseconf[i].x,pos.y+baseconf[i].y) ;
} // ��������� ������� ����� ������������ ������� ������� ������ � ������ �������� �� ������� ������������.

int Figure::getTextureIdx() const
{
    return texidx ; // ���������� ������ �������� ������.
}

int Figure::getCount() const
{ // ���������� ���������� ������ � ������, ����������� �� ������� ������� ������������.
    return baseconf.size() ; 
}

Figure* Figure::Clone() //  ������� � ���������� ����� ������� ������ � ������� ������������ �����������
{
    return new Figure(*this);
} // ������� ����� ������ Figure, ������������� ��� ���������� �������� �������.


// ��� ������ ��������� ������� �������� � �������� ������
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
    // ����������� ��������
    dir++ ;
    if (dir== startPos) dir=0 ; // ����������� � �������� ���������
    setConfByDir();
}

void Figure::Down()
{
    pos.y++;
}
