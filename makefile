VPATH = src

.PHONY: tip clean build msg

msg:
	@echo "usage: make build"

build: tips SimpleStudentSystem clean

SimpleStudentSystem:  main.o student.o studentList.o 
	@$(CXX) -o $@ $^ -Wall

main.o: main.cpp student.h studentList.h
	@$(CXX) -c $<

studentList.o: studentList.cpp studentList.h student.h
	@$(CXX) -c $<

student.o: student.cpp student.h 
	@$(CXX) -c $<

clean:
	@echo "编译完成, 正在清理杂项"
	@rm -f *.o *.gch
	@echo "清理已完成, 程序工作结束"

tips: 
	@echo "编译中..."
	@echo "制作者: Loritas / lorias@foxmail.com"
	@echo "程序适用于Linux/MacOS环境, Windows环境未作验证"

