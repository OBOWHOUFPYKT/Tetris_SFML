#include "figure4.h"

void Figure4::setConfByDir()
{
    baseconf.clear(); // ������� ������� ������������

    // � ����������� �� �������� ���������� dir (����������� �������� ������) ���������� ������������ ������
    if (dir==0) {
        // ����������� 0: �������������� �����
        baseconf.push_back(sf::Vector2i(0,0));
        baseconf.push_back(sf::Vector2i(-1,0));
        baseconf.push_back(sf::Vector2i(1,0));
        baseconf.push_back(sf::Vector2i(0,1));
    }
    if (dir==1) {
        // ����������� 1: ������������ �����
        baseconf.push_back(sf::Vector2i(0,-1));
        baseconf.push_back(sf::Vector2i(0,0));
        baseconf.push_back(sf::Vector2i(0,1));
        baseconf.push_back(sf::Vector2i(1,0));
    }
    if (dir==2) {
        // ����������� 2: �������������� �����
        baseconf.push_back(sf::Vector2i(0,0));
        baseconf.push_back(sf::Vector2i(-1,0));
        baseconf.push_back(sf::Vector2i(1,0));
        baseconf.push_back(sf::Vector2i(0,-1));
    }
    if (dir==3) {
        // ����������� 3: ������������ �����
        baseconf.push_back(sf::Vector2i(0,-1));
        baseconf.push_back(sf::Vector2i(0,0));
        baseconf.push_back(sf::Vector2i(0,1));
        baseconf.push_back(sf::Vector2i(-1,0));
    }
}

Figure4::Figure4(): // ������� ������������� �� ���������
    Figure()
{
    setConfByDir(); // ���������� ������������ ������ � ������������ � ������� ��������� dir.
}

Figure4::Figure4(Figure * src) : Figure(src) // ����������� ����������� ������ Figure4.
{ // �������� ����������� ����������� �������� ������ Figure, ����� ����������� ���� ������ �� ������� src.
}

Figure* Figure4::Clone() // �������� ����������� ������� �� �������� ������ Figure.
{
    return new Figure4(*this); // ���������� ��������� �� ����� ������ Figure4, ��������� � �������������� ������������ ����������� Figure4(*this).
}