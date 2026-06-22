#pragma once  //防止头文件被重复包含
#include<iostream>
using namespace std;

#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

#include <fstream>
#define FILENAME "empFile.txt"

class WorkerManager
{
public:

	WorkerManager();
	//显示菜单
	void Show_Menu();

	//退出系统
	void ExitSystem();

	//记录职工人数
	int m_EmpNum; 

	//添加职工
	void Add_Emp();

	//保存文件 
	void save();

	//初始化员工
	void init_Emp();

	//显示职工
	void Show_Emp();

	~WorkerManager();

	bool m_FileIsEmpty;
	//职工数组指针
	Worker** m_EmpArray;
	//统计文件中的人数
	int get_EmpNum();
};