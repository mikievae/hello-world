#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <functional>
#include <sstream>
using namespace std;
/**
第十一章、关联容器
有序：map set multimap multiset
无序: unordered_map unordered_set unordered_multimap unordered_multiset
第十二章、动态内存与智能指针
new,在动态内存中为对象分配空间并返回指向该对象的指针。
delete,接受一个动态对象的指针，销毁该对象，并释放与之关联的内存。
接受指针参数 智能指针的构造函数是explicit的。
shared_ptr<int> p1 = new int(1024);//wrong
shared_ptr<int> p1(new int(1024));//right
用new分配一个数组时，会得到一个元素类型的指针。由于分配的内存并不是一个数组类型，因此不能对动态数组调用begin or end.同时也不能用for类处理所谓的动态数组中的元素。
用new分配的对象，不管是单个还是数组，都是默认初始化的，加一个空括号，可以变成值初始化。
*/
class QueryResult {
	friend ostream& print(ostream&, const QueryResult&);
public:
	QueryResult(string s,
		shared_ptr<set<int>> p,
		shared_ptr<vector<string>> f) :
		sought(s), lines(p), file(f) {}
private:
	string sought;
	shared_ptr<set<int>> lines;
	shared_ptr<vector<string>> file;
};

class TextQuery
{
public:
	TextQuery(ifstream&);
	TextQuery() = default;
	QueryResult query(const string&) const;
private:
	shared_ptr<vector<string>> file;
	map<string, shared_ptr<set<int> >> dict;
};

TextQuery::TextQuery(ifstream &is) :file(new vector<string>)
{
	string text;
	while (getline(is, text))
	{
		file->push_back(text);
		int n = file->size() - 1;
		istringstream line(text);
		string word;
		while (line >> word)
		{
			auto &lines = dict[word];
			if (!lines)
				lines.reset(new set<int>);
			lines->insert(n);
		}
	}
}

QueryResult
TextQuery::query(const string &sought) const
{
	static shared_ptr<set<int> > nodate(new set<int>);
	auto loc = dict.find(sought);
	if (loc == dict.end())
		return QueryResult(sought, nodate, file);
	else
		return QueryResult(sought, loc->second, file);
}

void runQueries(ifstream &infile)
{
	TextQuery tq(infile);
	while (true)
	{
		cout << "enter word to look for, or 'q' to quit: ";
		string s;
		if (!(cin >> s) || s == "q") break;
		print(cout, tq.query(s)) << endl;
	}

}



ostream &print(ostream & os, const QueryResult &qr)
{
	os << qr.sought << " occurs " << qr.lines->size() << " "
		<<  "time" << endl;
	for (auto num : *qr.lines)
		os << "\t(line " << num + 1 << ")"
			<< *(qr.file->begin() + num) << endl;
	return os;
	
}

//int main()
//{
//	ifstream i;
//	runQueries(i);
//	return 0;
//}