#include <iostream>

using namespace std;
class SingleTon
{
public:
	static SingleTon *GetInstance()
	{
		return m_single;
	}
	void print(string text)
	{
		cout << text << endl;
		m_count++;
	}
	int GetCount()
	{
		return m_count;
	}
private:
	SingleTon()
	{
		cout << "构造函数调用" << endl;
		m_count = 0;
	}
	SingleTon(const SingleTon & p){};
	SingleTon & operator= (const SingleTon&);
	static 	SingleTon *m_single;
	int m_count;
};
SingleTon *SingleTon::m_single = new SingleTon;

void test()
{
	SingleTon *p1 = SingleTon::GetInstance();
	p1->print("222");
	p1->print("333");
	cout << "m_count = " << p1->GetCount() << endl;
}
int main()
{
	test();
	SingleTon *p1 = SingleTon::GetInstance();
	p1->print("11111");
	cout << "m_count = " << p1->GetCount() << endl;
}