#include <iostream>
#include <vector>
using namespace std;

//
// Q1. ���ڷ� �̷���� �迭�� �ֽ��ϴ�.
// �� �迭�� ���� ���ڰ� 2 ���� �����ؼ� ����������,
// �� �� �ϳ��� ���ڴ� 1 ���� �����մϴ�.
// (�� ���ڴ� �� �迭 �ȿ� �ִ� 2�� ���� ������ �� �ֽ��ϴ�.
// 
// [1, 1, 3, 3, 5, 4, 4, 6, 6]	(5 �� 1���� ����, 1, 3, 4, 6 �� 2 ���� ����)
//
// �� ��, �ð����⵵�� ����ؼ�, �ϳ��� �����ϴ� ���ڸ� ã�Ƴ��� �Լ��� ����� ������.
//



// ���� ���ڴ� 2 ���� �����ؼ� �����Ѵٴ� ���� �̿��Ͽ�
// 1 ���� ��ü�� Ž���ϴ� �ͺ��� 
// 2 ���� Ž���ϹǷ� �ð����⵵�� �� ��ŭ �� �̵��Դϴ�.
int Solution(const std::vector<int>& numbers)
{
	for (std::vector<int>::const_iterator cit = numbers.cbegin(); cit != numbers.end(); cit += 2)	// (n / 2) + 1
		if (cit == numbers.cend() - 1 || (*cit) != (*(cit + 1))) return (*cit);						// (n / 2)
}																									// �� 2 * (n / 2) :: O(n)

// ���� ������� �� �� ���� ���.
// �ð����⵵ ��Ʈ :: O(log n)
// BinarySearch�� log n�� ���⵵�� ����. (BinarySearch :: 2�� �˻�)
// ����  [1][1][3][3][5][4][4][6][6] ��

// ��Ʈ  [0][0][0][0][1][0][0][0][0] ���� �����غ���,
//        ^           ^           ^
// 1. ����� �����̶� ���� ��� �������� ¦�� ����, 
//    ���� ���ʿ� Ȧ�� �����̹Ƿ� ������ ��ġ,
// 2. ����� �������̶� ���� ��� ������ ¦�� ����,
//    ���� �����ʿ� Ȧ�� �����̹Ƿ� �������� ��ġ,
// 3. �Ѵ� �ƴ� ��쿣 ����� Ȧ�� ���� �̹Ƿ� ��� ��ȯ

int main()
{
	std::vector<int> numbers;
	numbers.push_back(1);
	numbers.push_back(1);
	numbers.push_back(3);
	numbers.push_back(3);
	numbers.push_back(5);
	//numbers.push_back(5);
	numbers.push_back(4);
	numbers.push_back(4);
	numbers.push_back(6);
	numbers.push_back(6);

	int result = Solution(numbers);

	cout << result << endl;

	return 0;
}



