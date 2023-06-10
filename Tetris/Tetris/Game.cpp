#include "Game.h"

#include "figurecube.h"
#include "figureline.h"
#include "figure4.h"
#include "figureg.h"

#define fontWay "data\\Arial.ttf" // путь к шрифту
#define texWay "data\\tex" // путь к текстурам
#define texFormat ".png" // формат текстур
#define textPosXScore 20 // позиция текста заработанных очков по х
#define textPosYScore 20 // позиция текста заработанных очков по у
#define fontSizeScore 28 // размер шрифта текста заработанных очков
#define textColorScore sf::Color::White // цвет текста заработанных очков
#define textPosXLevel 20 // позиция текста уровня игры по х
#define textPosYLevel 50 // позиция текста уровня игры по у
#define fontSizeLevel 28 // размер шрифта текста уровня игры
#define textColorLevel sf::Color::White // цвет текста уровня игры
#define textPosXGameOver 20 // позиция текста конца игры по х
#define textPosYGameOver 80 // позиция текста конца игры по у
#define fontSizeGameOver 28 // размер шрифта текста конца игры
#define textColorGameOver sf::Color::Red // цвет текста конца игры
#define heightCupBlocks 15 // высота игрового поля в стакане блоков
#define widthCupBlocks 10 // ширина игрового поля в стакане блоков
#define formulaInterval1 1.0f // коэффициенты для формулы интервала между движениями фигурок вниз
#define formulaInterval2 0.5f // коэффициенты для формулы интервала между движениями фигурок вниз
#define levelUp 10 // кол-во заполнений для повышения уровня

// Размер блока в пикселях
const int SIZE = 64;

Game::Game() {
	font.loadFromFile(fontWay); // загрузка шрифта

	// Загрузка ресурсов			
	for (int i = 0; i < TEXTURE_COUNT; i++) {
		textures[i] = new sf::Texture();
		textures[i]->loadFromFile(texWay+std::to_string(i)+texFormat);
	}

	// Инициализация состояния игры
	gamestate = Play;	

	// Создание стакана блоков, пустого по умолчанию
	blocks = new Block * [Width()];
	for (int i = 0; i < Width(); i++) {
		blocks[i] = new Block[Height()];
		for (int j = 0; j < Height(); j++)
			blocks[i][j].empty = true;
	}

	// Сброс счетчика и создание фигуры для отслеживания времени до следующего движения фигуры
	ResetCountdown();
	NextFigure(); // создает новую фигуру, которая будет падать в стакан.
	// Обнуление показателей, уровень 1 на старте
	level = 1;
	score = 0;
	lines = 0;
}

void Game::Update(sf::RenderWindow& window, float dt)
{
	// В цикле опрос событий
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close(); // закрытие окна

		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) window.close();			
			// Пока игра активна, управляем 
			if (gamestate == Play) {
				if (event.key.code == sf::Keyboard::Left) SendLeft();
				if (event.key.code == sf::Keyboard::Right) SendRight();
				if (event.key.code == sf::Keyboard::Up) SendRotate();
				if (event.key.code == sf::Keyboard::Down) SendDown();
			}

		}
	}

	// Пока игра активна, движение фигур
	if (gamestate == Play) {
		countdown -= dt; //  Счетчик уменьшается на значение, которое представляет прошедшее время с последнего кадра.
		if (countdown <= 0) {
			ResetCountdown(); // сбрасываее счетчика для отслеживания времени до следующего движения фигуры.

			// Проверка, опустилась ли фигура до блоков
			bool connect = false;
			for (int i = 0; i < figure->getCount(); i++) // итерация по каждому блоку фигуры
				if (!isBlockEmpty(figure->getBlock(i).x, figure->getBlock(i).y + 1)) // проверка, является ли блок под фигурой пустым
					connect = true;

			// Если да, то устанавливаем в стакан, убираем линии если есть и вызываем новую фигуры
			if (connect) {
				score += level; // увеличиваем очки 
				for (int i = 0; i < figure->getCount(); i++) { // Проходим по каждому блоку фигуры
					blocks[figure->getBlock(i).x][figure->getBlock(i).y].texidx = figure->getTextureIdx();
					blocks[figure->getBlock(i).x][figure->getBlock(i).y].empty = false;
					// устанавливаем в соответствующий блок стакана текстуру и помечаем его как непустой
				}
				TestAndShiftLine(); // проверяет и сдвигает заполненные линии в стакане.
				NextFigure(); // создать новую фигуру для падения.
			}
			else
				figure->Down(); // иначе опускаем фигуру на одну ячейку вниз
		}
	}


}

void Game::Render(sf::RenderWindow& window) // отображение игры на экране
{
	// Вывод блоков с текстурами 	
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(SIZE, SIZE));
	for (int i = 0; i < Width(); i++)
		for (int j = 0; j < Height(); j++) { // итерация по каждому блоку в игровом стакане
			if (isColored(i, j)) { // имеет ли текущий блок текстуру, тогда блок относится к текущей фигуре
				shape.setPosition(i * SIZE, j * SIZE); // Создается прямоугольная форма и устанавливается ее позиция
				shape.setTexture(textures[getBlockTexIdx(i,j)]);
				window.draw(shape);
			}
		}

	// Вывод очков и уровня
	drawLabelW(window, L"Очков: "+std::to_wstring(getScore()), textPosXScore, textPosYScore, font, fontSizeScore, textColorScore);
	drawLabelW(window, L"Уровень: " + std::to_wstring(getLevel()), textPosXLevel, textPosYLevel, font, fontSizeLevel, textColorLevel);

	// Вывод меток игры
	if (gamestate == End)
		drawLabelW(window, L"Игра окончена!", textPosXGameOver, textPosYGameOver, font, fontSizeGameOver, textColorGameOver);
}

void Game::loadFileTo(sf::Sprite& sprite, const std::string& filename) //  принимает ссылку на объект sf::Sprite и имя файла в качестве параметров. 
{ // Создание указателя на объект sf::Texture:
	sf::Texture* tex = new sf::Texture(); // Объект sf::Texture будет использован для хранения загруженной текстуры из файла.

	// Загрузка текстуры из файла
	tex->loadFromFile(filename); // Этот метод загружает содержимое файла и связывает его с текстурой.

	// Установка текстуры в спрайт
	sprite.setTexture(*tex);	 // Это устанавливает загруженную текстуру в спрайт, чтобы он мог отображать содержимое текстуры.
}

void Game::drawSprite(sf::RenderTarget& target, sf::Sprite& sprite, int x, int y)
{ // принимает ссылку на объект sf::RenderTarget, ссылку на объект sf::Sprite и координаты x и y в качестве параметров.
	// Установка позиции спрайта
	sprite.setPosition(x, y);// Это определяет местоположение, где спрайт будет отображаться на экране.

	// Отрисовка спрайта на целевом объекте
	target.draw(sprite); // Это приводит к отрисовке спрайта на экране в заданной позиции.
}

void Game::drawLabelW(sf::RenderTarget& target, const std::wstring& wstr, int x, int y, const sf::Font& font, int size,
	sf::Color color)// принимает ссылку на объект sf::RenderTarget, ссылку на константную строку типа std::wstring, координаты x и y, ссылку на константный объект sf::Font, размер текста size и цвет color в качестве параметров. 
{
	sf::Text text(wstr, font, size);//отображаемый на экране текст
	text.setPosition(x, y); // позиция текста
	text.setFillColor(color); // цвет текста
	target.draw(text); //отрисовка текста
}

void Game::ResetCountdown()// сброс значения переменной countdown, которая определяет интервал времени между автоматическим движением фигуры вниз в игре
{//Формула используется для определения интервала времени, который будет проходить между движениями фигуры вниз. 
	countdown = formulaInterval1 / (formulaInterval1 + formulaInterval2 * (double)level);
}//Чем выше уровень игры, тем меньше будет интервал времени между движениями.

void Game::NextFigure()
{
	// Случайное создание фигуры 
	int fign = rand() % 4; // генерирует случайное число от 0 до 3, которое будет использоваться для выбора типа фигуры.
	//В зависимости от значения fign создается новый объект фигуры определенного типа.
	if (fign == 0) figure = new FigureLine(); else
		if (fign == 1) figure = new Figure4(); else
			if (fign == 2) figure = new FigureG();
			else
				figure = new FigureCube();

	
	// Если после создания фигуры она застряла с другими блоками, то конец игры
	for (int i = 0; i < figure->getCount(); i++) // проверка каждого блока новой фигуры
		if (!isBlockEmpty(figure->getBlock(i).x, figure->getBlock(i).y)) // Если хотя бы один блок не является пустым (занятым другими блоками)
			gamestate = End; // конец игры
}

void Game::TestAndShiftLine() // для проверки заполненных линий в стакане блоков и их сдвига вниз
{
	int y = Height() - 1; // индекс строки, начиная с самой нижней строки в стакане блоков
	while (y > 0) {
		bool isfill = true;
		for (int x = 0; x < Width(); x++)

			//проверка каждого блока
			isfill = isfill && (!isBlockEmpty(x, y)); // заполнена ли текущая строка y в стакане блоков.
		if (isfill) {
			// Сдвиг всех блоков выше заполненной линии вниз
			for (int j = y; j > 0; j--)
				for (int x = 0; x < Width(); x++) // перебирает строки выше заполненной строки
					blocks[x][j] = blocks[x][j - 1];
			// Очистка верхней строки
			for (int x = 0; x < Width(); x++)
				blocks[x][0].empty = true;
			// Увеличение счетчика заполненных линий
			lines++;
			// Проверка, достигнут ли порог заполненных линий для повышения уровня
			if (lines == levelUp) {
				level++;
				lines = 0;
			}
		}
		else
			y--; // перейти к проверке предыдущей строки в стакане блоков.
	}
}

int Game::Width()
{
	return widthCupBlocks;
}

int Game::Height()
{
	return heightCupBlocks;
}

int Game::getBlockTexIdx(int x, int y)
{
	// Возврат текстуры(индекс) блока, если он не пустой
	if (!blocks[x][y].empty) return blocks[x][y].texidx;

	// или фигуры 
	for (int i = 0; i < figure->getCount(); i++)// перебор блоков текущей фигуры
		if ((figure->getBlock(i).x == x) && (figure->getBlock(i).y == y)) // блок принадлежит текущей фигуре?
			return figure->getTextureIdx(); // возврат индекса текстуры фигуры

	return -1; // иначе ошибка
}

bool Game::isBlockEmpty(int x, int y)// проверяет блок на пустоту
{
	if (y >= Height()) return false;
	if (x < 0) return false;
	if (x >= Width()) return false;
	return blocks[x][y].empty;
}

bool Game::isColored(int x, int y)
{
	// Проверка наличия блока
	if (!blocks[x][y].empty) return true;
	// или фигуры
	for (int i = 0; i < figure->getCount(); i++)
		if ((figure->getBlock(i).x == x) && (figure->getBlock(i).y == y))
			return true;
	return false;
}

void Game::SendLeft()
{
	// Движение, если нет пересечений с краем или блоками
	bool connect = false;
	for (int i = 0; i < figure->getCount(); i++)
		if (!isBlockEmpty(figure->getBlock(i).x - 1, figure->getBlock(i).y)) // является ли блок слева от текущего блока пустым
			connect = true; // наличие пересечений
	if (!connect) figure->Left(); // перемещение фигуры влево.
}

void Game::SendRight()
{
	// Движение, если нет пересечений с краем или блоками
	bool connect = false;
	for (int i = 0; i < figure->getCount(); i++)
		if (!isBlockEmpty(figure->getBlock(i).x + 1, figure->getBlock(i).y))
			connect = true;
	if (!connect) figure->Right();
}

void Game::SendRotate()
{
	// Поворот, если нет пересечений с краем или блоками
	// Тестируем на клоне фигуры, поворачивая его вместо основной фигуры
	Figure* rolled = figure->Clone();
	rolled->Roll();
	// проверка на пересечения клонированной фигуры с краем игрового поля или другими блоками.
	for (int i = 0; i < rolled->getCount(); i++) {
		if (!isBlockEmpty(rolled->getBlock(i).x, rolled->getBlock(i).y)) return; // встречается занятый блок
	}
	figure->Roll();
	delete rolled;
}

int Game::getScore()
{
	return score;
}

int Game::getLevel()
{
	return level;
}

void Game::SendDown()
{
	// Двигаем фигуры вниз, только если не упираемся в блоки
	bool connect = false;
	for (int i = 0; i < figure->getCount(); i++)
		if (!isBlockEmpty(figure->getBlock(i).x, figure->getBlock(i).y + 1))
			connect = true;
	if (!connect) figure->Down();
}
