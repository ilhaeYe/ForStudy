#include <iostream>
#include <vector>
#include <ctime>
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
int SolutionIterator(const std::vector<int>& numbers)
{
    for (std::vector<int>::const_iterator cit = numbers.cbegin(); cit != numbers.end(); cit += 2)	// (n / 2) + 1
        if (cit == numbers.cend() - 1 || (*cit) != (*(cit + 1))) return (*cit);						// (n / 2)
}																									// �� 2 * (n / 2) :: O(n)


// ���� ������� �� �� ���� ���.
// �ð����⵵ ��Ʈ :: O(log n)
// BinarySearch�� log n�� ���⵵�� ����. (BinarySearch :: 2�� �˻�)

// ����1  [1][1][4][4][7][6][6]
//         ^        ^        ^
// ����1  [7][1][1][5][5][4][4][6][6]
//         ^           ^           ^
// 1. ����� ��� ������ĭ�� ���� ���,
//    ����, ������ ������ ���� Ȧ���� ������ �� Ž�� �õ�,


// ����2  [1][1][7][4][4][6][6]
//         ^        ^        ^
// ����2  [1][1][5][5][4][4][7][6][6]
//         ^           ^           ^
// 2. ����� �������̶� ���� ���
//    ����, ������ ������ ���� Ȧ���� ������ �� Ž�� �õ�,


// ����3  [1][1][5][5][7][4][4][6][6]
//         ^           ^           ^
// 3. �Ѵ� �ƴ� ��쿣 ����� Ȧ�� ���� �̹Ƿ� ��� ��ȯ



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

// 1,000,001���� �����Ϳ��� ã�� �����Ͱ� 1,000,001��°�� ���� ��,

// ���̳ʸ� ��ġ (���� Ž��)�� ����� ��찡
// 0.005��
// �ܹ��� ��ġ�� ��찡
// 2.03��

// 1,000,001���� �����Ϳ��� ã�� �����Ͱ� 300,001��°�� ���� ��,
// ���̳ʸ� ��ġ (���� Ž��)�� ����� ��찡
// 0.005��
// �ܹ��� ��ġ�� ��찡
// 0.657��



// ���

// �ܹ����� ã�� �����Ͱ� �տ� ���� ���� ������, �ڷ� ������ ������.
// ���̳ʸ� ��ġ�� ������ �ӵ�, ��������� �ܹ��� ���� ������.

// �ܹ����� �־��� ���(ã�� �����Ͱ� �� �ڿ� �ִ� ���)�� ���̳ʸ� ��ġ�� ���ϸ�
// ü���� ������ ������ �ӵ����̰� ���� ����.


