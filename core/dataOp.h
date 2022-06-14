/*
 * @Author: Loritas 2223292817@qq.com
 * @Date: 2022-06-09 17:50:00
 * @LastEditors: Loritas 2223292817@qq.com
 * @LastEditTime: 2022-06-14 21:54:37
 * @FilePath: /SimpleStudentManageSystem/core/dataOp.h
 * @Description: 
 * Copyright (c) 2022 by Loritas 2223292817@qq.com, All Rights Reserved. 
 */
#ifndef __WRITER_H__
#define __WRITER_H__
#include <fstream>
#include "config.h"

static int AOFBufferSize = 0;

static std::string AOFBuffer[AOF_BUF_SIZE];

template<class T>
static void writeHead(T, std::ofstream &);
template<class T>
static void writeData(std::string, T, std::ofstream &);
static void writeIniHeadAnnotation(std::ofstream &);
static void writeAOFHeadAnnotation(std::ofstream &);

extern void execCommands(const std::string &cmd, char *msg);

static void saveStudentData();
static void readStudentData();
static void aofRead();
static void aofSave();

template<class T>
static void writeHead(T data, std::ofstream &os)
{
    os << std::endl << "[" << data << "]" << std::endl;
}

template<class T>
static void writeData(std::string dataName, T data, std::ofstream &os)
{
    os << dataName << "=" << data << ";" << std::endl;
}

static void writeIniHeadAnnotation(std::ofstream &ofs)
{
    ofs << "# Author: Loritas / loritas@foxmail.com" << std::endl;
    ofs << "# Version: 0.2" << std::endl;
    ofs << "# this format is a poor imitation of ini" << std::endl;
    ofs << "# it can only do a simple check" << std::endl;
    ofs << "# use '#' as an annotation" << std::endl;
    ofs << "# each sequence end by ';'" << std::endl;
    ofs << "# usage: Stu_Name=loritas;" << std::endl;
    ofs << "# do not leave a ' ' besides '=' or the head of each sequence" << std::endl;
}

static void writeAOFHeadAnnotation(std::ofstream &ofs)
{
    ofs << "# Author: Loritas / loritas@foxmail.com" << std::endl;
    ofs << "# Version: 0.2" << std::endl;
    ofs << "# this format is a poor imitation of aof" << std::endl;
    ofs << "# it can only do a simple check" << std::endl;
    ofs << "# use '#' as an annotation" << std::endl;
    ofs << "# and you should not add or change anything except annotation'" << std::endl;
}

static void saveStudentData()
{
    if (AOF)
    {
        aofSave();
        return;
    }
    std::ofstream ofs;
    ofs.open(DATA_PATH+DATA_FILE_NAME, std::ios::out);
    if (!ofs)
    {
        // TODO err_msg
    }   
    writeIniHeadAnnotation(ofs);

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
    if (AOF)
    {
        aofRead();
        return;
    }
    Student curStu;

    std::ifstream ifs;
    // "data.ini"
    ifs.open(DATA_PATH+DATA_FILE_NAME, std::ios::in);
    if (!ifs.is_open())
    {
        std::ofstream ofs;
        ofs.open(DATA_PATH+DATA_FILE_NAME, std::ios::out);
        if (!ofs.is_open())
        {
            // TODO err_msg here
            exit(-1);
        }
        ofs.close();
        ifs.open(DATA_PATH+DATA_FILE_NAME, std::ios::in);
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

static void aofRead()
{
    std::ifstream ifs;
    ifs.open(AOF_PATH, std::ios::in);
    if (!ifs.is_open())
    {
        std::ofstream ofs;
        ofs.open(AOF_PATH, std::ios::out);
        if (!ofs.is_open())
        {
            // TODO err_msg here
            exit(-1);
        }
        ofs.close();
        ifs.open(AOF_PATH, std::ios::in);
    }

    char c;
    ifs >> c;
    if (ifs.eof())
    {
        AOF = false;
        ifs.close();
        readStudentData();
        AOF = true;
        return;
    }

    char buf[BUF_SIZE];
    char log_msg[128];
    
    while (!ifs.eof())
    {
        ifs.getline(buf, BUF_SIZE);
        if (buf[0] == '\n' || buf[0] == '#' || buf[0] == '\0')
        {
            continue;
        }
        execCommands(buf, log_msg);
        // TODO save log
    }

    ifs.close();
}

static void aofSave()
{
    bool emptyFile = false;
    std::ifstream ifs;
    ifs.open(AOF_PATH, std::ios::in);
    if (!ifs.is_open())
    {
        // TODO err_msg here
    }

    char c;
    ifs >> c;
    if (ifs.eof())
    {
        emptyFile = true;
    }
    ifs.close();
    
    std::ofstream ofs;
    ofs.open(AOF_PATH, std::ios::out | std::ios::app);
    if (!ofs.is_open())
    {
        // TODO err_msg here
    }

    if (!emptyFile)
    {
        for (int i = 0; i < AOFBufferSize; i++)
        {
            ofs << AOFBuffer[i] << std::endl;
            AOFBuffer[i].clear();
            AOFBuffer[i].shrink_to_fit();
        }
        AOFBufferSize = 0;
    }
    else {
        auto list = sList.getList();
        char buf[SAVE_BUF_SIZE];
        writeAOFHeadAnnotation(ofs);
        for(std::vector<Student>::iterator iter= list.begin(); iter != list.end(); iter++)
        {       
            sprintf(buf, "add %s %s %lf %lf", iter->getName().c_str(), iter->getSid().c_str(), 
                                            iter->getCppScore(), iter->getJavaScore());
            ofs << buf << std::endl;
        }
    }
    
    ofs.close();
}
#endif