/*
 * @Author: Loritas 2223292817@qq.com
 * @Date: 2022-06-08 20:26:13
 * @LastEditors: Loritas 2223292817@qq.com
 * @LastEditTime: 2022-06-12 00:37:34
 * @FilePath: /SimpleStudentManageSystem/src/studentList.h
 * @Description:    学生队列的头文件，用于保存队列相关信息，使用vector和unordered_set实现
 * Copyright (c) 2022 by Loritas 2223292817@qq.com, All Rights Reserved. 
 */
#ifndef __STUDENT_LIST_H__
#define __STUDENT_LIST_H__
#include <vector>
#include <unordered_set>
#include "student.h"

static const int OK = 60;
static const int GOOD = 80;

class StudentList
{
private:
    std::vector<Student> list;
    std::unordered_set<std::string> set;
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
    bool updateStudent(std::string, std::string, std::string, std::string, std::string);
    bool deleteStudent(std::string info);
    Student getStudent(std::string info);

    std::vector<Student> getList();
};

#endif