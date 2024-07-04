#include <iostream>
#include <string>
#include <ctime>
#include <vector>

bool isGameEnded = false;


struct Character {
    std::string name;
    int health = 0,
        armor = 0,
        damage = 0,
        x = 0,
        y = 0;

    Character() {}

    Character(int number) {
        if (number == 0) {
            std::cout << "Insert name of your character:\n";
            std::cin >> this->name;
        } else
            this->name = "Enemy #" + std::to_string(number);

        std::srand(std::time(nullptr));

        this->health = 50 + rand() % 101;
        this->armor = rand() % 51;
        this->damage = 15 + rand() % 16;
        Character isFieldBusy = NULL;
        do {
            this->x = rand() % 20;
            this->y = rand() % 20;
            isFieldBusy = map[this->x][this->y];
            if (isFieldBusy == NULL)
                map[this->x][this->y] = this;
        } while (isFieldBusy != NULL);
            
    }
};




Character player(0);
Character map[20][20];


void create_enemies() {
    for (int i = 1; i < 6; ++i) {
        Character enemy(i);
    }
}

void filling_map() {
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            map[i][j] = NULL;
        }
    }
}

void map_output() {
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            if (map[i][j] == player)
                std::cout << ".";
            else {
                if (player.x == i && player.y == j)
                    std::cout << "P";
                else
                    std::cout << "E";
            }
        }
        std::cout << "\n";
    }

    std::cout << "\n\n";
}

void create_new_game() {
    filling_map();
    create_enemies();
}

int main() {
    create_new_game();
    std::cout << "\n\n";
    do {
        map_output();
        std::cout << "smth";
        isGameEnded = true;
    } while(!isGameEnded);
}
