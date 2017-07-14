#include <iostream>
#include <vector>
#include <ctime>
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
int SolutionIterator(const std::vector<int>& numbers)
{
    for (std::vector<int>::const_iterator cit = numbers.cbegin(); cit != numbers.end(); cit += 2)	// (n / 2) + 1
        if (cit == numbers.cend() - 1 || (*cit) != (*(cit + 1))) return (*cit);						// (n / 2)
}																									// 총 2 * (n / 2) :: O(n)


// 위의 방법보다 좀 더 빠른 방법.
// 시간복잡도 힌트 :: O(log n)
// BinarySearch가 log n의 복잡도를 가짐. (BinarySearch :: 2진 검색)

// 예제1  [1][1][4][4][7][6][6]
//         ^        ^        ^
// 예제1  [7][1][1][5][5][4][4][6][6]
//         ^           ^           ^
// 1. 가운데가 가운데 왼쪽한칸과 같은 경우,
//    왼쪽, 오른쪽 갯수를 세서 홀수인 쪽으로 재 탐색 시도,


// 예제2  [1][1][7][4][4][6][6]
//         ^        ^        ^
// 예제2  [1][1][5][5][4][4][7][6][6]
//         ^           ^           ^
// 2. 가운데가 오른쪽이랑 같은 경우
//    왼쪽, 오른쪽 갯수를 세서 홀수인 쪽으로 재 탐색 시도,


// 예제3  [1][1][5][5][7][4][4][6][6]
//         ^           ^           ^
// 3. 둘다 아닌 경우엔 가운데가 홀수 갯수 이므로 가운데 반환



int SolutionBinarySearch(const std::vector<int>& numbers)
{
    int s = 0;
    int e = numbers.size() - 1;
    int result = -1;

    if (s == e)
        return numbers[s];

    int m = (s + e) >> 1;

    bool isLeftOdd = false;

    // left
    if (numbers[m - 1] == numbers[m])
    {
        int left = (m - 2) - s + 1;
        isLeftOdd = (left % 2 != 0) ? true : false;
        if (isLeftOdd) e = m - 2;
        else s = m + 1;
    }
    // right
    else if (numbers[m + 1] == numbers[m])
    {
        int right = e - (m + 2) + 1;
        isLeftOdd = (right % 2 == 0) ? true : false;
        if (isLeftOdd) e = m - 1;
        else s = m + 2;
    }
    // find
    else
    {
        return numbers[m];
    }

    result = SolutionBinarySearch(vector<int>(numbers.begin() + s, numbers.begin() + e + 1));

    return result;
}

int main()
{
    //	std::vector<int> numbers(13);
    std::vector<int> numbers;

    int size = 1000001;
    int dst = 300000;
    int insertI = 0;
    int cnt = 0;
    for (int i = 0; i < size; i++)
    {
        if (i == dst)
        {
            numbers.push_back(-100);
            continue;
        }
        if (cnt % 2 == 0) insertI++;
        numbers.push_back(insertI);
        cnt++;
    }

    int result = 0;

    clock_t begin2 = clock();
    result = SolutionBinarySearch(numbers);
    float test2 = float(clock() - begin2) / CLOCKS_PER_SEC;
    cout << result << endl;
    cout << "Binary Search Time :: " << test2 << endl;

    cout << endl << endl;

    clock_t begin1 = clock();
    result = SolutionIterator(numbers);
    float test1 = float(clock() - begin1) / CLOCKS_PER_SEC;
    cout << result << endl;
    cout << "IteratorSearch Time :: " << test1 << endl;

    return 0;
}

// 1,000,001개의 데이터에서 찾는 데이터가 1,000,001번째에 있을 때,

// 바이너리 서치 (이진 탐색)를 사용한 경우가
// 0.005초
// 단방향 서치한 경우가
// 2.03초

// 1,000,001개의 데이터에서 찾는 데이터가 300,001번째에 있을 때,
// 바이너리 서치 (이진 탐색)를 사용한 경우가
// 0.005초
// 단방향 서치한 경우가
// 0.657초



// 결론

// 단방향은 찾는 데이터가 앞에 있을 수록 빠르고, 뒤로 갈수록 느리다.
// 바이너리 서치는 일정한 속도, 평균적으로 단방향 보다 빠르다.

// 단방향의 최악의 경우(찾는 데이터가 맨 뒤에 있는 경우)와 바이너리 서치를 비교하면
// 체감이 가능할 정도의 속도차이가 많이 난다.


