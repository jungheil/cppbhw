## 注意事项

1. 本项目IDE环境为Clion，使用的编译工具为Cmake，建议使用Cmake 3.17以上版本编译。
2. Release文件夹中是用Cmake的Release模式编译的程序。
3. `doc.md`或`doc.pdf`是本次作业的相关文档。
4. 若自行编译，不建议在Clion中运行，建议双击打开可执行文件，使用系统的命令窗口执行，否则`system("cls")`不能清屏。
5. 运行第一个程序时，因为程序要读取汇率，所以必须在程序目录新建一个存有汇率的`rate.csv`档，否则会闪退。可在Release文件夹中拷贝。
6. 运行最后一个程序时，可从Release文件中拷贝`employee.csv`和`config.csv`。这样程序就能自动读取我已经存入的员工信息和设置。在此基础上也能进行增、删、改、保存。
7. 由于一开始不小心把github仓库设置成public了，所以干脆开源，[点击这里](https://github.com/jungheil/cppbhw)访问仓库。

