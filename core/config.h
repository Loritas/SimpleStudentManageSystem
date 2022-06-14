/*
 * @Author: Loritas 2223292817@qq.com
 * @Date: 2022-06-09 20:29:44
 * @LastEditors: Loritas 2223292817@qq.com
 * @LastEditTime: 2022-06-14 21:19:42
 * @FilePath: /SimpleStudentManageSystem/core/config.h
 * @Description: 配置程序的各项属性
 * Copyright (c) 2022 by Loritas 2223292817@qq.com, All Rights Reserved. 
 */
#ifndef __CONFIG_H__
#define __CONFIG_H__
#include <unordered_map>
#include <cstring>
#include "../src/studentList.h"

static StudentList sList;

const static std::string CONFIG_PATH = "./SimpleStudentManageSystem/data/config.ini";
const static std::string AOF_PATH = "./SimpleStudentManageSystem/data/aof.storage";

const static int BUF_SIZE = 1024;
const static int SAVE_BUF_SIZE = 1536;
const static int AOF_BUF_SIZE = 2048;

// 我实在没搞明白它的工作路径为什么在这个文件夹外边……
static std::string DATA_PATH = "./SimpleStudentManageSystem/data/";
static std::string DATA_FILE_NAME = "data.ini";

static bool AOF = false;
static bool initFlag = false;

typedef void(Student::*studentSetFunc)(std::string);
static std::unordered_map<std::string, studentSetFunc> studentSetAbtMap;
static std::unordered_set<std::string> configSet;
static std::unordered_map<std::string, std::string> configMap;

static void init();

static void readConfig();
static void setConfig();

static void init()
{
    initFlag = true;
    studentSetAbtMap["Stu_Name"] = &Student::setName;
    studentSetAbtMap["Stu_JavaScore"] = &Student::setJavaScore;
    studentSetAbtMap["Stu_CppScore"] = &Student::setCppScore;

    configSet.insert("sys_data_path");
    configSet.insert("sys_data_file_name");
    configSet.insert("aof");

    readConfig();
    setConfig();
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
        DATA_FILE_NAME = pair->second;
    }

    pair = configMap.find("aof");
    if (pair != configMap.end())
    {
        if (pair->second == "true")
        {
            AOF = true;
        }
    }
}

#endif