#include <iostream>
#include <cstddef>
#include <string>
#include <cstdlib>

#include "Gradebook.h"

using namespace std;

ofstream Gradebook::transLogOut("Grades.trn");

Gradebook::Gradebook() : head(NULL) {
    makeEmpty();
}

Gradebook::~Gradebook() {
    deleteStudents();
    
    transLogOut << "Quit Gradebook." << endl;
    transLogOut.close();
}

void Gradebook::initialize(int p, int t, int f, int pw, int tw, int fw) {
    makeEmpty();
    numPrograms = p;
    numTests = t;
    numFinals = f;
    programsWeight = pw;
    testsWeight = tw;
    if (numFinals > 0) {
        finalExamWeight = fw;
    }
    
    transLogOut 
        << "Initialized Gradebook:\t" 
        << "Programs: " << p 
        << " Tests: " << t 
        << " Finals: " << f << "  | "
        << " Pwt: " << pw
        << " Twt: " << tw
        << " Fwt: " << fw << endl;
}

int Gradebook::getNumPrograms() const {
    return numPrograms;
}

int Gradebook::getNumTests() const {
    return numTests;
}

int Gradebook::getNumFinals() const {
    return numFinals;
}

void Gradebook::makeEmpty() {
    numPrograms = -1;
    numTests = -1;
    numFinals = -1;
    programsWeight = -1;
    testsWeight = -1;
    finalExamWeight = -1;
    deleteStudents();
}

void Gradebook::deleteStudents() {
    while (head != NULL) {
        Student * current = head;
        delete head;
        head = current->next;
    }
    numStudents = 0;
}

Student * Gradebook::addStudent(int newId) {
    Student * current = head;
    Student * previous = NULL;
    while (current != NULL) {
        if (current->getId() == newId) {
            throw "Student Id " + to_string(newId) + " already exists.";
        }
        if (current->getId() > newId) {
            break;
        }
        previous = current;
        current = current->next;
    }
    Student * newStudent = new Student(numPrograms, numTests, numFinals);
    newStudent->setId(newId);
    if (previous != NULL) {
        previous->next = newStudent;
    } else {
        head = newStudent;
    }
    newStudent->next = current;
    numStudents += 1;
    
    transLogOut << "Added new student: " << newId << endl;
    
    return newStudent;
}


Student * Gradebook::findStudentById(int id) {
    Student * current = head;
    while (current != NULL) {
        if (current->getId() == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}


void Gradebook::printStudents(std::ostream& out) const {
    Student * current = head;
    while (current != NULL) {
        out << "Student " << current->getId() << ": " << current->getFirstName() << " " << current->getLastName() << endl;
        current = current->next;
    }
}

int Gradebook::getNumStudents() const {
    return numStudents;
}

Student * Gradebook::getHead() const {
    return head;
}

void Gradebook::serialize(ostream& out) {
    out << numPrograms << " ";
    out << numTests << " ";
    out << numFinals << endl;
    out << programsWeight << " ";
    out << testsWeight << " ";
    out << finalExamWeight << endl;
    out << numStudents << endl;
    Student * current = head;
    while (current != NULL) {
        current->serialize(out);
        out << endl;
        current = current->next;
    }
    
    transLogOut << "Saved data to Grades.dat" << endl;
}

void Gradebook::deserialize(istream& in) {
    
    transLogOut << "Loaded data from Grades.dat" << endl;
    
    int numPrograms, numTests, numFinals;
    int programsWeight, testsWeight, finalExamWeight;
    int numStudents;
    in >> numPrograms >> numTests >> numFinals;
    in >> programsWeight >> testsWeight >> finalExamWeight;
    initialize(
               numPrograms,
               numTests,
               numFinals,
               programsWeight,
               testsWeight,
               finalExamWeight
               );
    in >> numStudents;
    for (int n = 0; n < numStudents; n++) {
        int i, j, k, grade, id;
        string firstName, lastName;
        in >> id >> firstName >> lastName;
        Student * student = addStudent(id);
        student->setFirstName(firstName);
        student->setLastName(lastName);
        for (int i = 0; i < numPrograms; i++) {
            in >> grade;
            student->setProgramGrade(i, grade);
        }
        for (int i = 0; i < numTests; i++) {
            in >> grade;
            student->setTestGrade(i, grade);
        }
        for (int i = 0; i < numFinals; i++) {
            in >> grade;
            student->setFinalExamGrade(grade);
        }
        in >> grade;
        student->setFinalAverage(grade);
    }
}
