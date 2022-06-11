# SimpleStudentManageSystem
## 这是什么
学校布置的程序设计实践的大作业，经典项目之学生管理系统

## 环境
Linux/MacOS 等Unix环境

编译器采用GNU/g++，标准是C++11

程序构建使用make

## 构建方法
通过终端进入项目根目录（`/SimpleStudentManageSystem`)后运行`make build`即可构建

## 配置与数据文件
`/SimpleStudentSystem/data`下存放配置文件`config.ini`和数据文件`data.ini`

`config.ini`的存放位置不可以变更，只能存放在`data`目录下，而数据文件`data.ini`可以自定义存放路径，也可以自定义一个新的数据文件名

所有可修改的配置均包含在`config.ini`文件中

修改以上文件时务必按照示例写法（程序并没有实现标准化的ini读写，仅仅只是个简单模仿，So……）
