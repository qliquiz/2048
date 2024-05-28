#include "game.h"


void Game::addTile() {
    vector< pair<int, int> > emptyTiles;

    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            if (field[i][j] == 0) emptyTiles.push_back(make_pair(i, j)); // запоминаем пустые клетки
        }
    }

    if (!emptyTiles.empty()) {
        int index = rand() % emptyTiles.size(); // выбираем случайную пустую клетку
        int value = (rand() % 10 == 0) ? 4 : 2; // с вероятностью 10% выбираем значение 4, иначе 2
        field[emptyTiles[index].first][emptyTiles[index].second] = value; // устанавливаем плитку на поле
    }
}


bool Game::isMovable() {
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            if (field[i][j] == 0) return true;
            if (i > 0 && field[i][j] == field[i - 1][j]) return true;
            if (i < FIELD_SIZE - 1 && field[i][j] == field[i + 1][j]) return true;
            if (j > 0 && field[i][j] == field[i][j - 1]) return true;
            if (j < FIELD_SIZE - 1 && field[i][j] == field[i][j + 1]) return true;
        }
    }
    return false;
}


bool Game::shift(vector<int>& row) {
    bool moved = false;
    int insertPos = 0;
    for (int i = 0; i < FIELD_SIZE; i++) {
        if (row[i] != 0) {
            if (insertPos != i) {
                row[insertPos] = row[i]; // сдвигаем плитку
                row[i] = 0; // освобождаем старую позицию
                moved = true;
            }
            insertPos++;
        }
    }
    return moved;
}


bool Game::merge(vector<int>& row) {
    bool moved = false;
    for (int i = 0; i < FIELD_SIZE - 1; i++) {
        if (row[i] != 0 && row[i] == row[i + 1]) {
            row[i] *= 2; // удваиваем значение плитки
            row[i + 1] = 0; // обнуляем вторую плитку
            score += row[i];
            moved = true;
        }
    }
    return moved;
}


Game::Game() {
    field.resize(FIELD_SIZE, vector<int>(FIELD_SIZE, 0));
    score = 0;
    addTile();
    addTile();
}


void Game::show() {
    system("cls");
    cout << "Score: " << score << endl;
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            if (field[i][j] == 0) cout << "  .";
            else cout << "  " << field[i][j];
        }
        cout << endl;
    }
}


bool Game::move(Direction dir) {
    bool moved = false;

    for (int i = 0; i < FIELD_SIZE; i++) {
        vector<int> row(FIELD_SIZE);

        for (int j = 0; j < FIELD_SIZE; j++) {
            switch (dir) {
            case UP:
                row[j] = field[j][i]; // заполняем строку значением из столбца
                break;
            case DOWN:
                row[j] = field[FIELD_SIZE - j - 1][i]; // заполняем строку значением из столбца, в обратном порядке
                break;
            case LEFT:
                row[j] = field[i][j]; // заполняем строку значением из строки
                break;
            case RIGHT:
                row[j] = field[i][FIELD_SIZE - j - 1]; // заполняем строку значением из строки, в обратном порядке
                break;
            }
        }

        moved |= shift(row); // сдвигаем плитки
        moved |= merge(row); // объединяем плитки
        shift(row); // повторный сдвиг плиток (если возможно)

        for (int j = 0; j < FIELD_SIZE; j++) {
            switch (dir) {
            case UP:
                field[j][i] = row[j]; // обновляем столбец значениями из строки
                break;
            case DOWN:
                field[FIELD_SIZE - j - 1][i] = row[j]; // обновляем столбец значениями из строки, в обратном порядке
                break;
            case LEFT:
                field[i][j] = row[j]; // обновляем строку значениями из строки
                break;
            case RIGHT:
                field[i][FIELD_SIZE - j - 1] = row[j]; // обновляем строку значениями из строки, в обратном порядке
                break;
            }
        }
    }

    if (moved) addTile();

    return moved;
}


bool Game::isGameOver() { return !isMovable(); }