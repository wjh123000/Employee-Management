#include "workerManager.h"

WorkerManager::WorkerManager(){
	//1.文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open()) {
		//cout << "文件不存在!" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = nullptr;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//2.文件存在但内容为空
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//cout << "文件为空!" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = nullptr;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//3.文件存在且内容不为空
	this->m_FileIsEmpty = false;
	int num = this->get_EmpNum();
	//cout << "职工人数: " << num << endl;
	this->m_EmpNum = num;
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	this->init_Emp();//从文件中读取数据，初始化员工信息

	//for (int i = 0;i < this->m_EmpNum;i++) {
	//	cout << "职工编号: " << this->m_EmpArray[i]->m_Id
	//		<< "\t职工姓名: " << this->m_EmpArray[i]->m_Name
	//		<< "\t岗位编号: " << this->m_EmpArray[i]->m_DeptId << endl;
	//}
	
}

WorkerManager::~WorkerManager(){
	if (this->m_EmpArray != nullptr) {
		for (int i = 0; i < this->m_EmpNum; i++) {
			if (this->m_EmpArray[i] != nullptr) {
				delete this->m_EmpArray[i];
			}
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = nullptr;
	}

}

void WorkerManager::Show_Menu() {
	cout << "*********************************" << endl;
	cout << "*******欢迎使用职工管理系统!*******" << endl;
	cout << "********* 0.退出管理程序 *********" << endl;
	cout << "********* 1.增加职工信息 *********" << endl;
	cout << "********* 2.显示职工信息 *********" << endl;
	cout << "********* 3.删除职工信息 *********" << endl;
	cout << "********* 4.修改职工信息 *********" << endl;
	cout << "********* 5.查找职工信息 *********" << endl;
	cout << "********* 6.按照编号排序 *********" << endl;
	cout << "********* 7.清空所有文档 *********" << endl;
	cout << "*********************************" << endl;
	cout << endl;
}

void WorkerManager::ExitSystem() {
	cout << "欢迎下次使用!" << endl;
	system("pause");
	exit(0);
}

//添加职工
void WorkerManager::Add_Emp() {
	cout << "请输入要添加的职工数量: " << endl;
	int addNum = 0;
	cin >> addNum;

	if (addNum > 0) {
		//添加职工
		//计算添加新空间的大小
		int newSize = this->m_EmpNum + addNum;

		//开辟新空间
		Worker** newSpace = new Worker * [newSize];
		//将原来空间的数据拷贝到新空间
		if (this->m_EmpArray != nullptr) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		
		//输入新数据
		for (int i = 0;i < addNum; i++) {
			int id;
			string name;
			int dSelect;
			cout << "请输入第" << i + 1 << "个新职工编号: " << endl;
			cin >> id;
			if (this->IsExist(id) != -1) {
				cout << "职工编号已存在，请重新输入!" << endl;
				i--;
				continue;
			}


			cout << "请输入第" << i + 1 << "个新职工姓名: " << endl;
			cin >> name;
			cout << "请输入第" << i + 1 << "个新职工岗位: " << endl;
			cout << "1.员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dSelect;

			Worker* worker = nullptr;
			switch (dSelect) {
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}

			//将创建的职工对象指针保存到数组中
			newSpace[this->m_EmpNum + i] = worker;

		}

		//释放原来空间
		delete[] this->m_EmpArray;
		//更改新空间的指向
		this->m_EmpArray = newSpace;
		//更新职工人数
		this->m_EmpNum = newSize;
		//提示添加成功
		cout << "成功添加" << addNum << "名新职工!" << endl;
		this->m_FileIsEmpty = false;

		//保存文件
		this->save();

	}
	else {
		cout << "输入数据有误" << endl;
	}
	//按任意键，清屏回到上级目录
	system("pause");
	system("cls");

}

void WorkerManager::save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out); //以写的方式打开文件
	//将职工人数写入文件
	for (int i = 0;i < this->m_EmpNum;i++) {
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	ofs.close();
}


int WorkerManager::get_EmpNum() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in); //以读的方式打开文件

	int id;
	string name;
	int deptId;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> deptId) {
		num++;
	}
	ifs.close();
	return num;
}

void WorkerManager::init_Emp() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in); //以读的方式打开文件

	int id;
	string name;
	int deptId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> deptId) {
		Worker* worker = nullptr;
		if (deptId == 1) {
			worker = new Employee(id, name, deptId);
		}
		else if (deptId == 2) {
			worker = new Manager(id, name, deptId);
		}
		else if (deptId == 3) {
			worker = new Boss(id, name, deptId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}

	ifs.close();
}

void WorkerManager::Show_Emp() {
	//判断文件是否为空
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空!" << endl;
	}
	else {
		for (int i = 0; i < this->m_EmpNum; i++) {
			this->m_EmpArray[i]->showInfo();
		}
	}

	system("pause");
	system("cls");
	
}

int WorkerManager::IsExist(int id) {
	int index = -1;

	for (int i = 0;i < this->m_EmpNum;i++) {
		if (this->m_EmpArray[i]->m_Id == id) {
			index = i;
			break;
		}
	}

	return index;
}

void WorkerManager::Del_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空!" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "请输入要删除的职工编号: " << endl;
	int id = 0;
	cin >> id;
	
	int index = this->IsExist(id);

	if (index != -1) {
		delete this->m_EmpArray[index];
		for (int i = index; i < this->m_EmpNum - 1; i++) {
			this->m_EmpArray[i] = this->m_EmpArray[i + 1];
		}
		this->m_EmpArray[this->m_EmpNum - 1] = nullptr;
		this->m_EmpNum--;
		this->save();
		cout << "删除成功!" << endl;
	}
	else {
		cout << "删除失败，未找到该职工!" << endl;
	}

	system("pause");
	system("cls");
}


void WorkerManager::Mod_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空!" << endl;
	}
	else {
		cout << "请输入要修改的职工编号: " << endl;
		int id;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1) {
			delete this->m_EmpArray[ret];
			int newId;
			string newName;
			int dSelect;

			cout << "查到： " << id << "号职工，请输入新职工号" << endl;
			cin >> newId;
			cout << "请输入新职工姓名: " << endl;
			cin >> newName;
			cout << "请输入新职工岗位: " << endl;
			cout << "1.员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dSelect;

			Worker* worker = nullptr;
			switch (dSelect) {
			case 1:
				worker = new Employee(newId, newName, 1);
				break;
			case 2:
				worker = new Manager(newId, newName, 2);
				break;
			case 3:
				worker = new Boss(newId, newName, 3);
				break;
			default:
				break;
			}

			//更新数组中的职工指针
			this->m_EmpArray[ret] = worker;

			cout << "修改成功!" << endl;

			this->save();

		}
		else {
			cout << "修改失败，未找到该职工!" << endl;
		}

	}
	system("pause");
	system("cls");
}


void WorkerManager::Find_Emp() {
	if (this->m_FileIsEmpty){
		cout << "文件不存在或记录为空!" << endl;
	}
	else {
		cout << "请输入查找的方式" << endl;
		cout << "1.按职工编号查找" << endl;
		cout << "2.按职工姓名查找" << endl;
		
		int select = 0;
		cin >> select;
		if (select == 1) {
			int id;
			cout << "请输入要查找的职工编号: " << endl;
			cin >> id;

			int ret = this->IsExist(id);
			if (ret != -1) {
				cout << "查找成功!" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else {
				cout << "查找失败，未找到该职工!" << endl;
			}
		}
		else if (select == 2) {
			string name;
			cout << "请输入要查找的职工姓名: " << endl;
			cin >> name;

			bool flag = false;
			for (int i = 0;i < this->m_EmpNum;i++) {
				if (this->m_EmpArray[i]->m_Name == name) {
					if (!flag) {
						cout << "查找成功!" << endl;
						flag = true;
					}
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (!flag) {
				cout << "查找失败，未找到该职工!" << endl;
			}
		}
		else {
			cout << "输入有误!" << endl;
		}
	}
	system("pause");
	system("cls");
	return;
}


void WorkerManager::Sort_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空!" << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "请选择排序方式: " << endl;
		cout << "1.按职工编号升序" << endl;
		cout << "2.按职工编号降序" << endl;

		int select = 0;
		cin >> select;
		for (int i = 0;i < this->m_EmpNum;i++) {
			int minOrMax = i;
			for (int j = i + 1;j < this->m_EmpNum;j++){
				if (select == 1) {
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id) {
						minOrMax = j;
					}
				}
				else {
					if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id) {
						minOrMax = j;
					}
				}
			}
			if (i != minOrMax) {
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}
		cout << "排序成功，排序后结果为: " << endl;
		this->save();
		this->Show_Emp();
	}
	
	return;
}