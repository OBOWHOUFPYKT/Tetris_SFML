#pragma once

#include "figure.h"

// ������ ��� - �������������� ��������� ������������, ����������� ����������� � ������� ������������
class FigureCube : public Figure
{
protected:
    virtual void setConfByDir() override; // ���������� ����������� ������������ ������ ��� ������-����.
public:
    FigureCube(); // ����������� �� ���������
    FigureCube(Figure* src); // ����������� �����������, ��������� ��������� �� ������ �������� ������ "Figure" � �������� ��������� � �������� ��� ���� � ����� ������ ������ FigureCube.
    virtual Figure* Clone(); // ������� � ���������� ����� ������� ������ FigureCube.
};


