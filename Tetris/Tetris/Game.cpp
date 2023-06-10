#include "Game.h"

#include "figurecube.h"
#include "figureline.h"
#include "figure4.h"
#include "figureg.h"

#define fontWay "data\\Arial.ttf" // ���� � ������
#define texWay "data\\tex" // ���� � ���������
#define texFormat ".png" // ������ �������
#define textPosXScore 20 // ������� ������ ������������ ����� �� �
#define textPosYScore 20 // ������� ������ ������������ ����� �� �
#define fontSizeScore 28 // ������ ������ ������ ������������ �����
#define textColorScore sf::Color::White // ���� ������ ������������ �����
#define textPosXLevel 20 // ������� ������ ������ ���� �� �
#define textPosYLevel 50 // ������� ������ ������ ���� �� �
#define fontSizeLevel 28 // ������ ������ ������ ������ ����
#define textColorLevel sf::Color::White // ���� ������ ������ ����
#define textPosXGameOver 20 // ������� ������ ����� ���� �� �
#define textPosYGameOver 80 // ������� ������ ����� ���� �� �
#define fontSizeGameOver 28 // ������ ������ ������ ����� ����
#define textColorGameOver sf::Color::Red // ���� ������ ����� ����
#define heightCupBlocks 15 // ������ �������� ���� � ������� ������
#define widthCupBlocks 10 // ������ �������� ���� � ������� ������
#define formulaInterval1 1.0f // ������������ ��� ������� ��������� ����� ���������� ������� ����
#define formulaInterval2 0.5f // ������������ ��� ������� ��������� ����� ���������� ������� ����
#define levelUp 10 // ���-�� ���������� ��� ��������� ������

// ������ ����� � ��������
const int SIZE = 64;

Game::Game() {
	font.loadFromFile(fontWay); // �������� ������

	// �������� ��������			
	for (int i = 0; i < TEXTURE_COUNT; i++) {
		textures[i] = new sf::Texture();
		textures[i]->loadFromFile(texWay+std::to_string(i)+texFormat);
	}

	// ������������� ��������� ����
	gamestate = Play;	

	// �������� ������� ������, ������� �� ���������
	blocks = new Block * [Width()];
	for (int i = 0; i < Width(); i++) {
		blocks[i] = new Block[Height()];
		for (int j = 0; j < Height(); j++)
			blocks[i][j].empty = true;
	}

	// ����� �������� � �������� ������ ��� ������������ ������� �� ���������� �������� ������
	ResetCountdown();
	NextFigure(); // ������� ����� ������, ������� ����� ������ � ������.
	// ��������� �����������, ������� 1 �� ������
	level = 1;
	score = 0;
	lines = 0;
}

void Game::Update(sf::RenderWindow& window, float dt)
{
	// � ����� ����� �������
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close(); // �������� ����

		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) window.close();			
			// ���� ���� �������, ��������� 
			if (gamestate == Play) {
				if (event.key.code == sf::Keyboard::Left) SendLeft();
				if (event.key.code == sf::Keyboard::Right) SendRight();
				if (event.key.code == sf::Keyboard::Up) SendRotate();
				if (event.key.code == sf::Keyboard::Down) SendDown();
			}

		}
	}

	// ���� ���� �������, �������� �����
	if (gamestate == Play) {
		countdown -= dt; //  ������� ����������� �� ��������, ������� ������������ ��������� ����� � ���������� �����.
		if (countdown <= 0) {
			ResetCountdown(); // ���������� �������� ��� ������������ ������� �� ���������� �������� ������.

			// ��������, ���������� �� ������ �� ������
			bool connect = false;
			for (int i = 0; i < figure->getCount(); i++) // �������� �� ������� ����� ������
				if (!isBlockEmpty(figure->getBlock(i).x, figure->getBlock(i).y + 1)) // ��������, �������� �� ���� ��� ������� ������
					connect = true;

			// ���� ��, �� ������������� � ������, ������� ����� ���� ���� � �������� ����� ������
			if (connect) {
				score += level; // ����������� ���� 
				for (int i = 0; i < figure->getCount(); i++) { // �������� �� ������� ����� ������
					blocks[figure->getBlock(i).x][figure->getBlock(i).y].texidx = figure->getTextureIdx();
					blocks[figure->getBlock(i).x][figure->getBlock(i).y].empty = false;
					// ������������� � ��������������� ���� ������� �������� � �������� ��� ��� ��������
				}
				TestAndShiftLine(); // ��������� � �������� ����������� ����� � �������.
				NextFigure(); // ������� ����� ������ ��� �������.
			}
			else
				figure->Down(); // ����� �������� ������ �� ���� ������ ����
		}
	}


}

void Game::Render(sf::RenderWindow& window) // ����������� ���� �� ������
{
	// ����� ������ � ���������� 	
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(SIZE, SIZE));
	for (int i = 0; i < Width(); i++)
		for (int j = 0; j < Height(); j++) { // �������� �� ������� ����� � ������� �������
			if (isColored(i, j)) { // ����� �� ������� ���� ��������, ����� ���� ��������� � ������� ������
				shape.setPosition(i * SIZE, j * SIZE); // ��������� ������������� ����� � ��������������� �� �������
				shape.setTexture(textures[getBlockTexIdx(i,j)]);
				window.draw(shape);
			}
		}

	// ����� ����� � ������
	drawLabelW(window, L"�����: "+std::to_wstring(getScore()), textPosXScore, textPosYScore, font, fontSizeScore, textColorScore);
	drawLabelW(window, L"�������: " + std::to_wstring(getLevel()), textPosXLevel, textPosYLevel, font, fontSizeLevel, textColorLevel);

	// ����� ����� ����
	if (gamestate == End)
		drawLabelW(window, L"���� ��������!", textPosXGameOver, textPosYGameOver, font, fontSizeGameOver, textColorGameOver);
}

void Game::loadFileTo(sf::Sprite& sprite, const std::string& filename) //  ��������� ������ �� ������ sf::Sprite � ��� ����� � �������� ����������. 
{ // �������� ��������� �� ������ sf::Texture:
	sf::Texture* tex = new sf::Texture(); // ������ sf::Texture ����� ����������� ��� �������� ����������� �������� �� �����.

	// �������� �������� �� �����
	tex->loadFromFile(filename); // ���� ����� ��������� ���������� ����� � ��������� ��� � ���������.

	// ��������� �������� � ������
	sprite.setTexture(*tex);	 // ��� ������������� ����������� �������� � ������, ����� �� ��� ���������� ���������� ��������.
}

void Game::drawSprite(sf::RenderTarget& target, sf::Sprite& sprite, int x, int y)
{ // ��������� ������ �� ������ sf::RenderTarget, ������ �� ������ sf::Sprite � ���������� x � y � �������� ����������.
	// ��������� ������� �������
	sprite.setPosition(x, y);// ��� ���������� ��������������, ��� ������ ����� ������������ �� ������.

	// ��������� ������� �� ������� �������
	target.draw(sprite); // ��� �������� � ��������� ������� �� ������ � �������� �������.
}

void Game::drawLabelW(sf::RenderTarget& target, const std::wstring& wstr, int x, int y, const sf::Font& font, int size,
	sf::Color color)// ��������� ������ �� ������ sf::RenderTarget, ������ �� ����������� ������ ���� std::wstring, ���������� x � y, ������ �� ����������� ������ sf::Font, ������ ������ size � ���� color � �������� ����������. 
{
	sf::Text text(wstr, font, size);//������������ �� ������ �����
	text.setPosition(x, y); // ������� ������
	text.setFillColor(color); // ���� ������
	target.draw(text); //��������� ������
}

void Game::ResetCountdown()// ����� �������� ���������� countdown, ������� ���������� �������� ������� ����� �������������� ��������� ������ ���� � ����
{//������� ������������ ��� ����������� ��������� �������, ������� ����� ��������� ����� ���������� ������ ����. 
	countdown = formulaInterval1 / (formulaInterval1 + formulaInterval2 * (double)level);
}//��� ���� ������� ����, ��� ������ ����� �������� ������� ����� ����������.

void Game::NextFigure()
{
	// ��������� �������� ������ 
	int fign = rand() % 4; // ���������� ��������� ����� �� 0 �� 3, ������� ����� �������������� ��� ������ ���� ������.
	//� ����������� �� �������� fign ��������� ����� ������ ������ ������������� ����.
	if (fign == 0) figure = new FigureLine(); else
		if (fign == 1) figure = new Figure4(); else
			if (fign == 2) figure = new FigureG();
			else
				figure = new FigureCube();

	
	// ���� ����� �������� ������ ��� �������� � ������� �������, �� ����� ����
	for (int i = 0; i < figure->getCount(); i++) // �������� ������� ����� ����� ������
		if (!isBlockEmpty(figure->getBlock(i).x, figure->getBlock(i).y)) // ���� ���� �� ���� ���� �� �������� ������ (������� ������� �������)
			gamestate = End; // ����� ����
}

void Game::TestAndShiftLine() // ��� �������� ����������� ����� � ������� ������ � �� ������ ����
{
	int y = Height() - 1; // ������ ������, ������� � ����� ������ ������ � ������� ������
	while (y > 0) {
		bool isfill = true;
		for (int x = 0; x < Width(); x++)

			//�������� ������� �����
			isfill = isfill && (!isBlockEmpty(x, y)); // ��������� �� ������� ������ y � ������� ������.
		if (isfill) {
			// ����� ���� ������ ���� ����������� ����� ����
			for (int j = y; j > 0; j--)
				for (int x = 0; x < Width(); x++) // ���������� ������ ���� ����������� ������
					blocks[x][j] = blocks[x][j - 1];
			// ������� ������� ������
			for (int x = 0; x < Width(); x++)
				blocks[x][0].empty = true;
			// ���������� �������� ����������� �����
			lines++;
			// ��������, ��������� �� ����� ����������� ����� ��� ��������� ������
			if (lines == levelUp) {
				level++;
				lines = 0;
			}
		}
		else
			y--; // ������� � �������� ���������� ������ � ������� ������.
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
	// ������� ��������(������) �����, ���� �� �� ������
	if (!blocks[x][y].empty) return blocks[x][y].texidx;

	// ��� ������ 
	for (int i = 0; i < figure->getCount(); i++)// ������� ������ ������� ������
		if ((figure->getBlock(i).x == x) && (figure->getBlock(i).y == y)) // ���� ����������� ������� ������?
			return figure->getTextureIdx(); // ������� ������� �������� ������

	return -1; // ����� ������
}

bool Game::isBlockEmpty(int x, int y)// ��������� ���� �� �������
{
	if (y >= Height()) return false;
	if (x < 0) return false;
	if (x >= Width()) return false;
	return blocks[x][y].empty;
}

bool Game::isColored(int x, int y)
{
	// �������� ������� �����
	if (!blocks[x][y].empty) return true;
	// ��� ������
	for (int i = 0; i < figure->getCount(); i++)
		if ((figure->getBlock(i).x == x) && (figure->getBlock(i).y == y))
			return true;
	return false;
}

void Game::SendLeft()
{
	// ��������, ���� ��� ����������� � ����� ��� �������
	bool connect = false;
	for (int i = 0; i < figure->getCount(); i++)
		if (!isBlockEmpty(figure->getBlock(i).x - 1, figure->getBlock(i).y)) // �������� �� ���� ����� �� �������� ����� ������
			connect = true; // ������� �����������
	if (!connect) figure->Left(); // ����������� ������ �����.
}

void Game::SendRight()
{
	// ��������, ���� ��� ����������� � ����� ��� �������
	bool connect = false;
	for (int i = 0; i < figure->getCount(); i++)
		if (!isBlockEmpty(figure->getBlock(i).x + 1, figure->getBlock(i).y))
			connect = true;
	if (!connect) figure->Right();
}

void Game::SendRotate()
{
	// �������, ���� ��� ����������� � ����� ��� �������
	// ��������� �� ����� ������, ����������� ��� ������ �������� ������
	Figure* rolled = figure->Clone();
	rolled->Roll();
	// �������� �� ����������� ������������� ������ � ����� �������� ���� ��� ������� �������.
	for (int i = 0; i < rolled->getCount(); i++) {
		if (!isBlockEmpty(rolled->getBlock(i).x, rolled->getBlock(i).y)) return; // ����������� ������� ����
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
	// ������� ������ ����, ������ ���� �� ��������� � �����
	bool connect = false;
	for (int i = 0; i < figure->getCount(); i++)
		if (!isBlockEmpty(figure->getBlock(i).x, figure->getBlock(i).y + 1))
			connect = true;
	if (!connect) figure->Down();
}
