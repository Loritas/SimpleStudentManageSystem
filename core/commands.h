/*
 * @Author: Loritas 2223292817@qq.com
 * @Date: 2022-06-10 12:56:10
 * @LastEditors: Loritas 2223292817@qq.com
 * @LastEditTime: 2022-06-12 00:38:16
 * @FilePath: /SimpleStudentManageSystem/core/commands.h
 * @Description: 
 * Copyright (c) 2022 by Loritas 2223292817@qq.com, All Rights Reserved. 
 */
#ifndef __COMMANDS_H__
#define __COMMANDS_H__
#include <iostream>
#include <sstream>
#include "config.h"

typedef std::string string;
typedef void(*commandFunc)(const std::vector<string>&, int, char*);

static std::unordered_map<string, commandFunc> commandsMap;
static std::unordered_map<string, string> helpMap;

const static string HELP = "help";
const static string ADD = "add";
const static string SELECT = "select";
const static string UPDATE = "update";
const static string DELETE = "delete";
const static string SAVE = "save";
const static string QUIT = "q";

static void initCommandsMap();
static void execCommands(const string &cmd, char *msg);

static void help(const std::vector<string> &args, int argc, char *msg);
static void add(const std::vector<string> &args, int argc, char *msg);
static void select(const std::vector<string> &args, int argc, char *msg);
static void update(const std::vector<string> &args, int argc, char *msg);
static void _delete(const std::vector<string> &args, int argc, char *msg);
static void save(const std::vector<string> &args, int argc, char *msg);

static void execCommands(const string &cmd, char *msg)
{
    if (cmd[0] == '\n' || cmd[0] == '#' || cmd[0] == '\0')
    {
        sprintf(msg, "");
        return;
    }
    int len = cmd.length();
    int idx = 0;
    
    std::vector<string> args;
    
    std::stringstream ss(cmd);
    string item;
    while (std::getline(ss, item, ' '))
    {
        args.push_back(item);
        idx++;
    }
    auto cmdFuncKey = commandsMap.find(args[0]);
    if (cmdFuncKey == commandsMap.end())
    {
        sprintf(msg, "unknow command: %s \n", args[0].c_str());
        return;
    }
    commandFunc cmdFunc = cmdFuncKey->second;
    (*cmdFunc)(args, idx-1, msg);
}

static void help(const std::vector<string> &args, int argc, char *msg)
{
    if (argc == 0)
    {
        sprintf(msg, "help- system has 7 commands: help/add/select/update/delete/save/q\nuse 'help [command]' to get more information\n");
        return;
    }

    if (argc > 1)
    {
        sprintf(msg, "help- error: too much values\n");
        return;
    }
    auto command = helpMap.find(args[1]);
    if (command == helpMap.end())
    {
        sprintf(msg, "help- unknow command: %s \n", args[1].c_str());
    }
    else
    {
        sprintf(msg, "%s", command->second.c_str());
    }
}

static void add(const std::vector<string> &args, int argc, char *msg)
{
    if (argc > 4)
    {
        sprintf(msg, "add- error: too much values\n");
        return;
    }

    if (argc < 4)
    {
        sprintf(msg, "add- error: need more values\n");
        return;
    }

    if (sList.getStudent(args[1]).getCppScore() == -1)
    {
        sprintf(msg, "add failed because the duplicate sid: %s\n", args[1].c_str());
    }
    Student stu = Student(args[1], args[2], atof(args[3].c_str()), atof(args[4].c_str()));
    sList.addStudent(stu);
    sprintf(msg, "add student '%s' to the list\n", args[1].c_str());
}

static void select(const std::vector<string> &args, int argc, char *msg)
{
    if (argc > 2)
    {
        sprintf(msg, "select- error: too much values\n");
        return;
    }

    if (argc < 1)
    {
        sprintf(msg, "select- error: need more values\n");
        return;
    }

    if (sList.studentSum() == 0)
    {
        sprintf(msg, "list is empty now, please add some student\n");
        return;
    }
    
    if (args[1] == "all")
    {
        if (argc == 1 || args[2] == "incr")
        {
            sList.incrSort();
        }
        else if (args[2] == "desc")
        {
            sList.descSort();
        }

        auto list = sList.getList();
        std::cout <<  "==========" << std::endl;
        for(std::vector<Student>::iterator iter= list.begin(); iter != list.end(); iter++)
        {       
            std::cout << "Sid: " << iter->getSid() << std::endl;
            std::cout << "Name: " << iter->getName() << std::endl;
            std::cout << "CppScore: " << iter->getCppScore() << std::endl;
            std::cout << "JavaScore: " << iter->getJavaScore() << std::endl << std::endl;
        }
        sprintf(msg, "select completed\n");
    }
    else if (args[1] == "sid")
    {
        if (argc != 2)
        {
            sprintf(msg, "select- error: need student sid \n");
            return;
        }
        Student stu = sList.getStudent(args[2]);
        if (stu.getCppScore() == -1)
        {
            sprintf(msg, "unknown student, sid: %s \n", args[2].c_str());
            return;
        }
        std::cout <<  "==========" << std::endl;
        std::cout << "Sid: " << stu.getSid() << std::endl;
        std::cout << "Name: " << stu.getName() << std::endl;
        std::cout << "CppScore: " << stu.getCppScore() << std::endl;
        std::cout << "JavaScore: " << stu.getJavaScore() << std::endl << std::endl;
        sprintf(msg, "select completed\n");
    }
    else
    {
        sprintf(msg, "select- error: wrong value %s\n", args[1].c_str());
        return;
    }
    
}

static void update(const std::vector<string> &args, int argc, char *msg)
{
    if (argc > 5)
    {
        sprintf(msg, "update- error: too much values\n");
        return;
    }

    if (argc < 5)
    {
        sprintf(msg, "update- error: need more values\n");
        return;
    }
    
    if (!sList.updateStudent(args[1], args[2], args[3], args[4], args[5]))
    {
        sprintf(msg, "unknown student or duplicate sid, sid: %s, new sid: %s\n", args[1].c_str(), args[2].c_str());
        return;
    }
    sprintf(msg, "update completed\n");
}

static void _delete(const std::vector<string> &args, int argc, char *msg)
{
    if (argc > 1)
    {
        sprintf(msg, "delete- error: too much values\n");
        return;
    }

    if (argc < 1)
    {
        sprintf(msg, "delete- error: need more values\n");
        return;
    }

    if (!sList.deleteStudent(args[1]))
    {
        sprintf(msg, "unknown student, sid: %s\n", args[1].c_str());
        return;
    }
    sprintf(msg, "delete student completed, sid: %s\n", args[1].c_str());
}

static void save(const std::vector<string> &args, int argc, char *msg)
{
    saveStudentData();
    sprintf(msg, "save completed\n");
}

static void initCommandsMap()
{
    commandsMap[HELP] = &help;
    commandsMap[ADD] = &add;
    commandsMap[SELECT] = &select;
    commandsMap[UPDATE] = &update;
    commandsMap[DELETE] = &_delete;
    commandsMap[SAVE] = &save;

    helpMap[HELP] = "(you really don't konw how to use 'help' huh)\n'help' usage: help [command]\n";
    helpMap[ADD] = "'add' usage: add [StudentName] [StudentSid] [CppScore] [JavaScore]\n";
    helpMap[SELECT] = "'select usage: select [option: all / sid] [-sid: StudentSid] [order: desc/incr]\n";
    helpMap[UPDATE] = "'update' usage: update [StudentSid] [New Sid] [New name] [New CppScore] [New JavaScore]\n";
    helpMap[DELETE] = "'delete' usage: delete [StudentSid]\n";
    helpMap[SAVE] = "'save' usage: save\n";
    helpMap[QUIT] = "enter command 'q' can quit the system\n";
}


#endif