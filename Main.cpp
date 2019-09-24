#include <iostream>
#include <fstream>
#include <string>

#include "Gradebook.h"
#include "Student.h"
#include "GradebookPrinter.h"

using namespace std;

void handleSetup(int &state, Gradebook &gradebook) {
    int numPrograms, numTests, numFinals;
    int programsWeight, testsWeight, finalExamWeight;
    cout << "Enter number of programming assignments: " << endl;
    cin >> numPrograms;
    cout << "Enter number of tests: " << endl;
    cin >> numTests;
    cout << "Enter number of Final Exams: (0 or 1)" << endl;
    cin >> numFinals;
    if (numFinals > 0) {
        cout << "Enter the relative percentages for programs, tests, and final exam. example: \n30 50 20" << endl;
        cin >> programsWeight >> testsWeight >> finalExamWeight;
    } else {
        cout << "Enter the relative percentages for programs, and tests. example: \n40 60" << endl;
        cin >> programsWeight >> testsWeight;
    }
    gradebook.initialize(
                         numPrograms,
                         numTests,
                         numFinals,
                         programsWeight,
                         testsWeight,
                         finalExamWeight
                         );
    state = 1;
}

void handleQuit(int &state, Gradebook &gradebook) {
    cout << "Saving grades and exiting..." << endl;
    ofstream saveFile;
    saveFile.open("Grades.dat");
    gradebook.serialize(saveFile);
    state = 3;
}

void handleAddProgramGrade(Gradebook &gradebook) {
    int programNumber, programGrade;
    cout << "Enter programming assignment number: (1 - " << gradebook.getNumPrograms() << ")" << endl;
    cin >> programNumber;
    if (programNumber < 0 || programNumber > gradebook.getNumPrograms()) {
        cout << "Invalid Program Number.";
        return;
    }
    Node * current = gradebook.getIndex();
    while (current != NULL) {
        Student * student = current->student;
        cout << "Enter Program Grade for "
             << student->getLastName() << ", " << student->getFirstName() << endl;
        cin >> programGrade;
        student->setProgramGrade(programNumber, programGrade);
        current = current->next;
    }
}

void handleAddTestGrade(Gradebook &gradebook) {
    int testNumber, testGrade;
    cout << "Enter test number: (1 - " << gradebook.getNumTests() << ")" << endl;
    cin >> testNumber;
    if (testNumber < 0 || testNumber > gradebook.getNumTests()) {
        cout << "Invalid Test Number.";
        return;
    }
    Node * current = gradebook.getIndex();
    while (current != NULL) {
        Student * student = current->student;
        cout << "Enter Test Grade for "
             << student->getLastName() << ", " << student->getFirstName() << endl;
        cin >> testGrade;
        student->setTestGrade(testNumber, testGrade);
        current = current->next;
    }
}

void handleAddFinalExamGrade(Gradebook &gradebook) {
    int finalExamGrade;
    Node * current = gradebook.getIndex();
    while (current != NULL) {
        Student * student = current->student;
        cout << "Enter Final Exam Grade for "
             << student->getLastName() << ", " << student->getFirstName() << endl;
        cin >> finalExamGrade;
        student->setFinalExamGrade(finalExamGrade);
        current = current->next;
    }
}

void handleChangeGrade(Gradebook &gradebook) {
    int studentNumber;
    int newGrade;
    char gradeType;
    cout << "Enter the student number: " << endl;
    cin >> studentNumber;
    cout << "Enter the new grade: " << endl;
    cin >> newGrade;
    if (gradebook.getNumFinals() > 0) {
        cout << "Enter the type of grade: ('P' for program, 'T' for test, 'F' for final exam)" << endl;
    } else {
        cout << "Enter the type of grade: ('P' for program, 'T' for test)" << endl;
    }
    cin >> gradeType;
    cout << "Getting the student by id and changing their grade..." << endl;
}

void handleCalculateGrades(Gradebook &gradebook) {
    cout << "Calculating the final grades for every student..." << endl;
}

void handleOutputGrades(Gradebook &gradebook) {
    cout << "Outputting the complete gradebook to Grades.out..." << endl;
    ofstream outfile;
    outfile.open("Grades.out");
    GradebookPrinter::printGradebook(gradebook, outfile);
    GradebookPrinter::printGradebook(gradebook, cout);
    cout << endl;
}

void handleAddStudent(Gradebook &gradebook) {
    string firstName, lastName;
    int studentId;
    cout << "Enter the new student's first and last name: " << endl;
    cin >> firstName;
    cin >> lastName;
    cout << "Enter the new student's ID number: " << endl;
    cin >> studentId;
    cout << "Adding " << firstName << " " << lastName << " (" << studentId << ") to the gradebook" << endl;
    try {
        Student * newStudent = gradebook.addStudent(studentId, firstName, lastName);
        cout << "Successfully added student " << newStudent->getId() << ": "
             << newStudent->getFirstName() << " " << newStudent->getLastName() << endl;
    } catch (const string& reason) {
        cout << "Unable to add new student: " << endl << reason << endl;
    }

}

void displayMenu(int state, Gradebook& gradebook) {
    switch (state) {
    case 0:
        cout << "WELCOME TO GRADEBOOK!" << endl;
        cout << "Type 'S' to setup a new semester." << endl;
        cout << "Type 'Q' to quit." << endl;
        break;
    case 1:
        cout << "GRADEBOOK MENU" << endl;
        cout << "Type 'A' to add a new student." << endl;
        if (gradebook.getNumStudents() > 0) {
            cout << "Type 'P' to enter a program grade for all students." << endl;
            cout << "Type 'T' to enter a test grade for all students." << endl;          if (gradebook.getNumFinals() > 0) {
                cout << "Type 'F' to enter a final exam grade for all students." << endl;
            }
        }
        cout << "Type 'G' to calculate and store the final grade for all students." << endl;
        cout << "Type 'O' to output the grade data." << endl;
        cout << "Type 'S' to re-initialize the semester (all grades will be lost)." << endl;
        cout << "Type 'Q' to quit" << endl;
    }
}


int main() {
    int state; // 0 = unitialized, 1 = initialized, 2 = done
    Gradebook gradebook;
    char C;
    bool done = false;
    ifstream inData;
    inData.open("Grades.dat");
    if (!inData) {
        state = 0;
    } else {
        gradebook.deserialize(inData);
        state = 1;
    }
    while (state != 3) {
        displayMenu(state, gradebook);
        cin >> C;
        if (state == 0) {
            switch (C) {
            case 'Q':
                handleQuit(state, gradebook);
                break;
            case 'S':
                handleSetup(state, gradebook);
                break;
            default :
                cout << "Unrecognized command." << endl;
                break;
            }
        } else if (state == 1) {
            switch (C) {
            case 'A':
                handleAddStudent(gradebook);
                break;
            case 'G':
                handleCalculateGrades(gradebook);
                break;
            case 'O':
                handleOutputGrades(gradebook);
                break;
            case 'S':
                handleSetup(state, gradebook);
                break;
            case 'Q':
                handleQuit(state, gradebook);
                break;
            case 'P':
                if (gradebook.getNumStudents() > 0) {
                    handleAddProgramGrade(gradebook);
                    break;
                }
            case 'T':
                if (gradebook.getNumStudents() > 0) {
                    handleAddTestGrade(gradebook);
                    break;
                }
            case 'F':
                if (gradebook.getNumStudents() > 0) {
                    handleAddFinalExamGrade(gradebook);
                    break;
                }
            case 'C':
                if (gradebook.getNumStudents() > 0) {
                    handleChangeGrade(gradebook);
                    break;
                }
            default :
                cout << "Unrecognized Command." << endl;
            }
        }
    }
    exit(0);
}





