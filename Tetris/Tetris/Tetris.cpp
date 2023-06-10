#include <SFML\Graphics.hpp>
#include <SFML\System\Clock.hpp>
#include <SFML\Window\Keyboard.hpp>
#include <SFML\Window\Mouse.hpp>
#include "Game.h"

// Подключаем SFML
#pragma comment (lib, "lib\\sfml-window.lib")
#pragma comment (lib, "lib\\sfml-system.lib")
#pragma comment (lib, "lib\\sfml-graphics.lib")
#pragma comment (lib, "lib\\sfml-main.lib")

#define winWidth 640 // ширина окна
#define winHeight 960 // высота окна
#define fps 60

int main()
{
    // Создаем окно
    sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Tetris");
    window.setVerticalSyncEnabled(true); // вертикальная синхронизация
    window.setFramerateLimit(fps); // ограничение частоты кадров

    srand(time(NULL));// генератор случайных чисел
    // Игра и часы
    Game game;
    sf::Clock clock;
    float lasttime = clock.getElapsedTime().asSeconds();
    // Запуск главного цикла игры
    while (window.isOpen()) {
        // В каждой итерации цикла происходит обновление состояния игры 
        float newtime = clock.getElapsedTime().asSeconds();
        game.Update(window, newtime - lasttime);
        lasttime = newtime;
        // Разница времени между текущим и предыдущим тактами сохраняется в переменную newtime, а затем передается в метод Update в качестве параметра dt.

        // Выводим игру на экран
        window.clear(); // очистка окна
        game.Render(window); // вызов игры на экран
        window.display(); // изменения на экране
    }
    return 0;
}

