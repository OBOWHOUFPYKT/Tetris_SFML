#pragma once

#include "figure.h"

// Фигура Г - переопределяет установку конфигурации, конструктор копирования и функцию клонирования
class FigureG : public Figure
{
protected:
    virtual void setConfByDir() override; //  определяет специфичную конфигурацию фигуры для фигуры-буквы "Г".
public:
    FigureG(); // конструктор по умолчанию
    FigureG(Figure* src); // конструктор копирования, принимает указатель на объект базового класса "Figure" в качестве параметра и копирует его поля в новый объект класса FigureG.
    virtual Figure* Clone(); // создает и возвращает копию объекта класса FigureG.
};

