/*
 * @Author: Loritas 2223292817@qq.com
 * @Date: 2022-06-09 20:29:44
 * @LastEditors: Loritas 2223292817@qq.com
 * @LastEditTime: 2022-06-10 17:15:34
 * @FilePath: /SimpleStudentManageSystem/utils/config.h
 * @Description: 配置程序的各项属性
 * Copyright (c) 2022 by Loritas 2223292817@qq.com, All Rights Reserved. 
 */
#ifndef __CONFIG_H__
#define __CONFIG_H__
#include <unordered_map>
#include <cstring>
#include "writer.h"
#include "../src/studentList.h"

static StudentList sList;

const static std::string CONFIG_PATH = "./SimpleStudentManageSystem/data/config.ini";
const static int BUF_SIZE = 1024;

// 我实在没搞明白它的工作路径为什么在这个文件夹外边……
static std::string DATA_PATH = "./SimpleStudentManageSystem/data/";
static std::string DATA_FILE_NAME = "data.ini";

typedef void(Student::*studentSetFunc)(std::string);
static std::unordered_map<std::string, studentSetFunc> studentSetAbtMap;
static std::unordered_set<std::string> configSet;
static std::unordered_map<std::string, std::string> configMap;

static void init();
static void saveStudentData();
static void readStudentData();
static void readConfig();
static void setConfig();

static void init()
{
    studentSetAbtMap["Stu_Name"] = &Student::setName;
    studentSetAbtMap["Stu_JavaScore"] = &Student::setJavaScore;
    studentSetAbtMap["Stu_CppScore"] = &Student::setCppScore;

    configSet.insert("sys_data_path");
    configSet.insert("sys_data_file_name");

    readConfig();
    setConfig();
    
}

static void saveStudentData()
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
    ofs << "# usage: Stu_Name=loritas;" << std::endl;
    ofs << "# do not leave a ' ' besides '=' or the head of each sequence" << std::endl;

    std::vector<Student> list = sList.getList();
    for(std::vector<Student>::iterator iter= list.begin(); iter != list.end(); iter++)
    {       
        writeHead(iter->getSid(), ofs);
        writeData("Stu_Name", iter->getName(), ofs);
        writeData("Stu_JavaScore", iter->getJavaScore(), ofs);
        writeData("Stu_CppScore", iter->getCppScore(), ofs);
    }
    ofs.close();
}

static void readStudentData()
{
    Student curStu;

    std::ifstream ifs;
    // "data.ini"
    ifs.open(DATA_PATH+DATA_FILE_NAME, std::ios::in);
    if (!ifs.is_open())
    {
        // TODO err_msg
    }
    
    char buf[BUF_SIZE];
    
    while (!ifs.eof())
    {
        ifs.getline(buf, BUF_SIZE);
        if (buf[0] == '\n' || buf[0] == '#' || buf[0] == '\0')
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
}


static void readConfig()
{
    std::ifstream ifs;
    ifs.open(CONFIG_PATH, std::ios::in);
    if (!ifs.is_open())
    {
        // TODO err_msg
    }

    char buf[BUF_SIZE] = {0};
    while (!ifs.eof())
    {
        ifs.getline(buf, BUF_SIZE);
        if (buf[0] == '\n' || buf[0] == '#' || buf[0] == '\0')
        {
            continue;
        }

        if (buf[0] == '[')
        {
            char *savePtr = NULL;
            char *attri = buf+1;
            attri = strtok_r(attri, "]", &savePtr);
            if (strcmp(attri, "Config") != 0)
            {
                break;
                // TODO err_msg
            }
        }
        else 
        {
            char *savePtr = NULL;
            char *attri = strtok_r(buf, "=", &savePtr);
            if (configSet.find(attri) == configSet.end())
            {
                continue;
            }
            char *key = attri;
            int len = strlen(attri);
            attri = strtok_r(buf + len + 1, ";", &savePtr);
            configMap[key] = attri;
        }
    }

    ifs.close();
}

static void setConfig()
{
    auto pair = configMap.find("sys_data_path");
    if (pair != configMap.end())
    {
        DATA_PATH = pair->second;
    }

    pair = configMap.find("sys_data_file_name");
    if (pair != configMap.end())
    {
        DATA_PATH = pair->second;
    }
}

#endif