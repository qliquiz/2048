#include "game.cpp"
#include <conio.h>


int main() {
    Game game;

    while (true) {
        game.show();

        if (game.isGameOver()) {
            cout << "Game Over!" << endl;
            break;
        }

        switch (_getch()) {
        case 72:
            game.move(UP);
            break;
        case 80:
            game.move(DOWN);
            break;
        case 75:
            game.move(LEFT);
            break;
        case 77:
            game.move(RIGHT);
            break;
        case 27:
            return 0;
        }
    }

    return 0;
}