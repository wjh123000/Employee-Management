#include<iostream>
using namespace std;
#include "workerManager.h"

//#include "worker.h"
//#include "employee.h"
//#include "boss.h"
//#include "manager.h"


int main() {

	//Worker* worker = nullptr;
	//worker = new Employee(1, "张三", 1);
	//worker->showInfo();
	//delete worker;

	//Worker* worker2 = nullptr;
	//worker2 = new Boss(2, "李四", 2);
	//worker2->showInfo();
	//delete worker2;

	//Worker* worker3 = nullptr;
	//worker3 = new Manager(3, "王五", 3);
	//worker3->showInfo();
	//delete worker3;

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
			wm.Add_Emp();
			break;
		case 2://显示职工信息
			wm.Show_Emp();
			break;
		case 3://删除职工信息
			wm.Del_Emp();
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