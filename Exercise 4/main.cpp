#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <time.h>
#include <fstream>

bool map[20][20],
    isGameEnded = false;
int moveCounter = 0;
std::string logOfTurn = "";

struct Character {
    std::string name;
    bool isDead = false;
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

    void Damage(Character* person) {
        person->armor -= this->damage;

        if (person->armor < 0) {
            person->health += person->armor;
            person->armor = 0;
        }

        logOfTurn += this->name + " damaged " + person->name + " on " + std::to_string(this->damage) + " units!\n";
        logOfTurn += "Stats of " + person->name + ": [A:" + std::to_string(person->armor) + ", H: " + std::to_string(person->health) + "]\n";
    }

    void Move(int newX, int newY) {
        map[this->x][this->y] = false;
        logOfTurn += this->name + " moved to " + std::to_string(newX) + "-" + std::to_string(newY) + "! (was on " + std::to_string(this->x) + "-" + std::to_string(this->y) + ")\n";  
        this->x = newX;
        this->y = newY;
        map[newX][newY] = true;
    }

    void Save(std::ofstream& file) {
        int len = this->name.length();
        file.write((char*)&len, sizeof(len));
        file.write(this->name.c_str(), len);
        file.write((char*)&this->isDead, sizeof(this->isDead));
        file.write((char*)&this->health, sizeof(this->health));
        file.write((char*)&this->armor, sizeof(this->armor));
        file.write((char*)&this->damage, sizeof(this->damage));
        file.write((char*)&this->x, sizeof(this->x));
        file.write((char*)&this->y, sizeof(this->y));
    }

    void Load(std::ifstream& file) {
        int len;
        file.read((char*)&len, sizeof(len));
        this->name.resize(len);
        file.read((char*)this->name.c_str(), len);
        file.read((char*)&this->isDead, sizeof(this->isDead));
        file.read((char*)&this->health, sizeof(this->health));
        file.read((char*)&this->armor, sizeof(this->armor));
        file.read((char*)&this->damage, sizeof(this->damage));
        file.read((char*)&this->x, sizeof(this->x));
        file.read((char*)&this->y, sizeof(this->y));
        map[this->x][this->y] = true;
    }
};



void FillingMapWithNothing() {
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            map[i][j] = false;
        }
    }
}

void SaveProgress() {
    std::ofstream file("save.bin", std::ios::binary);
    file.write((char*)& moveCounter, sizeof(moveCounter));
    player.Save(file);
    for (int i = 0; i < enemies.size(); i++) {
        enemies.at(i).Save(file);
    }
    std::cout << "Progress saved!\n\n";
    file.close();
}

void LoadProgress() {
    FillingMapWithNothing();
    std::ifstream file("save.bin", std::ios::binary);
    file.read((char*)&moveCounter, sizeof(moveCounter));
    player.Load(file);
    for (int i = 0; i < enemies.size(); i++) {
        enemies.at(i).Load(file);
    }
    std::cout << "Progress loaded!\n\n";
    file.close();
}

void CreateEnemies() {
    for (int i = 1; i < 6; ++i) {
        Character enemy(i);
    }
}

void MapOutput() {
    std::cout << "-------Move#" << moveCounter << "-------\n";

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
    
    std::cout << "--------------------\n\n";
}

void CreateNewGame() {
    FillingMapWithNothing();
    map[player.x][player.y] = true;
    CreateEnemies();
}

bool IsFieldExisting(int x, int y) {
    return x >= 0 && y >= 0 && x < 20 && y < 20;
}

void CheckIfPersonIsDead(Character* person) {
    if (person->health <= 0) {
        person->isDead = true;
        if (person->name.find("Enemy") != std::string::npos) {
            map[person->x][person->y] = false;
        } else {
            isGameEnded = true;
        }

        logOfTurn += person->name + " is dead!\n";
    }
}

void DefineFieldToMove(Character* person, char direction, int& moveX, int& moveY) {
    moveX = person->x;
    moveY = person->y;

    switch (direction) {
            case 'R':
                moveY += 1;
                break;
            case 'L':
                moveY -= 1;
                break;
            case 'U':
                moveX -= 1;
                break;
            case 'D':
                moveX += 1;
                break;
            default:
                moveX = 0;
                moveY = 0;
    }
}

int SearchIndexOfEnemy(int x, int y) {
    for (int i = 0; i < enemies.size(); ++i) {
        if (enemies.at(i).x == x && enemies.at(i).y == y && (!enemies.at(i).isDead)) {
            return i;
        }
    }

    return -1;
}

std::string RequestAction() {
    std::string action = "";

    std::cout << "Make a move!\n"
                    << "Type in the direction:\n"
                    << "'U' - to go up,\n"
                    << "'R' - to go right,\n"
                    << "'D' - to go down,\n"
                    << "'L' - to go left.\n\n";
    std::cout << "Also you may type:\n" 
                    << "'save' to save game,\n"
                    << "'load' to load game.\n\n";

    std::cout << "Your action: ";
    std::cin >> action;
    std::cout << "\n";

    return action;
}

bool IsActionSaveOrLoad(std::string action) {
    return action == "save" || action == "load"; 
}

void DeclineMove(char direction) {
    std::cout << "You may not go in " << direction << " direction!\n"
                        << "Try again!\n\n";
    MapOutput();
}

bool IsSomebodyInField(int x, int y) {
    return map[x][y];
}

void ActivateAction(std::string action) {
    if (action == "save") {
        SaveProgress();
    } else {
        LoadProgress();
    }
    MapOutput();
}

void PlayerMove() {
    bool canMoveBeDone;
    do {
        int moveX, moveY;
        canMoveBeDone = false;

        std::string action = RequestAction();
        char direction;

        if (IsActionSaveOrLoad(action)) {
            ActivateAction(action);
            continue;
        }
        
        direction = action[0];

        DefineFieldToMove(&player, direction, moveX, moveY);
        canMoveBeDone = IsFieldExisting(moveX, moveY);

        if (!canMoveBeDone) {
            DeclineMove(direction);
            continue;
        }
        
        if (IsSomebodyInField(moveX, moveY)) {
            int indexOfEnemy = SearchIndexOfEnemy(moveX, moveY);
            player.Damage(&enemies.at(indexOfEnemy));
            CheckIfPersonIsDead(&enemies.at(indexOfEnemy));
        } else {
            player.Move(moveX, moveY);
        }
    } while (!canMoveBeDone);
}

char GetRandomDirection() {
    std::string directions = "URDL";

    int randomIndex = rand() % 4;
    
    return directions[randomIndex]; 
}

bool IsPlayerInField(int x, int y) {
    return x == player.x && y == player.y;
}

void EnemiesMove() {
    bool canMoveBeDone;
    for (int i = 0; i < enemies.size(); i++) {
        if (enemies.at(i).isDead) continue;
        canMoveBeDone = false;

        do {
            int moveX, moveY;
            char direction = GetRandomDirection();
            DefineFieldToMove(&enemies.at(i), direction, moveX, moveY);
            canMoveBeDone = IsFieldExisting(moveX, moveY);

            if (!canMoveBeDone) {
                continue;
            } 
                
            if (IsSomebodyInField(moveX, moveY)) {
                if (IsPlayerInField(moveX, moveY)) {
                    enemies.at(i).Damage(&player);
                    CheckIfPersonIsDead(&player);
                } else {
                    logOfTurn += enemies.at(i).name + " has done nothing.\n";
                }
            } else {
                enemies.at(i).Move(moveX, moveY);
            }
        } while (!canMoveBeDone);
    }
}

void LogOutput() {
    std::cout << "||||||||||||||||Turn#" << moveCounter << "||||||||||||||||\n";
    std::cout << logOfTurn;
    std::cout << "||||||||||||||||||||||||||||||||||||||\n\n\n";
    logOfTurn = "";
}

void TurnOfGame() {
    MapOutput();
    PlayerMove();
    EnemiesMove();
    LogOutput();
    moveCounter++;
    logOfTurn = "";
}

void ShowGameOverScreen() {
    std::cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n";
    std::cout << "\tGame over!\n";
    std::cout << "\t";
    if (!player.isDead) {
        std::cout << "You have won!";
    } else {
        std::cout << "You've lost.";
    }
    std::cout << "\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n";
}

void PlayGame() {
    CreateNewGame();
    std::cout << "\n\n";

    do {
        TurnOfGame();
    } while (!isGameEnded);

    ShowGameOverScreen();
}

int main() {
    std::srand(time(0));
    PlayGame();
}