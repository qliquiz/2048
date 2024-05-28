#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip> // для форматирования вывода
#define FIELD_SIZE 4
#ifndef GAME_H
#define GAME_H


using namespace std;


enum Direction { UP, DOWN, LEFT, RIGHT };


class Game {
    vector< vector<int> > field;
    int score;

    void addTile();
    bool isMovable();
    bool shift(vector<int>& row); // перемещает непустые элементы в начало строки, оставляя пустые (нули) в конце
    bool merge(vector<int>& row); // объединяет соседние одинаковые элементы, удваивая значение и добавляя к счету игрока

public:
    Game();

    void show();
    bool move(Direction dir);
    bool isGameOver();
};


#endif