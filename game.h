#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip> // ��� �������������� ������
#ifndef GAME_H
#define GAME_H


using namespace std;


const int GRID_SIZE = 4;


enum Direction { UP, DOWN, LEFT, RIGHT };


class Game2048 {
    vector< vector<int> > grid;
    int score;

    void addRandomTile();
    void rotateGrid(); // ������������ ����� �� 90 �������� �� ������� �������
    bool canMove();
    bool slide(vector<int>& row); // ���������� �������� �������� � ������ ������, �������� ������ (����) � �����
    bool combine(vector<int>& row); // ���������� �������� ���������� ��������, �������� �������� � �������� � ����� ������

public:
    Game2048();

    void display();
    bool move(Direction dir);
    bool isGameOver();
};


#endif