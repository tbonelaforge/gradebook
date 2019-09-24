#ifndef _GRADEBOOK_H_
#define _GRADEBOOK_H_


#include <iostream>
#include "Student.h"

using namespace std;

struct Node {
    Student * student;
    Node * next;
};

class Gradebook {
public:
    Gradebook();
    ~Gradebook();
    void initialize(int p, int t, int f, int pw, int tw, int fw);
    int getNumPrograms() const;
    int getNumTests() const;
    int getNumFinals() const;
    Student * addStudent(int id, string firstName, string lastName);
    void printStudents(std::ostream& out) const;
    int getNumStudents() const;
    Student * getHead() const;
    void serialize(ostream& out);
    void deserialize(istream& in);
    Node * getIndex() const;
private:
    int numPrograms;
    int numTests;
    int numFinals;
    int programsWeight;
    int testsWeight;
    int finalExamWeight;
    Student * head;
    Node * index;
    int numStudents;
    void makeEmpty();
    void deleteStudents();
    void addToIndex(Student * newStudent);
};

#endif
