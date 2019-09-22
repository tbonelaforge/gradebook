#include <iostream>
#include <string>
#include "GradebookPrinter.h"

using namespace std;

void GradebookPrinter::printGradebook(Gradebook& gradebook, ostream& out) {
    GradebookPrinter gp(gradebook);
    gp.print(out);
}

GradebookPrinter::GradebookPrinter(Gradebook& gradebook) : gradebook(gradebook) {
    numRows = gradebook.getNumStudents() + 1; // Extra row for table header
    numColumns = gradebook.getNumPrograms() + gradebook.getNumTests() + gradebook.getNumFinals() + 3;
    cellContents = new string*[numRows];
    for (int i = 0; i < numRows; i++) {
        cellContents[i] = new string[numColumns];
    }
    columnWidths = new int[numColumns];
}

GradebookPrinter::~GradebookPrinter() {
    for (int i = 0; i < numRows; i++) {
        delete[] cellContents[i];
    }
    delete[] cellContents;
    delete[] columnWidths;
}
 
    
void GradebookPrinter::print(ostream& out) {
    fillHeaders();
    fillStudentData();
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numColumns; j++) {
            out << centerString(cellContents[i][j], columnWidths[j]);
            if (j < numColumns - 1) {
                out << '|';
            }
        }
        out << endl;
        if (i < numRows - 1) {
            printRowSeparator(out);
            out << endl;
        }
    }
}

void GradebookPrinter::fillStudentData() {
    int i = 0;
    Student * current = gradebook.getHead();
    while (current != NULL) {
        string * studentRow = cellContents[1 + i];
        fillStudentRow(studentRow, current);
        i += 1;
        current = current->next;
    }
}


void GradebookPrinter::fillHeaders() {
    int i, j, k;
    string * headers = cellContents[0];
    headers[0] = " ID ";
    columnWidths[0] = headers[0].length();
    headers[1] = " Name ";
    columnWidths[1] = headers[1].length();
    for (i = 0; i < gradebook.getNumPrograms(); i++) {
        fillHeader(2 + i, " Program " + to_string(i + 1) + " ");
    }
    for (j = 0; j < gradebook.getNumTests(); j++) {
        fillHeader(2 + i + j, " Test " + to_string(j + 1) + " ");
    }
    for (k = 0; k < gradebook.getNumFinals(); k++) {
        fillHeader(2 + i + j + k, " Final Exam ");
    }
    fillHeader(2 + i + j + k, " Final Grade ");
}

void GradebookPrinter::fillHeader(int i, string columnHeading) {
    string * headers = cellContents[0];
    headers[i] = columnHeading;
    columnWidths[i] = columnHeading.length();
}


void GradebookPrinter::fillStudentRow(string * studentRow, Student * student) {
    int i, j, k;
    string grade;
    setColumn(0, studentRow, " " + to_string(student->getId()) + " ");
    setColumn(1, studentRow, " " + student->getFirstName()  + " " + student->getLastName() + " ");
    for (i = 0; i < student->getNumPrograms(); i++) {
        grade =  " " + to_string(student->getProgramGrade(i)) + " ";
        setColumn(2 + i, studentRow, grade);
    }
    for (j = 0; j < student->getNumTests(); j++) {
        grade = " " + to_string(student->getTestGrade(j)) + " ";
        setColumn(2 + i + j, studentRow, grade);
    }
    for (k = 0; k < student->getNumFinals(); k++) {
        grade = " " + to_string(student->getFinalExamGrade()) + " ";
        setColumn(2 + i + j + k, studentRow, grade);
    }
    grade = " " + to_string(student->getFinalAverage()) + " ";
    setColumn(2 + i + j + k, studentRow, grade);
}

void GradebookPrinter::setColumn(int j, string * studentRow, string data) {
    studentRow[j] = data;
    if (data.length() > columnWidths[j]) {
        columnWidths[j] = data.length();
    }
}

string GradebookPrinter::centerString(string data, int columnWidth) {
    int blanksNeeded = columnWidth - data.length();
    int lb = blanksNeeded / 2;
    int rb = blanksNeeded - lb;
    string lbs = "";
    string rbs = "";
    for (int i = 0; i < lb; i++) {
        lbs += " ";
    }
    for (int i = 0; i < rb; i++) {
        rbs += " ";
    }
    return lbs + data + rbs;
}


void GradebookPrinter::printRowSeparator(ostream& out) {
    for (int j = 0; j < numColumns; j++) {
        for (int k = 0; k < columnWidths[j]; k++) {
            out << '-';
        }
        if (j < numColumns - 1) {
            out << '-';
        }
    }
}
