// Jones_Haley_Chapter_7_Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>  // for exit()

using namespace std;

// Function declarations
void getTeams(const string& filename, vector<string>& teams);
int findWinner(const string& teamName, const vector<string>& winners);

int main() {
    vector<string> teams;
    vector<string> winners;
    string teamName;

    // This function receives the name of a file containing team names
    getTeams("Teams.txt", teams);
    getTeams("WorldSeriesWinners.txt", winners);

    // Display all valid team names
    cout << "Teams that have won the World Series (1903–2012):\n";
    for (const string& team : teams) {
        cout << "- " << team << endl;
    }

    // Prompt user input
    cout << "\nEnter a team name to see how many times they won (or enter \"quit\" to stop): ";
    getline(cin, teamName);

    while (teamName != "quit") {
        int count = findWinner(teamName, winners);
        cout << teamName << " won the World Series " << count << " time(s)." << endl;

        cout << "\nEnter another team name (or \"quit\" to stop): ";
        getline(cin, teamName);
    }

    cout << "\nProgram terminated.\n";
    return 0;
}

// Reads team names or winners from a file into a vector
void getTeams(const string& filename, vector<string>& names) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error: Could not open file " << filename << endl;
        exit(1);
    }

    string line;
    while (getline(inFile, line)) {
        names.push_back(line);
    }

    inFile.close();
}

// This function takes the name of a team and the vector of winners
int findWinner(const string& teamName, const vector<string>& winners) {
    int count = 0;
    for (const string& winner : winners) {
        if (winner == teamName) {
            ++count;
        }
    }
    return count;
}