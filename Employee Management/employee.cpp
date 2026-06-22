#include "employee.h"

Employee::Employee(int id, string name, int deptId) {
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = deptId;
}

void Employee::showInfo() {
	cout << "职工编号: " << this->m_Id
		<< "\t职工姓名: " << this->m_Name
		<< "\t岗位: 完成经理交给的任务" << this->getDeptName()
		<< endl;
}


string Employee::getDeptName() {
	return string("员工");
}
