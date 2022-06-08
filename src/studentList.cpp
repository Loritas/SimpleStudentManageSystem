#include <algorithm>
#include <functional>
#include "studentList.h"

StudentList::StudentList() 
{
    this->list = std::vector<Student>();
    this->sum = 0;
    this->okSum = 0;
    this->goodSum = 0;
}

StudentList::~StudentList()
{

}

void StudentList::descSort()
{
    std::sort(list.begin(), list.end(), std::greater<Student>());
}

void StudentList::incrSort()
{
    std::sort(list.begin(), list.end());
}

int StudentList::studentSum()
{
    return sum;
}

int StudentList::studentOkSum()
{
    return okSum;
}

int StudentList::studentGoodSum()
{
    return goodSum;
}

double StudentList::okPercent()
{
    return (double)okSum / sum;
}

double StudentList::nonOkPercent()
{
    return (double)(sum - okSum) / sum;
}

double StudentList::goodPercent()
{
    return (double)goodSum / sum;
}

void StudentList::addStudent(Student &stu)
{
    sum++;
    if (stu.score() >= GOOD) goodSum++;
    if (stu.score() >= OK) okSum++;
    list.push_back(stu);
}

void StudentList::deleteStudent(std::string info)
{
    for(std::vector<Student>::iterator iter= list.begin(); iter != list.end(); iter++)
    {       
        if(iter->getName() == info){
            sum--;
            if (iter->score() >= GOOD) goodSum--;
            if (iter->score() >= OK) okSum--;
            list.erase(iter);
            break;
        }
    }
}

Student* StudentList::getStudent(std::string info)
{
    for(std::vector<Student>::iterator iter= list.begin(); iter != list.end(); iter++)
    {       
        if(iter->getName() == info){
            return &*iter;
        }
    }

    return nullptr;
}
