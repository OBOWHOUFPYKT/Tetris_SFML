#pragma once

#include "figure.h"

// Фигура 4 в ряд - переопределяет установку конфигурации, конструктор копирования и функцию клонирования
class FigureLine : public Figure
{
protected:
    virtual void setConfByDir() override; //  В производном классе "FigureLine" она определяет специфичную конфигурацию фигуры для фигуры "4 в ряд".
public:
    FigureLine(); // конструктор по умолчанию
    FigureLine(Figure* src); // конструктор копирования, принимает указатель на объект базового класса "Figure" в качестве параметра и копирует его поля в новый объект класса FigureLine.
    virtual Figure* Clone(); // создает и возвращает копию объекта класса FigureLine.
};

