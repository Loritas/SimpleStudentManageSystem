/*
 * @Author: Loritas 2223292817@qq.com
 * @Date: 2022-06-08 20:13:27
 * @LastEditors: Loritas 2223292817@qq.com
 * @LastEditTime: 2022-06-09 15:38:59
 * @FilePath: /SimpleStudentManageSystem/src/student.cpp
 * @Description: 学生类的实现
 * Copyright (c) 2022 by Loritas 2223292817@qq.com, All Rights Reserved. 
 */

#include "student.h"

Student::Student(std::string name, std::string sid, double cppScore, double javaScore) 
{
    this->name = name;
    this->sid = sid;
    this->cppScore = cppScore;
    this->javaScore = javaScore;
}

Student::Student()
{
    this->cppScore = -1;
    this->javaScore = -1;
}

Student::~Student()
{

}

double Student::score() const
{
    return this->cppScore + this->javaScore;
}

std::string Student::getName()
{
    return this->name;
}
std::string Student::getSid()
{
    return this->sid;
}

bool Student::operator>(const Student &s) const
{
    return this->score() > s.score();
}

bool Student::operator<(const Student &s) const
{
    return this->score() < s.score();
}

bool Student::operator==(const Student &s) const
{
    return this->score() == s.score();
}

bool Student::operator>=(const Student &s) const
{
    return this->score() >= s.score();
}

bool Student::operator<=(const Student &s) const
{
    return this->score() <= s.score();
}

double Student::getCppScore()
{
    return this->cppScore;
}
double Student::getJavaScore()
{
    return this->javaScore;
}

void Student::setName(std::string name)
{
    this->name = name;
}

void Student::setSid(std::string sid)
{
    this->sid = sid;
}

void Student::setCppScore(double score)
{
    this->cppScore = score;
}

void Student::setJavaScore(double score)
{
    this->javaScore = score;
}