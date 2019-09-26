Main: Main.cpp Gradebook.o Student.o GradebookPrinter.o Gradebook.h Student.h
	g++ Main.cpp Gradebook.o Student.o GradebookPrinter.o -o Main


Gradebook.o: Gradebook.cpp Gradebook.h Student.h
	g++ -c Gradebook.cpp -o Gradebook.o


Student.o: Student.cpp Student.h
	g++ -c Student.cpp -o Student.o


GradebookPrinter.o: GradebookPrinter.cpp GradebookPrinter.h Gradebook.h Student.h
	g++ -c GradebookPrinter.cpp -o GradebookPrinter.o

clean:
	rm -f *.o
	rm -f Main
	rm -f *~
	rm -f Grades.out
	rm -f Grades.dat
