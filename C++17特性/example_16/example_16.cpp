#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

void split(const string& s, vector<string>& v, const string& c)
{
	string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while(string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2-pos1));
		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if(pos1 != s.length())
		v.push_back(s.substr(pos1));
}

void parseWildcard(const string& enteredValue, std::vector<string>& v)
{
	
	string::size_type pos1=enteredValue.find("[");
	string::size_type pos2=enteredValue.find("]");
	if(string::npos == pos1 || string::npos == pos2)
	{
		v.push_back(enteredValue);
		return;
	}
	else if (string::npos == pos1 || string::npos == pos2 || pos1 > pos2)
	{
		std::cout<<"wrong format"<<std::endl;
		return;
	}

	string value1=enteredValue.substr(0, pos1);
	string value2=enteredValue.substr(pos1+1, pos2-1-pos1);
	if(value2.find("...") == string::npos)
	{
		cout<<"wrong format"<<endl;
		return;
	}

	vector<string> vec;
	split(value2,vec,"...");
	if(vec.size() == 2)
	{
		int start=std::stoi(vec[0]);
		int end= std::stoi(vec[1]);
		if (end < start)
		{
			cout<<"wrong format"<<endl;
			return;
		}
		string tmp;
		for(int i=start; i<=end; i++)
		{
			tmp=value1 + std::to_string(i);

			v.push_back(std::move(tmp));
		}
	}
	else
	{
		cout<<"wrong format"<<endl;
	}
}

void parseInterface(const string& enteredValue, string& output)
{
	vector<string> vec;
	vector<string> v;

	if (enteredValue.find("[") == string::npos && enteredValue.find("]") == string::npos)
	{
		cout<<1<<endl;
		output=enteredValue;
	}
	else
	{
		split(enteredValue, vec, ",");
		for (auto ve : vec)
		{ 

			// if(string::npos != ve.find("["))
				parseWildcard(ve, v);
		}

		vector<string>::iterator it=v.begin();
		output = (*it);
		it++;
		for (;it!=v.end();it++)
		{
			output +=",";
			output +=(*it);
		}
	}
}

int main()
{
	// string enteredValue="1/1/7/2,1/1/7/[3...8]";
	string enteredValue="1/1/7/2";
	// string enteredValue="1/1/7/2,1/1/7/3,1/1/7/4";
	string outValue="";
	parseInterface(enteredValue, outValue);
	
	cout<<outValue<<endl;
	cout<<strlen((char*)outValue.c_str())<<endl;
	cout<<outValue.size()<<endl;
	
	system("pause");
	return 0;
}