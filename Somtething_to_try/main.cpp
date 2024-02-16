#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cstring>

struct character {
    std::string name = "unknown";
    int health = 0,
        armor = 0;
};

void take_damage(character& person, int damage) {
    std::cout << person.name << " took damage: - " << damage << std::endl;
    person.armor -= damage;

    if (person.armor < 0) {
        person.health += person.armor;
        person.armor = 0;
    }
}

// Серилизация
void save_character(std::ofstream& file, character& person) {
    int len = person.name.length();
    file.write((char*)&len, sizeof(len));
    file.write(person.name.c_str(), len);
    file.write((char*)&person.health, sizeof(person.health));
    file.write((char*)&person.armor, sizeof(person.armor));
}

// Десерилизация
void load_character(std::ifstream& file, character& person) {
    int len;
    file.read((char*)&len, sizeof(len));
    person.name.resize(len);
    file.read((char*)person.name.c_str(), len);
    file.read((char*)&person.health, sizeof(person.health));
    file.read((char*)&person.armor, sizeof(person.armor));
}

int main() {
/*    character person = {"Maximus", .health=100, .armor=20};

    person.armor = 30;

    character* person_ptr = &person;
    take_damage(person_ptr, 40);
    take_damage(&person, 20);

    std::cout << "Health: " << person.health << " Armor: " << person.armor << std::endl;*/

    character people[10];
/*

    for (int i = 0; i < 10; ++i) {
        people[i].name = "Character #" + std::to_string(i);
        people[i].health = (std::rand() % 100) + 100;
        people[i].armor = (std::rand() % 40) + 10;
    }

    for (int i = 0; i < 10; ++i) {
        take_damage(people[i], 30);
    }

*/

/*    std::ofstream file("save.bin", std::ios::binary);
    for (int i = 0; i < 10; ++i) {
        save_character(file, people[i]);
*/

    std::ifstream file("save.bin", std::ios::binary);
    for (int i = 0; i < 10; ++i) {
        load_character(file, people[i]);
    }

    for (int i = 0; i < 10; ++i) {
        std::cout << people[i].name << std::endl;
    }
}
