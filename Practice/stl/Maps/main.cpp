#include <iostream>
#include <map>
using namespace std;

int main(int argc, char *argv[])
{

	// 1.初始化一个map
	map<int, char> m;

	// 2.插入一个键值对
	m.insert(pair<int, char>(1, 'a'));
	m.insert(pair<int, char>(2, 'b'));
	m.insert(pair<int, char>(3, 'c'));
	// 或者这种方式
	m[4] = 'd';
	m[5] = 'e';
	// 3.迭代器输出键值对
	cout << "iterator output:" << endl;
	map<int, char>::iterator it;
	for (it = m.begin(); it != m.end(); it++)
	{
		cout << it->first << " => " << it->second << endl;
	}

	// 4.返回指定元素出现的次数
	cout << "count('a')= " << m.count('a') << endl;
	if (m.empty() == true)
	{
		cout << "empty()=true" << endl;
	}
	else
	{
		cout << "empty()=false" << endl;
	}

	// 5.查找一个元素（key）,返回指向这个key键值对迭代器
	it = m.find(3);
	cout << "search an element(c):" << it->first << "=>" << it->second << endl;

	// 6.删除一个元素（key=3），传入的参数为迭代器。
	m.erase(m.find(3));
	cout << "erased a key" << endl;

	// 7.lower_bound()返回指定key的上界，即第一个value
	it = m.lower_bound(2);
	cout << "lower_bound:" << it->first << "=>" << it->second << endl;

	// 8.map能够保存的最大元素个数
	cout << "max_size(): " << m.max_size() << endl;

	// 9.使用逆迭代器(reverse_iterator)倒序输出
	cout << "reverse_iterator output:" << endl;
	map<int, char>::reverse_iterator rit;
	for (rit = m.rbegin(); rit != m.rend(); rit++)
	{
		cout << rit->first << " => " << rit->second << endl;
	}

	// 10.输出map的键值对数
	cout << "size():" << m.size() << endl;

	cout << endl;
	system("pause");
	return 0;
}
