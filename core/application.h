/*
 * @Author: Loritas 2223292817@qq.com
 * @Date: 2022-06-10 18:57:36
 * @LastEditors: Loritas 2223292817@qq.com
 * @LastEditTime: 2022-06-10 19:56:51
 * @FilePath: /SimpleStudentManageSystem/core/application.h
 * @Description: 
 * Copyright (c) 2022 by Loritas 2223292817@qq.com, All Rights Reserved. 
 */
#include "commands.h"

static void runApplication();

static void runApplication()
{
    std::cout << "Welcome to the Simple Student Manage System!" << std::endl;
    std::cout << "enter 'q' to quit from the system" << std::endl;
    std::cout << "use 'help' to get the usage of a command" << std::endl;
    std::cout << "hind: command can only be lowercase" << std::endl;

    init();
    readStudentData();
    initCommandsMap();
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