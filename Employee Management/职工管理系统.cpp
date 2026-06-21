#include<iostream>
using namespace std;
#include "workerManager.h"



int main() {
	//创建职工管理系统对象
	WorkerManager wm;
	int choice = 0;
	while (true) {
		//调用展示菜单的函数
		wm.Show_Menu();
		cout << "请输入您的选择: " << endl;
		cin >> choice;

		switch (choice) {
		case 0: //退出系统
			wm.ExitSystem();
			break;
		case 1://增加职工信息
			break;
		case 2://显示职工信息
			break;
		case 3://删除职工信息
			break;
		case 4://修改职工信息
			break;
		case 5://查找职工信息
			break;
		case 6://按照编号排序
			break;
		case 7://清空所有文档
			break;
		default:
			system("cls");//清屏
			break;
		}

	}
	

	system("pause");
	return 0;
}