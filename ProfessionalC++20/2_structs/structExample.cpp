//使用module到处的结构体示例
//导入结构体，初始化并打印内容
import <iostream>;
import <format>;
import employee;

int main()
{
	Employee emp = { 'J','D',42,8000 };
	using std::cout;
	using std::endl;
	using std::format;
	cout << format("Employee:{} {}", emp.firstInitial, emp.lastInitial) << endl;
	cout << format("Number: {}, Salary: {}", emp.employeeNumber, emp.salary) << endl;
	return 0;
}
