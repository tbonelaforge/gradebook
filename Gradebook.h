#ifndef _GRADEBOOK_H_
#define _GRADEBOOK_H_


#include <iostream>
#include <fstream>
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
    Student * findStudentById(int id);
    void printStudents(std::ostream& out) const;
    int getNumStudents() const;
    Student * getHead() const;
    void serialize(ostream& out);
    void deserialize(istream& in);
    Node * getIndex() const;
    int getProgramsWeight();
    int getTestsWeight();
    int getFinalExamWeight();
    void setProgramRecorded(int i);
    bool getProgramRecorded(int i);
    void setTestRecorded(int i);
    bool getTestRecorded(int i);
    void setFinalExamRecorded();
    bool getFinalExamRecorded();
    static ofstream transLogOut;
  
private:
    int numPrograms;
    bool * programRecorded;
    int numTests;
    bool * testRecorded;
    int numFinals;
    bool finalExamRecorded;
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
