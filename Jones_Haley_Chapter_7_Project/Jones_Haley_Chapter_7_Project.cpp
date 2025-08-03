// Jones_Haley_Chapter_7_Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>  // for exit()

using namespace std;

const int NUM_QUESTIONS = 20;

// Function declarations
void getAnswers(const string& filename, char answers[]);
int gradeExam(const char correct[], const char student[], int missed[], char missedAnswers[][2]);
void writeReport(const int missed[], int numMissed, const char missedAnswers[][2]);

int main() {
    char correctAnswers[NUM_QUESTIONS];
    char studentAnswers[NUM_QUESTIONS];
    int missedQuestions[NUM_QUESTIONS];
    char missedAnswers[NUM_QUESTIONS][2];  // [][0] = correct, [][1] = student

    // Load the correct and student answers
    getAnswers("CorrectAnswers.txt", correctAnswers);
    getAnswers("StudentAnswers.txt", studentAnswers);

    // Grade the exam
    int numMissed = gradeExam(correctAnswers, studentAnswers, missedQuestions, missedAnswers);

    // Write the report
    writeReport(missedQuestions, numMissed, missedAnswers);

    return 0;
}

// Function to read answers from file into array
void getAnswers(const string& filename, char answers[]) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error: Unable to open file " << filename << endl;
        exit(1);
    }

    for (int i = 0; i < NUM_QUESTIONS; ++i) {
        inFile >> answers[i];
    }

    inFile.close();
}

// Function to compare answers and record missed questions
int gradeExam(const char correct[], const char student[], int missed[], char missedAnswers[][2]) {
    int numMissed = 0;

    for (int i = 0; i < NUM_QUESTIONS; ++i) {
        if (correct[i] != student[i]) {
            missed[numMissed] = i + 1;  // Question number (1-based)
            missedAnswers[numMissed][0] = correct[i];
            missedAnswers[numMissed][1] = student[i];
            ++numMissed;
        }
    }

    return numMissed;
}

// Function to generate the report
void writeReport(const int missed[], int numMissed, const char missedAnswers[][2]) {
    cout << fixed << setprecision(2);

    // Report missed questions
    if (numMissed > 0) {
        cout << "Questions missed:\n";
        for (int i = 0; i < numMissed; ++i) {
            cout << "Question " << missed[i]
                << ": Correct Answer = " << missedAnswers[i][0]
                << ", Student Answer = " << missedAnswers[i][1] << endl;
        }
    }
    else {
        cout << "Great job! No questions were missed.\n";
    }

    // Total and percentage
    int correct = NUM_QUESTIONS - numMissed;
    double percentage = static_cast<double>(correct) / NUM_QUESTIONS * 100.0;

    cout << "\nTotal Questions Missed: " << numMissed << endl;
    cout << "Percentage Correct: " << percentage << "%\n";

    if (percentage >= 70.0)
        cout << "Result: PASS\n";
    else
        cout << "Result: FAIL\n";
}