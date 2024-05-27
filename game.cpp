#include "game.h"


void Game2048::rotateGrid() {
    vector< vector<int> > newGrid(GRID_SIZE, vector<int>(GRID_SIZE, 0));

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++)
            newGrid[i][j] = grid[GRID_SIZE - j - 1][i];
    }

    grid = newGrid;
}


void Game2048::addRandomTile() {
    vector< pair<int, int> > emptyTiles;

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == 0) emptyTiles.push_back(make_pair(i, j)); // ���������� ������ ������
        }
    }

    if (!emptyTiles.empty()) {
        int index = rand() % emptyTiles.size(); // �������� ��������� ������ ������
        int value = (rand() % 10 == 0) ? 4 : 2; // � ������������ 10% �������� �������� 4, ����� 2
        grid[emptyTiles[index].first][emptyTiles[index].second] = value; // ������������� ������ �� ����
    }
}


bool Game2048::canMove() {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == 0) return true;
            if (i > 0 && grid[i][j] == grid[i - 1][j]) return true;
            if (i < GRID_SIZE - 1 && grid[i][j] == grid[i + 1][j]) return true;
            if (j > 0 && grid[i][j] == grid[i][j - 1]) return true;
            if (j < GRID_SIZE - 1 && grid[i][j] == grid[i][j + 1]) return true;
        }
    }
    return false;
}


bool Game2048::slide(vector<int>& row) {
    bool moved = false;
    int insertPos = 0;
    for (int i = 0; i < GRID_SIZE; i++) {
        if (row[i] != 0) {
            if (insertPos != i) {
                row[insertPos] = row[i]; // �������� ������
                row[i] = 0; // ����������� ������ �������
                moved = true;
            }
            insertPos++;
        }
    }
    return moved;
}


bool Game2048::combine(vector<int>& row) {
    bool moved = false;
    for (int i = 0; i < GRID_SIZE - 1; i++) {
        if (row[i] != 0 && row[i] == row[i + 1]) {
            row[i] *= 2; // ��������� �������� ������
            row[i + 1] = 0; // �������� ������ ������
            score += row[i];
            moved = true;
        }
    }
    return moved;
}


Game2048::Game2048() {
    grid.resize(GRID_SIZE, vector<int>(GRID_SIZE, 0));
    score = 0;
    addRandomTile();
    addRandomTile();
}


void Game2048::display() {
    system("cls");
    cout << "Score: " << score << endl;
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == 0) cout << setw(4) << ".";
            else cout << setw(4) << grid[i][j];
        }
        cout << endl;
    }
}


bool Game2048::move(Direction dir) {
    bool moved = false;

    for (int i = 0; i < GRID_SIZE; i++) {
        vector<int> row(GRID_SIZE);

        for (int j = 0; j < GRID_SIZE; j++) {
            switch (dir) {
            case UP:
                row[j] = grid[j][i]; // ��������� ������ ��������� �� �������
                break;
            case DOWN:
                row[j] = grid[GRID_SIZE - j - 1][i]; // ��������� ������ ��������� �� �������, � �������� �������
                break;
            case LEFT:
                row[j] = grid[i][j]; // ��������� ������ ��������� �� ������
                break;
            case RIGHT:
                row[j] = grid[i][GRID_SIZE - j - 1]; // ��������� ������ ��������� �� ������, � �������� �������
                break;
            }
        }

        moved |= slide(row); // �������� ������
        moved |= combine(row); // ���������� ������
        slide(row); // ��������� ����� ������ (���� ��������)

        for (int j = 0; j < GRID_SIZE; j++) {
            switch (dir) {
            case UP:
                grid[j][i] = row[j]; // ��������� ������� ���������� �� ������
                break;
            case DOWN:
                grid[GRID_SIZE - j - 1][i] = row[j]; // ��������� ������� ���������� �� ������, � �������� �������
                break;
            case LEFT:
                grid[i][j] = row[j]; // ��������� ������ ���������� �� ������
                break;
            case RIGHT:
                grid[i][GRID_SIZE - j - 1] = row[j]; // ��������� ������ ���������� �� ������, � �������� �������
                break;
            }
        }
    }

    if (moved) addRandomTile();

    return moved;
}


bool Game2048::isGameOver() { return !canMove(); }