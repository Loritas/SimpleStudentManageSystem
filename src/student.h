/*
 * @Author: Loritas 2223292817@qq.com
 * @Date: 2022-06-08 20:13:20
 * @LastEditors: Loritas 2223292817@qq.com
 * @LastEditTime: 2022-06-09 15:38:39
 * @FilePath: /SimpleStudentManageSystem/src/student.h
 * @Description: 学生类的定义
 * Copyright (c) 2022 by Loritas 2223292817@qq.com, All Rights Reserved. 
 */
#ifndef __STUDENT_H__
#define __STUDENT_H__
#include <string>

class Student
{
private:
    std::string name;
    std::string sid;
    double cppScore;
    double javaScore;
public:
    Student(std::string, std::string, double, double);
    Student();
    ~Student();

    double score() const;
    std::string getName();
    std::string getSid();
    double getCppScore();
    double getJavaScore();

    void setName(std::string);
    void setSid(std::string);
    void setCppScore(double);
    void setJavaScore(double);

    bool operator>(const Student &) const;
    bool operator<(const Student &) const;
    bool operator==(const Student &) const;
    bool operator>=(const Student &) const;
    bool operator<=(const Student &) const;
};

#endif