#include <iostream>
#include <string>
#include <ctime>
#include <vector>

bool map[20][20],
    isGameEnded = false;


struct Character {
    std::string name;
    int health = 0,
        armor = 0,
        damage = 0,
        x = 0,
        y = 0;

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
        bool isFieldBusy = false;
        do {
            this->x = rand() % 20;
            this->y = rand() % 20;
            isFieldBusy = map[this->x][this->y];
            if (!isFieldBusy)
                map[this->x][this->y] = true;
        } while(isFieldBusy);
    }
};

Character player(0);
std::vector<Character> enemies;



void create_enemies() {
    for (int i = 1; i < 6; ++i) {
        Character enemy(i);
        enemies.push_back(enemy);
    }
}

void filling_map() {
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            map[i][j] = false;
        }
    }
}

void map_output() {
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            if (!map[i][j])
                std::cout << "_";
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
    map[player.x][player.y] = true;
    create_enemies();
}

bool isFieldExisting(int x, int y) {
    return x >= 0 && y >= 0 && x < 20 && y < 20;
}


void characterMove() {
    bool canMoveBeDone = false;
    do {
        char move = 'N';
        std::cout << "Make a move!\n"
                    << "Type in the direction:\n"
                    << "'R' - to go right,\n"
                    << "'L' - to go left,\n"
                    << "'U' - to go up,\n"
                    << "'D' - to go down.\n\n";

        std::cout << "Your move: ";
        std::cin >> move;
        std::cout << "\n";
        
        int moveX = player.x,
            moveY = player.y;
        
        switch (move) {
            case 'R':
                if (isFieldExisting(moveX, moveY + 1)) {
                    moveY += 1;
                    canMoveBeDone = true;
                }
                break;
            case 'L':
                if (isFieldExisting(moveX, moveY - 1)) {
                    moveY -= 1;
                    canMoveBeDone = true;
                }
                break;
            case 'U':
                if (isFieldExisting(moveX - 1, moveY)) {
                    moveX -= 1;
                    canMoveBeDone = true;
                }
                break;
            case 'D':
                if (isFieldExisting(moveX + 1, moveY)) {
                    moveX += 1;
                    canMoveBeDone = true;
                }
                break;
            default:
                canMoveBeDone = false;
        }
        
        if (!canMoveBeDone) {
            std::cout << "You may not go in " << move << " direction!\n"
                        << "Try again!\n\n";
        }
        
            // Checking if there is an enemy on the field where we move
        if (map[moveX][moveY]) {
            int indexOfEnemy = -1;
            for (int i = 0; i < enemies.size(); ++i) {
                if (enemies.at(i).x == moveX &&
                    enemies.at(i).y == moveY) {
                    indexOfEnemy = i;
                    break;
                }
            }

            Here we must do damage to the enemy
        } else {
            Here we must do a move to the field
        }

        
    } while (!canMoveBeDone);
}

int main() {
    create_new_game();
    std::cout << "\n\n";
    do {
        map_output();
        std::cout << "smth";
        characterMove();
        isGameEnded = true;
    } while(!isGameEnded);
}

