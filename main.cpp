#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();

    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    bool running = true; //Main menu loop
    while (running) {
        int choice = main_menu();
        switch (choice) {
            case 1:
                add_goat(trip, names, colors);
                break;
            case 2:
                delete_goat(trip);
                break;
            case 3:
                display_trip(trip);
                break;
            case 4;
                cout << "Goodbye\n";
                running = false;
                break;
            default:
                cout << "Invalid choice. Try again.\n";

        }

    }

    return 0;
}

int main_menu() { // Main menu display and returns user's choices
    int choice;
    cout << "\n*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Quit\n";
    cout << "Choice --> ";
    cin >> choice;
    cout << endl;
    return choice;

}

void add_goat(list<Goat> &trip, string names[], string colors[]) { // Random goat gets added
    int randname = rand() % SZ_NAMES;
    int randColor = rand() % SZ_COLORS;
    int randAge = rand() % (MAX_AGE + 1);

    string name = names[randName];
    string color = colors[randColor];
    Goat g(name, randAge, color);

    trip.push_back(g);
    trip.sort();

    cout << "Added: " << g << endl;

}

void display_trip(const list<Goat> &trip) { // Displays all goats on the trip (or none)
    if (trip.empty()) {
        cout << "No goats on the trip.\n";
        return;
    }

    cout << "Current Goat Trip:\n";
    int i = 1;
    for (const Goat &g : trip) {
        cout << setw(3) << "[" << i++ << "] " << g << endl;

    }

}


int select_goat(const list<Goat> &trip) { // Allows user to choose a goat from the list
    if (trip.empty()) {
        cout << "No goats available.\n";
        return -1;

    }

    display_trip(trip);
    int choice;
    cout << "Select a goat # to delete: ";
    cin >> choice;
    return choice;
}

void delete_goat(list<Goat> &trip) { // Deletes a goat from the list
    if (trip.empty()) {
        cout << "No goats to delete.\n";
        return;
    }

    int choice = select_goat(trip);
    if (choice < 1 || choice > (int)trip.size()) {
        cout << "Invalid choice.\n";
        return;

    }

    auto it = trip.begin();
    advance(it, choice - 1);
    cout << "Deleting: " << *it << endl;
    trip.erase(it);

}
