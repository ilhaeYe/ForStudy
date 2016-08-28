#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

int main()
{
	int size = 100000;

	vector<int> v(size);

	clock_t begin_time = clock();
	for (int i = 0; i < size; i++)
	{
		v[i] = 0;
	}
	float test1 = float(clock() - begin_time) / CLOCKS_PER_SEC;


	vector<int> v2(size);
	clock_t begin_time2 = clock();
	for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
	{
		(*it) = 0;
	}
	float test2 = float(clock() - begin_time) / CLOCKS_PER_SEC;

	cout << "test1 :: " << test1 << endl;
	cout << "test2 :: " << test2 << endl;

	return 0;
}


// size 10000 
// test 1 :: 0.004
// test 2 :: 0.029

// size 100000
// test 1 :: 0.039
// test 2 :: 0.31

// vector�� ���� ���ٿ� ����ȭ �Ǿ� �����Ƿ�,
// iterator ���ٴ� index�� �ӵ��� ������.

// �׷����� iterator�� ����ϴ� ������ ������ ����,
// �������� �ҽ��ڵ带 ���� ���.
// �� �ڼ��� ������ WhyIterator.cpp ����
