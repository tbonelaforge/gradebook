
#include <cstddef>
#include <string>

#include "Gradebook.h"


Gradebook::Gradebook() {
    makeEmpty();
}

Gradebook::~Gradebook() {
    deleteStudents();
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
    return newStudent;
}

void Gradebook::printStudents(std::ostream& out) const {
    Student * current = head;
    while (current != NULL) {
        out << "Student " << current->getId() << ": " << current->getFirstName() << " " << current->getLastName() << std::endl;
        current = current->next;
    }
}

int Gradebook::getNumStudents() const {
    return numStudents;
}

Student * Gradebook::getHead() const {
    return head;
}
