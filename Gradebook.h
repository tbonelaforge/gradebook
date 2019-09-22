#ifndef _GRADEBOOK_H_
#define _GRADEBOOK_H_


#include <iostream>
#include "Student.h"

class Gradebook {
public:
    Gradebook();
    ~Gradebook();
    void initialize(int p, int t, int f, int pw, int tw, int fw);
    int getNumPrograms() const;
    int getNumTests() const;
    int getNumFinals() const;
    Student * addStudent(int id);
    void printStudents(std::ostream& out) const;
    int getNumStudents() const;
    Student * getHead() const;
private:
    int numPrograms;
    int numTests;
    int numFinals;
    int programsWeight;
    int testsWeight;
    int finalExamWeight;
    Student * head;
    int numStudents;
    void makeEmpty();
    void deleteStudents();
};

#endif
