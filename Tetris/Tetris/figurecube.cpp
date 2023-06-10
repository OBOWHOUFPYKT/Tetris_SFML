#include "figurecube.h"

void FigureCube::setConfByDir()
{
    baseconf.clear(); // ������� ������� ������������
    // ������������� ������������ ��� ������ ���
    // ��� ������� �� ������� ������, ������������� � ��������
    baseconf.push_back(sf::Vector2i(0,0));
    baseconf.push_back(sf::Vector2i(1,0));
    baseconf.push_back(sf::Vector2i(0,1));
    baseconf.push_back(sf::Vector2i(1,1));
}

FigureCube::FigureCube()://����������� �������� ����������� �������� ������ Figure() � ����� �������� ������� setConfByDir() ��� ��������� ������������ ������ "���".
    Figure()
{
    setConfByDir();
}

FigureCube::FigureCube(Figure* src) : Figure(src)
{// ����������� �������� ����������� �������� ������ Figure(Figure* src) ��� ����������� ������ �� ��������� ������� src � ����� ������ FigureCube.
}

Figure* FigureCube::Clone()
{//������� � ���������� ����� ������ FigureCube, ������� �������� ������ �������� �������.
    return new FigureCube(*this);
}