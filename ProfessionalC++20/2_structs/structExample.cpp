//ʹ��module�����Ľṹ��ʾ��
//����ṹ�壬��ʼ������ӡ����
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
