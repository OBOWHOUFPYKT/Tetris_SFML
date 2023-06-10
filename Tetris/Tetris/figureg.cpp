#include "figureg.h"

void FigureG::setConfByDir()
{
    baseconf.clear(); // ������� ������� ������������

    // ������������� ������������ ��� ������ "�"
    // ������ "�" ����� 4 ��������� ���������� (dir = 0, 1, 2, 3)
    // � ����������� �� ���������� (dir), ������������ ����� ����������� � ������������
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

FigureG::FigureG()://����������� �������� ����������� �������� ������ Figure() � ����� �������� ������� setConfByDir() ��� ��������� ������������ ������ "�".
    Figure()
{
    setConfByDir();
}

FigureG::FigureG(Figure* src) : Figure(src)
{// ����������� �������� ����������� �������� ������ Figure(Figure* src) ��� ����������� ������ �� ��������� ������� src � ����� ������ FigureG.
}

Figure* FigureG::Clone()
{// ������� � ���������� ����� ������ FigureG, ������� �������� ������ �������� �������.
    return new FigureG(*this);
}