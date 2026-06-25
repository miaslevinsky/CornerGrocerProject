/*
 * CS 210 Project Three
 * Corner Grocer Item Tracking Program
 */

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <limits>

using namespace std;

class GroceryTracker {
private:
    map<string, int> itemFrequency;

public:
    void LoadItemsFromFile(string fileName) {
        ifstream inputFile(fileName);
        string item;

        if (!inputFile.is_open()) {
            cout << "Error: Could not open input file." << endl;
            return;
        }

        while (inputFile >> item) {
            itemFrequency[item]++;
        }

        inputFile.close();
    }

    void CreateBackupFile(string fileName) {
        ofstream outputFile(fileName);

        for (const auto& pair : itemFrequency) {
            outputFile << pair.first << " " << pair.second << endl;
        }

        outputFile.close();
    }

    int GetItemFrequency(string itemName) {
        if (itemFrequency.count(itemName)) {
            return itemFrequency[itemName];
        }

        return 0;
    }

    void PrintAllFrequencies() {
        for (const auto& pair : itemFrequency) {
            cout << pair.first << " " << pair.second << endl;
        }
    }

    void PrintHistogram() {
        for (const auto& pair : itemFrequency) {
            cout << pair.first << " ";

            for (int i = 0; i < pair.second; ++i) {
                cout << "*";
            }

            cout << endl;
        }
    }
};

void DisplayMenu() {
    cout << endl;
    cout << "Corner Grocer Item Tracking Menu" << endl;
    cout << "1. Search for an item frequency" << endl;
    cout << "2. Print all item frequencies" << endl;
    cout << "3. Print item frequency histogram" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    GroceryTracker tracker;
    int choice;
    string itemName;

    tracker.LoadItemsFromFile("CS210_Project_Three_Input_File.txt");

    // Creates backup file automatically at the beginning of the program
    tracker.CreateBackupFile("frequency.dat");

    do {
        DisplayMenu();

        while (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number from 1 to 4: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
        case 1:
            cout << "Enter the item you want to search for: ";
            cin >> itemName;
            cout << itemName << " appears "
                << tracker.GetItemFrequency(itemName)
                << " time(s)." << endl;
            break;

        case 2:
            tracker.PrintAllFrequencies();
            break;

        case 3:
            tracker.PrintHistogram();
            break;

        case 4:
            cout << "Exiting program." << endl;
            break;

        default:
            cout << "Invalid choice. Please enter a number from 1 to 4." << endl;
            break;
        }

    } while (choice != 4);

    return 0;
}