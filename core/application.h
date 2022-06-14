/*
 * @Author: Loritas 2223292817@qq.com
 * @Date: 2022-06-10 18:57:36
 * @LastEditors: Loritas 2223292817@qq.com
 * @LastEditTime: 2022-06-14 21:45:41
 * @FilePath: /SimpleStudentManageSystem/core/application.h
 * @Description: 负责应用的初始化与启动
 * Copyright (c) 2022 by Loritas 2223292817@qq.com, All Rights Reserved. 
 */
#include "commands.h"

static void runApplication();

static void runApplication()
{
    init();
    initCommandsMap();
    readStudentData();
    initFlag = false;
    
    std::cout << "Welcome to the Simple Student Manage System!" << std::endl;
    std::cout << "enter 'q' to quit from the system" << std::endl;
    std::cout << "use 'help' to get the usage of a command" << std::endl;
    std::cout << "hint: command can only be lowercase" << std::endl;

    while (true)
    {
        std::cout << "% ";
        char buf[1024];
        std::cin.getline(buf, 1024);
        if (buf[0] != 'q')
        {
            char msg[128];
            execCommands(buf, msg);
            std::cout << msg;
        }
        else
        {
            break;
        }
    }
    saveStudentData();
}