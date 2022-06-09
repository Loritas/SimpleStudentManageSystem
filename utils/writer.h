/*
 * @Author: Loritas 2223292817@qq.com
 * @Date: 2022-06-09 17:50:00
 * @LastEditors: Loritas 2223292817@qq.com
 * @LastEditTime: 2022-06-09 23:50:07
 * @FilePath: /SimpleStudentManageSystem/utils/writer.h
 * @Description: 
 * Copyright (c) 2022 by Loritas 2223292817@qq.com, All Rights Reserved. 
 */
#ifndef __WRITER_H__
#define __WRITER_H__
#include <fstream>

template<class T>
const static void writeHead(T data, std::ofstream &os)
{
    os << std::endl << "[" << data << "]" << std::endl;
}

template<class T>
const static void writeData(std::string dataName, T data, std::ofstream &os)
{
    os << dataName << "=" << data << ";" << std::endl;
}

#endif