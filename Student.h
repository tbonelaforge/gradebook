
#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <string>
#include <iostream>

using namespace std;

class Student {
 public:
    Student();
    Student(int np, int nt, int nf);
    ~Student();
    void setId(int n);
    void setFirstName(string name);
    void setLastName(string name);
    string getFirstName();
    string getLastName();
    int getId();
    Student * next;
    int getNumPrograms();
    int getNumTests();
    int getNumFinals();
    int getProgramGrade(int i);
    void setProgramGrade(int i, int g);
    int getTestGrade(int i);
    void setTestGrade(int i, int g);
    int getFinalExamGrade();
    void setFinalExamGrade(int g);
    float getFinalAverage();
    void setFinalAverage(float x);
    void serialize(ostream& out);
    void calculateFinalAverage(int programsWeight, int testsWeight, int finalExamWeight);
 private:
    Student(Student& other); // Forbid pass by value
    int id;
    string firstName;
    string lastName;
    int numPrograms;
    int numTests;
    int numFinals;
    int * programGrades;
    int * testGrades;
    int finalExamGrade;
    float finalAverage;
};

typedef Student ItemType;

#endif
