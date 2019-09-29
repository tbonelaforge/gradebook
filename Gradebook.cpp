#include <iostream>
#include <cstddef>
#include <string>
#include <cstdlib>

#include "Gradebook.h"

using namespace std;

Gradebook::Gradebook() : head(NULL), index(NULL) {
    makeEmpty();
}

Gradebook::~Gradebook() {
    delete [] programRecorded;
    delete [] testRecorded;
    deleteStudents();
}

void Gradebook::initialize(int p, int t, int f, int pw, int tw, int fw) {
    makeEmpty();
    numPrograms = p;
    programRecorded = new bool[numPrograms];
    for (int i = 0; i < numPrograms; i++) {
        programRecorded[i] = false;
    }
    numTests = t;
    testRecorded = new bool[numTests];
    for (int i = 0; i < numTests; i++) {
        testRecorded[i] = false;
    }
    numFinals = f;
    finalExamRecorded = false;
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
    programRecorded = NULL;
    numTests = -1;
    testRecorded = NULL;
    numFinals = -1;
    finalExamRecorded = false;
    programsWeight = -1;
    testsWeight = -1;
    finalExamWeight = -1;
    deleteStudents();
}

void Gradebook::deleteStudents() {
    while (head != NULL) {
        Student * next = head->next;
        delete head;
        head = next;
    }
    while (index != NULL) {
        Node * next = index->next;
        delete index;
        index = next;
    }
    numStudents = 0;
}

Student * Gradebook::addStudent(int newId, string firstName, string lastName) {
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
    newStudent->setFirstName(firstName);
    newStudent->setLastName(lastName);
    if (previous != NULL) {
        previous->next = newStudent;
    } else {
        head = newStudent;
    }
    newStudent->next = current;
    addToIndex(newStudent);
    numStudents += 1;
    return newStudent;
}

void Gradebook::addToIndex(Student * newStudent) {
    Node * current = index;
    Node * previous = NULL;
    while (current != NULL) {
        if (current->student->getLastName() > newStudent->getLastName()) {
            break;
        }
        previous = current;
        current = current->next;
    }
    Node * newNode = new Node();
    newNode->student = newStudent;
    newNode->next = NULL;
    if (previous != NULL) {
        previous->next = newNode;
    } else {
        index = newNode;
    }
    newNode->next = current;
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

Node * Gradebook::getIndex() const {
    return index;
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
    for (int i = 0; i < numPrograms; i++) {
        out << programRecorded[i] << " ";
    }
    out << endl;
    for (int i = 0; i < numTests; i++) {
        out << testRecorded[i] << " ";
    }
    out << endl;
    out << finalExamRecorded << endl;
}

void Gradebook::deserialize(istream& in) {
    int numPrograms, numTests, numFinals;
    int programsWeight, testsWeight, finalExamWeight;
    int numStudents;
    bool recorded;
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
        float finalAverage;
        in >> id >> firstName >> lastName;
        Student * student = addStudent(id, firstName, lastName);
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
        in >> finalAverage;
        student->setFinalAverage(finalAverage);
    }
    for (int i = 0; i < numPrograms; i++) {
        in >> recorded;
        if (recorded) {
            setProgramRecorded(i);
        }
    }
    for (int i = 0; i < numTests; i++) {
        in >> recorded;
        if (recorded) {
            setTestRecorded(i);
        }
    }
    in >> recorded;
    if (recorded) {
        setFinalExamRecorded();
    }
}

int Gradebook::getProgramsWeight() {
    return programsWeight;
}

int Gradebook::getTestsWeight() {
    return testsWeight;
}

int Gradebook::getFinalExamWeight() {
    return finalExamWeight;
}

void Gradebook::setProgramRecorded(int i) {
    programRecorded[i] = true;
}

bool Gradebook::getProgramRecorded(int i) {
    return programRecorded[i];
}

void Gradebook::setTestRecorded(int i) {
    testRecorded[i] = true;
}

bool Gradebook::getTestRecorded(int i) {
    return testRecorded[i];
}

void Gradebook::setFinalExamRecorded() {
    finalExamRecorded = true;
}

bool Gradebook::getFinalExamRecorded() {
    return finalExamRecorded;
}
