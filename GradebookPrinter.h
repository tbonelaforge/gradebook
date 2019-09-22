#ifndef _GRADEBOOK_PRINTER_H_
#define _GRADEBOOK_PRINTER_H_

#include <iostream>

#include "Gradebook.h"

class GradebookPrinter {
 public:
    static void printGradebook(Gradebook& gradebook, std::ostream& out);
 private:
    GradebookPrinter(Gradebook& gradebook);
    ~GradebookPrinter();
    const Gradebook& gradebook;
    int numRows;
    int numColumns;
    string ** cellContents;
    int* columnWidths;
    void print(std::ostream& out);
    void fillHeaders();
    void fillStudentData();
    void fillStudentRow(string * studentRow, Student* current);
    void setColumn(int j, string * studentRow, string data);
    void printRowSeparator(std::ostream& out);
    void fillHeader(int i, string columnHeading);
    static string centerString(string data, int columnWidth);
};

#endif
