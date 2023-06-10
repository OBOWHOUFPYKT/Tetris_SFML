#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <array>

enum GameState { Play, End }; // Состояние игры

const int TEXTURE_COUNT = 5; // Число текстур в игре

#include "figure.h"


struct Block { // Структура блока - код текстуры и признак пустоты блока
	int texidx;
	bool empty;
};


class Game // Основной класс игры
{
private:
	// Ресурсы игры
	sf::Font font; // шрифт 
	std::array<sf::Texture*, TEXTURE_COUNT> textures; // массив фигур 

	
	GameState gamestate; // Состояние игры
	void loadFileTo(sf::Sprite& sprite, const std::string& filename); // загрузчик спрайтов
	void drawSprite(sf::RenderTarget& target, sf::Sprite& sprite, int x, int y); // рисователь справйтов
	// Вывод текста
	void drawLabelW(sf::RenderTarget& target, const std::wstring& wstr, int x, int y, const sf::Font& font, int size,
		sf::Color color = sf::Color::White);

	// Параметры самого тетриса

	double countdown; // Отсчет до движения фигуры вниз на шаг
	Figure* figure; // Текущая фигура
	Block** blocks; // // Массив блоков тетриса уже уложенных

	// Очки, уровень, число линий
	int score;
	int level;
	int lines;

	void ResetCountdown(); // Сброс счетчика падения
	
	void NextFigure(); // Создание новой фигуры
	
	void TestAndShiftLine(); // Проверка и убирание линии, если нужно

public:
	Game(); // конструктор по умолчанию для создания объекта класса Game
	
	void Update(sf::RenderWindow& window, float dt); // Процедура обновления игры
	
	void Render(sf::RenderWindow& window); // Процедура вывода игры на экран

	// Размеры стакана
	static int Width();
	static int Height();

	// предоставляют информацию о блоках и их свойствах в игре.
	int getBlockTexIdx(int x, int y); // Получение текстуры блока (с учетом фигуры)
	bool isBlockEmpty(int x, int y); // Проверка пустоты блока (только упавшие)
	bool isColored(int x, int y); // Проверка наличия цвета в блоке (с учетом фигуры)

	// Команды игры движения и вращения
	void SendLeft();
	void SendRight();
	void SendDown();
	void SendRotate();

	// Получение данных для вывода
	int getScore();
	int getLevel();
};

