#include <iostream>
#include <fstream>
#include <string>

#include "Gradebook.h"
#include "Student.h"
#include "GradebookPrinter.h"

using namespace std;

ofstream transLog("Grades.trn", ios::out | ios::app);

void saveGrades(Gradebook &gradebook) {
    ofstream saveFile;
    saveFile.open("Grades.dat");
    gradebook.serialize(saveFile);
    
    transLog << "Saved to Grades.dat" << endl;
}

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
		while ((programsWeight + testsWeight + finalExamWeight) != 100) {
			cout << "Error, must equal 100%" << endl;
			cout << "Enter the relative percentages for programs, tests, and final exam. example: \n30 50 20" << endl;
			cin >> programsWeight >> testsWeight >> finalExamWeight;
		}
    } else {
        cout << "Enter the relative percentages for programs, and tests. example: \n40 60" << endl;
        cin >> programsWeight >> testsWeight;
		while ((programsWeight + testsWeight) != 100) {
			cout << "Error, must equal 100%" << endl;
			cout << "Enter the relative percentages for programs, and tests. example: \n40 60" << endl;
			cin >> programsWeight >> testsWeight;
		}
    }
    gradebook.initialize(
                         numPrograms,
                         numTests,
                         numFinals,
                         programsWeight,
                         testsWeight,
                         finalExamWeight
                         );
    saveGrades(gradebook);
    state = 1;
    
    transLog.close();
    transLog.open("Grades.trn");
    transLog << "Initialized Gradebook:" 
        << " Programs: " << numPrograms
        << " Tests: " << numTests
        << " Finals: " << numFinals << "  | "
        << " Pwt: " << programsWeight
        << " Twt: " << testsWeight
        << " Fwt: " << finalExamWeight << endl;
}



void handleQuit(int &state, Gradebook &gradebook) {
    //program hangs if no semester (student) data and no prior Grades.dat
    if (state == 0) {
        transLog << "Quit" << endl;
        return;
    }
    
    cout << "Saving grades and exiting..." << endl;
    saveGrades(gradebook);
    state = 2;
    
    transLog << "Quit" << endl;
}

void handleModeToggle(bool &idMode) {
    idMode = !idMode;
    cout << "Toggled output mode to: " << ( idMode ? "by Id" : "by Name" ) << endl;
    
    transLog << "Toggled output mode to: " << ( idMode ? "by Id" : "by Name" ) << endl;
}

void handleOutputGrades(Gradebook &gradebook, bool idMode) {
    ofstream outfile;
    outfile.open("Grades.out");
    GradebookPrinter::printGradebook(gradebook, cout, idMode);
    cout << "\nOutputing the complete gradebook to Grades.out..." << endl;
    GradebookPrinter::printGradebook(gradebook, outfile, idMode);
    cout << endl;
    
    transLog << "Output grades to Grades.out" << endl;
}

void handleAddProgramGrade(Gradebook &gradebook, bool idMode) {
    int programNumber, programGrade;
    cout << "Enter programming assignment number: (1 - " << gradebook.getNumPrograms() << ")" << endl;
    cin >> programNumber;
    if (programNumber < 1 || programNumber > gradebook.getNumPrograms()) {
        cout << "Invalid Program Number." << endl;
        return;
    }
    if (gradebook.getProgramRecorded(programNumber)) {
        cout << "Program " << programNumber << " already recorded..." << endl;
        return;
    }
    Student * student;
    if (!idMode) {
        Node * current = gradebook.getIndex();
        while (current != NULL) {
            student = current->student;
            cout << "Enter Program Grade for "
                 << student->getLastName() << ", " << student->getFirstName() << endl;
            cin >> programGrade;
            student->setProgramGrade(programNumber - 1, programGrade);
            saveGrades(gradebook);
            current = current->next;
        }
    } else {
        student = gradebook.getHead();
        while (student != NULL) {
            cout << "Enter Program Grade for "
                 << student->getLastName() << ", " << student->getFirstName() << endl;
            cin >> programGrade;
            student->setProgramGrade(programNumber - 1, programGrade);
            saveGrades(gradebook);
            student = student->next;
        }
    }
    gradebook.setProgramRecorded(programNumber);
    saveGrades(gradebook);
    handleOutputGrades(gradebook, idMode);
    
    transLog << "Recorded grades for Program: " << programNumber << endl;
}

void handleAddTestGrade(Gradebook &gradebook, bool idMode) {
    int testNumber, testGrade;
    cout << "Enter test number: (1 - " << gradebook.getNumTests() << ")" << endl;
    cin >> testNumber;
    if (testNumber < 1 || testNumber > gradebook.getNumTests()) {
        cout << "Invalid Test Number." << endl;
        return;
    }
    if (gradebook.getTestRecorded(testNumber)) {
        cout << "Test " << testNumber << " already recorded..." << endl;
        return;
    }
    Student * student;
    if (!idMode) {
        Node * current = gradebook.getIndex();
        while (current != NULL) {
            student = current->student;
            cout << "Enter Test " << testNumber << " Grade for "
                 << student->getLastName() << ", " << student->getFirstName() << endl;
            cin >> testGrade;
            student->setTestGrade(testNumber - 1, testGrade);
            saveGrades(gradebook);
            current = current->next;
        }
    } else {
        student = gradebook.getHead();
        while (student != NULL) {
            cout << "Enter Test " << testNumber << " Grade for "
                 << student->getLastName() << ", " << student->getFirstName() << endl;
            cin >> testGrade;
            student->setTestGrade(testNumber - 1, testGrade);
            saveGrades(gradebook);
            student = student->next;
        }
    }
    gradebook.setTestRecorded(testNumber);
    saveGrades(gradebook);
    handleOutputGrades(gradebook, idMode);
    
    transLog << "Recorded grades for Test: " << testNumber << endl;
}

void handleAddFinalExamGrade(Gradebook &gradebook, bool idMode) {
    int finalExamGrade;
    Student * student;
    if (gradebook.getFinalExamRecorded()) {
        cout << "Final Exam Already Recorded..." << endl;
        return;
    }
    if (!idMode) {
        Node * current = gradebook.getIndex();
        while (current != NULL) {
            student = current->student;
            cout << "Enter Final Exam Grade for "
                 << student->getLastName() << ", " << student->getFirstName() << endl;
            cin >> finalExamGrade;
            student->setFinalExamGrade(finalExamGrade);
            saveGrades(gradebook);
            current = current->next;
        }
    } else {
        student = gradebook.getHead();
        while (student != NULL) {
            cout << "Enter Final Exam Grade for "
                 << student->getLastName() << ", " << student->getFirstName() << endl;
            cin >> finalExamGrade;
            student->setFinalExamGrade(finalExamGrade);
            saveGrades(gradebook);
            student = student->next;
        }
    }
    gradebook.setFinalExamRecorded();
    saveGrades(gradebook);
    handleOutputGrades(gradebook, idMode);
    
    transLog << "Recorded grades for Final" << endl;
}

void handleChangeGrade(Gradebook &gradebook) {
    int studentId, gradeNumber, newGrade;
    char gradeType;
    Student * student;
    cout << "Enter the student number: " << endl;
    cin >> studentId;
    student = gradebook.findStudentById(studentId);
    if (student == NULL) {
        cout << "Student number " << studentId << " not found\n";
        return;
    }
    if (gradebook.getNumFinals() > 0) {
        cout << "Enter the type of grade: ('P' for program, 'T' for test, 'F' for final exam)" << endl;
    } else {
        cout << "Enter the type of grade: ('P' for program, 'T' for test)" << endl;
    }
    cin >> gradeType;
    gradeType = toupper(gradeType);
    switch (gradeType) {
    case 'P':
        cout << "Enter the program number (1 - " << gradebook.getNumPrograms() << ")\n";
        cin >> gradeNumber;
        if (gradeNumber < 1 || gradeNumber > gradebook.getNumPrograms()) {
            cout << "Invalid program number.\n";
            return;
        }
        break;
    case 'T':
        cout << "Enter the test number (1 - " << gradebook.getNumTests() << ")\n";
        cin >> gradeNumber;
        if (gradeNumber < 1 || gradeNumber > gradebook.getNumTests()) {
            cout << "Invalid test number.\n";
            return;
        }
        break;
    case 'F':
        if (gradebook.getNumFinals() > 0) {
            break;
        }
    default:
        cout << "Unrecognized Grade Type\n";
        return;
    }
    cout << "Enter the new grade: " << endl;
    cin >> newGrade;
	while (newGrade < 0 || newGrade>100) {
		cout << "Error, please enter a value between 0-100: " << endl;
		cin >> newGrade;
	}

    transLog << "Changed student " << student->getId();

    if (gradeType == 'P') {
        cout << "Changing the grade for program " << gradeNumber << " to " << newGrade << endl;
        student->setProgramGrade(gradeNumber - 1, newGrade);
        
        transLog << " program " << gradeNumber << " to " << newGrade << endl;
    } else if (gradeType == 'T') {
        cout << "Changing the grade for test " << gradeNumber << " to " << newGrade << endl;
        student->setTestGrade(gradeNumber - 1, newGrade);
        
        transLog << " test " << gradeNumber << " to " << newGrade << endl;
    } else {
        cout << "Changing the final exam grade to " << newGrade << endl;
        transLog << " Final grade from " << student->getFinalExamGrade() << " to " << newGrade << endl;
        student->setFinalExamGrade(newGrade);
    }
}


void handleCalculateGrades(Gradebook &gradebook, bool idMode) {
    cout << "Calculating the final grades for every student..." << endl;
    Student * student = gradebook.getHead();
    while (student != NULL) {
        student->calculateFinalAverage(
                                       gradebook.getProgramsWeight(),
                                       gradebook.getTestsWeight(),
                                       gradebook.getFinalExamWeight()
                                       );
        saveGrades(gradebook);
        student = student->next;
    }
    transLog << "Final grades calculated" << endl;
    
    handleOutputGrades(gradebook, idMode);
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
        Student * newStudent = gradebook.addStudent(studentId, firstName, lastName);
        cout << "Successfully added student " << newStudent->getId() << ": "
             << newStudent->getFirstName() << " " << newStudent->getLastName() << endl;
        saveGrades(gradebook);
    } catch (const string& reason) {
        cout << "Unable to add new student: " << endl << reason << endl;
    }
    transLog << "Added " << firstName << " " << lastName << " id " << studentId << endl;
}

void displayMenu(int state, Gradebook& gradebook, bool idMode) {
    switch (state) {
    case 0:
        cout << "WELCOME TO GRADEBOOK!" << endl;
        cout << "Type 'S' to setup a new semester." << endl;
        cout << "Type 'Q' to quit." << endl;
        break;
    case 1:
        cout << "GRADEBOOK MENU" << endl;
        cout << "Type 'S' to re-initialize the semester (all grades will be lost)." << endl;
        cout << "Type 'A' to add a new student." << endl;
        if (gradebook.getNumStudents() > 0) {
            cout << "Type 'P' to enter a program grade for all students." << endl;
            cout << "Type 'T' to enter a test grade for all students." << endl;          if (gradebook.getNumFinals() > 0) {
                cout << "Type 'F' to enter a final exam grade for all students." << endl;
            }
        }
        cout << "Type 'C' to change a grade for one student." << endl;
        cout << "Type 'G' to calculate and store the final grade for all students." << endl;
        cout << "Type 'O' to output the grade data." << endl;
        cout << "Type 'M' to toggle the output mode (currently " << ((idMode) ? "by Id)" : "by Name)") << endl;
        cout << "Type 'Q' to quit" << endl;
    }
}

int main() {
    int state; // 0 = unitialized, 1 = initialized, 2 = done
    bool idMode = true; // Whether to print students by id or by name.
    Gradebook gradebook;
    char C = '?';
    bool done = false;
    ifstream inData;

    try {
        inData.open("Grades.dat");
        if (!inData) {
            state = 0;
        } else {
            gradebook.deserialize(inData);
            state = 1;
        }
        while (C != 'Q' && state != 2) {
            displayMenu(state, gradebook, idMode);
            cin >> C;
            C = toupper(C);
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
                    handleCalculateGrades(gradebook, idMode);
                    break;
                case 'O':
                    handleOutputGrades(gradebook, idMode);
                    break;
                case 'S':
                    handleSetup(state, gradebook);
                    break;
                case 'Q':
                    handleQuit(state, gradebook);
                    break;
                case 'M':
                    handleModeToggle(idMode);
                    break;
                case 'P':
                    if (gradebook.getNumStudents() > 0) {
                        handleAddProgramGrade(gradebook, idMode);
                        break;
                    }
                case 'T':
                    if (gradebook.getNumStudents() > 0) {
                        handleAddTestGrade(gradebook, idMode);
                        break;
                    }
                case 'F':
                    if (gradebook.getNumStudents() > 0) {
                        handleAddFinalExamGrade(gradebook, idMode);
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
    } catch (string& e) {
        cout << "Got exception:" << endl << e;
        exit(1);
    }
    return 0;
}
