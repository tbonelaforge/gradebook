
#include <cstddef>
#include <iostream>

#include "Student.h"

using namespace std;

Student::Student(int np, int nt, int nf) {
    numPrograms = np;
    numTests = nt;
    numFinals = nf;
    programGrades = new int[numPrograms];
    for (int i = 0; i < numPrograms; i++) {
        programGrades[i] = -1;
    }
    testGrades = new int[numTests];
    for (int i = 0; i < numTests; i++) {
        testGrades[i] = -1;
    } 
    finalExamGrade = -1;
    finalAverage = -1.0;
    next = NULL;
}

Student::~Student() {
    delete[] programGrades;
    delete[] testGrades;
}

void Student::setId(int n) {
    id = n;
}

void Student::setFirstName(string name) {
    firstName = name;
}

void Student::setLastName(string name) {
    lastName = name;
}

int Student::getId() {
    return id;
}

string Student::getFirstName() {
    return firstName;
}

string Student::getLastName() {
    return lastName;
}

int Student::getNumPrograms() {
    return numPrograms;
}

int Student::getNumTests() {
    return numTests;
}

int Student::getNumFinals() {
    return numFinals;
}

int Student::getProgramGrade(int i) {
    return programGrades[i];
}

void Student::setProgramGrade(int i, int g) {
    programGrades[i] = g;
}

int Student::getTestGrade(int i) {
    return testGrades[i];
}

void Student::setTestGrade(int i, int g) {
    testGrades[i] = g;
}

int Student::getFinalExamGrade() {
    return finalExamGrade;
}

void Student::setFinalExamGrade(int g) {
    finalExamGrade = g;
}

float Student::getFinalAverage() {
    return finalAverage;
}

void Student::setFinalAverage(float x) {
    finalAverage = x;
}

void Student::serialize(ostream& out) {
    out << id << " ";
    out << firstName << " ";
    out << lastName << " ";
    for (int i = 0; i < numPrograms; i++) {
        out << programGrades[i] << " ";
    }
    for (int i = 0; i < numTests; i++) {
        out << testGrades[i] << " ";
    }
    for (int i = 0; i < numFinals; i++) {
        out << finalExamGrade << " ";
    }
    out << finalAverage;
}

void Student::calculateFinalAverage(int programsWeight, int testsWeight, int finalExamWeight) {
    float programAverage, testAverage;
	float d = 100;
    float programTotal = 0.0, testTotal = 0.0;
    for (int i = 0; i < numPrograms; i++) {
        if (programGrades[i] > -1) programTotal += (float) programGrades[i];
    }
    programAverage = programTotal / (float) numPrograms;
    for (int i = 0; i < numTests; i++) {
        if (testGrades[i] > -1) testTotal += (float) testGrades[i];
    }
    testAverage = testTotal / (float) numTests;
    float finalTotal =
        programAverage / d * programsWeight +
        testAverage / d * testsWeight;
    if (numFinals > 0) {
        if (finalExamGrade > -1) finalTotal += finalExamGrade / d * finalExamWeight;
    }
    setFinalAverage(finalTotal);
}
