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

building_type defineBuildingType(int numberOfType) {
    switch (numberOfType) {
        case 1:
            return house;
        case 2:
            return garage;
        case 3:
            return barn;
        case 4:
            return bathhouse;
        default:
            return house;
    }
}

enum room_type {
    bedroom,
    kitchen,
    bathroom,
    children,
    living
};

room_type defineRoomType(int numberOfType) {
    switch (numberOfType) {
        case 1:
            return bedroom;
        case 2:
            return kitchen;
        case 3:
            return bathroom;
        case 4:
            return children;
        case 5:
            return living;
        default:
            return bedroom;
    }
}

// Structures to define floors in house

struct Room {
    float square = 0;
    room_type type = bedroom;

    Room() {
        // Creating var
        int numberOfType;

        // Requesting type of the room
        std::cout << "Insert type of room by number:\n" <<
                  "  1 - bedroom,\n" <<
                  "  2 - kitchen,\n" <<
                  "  3 - bathroom,\n" <<
                  "  4 - children's room,\n" <<
                  "  5 - living room.\n\n";

        std::cin >> numberOfType;

        this->type = defineRoomType(numberOfType);

        // Requesting square of the room
        std::cout << "Insert square of current room:\n";
        std::cin >> this->square;

    };
};

struct Floor {
    std::vector<Room> rooms;
    float ceilingHeight = 0;

    Floor() {
        // Requesting ceiling height
        std::cout << "Insert ceiling height of current floor:\n";
        std::cin >> this->ceilingHeight;

        // Creating var
        int amount = 0;

        while (amount < 2 || amount > 4) {
            // Requesting amount of floors in the house
            std::cout << "Insert amount of rooms that are in the floor. There must be amount between 2 and 4 floors:\n";
            std::cin >> amount;
            std::cout << "\n\n";
        }

        // Creating cycle to fill the vector
        for (int i = 0; i < amount; ++i) {
            std::cout << i+1 << " room:\n\n";
            Room room;
            rooms.push_back(room);
        }
    }
};

// Structures of buildings

struct Building {
    building_type type;
    float square = 0;
    std::vector<Floor> floors;
    bool isThereAStove = false;

    Building() {
        // Creating var
        int numberOfType;

        // Requesting type of the building
        std::cout << "Insert type of building by number:\n" <<
                    "  1 - house,\n" <<
                    "  2 - garage,\n" <<
                    "  3 - barn,\n" <<
                    "  4 - bathhouse.\n\n";

        std::cin >> numberOfType;
        std::cout << "\n\n";

        this->type = defineBuildingType(numberOfType);

        // Requesting square of the building
        std::cout << "Insert square of current building:\n";
        std::cin >> this->square;

        // Requesting info about the stove
        if (this->type == house || this->type == bathhouse) {
            std::cout << "Is there a stove in the building? Choose the number:\n" <<
                        "  1 - yes,\n" <<
                        "  0 - no.\n";
            std::cin >> this->isThereAStove;
            std::cout << "\n\n";
        }

        // Requesting info about floors
        if (this->type == house) {
            // Creating var
            int amount = 0;

            while (amount < 1 || amount > 3) {
                // Requesting amount of floors in the house
                std::cout << "Insert amount of floors that are in the house. There must be amount between 1 and 3 floors:\n";
                std::cin >> amount;
                std::cout << "\n\n";
            }

            // Creating cycle to fill the vector
            for (int i = 0; i < amount; ++i) {
                std::cout << i+1 << " floor\n\n";
                Floor floor;
                floors.push_back(floor);
            }
        }
    };
};


// Structure of plot
struct Plot {
    int number = 0;
    float square = 0;
    std::vector<Building> buildings;
    float percentageOfPlotOccupiedByBuildings = 0;

    Plot() {
        // Requesting square of the building
        std::cout << "Insert number of plot:\n";
        std::cin >> this->number;


        // Requesting square of the plot
        std::cout << "Insert square of " << this->number << " plot:\n";
        std::cin >> this->square;


        // Creating var
        int amount;

        // Requesting amount of buildings in the plot
        std::cout << "Insert amount of buildings that are in the plot:\n";
        std::cin >> amount;
        std::cout << "\n\n";

        // Creating cycle to fill the vector
        for (int i = 0; i < amount; ++i) {
            std::cout << "Building " << i+1 << ":\n\n";
            Building building;
            percentageOfPlotOccupiedByBuildings += building.square / (this->square / 100);
            buildings.push_back(building);
        }
    };
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

        // Creating plots in the village
        this->set_plots();
    };

    void set_plots() {
        // Creating var
        int amount;

        // Requesting amount of plots in this village
        std::cout << "Insert amount of plots that are in " << this->name << " village:\n";
        std::cin >> amount;
        std::cout << "\n\n";

        // Creating cycle to fill the vector
        for (int i = 0; i < amount; ++i) {
            std::cout << "Filling information about " << i+1 << " plot:\n\n";
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

    return 0;
}
