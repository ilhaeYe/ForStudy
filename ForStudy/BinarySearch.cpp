#include <iostream>
#include <vector>
using namespace std;

//
// Q1. 숫자로 이루어진 배열이 있습니다.
// 이 배열은 동일 숫자가 2 개씩 연속해서 존재하지만,
// 그 중 하나의 숫자는 1 개만 존재합니다.
// (각 숫자는 이 배열 안에 최대 2개 까지 존재할 수 있습니다.
// 
// [1, 1, 3, 3, 5, 4, 4, 6, 6]	(5 가 1개만 존재, 1, 3, 4, 6 은 2 개씩 존재)
//
// 이 때, 시간복잡도를 고려해서, 하나만 존재하는 숫자를 찾아내는 함수를 만들어 보세요.
//



// 같은 숫자는 2 개씩 연속해서 존재한다는 점을 이용하여
// 1 개씩 전체를 탐색하는 것보다 
// 2 개씩 탐색하므로 시간복잡도가 반 만큼 더 이득입니다.
int Solution(const std::vector<int>& numbers)
{
	for (std::vector<int>::const_iterator cit = numbers.cbegin(); cit != numbers.end(); cit += 2)	// (n / 2) + 1
		if (cit == numbers.cend() - 1 || (*cit) != (*(cit + 1))) return (*cit);						// (n / 2)
}																									// 총 2 * (n / 2) :: O(n)

// 위의 방법보다 좀 더 빠른 방법.
// 시간복잡도 힌트 :: O(log n)
// BinarySearch가 log n의 복잡도를 가짐. (BinarySearch :: 2진 검색)
// 기존  [1][1][3][3][5][4][4][6][6] 을

// 힌트  [0][0][0][0][1][0][0][0][0] 으로 생각해보자,
//        ^           ^           ^
// 1. 가운데가 왼쪽이랑 같은 경우 오른쪽은 짝수 갯수, 
//    따라서 왼쪽에 홀수 갯수이므로 왼쪽을 서치,
// 2. 가운데가 오른쪽이랑 같은 경우 왼쪽은 짝수 갯수,
//    따라서 오른쪽에 홀수 갯수이므로 오른쪽을 서치,
// 3. 둘다 아닌 경우엔 가운데가 홀수 갯수 이므로 가운데 반환

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



