#include <iostream>
#include <vector>
#include <string>

// Enumerators of rooms and buildings

enum building_type {
    house,
    garage,
    barn,
    bathhouse
};

enum room_type {
    bedroom,
    kitchen,
    bathroom,
    children,
    living
};

// Structures to define floors in house

struct Room {
    float square = 0;
    room_type type = bedroom;
};

struct Floor {
    std::vector<Room> rooms;
    float ceililngHeight = 0;
};

// Structures of buildings

struct Building {
    float square = 0;
};

struct House : Building {
    std::vector<Floor> floors;
    bool isThereAStove = false;
};

struct Garage : Building { };

struct Barn : Building { };

struct Bathhouse : Building {
    bool isThereAStove = false;
};


// Structure of plot
struct Plot {
    House house;
    Garage garage;
    Barn barn;
    Bathhouse bathhouse;
};


// Structure of village
struct Village {
    std::string name;
    std::vector<Plot> plots;

    Village() {
        // Creating a name
        std::cout << "Insert the name of the village\n";
        std::cin >> this->name;
        std::cout << "\n\n";
    };

    void set_plots() {
        // Creating var
        int amount;

        // Requesting amount of plots in this village
        std::cout << "Insert amount of plots that are in " << this->name << " village\n";
        std::cin >> amount;
        std::cout << "\n\n";

        // Creating cycle to fill the vector
        for (int i = 0; i < amount; ++i) {
            Plot plot;
            plots.push_back(plot);
        }
    };
};


int main() {
    // Greeting
    std::cout << "\tVillage\n\n" << std::endl;

    // Creating var
    Village village;

    // Creating plots in the village
    village.set_plots();

    return 0;
}
