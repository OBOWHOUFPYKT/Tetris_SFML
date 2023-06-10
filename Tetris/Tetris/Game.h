#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <array>

enum GameState { Play, End }; // ��������� ����

const int TEXTURE_COUNT = 5; // ����� ������� � ����

#include "figure.h"


struct Block { // ��������� ����� - ��� �������� � ������� ������� �����
	int texidx;
	bool empty;
};


class Game // �������� ����� ����
{
private:
	// ������� ����
	sf::Font font; // ����� 
	std::array<sf::Texture*, TEXTURE_COUNT> textures; // ������ ����� 

	
	GameState gamestate; // ��������� ����
	void loadFileTo(sf::Sprite& sprite, const std::string& filename); // ��������� ��������
	void drawSprite(sf::RenderTarget& target, sf::Sprite& sprite, int x, int y); // ���������� ���������
	// ����� ������
	void drawLabelW(sf::RenderTarget& target, const std::wstring& wstr, int x, int y, const sf::Font& font, int size,
		sf::Color color = sf::Color::White);

	// ��������� ������ �������

	double countdown; // ������ �� �������� ������ ���� �� ���
	Figure* figure; // ������� ������
	Block** blocks; // // ������ ������ ������� ��� ���������

	// ����, �������, ����� �����
	int score;
	int level;
	int lines;

	void ResetCountdown(); // ����� �������� �������
	
	void NextFigure(); // �������� ����� ������
	
	void TestAndShiftLine(); // �������� � �������� �����, ���� �����

public:
	Game(); // ����������� �� ��������� ��� �������� ������� ������ Game
	
	void Update(sf::RenderWindow& window, float dt); // ��������� ���������� ����
	
	void Render(sf::RenderWindow& window); // ��������� ������ ���� �� �����

	// ������� �������
	static int Width();
	static int Height();

	// ������������� ���������� � ������ � �� ��������� � ����.
	int getBlockTexIdx(int x, int y); // ��������� �������� ����� (� ������ ������)
	bool isBlockEmpty(int x, int y); // �������� ������� ����� (������ �������)
	bool isColored(int x, int y); // �������� ������� ����� � ����� (� ������ ������)

	// ������� ���� �������� � ��������
	void SendLeft();
	void SendRight();
	void SendDown();
	void SendRotate();

	// ��������� ������ ��� ������
	int getScore();
	int getLevel();
};

