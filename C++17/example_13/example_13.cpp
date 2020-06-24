#include <iostream>
#include <string>
#include <regex>
using namespace std;

int main()
{
	string files[]={"foo.txt", "bar.txt", "test", "a0.txt", "AAA.txt"};
	//生成正则对象
	regex txt_regex("[a-z]+\\.txt");
	//仅查询
	for (const auto &file : files)
	{
		cout<<file<<": "<<regex_match(file, txt_regex)<<endl;
	}
	cout<<"========================"<<endl;

	smatch matches;
	for (const auto &file : files)
	{
		if (regex_match(file, matches, txt_regex))
		{
			//smatch第一个元素为整个字符串
			cout<<"whole string: "<<matches[0].str()<<endl;
			cout<<"match: "<<matches[1].str()<<endl;
		}
	}	
}