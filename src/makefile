clean: tips SimpleStudentSystem
	@echo "编译完成, 正在清理杂项"
	@rm -f *.o
	@echo "清理已完成, 程序工作结束"

SimpleStudentSystem:  main.o student.o studentList.o 
	@g++ -o SimpleStudentSystem main.o student.o studentList.o -Wall

main.o: main.cpp student.h studentList.h
	@g++ -c main.cpp

studentList.o: studentList.h studentList.cpp student.h
	@g++ -c studentList.cpp

student.o: student.h student.cpp
	@g++ -c student.cpp


.PHONY: tip
tips: 
	@echo "编译中..."
	@echo "制作者: Loritas / lorias@foxmail.com"
	@echo "程序适用于Linux/MacOS环境, Windows环境未作验证"

