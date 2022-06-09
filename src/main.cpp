/*
 * @Author: Loritas 2223292817@qq.com
 * @Date: 2022-06-08 20:12:35
 * @LastEditors: Loritas 2223292817@qq.com
 * @LastEditTime: 2022-06-10 01:57:22
 * @FilePath: /SimpleStudentManageSystem/src/main.cpp
 * @Description: 程序主入口
 * Copyright (c) 2022 by Loritas 2223292817@qq.com, All Rights Reserved. 
 */

#include <iostream>
#include "../utils/config.h"

int main(int argc, char const *argv[])
{
    std::cout << "Hello SSMS!" << std::endl;
    // just for test~
    // just for test~
    // just for test~
    init();
    StudentList list = readStudentData();
    Student stu = Student("Loritas", "1234", 99, 99);
    Student stu2 = Student("Mahry", "2345", 98, 97);
    std::cout << stu.getName() << std::endl;
    std::cout << stu.getSid() << std::endl;
    std::cout << stu.score() << std::endl;

    std::cout << list.studentGoodSum() << std::endl;
    std::cout << list.studentSum() << std::endl;
    std::cout << list.studentOkSum() << std::endl;
    std::cout << list.getStudent(stu.getSid()).score() << std::endl;

    std::cout << list.getStudent(stu.getSid()).getName() << std::endl;
    std::cout << list.getStudent(stu.getSid()).getSid() << std::endl;

    list.addStudent(stu2);
    saveStudentData(list);

    // list.deleteStudent(stu.getSid());
    // std::cout << list.studentGoodSum() << std::endl;
    // std::cout << list.studentSum() << std::endl;
    // std::cout << list.studentOkSum() << std::endl;

    return 0;
}
