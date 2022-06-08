#ifndef __STUDENT_LIST_H__
#define __STUDENT_LIST_H__
#include <vector>
#include "student.h"

static const int OK = 60;
static const int GOOD = 80;

class StudentList
{
private:
    std::vector<Student> list;
    int sum;
    int okSum;
    int goodSum;
public:
    StudentList();
    ~StudentList();

    void descSort();
    void incrSort();
    int studentSum();
    int studentOkSum();
    int studentGoodSum();
    double okPercent();
    double nonOkPercent();
    double goodPercent();
    void addStudent(Student &);
    void deleteStudent(std::string info);
    Student* getStudent(std::string info);
};

#endif