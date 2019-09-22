
#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <string>

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
    int getTestGrade(int i);
    int getFinalExamGrade();
    float getFinalAverage();
    void setFinalAverage(float x);
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
