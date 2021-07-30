//使用module特性，声明一个函数并导出
export module employee;

export struct Employee
{
	char firstInitial;
	char lastInitial;
	int employeeNumber;
	int salary;
};