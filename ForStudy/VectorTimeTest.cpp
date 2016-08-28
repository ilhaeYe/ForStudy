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

// vector는 랜덤 접근에 최적화 되어 있으므로,
// iterator 보다는 index가 속도가 빠르다.

// 그럼에도 iterator를 사용하는 이유는 다형성 때문,
// 독립적인 소스코드를 위해 사용.
// 더 자세한 내용은 WhyIterator.cpp 참고
