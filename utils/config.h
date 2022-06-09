/*
 * @Author: Loritas 2223292817@qq.com
 * @Date: 2022-06-09 20:29:44
 * @LastEditors: Loritas 2223292817@qq.com
 * @LastEditTime: 2022-06-10 01:55:05
 * @FilePath: /SimpleStudentManageSystem/utils/config.h
 * @Description: 
 * Copyright (c) 2022 by Loritas 2223292817@qq.com, All Rights Reserved. 
 */
#ifndef __CONFIG_H__
#define __CONFIG_H__
#include <unordered_map>
#include <cstring>
#include <stdlib.h>
#include <iostream>
#include "writer.h"
#include "../src/studentList.h"

const static std::string CONFIG_PATH = "../data/config.ini";
const static int BUF_SIZE = 1024;

// 我实在没搞明白它的工作路径为什么在这个文件夹外边……
static std::string DATA_PATH = "./SimpleStudentManageSystem/data/";
static std::string DATA_FILE_NAME = "data.ini";

typedef void(Student::*studentSetFunc)(std::string);
static std::unordered_map<std::string, studentSetFunc> studentSetAbtMap;

const static void init()
{
    studentSetAbtMap["Name"] = &Student::setName;
    studentSetAbtMap["JavaScore"] = &Student::setJavaScore;
    studentSetAbtMap["CppScore"] = &Student::setCppScore;
}

const static void saveStudentData(StudentList& sList)
{
    std::ofstream ofs;
    ofs.open(DATA_PATH+DATA_FILE_NAME, std::ios::out);
    if (!ofs)
    {
        // TODO err_msg
    }   
    ofs << "# Author: Loritas / loritas@foxmail.com" << std::endl;
    ofs << "# Version: 0.1" << std::endl;
    ofs << "# this format is a poor imitation of ini" << std::endl;
    ofs << "# it can only do a simple check" << std::endl;
    ofs << "# use '#' as an annotation" << std::endl;
    ofs << "# each sequence end by ';'" << std::endl;
    ofs << "# usage: name=loritas;" << std::endl;
    ofs << "# do not leave a ' ' besides '='" << std::endl;

    std::vector<Student> list = sList.getList();
    for(std::vector<Student>::iterator iter= list.begin(); iter != list.end(); iter++)
    {       
        writeHead(iter->getSid(), ofs);
        writeData("Name", iter->getName(), ofs);
        writeData("JavaScore", iter->getJavaScore(), ofs);
        writeData("CppSCore", iter->getCppScore(), ofs);
    }
    ofs.close();
}

const static StudentList readStudentData()
{
    StudentList sList;

    std::ifstream ifs;
    ifs.open(DATA_PATH+DATA_FILE_NAME, std::ios::in);
    if (!ifs.is_open())
    {
        // TODO err_msg
    }

    char buf[BUF_SIZE] = {0};
    Student curStu;
    while (ifs >> buf)
    {
        if (buf[0] == '\n' || buf[0] == '#')
        {
            continue;
        }

        if (buf[0] == '[')
        {
            if (curStu.getCppScore() != -1)
            {
                sList.addStudent(curStu);
            }
            curStu = Student();
            char *savePtr = NULL;
            char *attri = buf+1;
            attri = strtok_r(attri, "]", &savePtr);
            curStu.setSid(attri);
        }
        else 
        {
            char *savePtr = NULL;
            char *attri = strtok_r(buf, "=", &savePtr);
            int len = strlen(attri);
            if (studentSetAbtMap.find(attri) != studentSetAbtMap.end())
            {
                studentSetFunc func = studentSetAbtMap.find(attri)->second;
                attri = strtok_r(buf + len + 1, ";", &savePtr);
                (curStu.*func)(attri);
            }
        }
        
    }
    if (curStu.getCppScore() != -1)
    {
        sList.addStudent(curStu);
    }

    ifs.close();
    return sList;
}

#endif