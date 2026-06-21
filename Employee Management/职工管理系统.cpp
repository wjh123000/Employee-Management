#include<iostream>
using namespace std;
#include "workerManager.h"



int main() {
	//创建职工管理系统对象
	WorkerManager wm;

	//调用展示菜单的函数
	wm.Show_Menu();

	system("pause");
	return 0;
}