#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip> // для форматирования вывода
#ifndef GAME_H
#define GAME_H


using namespace std;


const int GRID_SIZE = 4;


enum Direction { UP, DOWN, LEFT, RIGHT };


class Game2048 {
    vector< vector<int> > grid;
    int score;

    void addRandomTile();
    void rotateGrid(); // поворачивает сетку на 90 градусов по часовой стрелке
    bool canMove();
    bool slide(vector<int>& row); // перемещает непустые элементы в начало строки, оставляя пустые (нули) в конце
    bool combine(vector<int>& row); // объединяет соседние одинаковые элементы, удваивая значение и добавляя к счету игрока

public:
    Game2048();

    void display();
    bool move(Direction dir);
    bool isGameOver();
};


#endif