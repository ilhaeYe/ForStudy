#include <iostream>
#include <vector>
using namespace std;

template <typename T>
void copy(typename vector<T>::iterator b, typename vector<T>::iterator e)
{
	vector<T> dst;
	// copy
	for (typename vector<T>::iterator it = b; it != e; it++)
		dst.push_back((*it));
	
	// print
	for (typename vector<T>::iterator it = dst.begin(); it != dst.end(); it++)
		cout << (*it) << " ";

	cout << endl;

}

int main()
{
//	vector<int> src(2);
	vector<float> src(2);
	src[0] = 10;
	src[1] = 20;

//	copy<int>(src.begin(), src.end());
	copy<float>(src.begin(), src.end());

	return 0;
}

// main 함수의 소스코드는 변하지만, ( 사용자 )
// copy 함수의 소스코드는 변하질 않음. ( 제공자 )
// 


