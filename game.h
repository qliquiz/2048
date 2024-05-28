#ifndef _GAME_H_
#define _GAME_H_
#define FIELD_SIZE 4
#include <iostream>
#include <vector>
#include <cstdlib>


using namespace std;


enum Direction { UP, DOWN, LEFT, RIGHT };


class Game {
    vector< vector<int> > field; // поле
    int score; // счёт

    void addTile(); // добавление случайной плитки (2 либо 4)
    bool isMovable(); // проверяет возможность совершить ход
    bool shift(vector<int>& row); // перемещает непустые элементы в начало строки, оставляя пустые (нули) в конце
    bool merge(vector<int>& row); // объединяет соседние одинаковые элементы, удваивая значение и добавляя к счету игрока

public:
    Game(); // конструктор

    void show(); // вывод в консоль
    bool move(Direction dir); // движение в сторону
    bool isGameOver(); // проверяет конец игры
};


#endif