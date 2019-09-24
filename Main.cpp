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

    cout << "Enter number of programming assignments (Between 0-6): " << endl;
    cin >> numPrograms;
    while (numPrograms<0||numPrograms>6){
      cout << "Error, incorrect value entered." <<endl<<"Enter number of programming assignments (Between 0-6): " << endl;
      cin >> numPrograms;
    }

    cout << "Enter number of tests (Between 0-4): " << endl;
    cin >> numTests;
    while (numTests<0||numTests>4){
      cout << "Error, incorrect value entered." <<endl<<"Enter number of tests (Between 0-4): " << endl;
      cin >> numTests;
    }

    cout << "Enter number of Final Exams: (0 or 1)" << endl;
    cin >> numFinals;
    while (numFinals<0||numFinals>1){
      cout << "Error, incorrect value entered." <<endl<< "Enter number of Final Exams: (0 or 1)" << endl;
      cin >> numFinals;
    }

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
    cout << "Saving grades and exiting...";
    ofstream saveFile;
    saveFile.open("Grades.dat");
    gradebook.serialize(saveFile);
    state = 3;
}

void handleAddProgramGrade(Gradebook &gradebook) {
    int programNumber, programGrade;
    cout << "Enter programming assignment number: " << endl;
    cin >> programNumber;
    cout << "Looping through all students in gradebook, prompting for grades each time" << endl;
}

void handleAddTestGrade(Gradebook &gradebook) {
    int testNumber, testGrade;
    cout << "Enter test number: " << endl;
    cin >> testNumber;
    cout << "Looping through all students in gradebook, prompting for grades each time." << endl;
}

void handleAddFinalExamGrade(Gradebook &gradebook) {
    int finalExamGrade;
    if (gradebook.getNumFinals() < 1) {
        cout << "This class has no final exam.";
        return;
    }
    cout << "Looping through all students in gradebook, prompting for grades each time..." << endl;
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
}

void handleAddStudent(Gradebook &gradebook) {
    string firstName, lastName;
    int studentId;
    cout << "Enter the new student's first and last name: " << endl;
    cin >> firstName;
    while (firstName.length() > 20){
      cout<< "Error, too many characters, please shorten to less than 20"<<endl;
      cout << "Enter the new student's first name: " << endl;
      cin >> firstName;
    }

    cin >> lastName;
    while (lastName.length() > 20){
      cout<< "Error, too many characters, please shorten to less than 20"<<endl;
      cout << "Enter the new student's last name: " << endl;
      cin >> lastName;
    }

    cout << "Enter the new student's ID number: " << endl;
    cin >> studentId;
    while (studentId>9999 || studentId<1){
      cout<< " Error please enter a value between 1-9999"<< endl;
      cout << "Enter the new student's ID number: " << endl;
      cin >> studentId;
    }

    cout << "Adding " << firstName << " " << lastName << " (" << studentId << ") to the gradebook" << endl;
    try {
        Student * newStudent = gradebook.addStudent(studentId);
        newStudent->setFirstName(firstName);
        newStudent->setLastName(lastName);
        cout << "Successfully added " << newStudent->getFirstName() << " " << newStudent->getLastName() << endl;
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
        cout << "Type 'P' to enter a program grade for all students." << endl;
        cout << "Type 'T' to enter a test grade for all students." << endl;
        if (gradebook.getNumFinals() > 0) {
            cout << "Type 'F' to enter a final exam grade for all students." << endl;
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
            case 'P':
                handleAddProgramGrade(gradebook);
                break;
            case 'T':
                handleAddTestGrade(gradebook);
                break;
            case 'F':
                handleAddFinalExamGrade(gradebook);
                break;
           case 'C':
                handleChangeGrade(gradebook);
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
            default :
                cout << "Unrecognized Command." << endl;
            }
        }
    }
    exit(0);
}
