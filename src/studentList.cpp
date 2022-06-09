/*
 * @Author: Loritas 2223292817@qq.com
 * @Date: 2022-06-08 20:45:08
 * @LastEditors: Loritas 2223292817@qq.com
 * @LastEditTime: 2022-06-09 23:56:10
 * @FilePath: /SimpleStudentManageSystem/src/studentList.cpp
 * @Description: 学生队列的功能实现
 * Copyright (c) 2022 by Loritas 2223292817@qq.com, All Rights Reserved. 
 */
#include <algorithm>
#include <functional>
#include "studentList.h"

StudentList::StudentList() 
{
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
    if (set.find(stu.getSid()) == set.end())
    {
        sum++;
        if (stu.score() >= GOOD) goodSum++;
        if (stu.score() >= OK) okSum++;
        list.push_back(stu);
        set.insert(stu.getSid());
    }
}

/**
 * @name: deleteStudent
 * @msg: 根据提供的学号信息，在队列中删除指定学生
 * @param {string} info: 学生的学号信息
 * @return {*}
 */
void StudentList::deleteStudent(std::string info)
{
    for(std::vector<Student>::iterator iter= list.begin(); iter != list.end(); iter++)
    {       
        if(iter->getSid() == info){
            sum--;
            if (iter->score() >= GOOD) goodSum--;
            if (iter->score() >= OK) okSum--;
            list.erase(iter);
            break;
        }
    }
}

/**
 * @name: 
 * @msg: 根据提供的学号信息，在队列中查找并返回指定学生
 * @param {string} info: 学生的学号信息
 * @return {Student}: 如果学生存在则返回该学生，否则返回一个空的学生实例
 */
Student StudentList::getStudent(std::string info)
{
    for(std::vector<Student>::iterator iter= list.begin(); iter != list.end(); iter++)
    {       
        if(iter->getSid() == info){
            return *iter;
        }
    }

    return Student();
}

std::vector<Student> StudentList::getList()
{
    return this->list;
}
