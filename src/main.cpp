#include <iostream>
#include "studentList.h"

int main(int argc, char const *argv[])
{
    std::cout << "Hello SSMS!";
    StudentList list = StudentList();
    Student stu = Student("Loritas", "1234", 99, 99);
    list.addStudent(stu);
    std::cout << stu.getName() << std::endl;
    std::cout << stu.getSid() << std::endl;
    std::cout << stu.score() << std::endl;

    std::cout << list.studentGoodSum() << std::endl;
    std::cout << list.studentSum() << std::endl;
    std::cout << list.studentOkSum() << std::endl;
    std::cout << list.getStudent(stu.getName()) << std::endl;

    std::cout << list.getStudent(stu.getName())->getName() << std::endl;
    std::cout << list.getStudent(stu.getSid())->getName() << std::endl;
    std::cout << list.getStudent(stu.getName())->getSid() << std::endl;

    list.deleteStudent(stu.getName());
    std::cout << list.studentGoodSum() << std::endl;
    std::cout << list.studentSum() << std::endl;
    std::cout << list.studentOkSum() << std::endl;

    return 0;
}
