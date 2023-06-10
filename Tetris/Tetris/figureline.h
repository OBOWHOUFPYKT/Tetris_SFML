#pragma once

#include "figure.h"

// ������ 4 � ��� - �������������� ��������� ������������, ����������� ����������� � ������� ������������
class FigureLine : public Figure
{
protected:
    virtual void setConfByDir() override; //  � ����������� ������ "FigureLine" ��� ���������� ����������� ������������ ������ ��� ������ "4 � ���".
public:
    FigureLine(); // ����������� �� ���������
    FigureLine(Figure* src); // ����������� �����������, ��������� ��������� �� ������ �������� ������ "Figure" � �������� ��������� � �������� ��� ���� � ����� ������ ������ FigureLine.
    virtual Figure* Clone(); // ������� � ���������� ����� ������� ������ FigureLine.
};

