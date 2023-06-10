#pragma once

#include "figure.h"

// ������ � - �������������� ��������� ������������, ����������� ����������� � ������� ������������
class FigureG : public Figure
{
protected:
    virtual void setConfByDir() override; //  ���������� ����������� ������������ ������ ��� ������-����� "�".
public:
    FigureG(); // ����������� �� ���������
    FigureG(Figure* src); // ����������� �����������, ��������� ��������� �� ������ �������� ������ "Figure" � �������� ��������� � �������� ��� ���� � ����� ������ ������ FigureG.
    virtual Figure* Clone(); // ������� � ���������� ����� ������� ������ FigureG.
};

