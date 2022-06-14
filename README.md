# SimpleStudentManageSystem
## 这是什么
学校布置的程序设计实践的大作业，经典项目之学生管理系统（GitHub上看到一个同名的都好多年前的产物了，令人感慨，果然流水的教学铁打的学生管理系统）

代码耦合好严重，头疼

## 环境
Linux/MacOS 等Unix环境

编译器采用GNU/g++，标准是C++11

程序构建使用make

## 构建方法
通过终端进入项目根目录（`/SimpleStudentManageSystem`)后运行`make build`即可构建

## 配置与数据文件
`/SimpleStudentSystem/data`下存放配置文件`config.ini`和数据文件`data.ini`、`aof.storage`

`config.ini`和`aof.storage`的存放位置不可以变更，只能存放在`data`目录下，而数据文件`data.ini`可以自定义存放路径，也可以自定义一个新的数据文件名

所有可修改的配置均包含在`config.ini`文件中

修改以上文件时务必按照示例写法（程序并没有实现标准化的ini读写，仅仅只是个简单模仿，So……）

## AOF持久化
对Redis的AOF持久化功能的拙劣仿制

当`config.ini`中的`aof`为`true`时，程序会开启AOF持久化功能

该功能将取代以往的`data.ini`，将会保存运行期间执行的有关数据更改的命令，然后在保存时写入`aof.storage`

恢复数据时，从`aof.storage`中读取命令并执行

如果`aof.storage`中什么也没有，程序会尝试从`data.ini`中获取数据来构建学生队列

未来会支持AOF文件过大时的内容重构，以缩小一定使用时间后臃肿的`aof.storage`的体积等功能
