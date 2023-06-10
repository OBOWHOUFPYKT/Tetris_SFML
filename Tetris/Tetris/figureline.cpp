#include "figureline.h"

void FigureLine::setConfByDir()
{
    baseconf.clear(); // ������� ������� ������������
    // ������������� ������������ ��� ������ "�����"
    // ������ "�����" ����� 4 ��������� ���������� (dir = 0, 1, 2, 3)
    // � ����������� �� ���������� (dir), ������������ ����� ����������� � ������������
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
    Figure() // ����������� �������� ����������� �������� ������ Figure() � ����� �������� ������� setConfByDir() ��� ��������� ������������ ������ "�����".
{
    setConfByDir();
}

FigureLine::FigureLine(Figure* src) : Figure(src)
{// ����������� �������� ����������� �������� ������ Figure(Figure* src) ��� ����������� ������ �� ��������� ������� src � ����� ������ FigureLine.
}

Figure* FigureLine::Clone()
{ // ������� � ���������� ����� ������ FigureLine, ������� �������� ������ �������� �������.
    return new FigureLine(*this);
}
