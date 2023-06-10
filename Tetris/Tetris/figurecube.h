#pragma once

#include "figure.h"

// Фигура Куб - переопределяет установку конфигурации, конструктор копирования и функцию клонирования
class FigureCube : public Figure
{
protected:
    virtual void setConfByDir() override; // определяет специфичную конфигурацию фигуры для фигуры-куба.
public:
    FigureCube(); // конструктор по умолчанию
    FigureCube(Figure* src); // конструктор копирования, принимает указатель на объект базового класса "Figure" в качестве параметра и копирует его поля в новый объект класса FigureCube.
    virtual Figure* Clone(); // создает и возвращает копию объекта класса FigureCube.
};


