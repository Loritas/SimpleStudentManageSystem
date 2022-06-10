/*
 * @Author: Loritas 2223292817@qq.com
 * @Date: 2022-06-10 12:56:10
 * @LastEditors: Loritas 2223292817@qq.com
 * @LastEditTime: 2022-06-10 19:03:44
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
        return;
    }
    int len = cmd.length();
    int idx = 0;
    
    std::vector<string> args;
    
    std::stringstream ss(cmd);
    string item;
    while (std::getline(ss, item, ' '))
    {
        std::cout << item << std::endl;
        args.push_back(item);
        idx++;
    }
    auto cmdFuncKey = commandsMap.find(args[0]);
    if (cmdFuncKey == commandsMap.end())
    {
        std::cout << args[0] << std::endl;
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
        sprintf(msg, "system has 7 commands: help/add/select/update/delete/save/q\nuse 'help [command]' to get more information\n");
        return;
    }

    if (argc > 1)
    {
        sprintf(msg, "error: too much values\n");
        return;
    }
    auto command = helpMap.find(args[1]);
    if (command == helpMap.end())
    {
        sprintf(msg, "unknow command: %s \n", args[1].c_str());
    }
    else
    {
        sprintf(msg, "%s", command->second.c_str());
    }
}

static void initCommandsMap()
{
    commandsMap[HELP] = &help;
    // commandsMap[ADD] = &add;
    // commandsMap[SELECT] = &select;
    // commandsMap[UPDATE] = &update;
    // commandsMap[DELETE] = &_delete;

    helpMap[HELP] = "(you really don't konw how to use 'help' huh)\n'help' usage: help [command]\n";
    helpMap[ADD] = "'add' usage: add [StudentName] [StudentSid] [JavaScore] [CppScore]\n";
    helpMap[SELECT] = "'select usage: select [option: -all / -sid] [-sid: StudentSid]\n";
    helpMap[UPDATE] = "'update' usage: update [StudentSid] [New Sid] [New name] [New JavaScore] [New CppScore]\n";
    helpMap[DELETE] = "'delete' usage: delete [StudentSid]\n";
    helpMap[SAVE] = "'save' usage: save\n";
    helpMap[QUIT] = "enter command 'q' can quit the system";
}


#endif