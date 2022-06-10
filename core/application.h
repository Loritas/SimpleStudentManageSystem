/*
 * @Author: Loritas 2223292817@qq.com
 * @Date: 2022-06-10 18:57:36
 * @LastEditors: Loritas 2223292817@qq.com
 * @LastEditTime: 2022-06-10 19:04:15
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
    std::cout << "use 'helo' to get the usage of a command" << std::endl;

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
            std::cout << buf << std::endl;
            char msg[128];
            execCommands(buf, msg);
            std::cout << msg;
            memset(msg, '\0', 128);
        }
        else
        {
            break;
        }
    }
    saveStudentData();
}