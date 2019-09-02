/*
剑指offer一刷
面试题1：Q1.h
面试题2：Singletion1.h Singleton2.h Singleton1.cpp Singleton2.cpp testSingleton.cpp
面试题3-68：:JianzhiOfferSolutions.cpp
Author:Xieyingying
Date:2019.2.20
*/


#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <cstring>
#include <algorithm>
#include <functional>
#include <cstring>
#include <list>
using namespace std;

/*-------------------------分类1：数组----------------------------*/

//面试题3：数组中的重复数字
//修改原数组，时间复杂度O(n),空间复杂度O(1)
bool duplicate1(vector<int> numbers, int* duplication) {
	int len = numbers.size();
	for (int i = 0; i < len; ++i) {
		while (i != numbers[i]) {
			int a = numbers[i], b = numbers[numbers[i]];
			if (a == b) {
				*duplication = a;
				return true;
			}
			else {
				numbers[numbers[i]] = a;
				numbers[i] = b;
			}
		}
	}
	return false;
}
bool duplicate(int numbers[], int length, int* duplication) {
	int i = 0;
	while (i < length) {
		int temp = numbers[i];
		if (temp != i) {
			if (numbers[temp] != temp)
				swap(numbers[i], numbers[temp]);
			else {
				*duplication = numbers[i];
				return true;
			}
		}
		else
			++i;
	}
	return false;
}
//不修改原数组，时间复杂度O(nlogn),空间复杂度O(1)
int countNum(const vector<int> &numbers, const int &len, const int& left, const int& right) {
	int result = 0;
	for (int i = 0; i < len; ++i) {
		if (numbers[i] >= left&&numbers[i] <= right)
			result++;
	}
	return result;
}
int duplicate2(const vector<int> &numbers) {
	int len = numbers.size();
	int left = 1, right = len - 1, mid = (left + right) / 2;
	while (left<right) {
		if (countNum(numbers, len, left, mid) > mid - left + 1)
			right = mid;
		else 
			left = mid+1;
		mid = (left + right) / 2;
	}
	return mid;
}
//面试题4：二维数组中的查找
//从右上角开始找
bool Find(const int &target, const vector<vector<int> > &array) {
	int row = array.size();
	if (row == 0)
		return false;
	int col = array[0].size();
	int i = 0, j = col - 1;
	while (i < row && j >= 0)
	{
		if (array[i][j] == target)
			return true;
		else if (array[i][j] > target)
			j--;
		else
			i++;
	}
	return false;
}

//面试题21：调整数组顺序使奇数位于偶数前面
//奇数之间、偶数之间相对位置不变（类似于冒泡排序）
void reOrderArray(vector<int> &array) {
	int len = array.size();
	if (len < 2)
		return;
	for (int i = len - 1; i > 0; --i)
		for (int j = 0; j < i; ++j) {
			if (((array[j] & 0x1) == 0) && ((array[j + 1] & 0x1) == 1)) { //==和!= > & > &&
				swap(array[j], array[j + 1]);
			}
		}
}
//相对次序可以变化
//把判断函数当成一个参数传进去，有利于提高代码重用
bool check(int n) {
	return (n & 0x1) == 1;
}
void reOrderArray1(vector<int> &array, bool(*func)(int) {
	int len = array.size();
	if (len < 2)
		return;
	int left = 0, right = len - 1;
	while (right > left) {
		while (right > left && func(array[left]))
			left++;
		while (right > left && !func(array[right]))
			right--;
		if (right > left) {
			swap(array[left], array[right]);
		}
	}
}

//面试题29：顺时针打印矩阵
void printOneCircle(vector<int>& result, const vector<vector<int>>& matrix,
	const int& rows, const int& cols, const int& start) { // 打印一圈
	int maxCol = cols - start - 1;
	int maxRow = rows - start - 1;
	for (int i = start; i <= maxCol; ++i)
		result.push_back(matrix[start][i]);
	//至少有两行时打印一列
	if (maxRow > start)
		for (int i = start + 1; i <= maxRow; ++i)
			result.push_back(matrix[i][maxCol]);
	//至少有两行两列时打印一行
	if (maxRow > start && maxCol > start)
		for (int i = maxCol - 1; i >= start; --i)
			result.push_back(matrix[maxRow][i]);
	//至少有三行两列时打印一列
	if (maxRow - start >= 2 && maxCol > start)
		for (int i = maxRow - 1; i > start; --i)
			result.push_back(matrix[i][start]);
}
vector<int> printMatrix(vector<vector<int> > matrix) {
	vector<int> result;
	int rows = matrix.size();
	if (rows == 0)
		return result;
	int cols = matrix[0].size();
	if (cols == 0)
		return result;
	int start = 0;
	while (rows > 2 * start && cols > 2 * start) { // 每一圈的起始点为（start,start)
		printOneCircle(result, matrix, rows, cols, start);
		++start;
	}
	return result;
}

//面试题39：数组中出现次数超过一半的数字
int MoreThanHalfNum_Solution(const vector<int>& numbers) {
	int len = numbers.size();
	if (len == 0)
		return 0;
	int count = 0, mark;
	for (int i = 0; i < len; ++i) {
		if (count == 0) {
			count++;
			mark = numbers[i];
		}
		else if (numbers[i] == mark) {
			count++;
		}
		else
			count--;
	}
	count = 0;
	for (int i = 0; i < len; ++i)//要检查是否真的存在出现次数大于一半的数字
		if (numbers[i] == mark)
			count++;
	if (count * 2 > len)
		return mark;
	else
		return 0;
}
//基于快速排序思想
//如果存在出现次数超过一半的数字，那么排序之后中位数一定出现次数超过一半；不用完全排序，只要找到第len/2大的数
int Partition(vector<int>& numbers, int left, int right) {
	int l = left, r = right, copy = numbers[l];
	while (l < r) {
		while (l<r&&numbers[r] > copy)
			r--;
		if (l<r)
			numbers[l] = numbers[r];
		while (l < r&&numbers[l] <= copy)
			l++;
		if (l < r)
			numbers[r] = numbers[l];
	}
	numbers[l] = copy;
	return l;
}
int MoreThanHalfNum_Solution2(vector<int> numbers) {
	int len = numbers.size();
	if (len == 0)
		return 0;
	int seq = 0, expectSeq = len / 2, left = 0, right = len - 1, result;
	while (true) {
		seq = Partition(numbers, left, right);
		if (seq == expectSeq) {
			result = numbers[seq];
			break;
		}
		else if (seq < expectSeq)
			left = seq + 1;
		else
			right = seq - 1;
	}
	int count = 0;
	for (int i = 0; i < len; ++i) { //可能并没有出现次数超过一半的数字，所以要检查
		if (result == numbers[i])
			count++;
	}
	if (count * 2 > len)
		return result;
	else
		return 0;
}

//面试题40：最小的k个数
int Partition_s(vector<int>& input, int left, int right) {
	int l = left, r = right, copy = input[left];
	while (l < r) {
		while (l<r&&input[r]>copy)
			r--;
		if (l < r)
			input[l] = input[r];
		while (l < r&&input[l] <= copy)
			l++;
		if (l < r)
			input[r] = input[l];
	}
	input[l] = copy;
	return l;
}
//基于快排思想，会改变原数组
vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
	vector<int> result;
	int len = input.size();
	if (len == 0 || k <= 0 || k>len)
		return result;
	int left = 0, right = len - 1;
	while (true) {
		int seq = Partition_s(input, left, right);
		if (seq == k - 1)
			break;
		else if (seq < k - 1)
			left = seq + 1;
		else
			right = seq - 1;
	}
	for (int i = 0; i < k; ++i)
		result.push_back(input[i]);
	return result;
}
//基于大根堆，维护一个大小为k的大根堆保存最小的k的数
vector<int> GetLeastNumbers_Solution2(vector<int> input, int k) {
	vector<int> result;
	int len = input.size();
	if (len == 0 || k <= 0 || k > len)
		return result;
	priority_queue<int> q; //默认的比较函数less,生成大根堆；priority_queue<int, vector<int>, greater<int>> q;生成小根堆
	for (int i = 0; i < len; ++i) {
		if (q.size() < k) {
			q.push(input[i]);
		}
		else if (input[i] < q.top()) {
			q.pop();
			q.push(input[i]);
		}
	}
	for (int i = 0; i < k; ++i) {
		result.push_back(q.top());
		q.pop();
	}
	return result;
}

//面试题41：数据流中的中位数
//维护一个大根堆、一个小根堆；小根堆中的数都大于等于大根堆中的数
//依次使得小根堆、大根堆的元素个数加1
//用push_heap, pop_heap
class Solution41 {
public:
	void Insert(int num)
	{
		if (((max.size() + min.size()) & 1) == 0)//插入最小堆.注意括号
		{
			if (max.size()>0 && max[0] > num) {
				max.push_back(num);
				push_heap(max.begin(), max.end(), less<int>());
				num = max[0];
				pop_heap(max.begin(), max.end(), less<int>());
				max.pop_back();
			}
			min.push_back(num);
			push_heap(min.begin(), min.end(), greater<int>());
		}
		else {
			if (min.size() > 0 && num > min[0]) {
				min.push_back(num);
				push_heap(min.begin(), min.end(), greater<int>());
				num = min[0];
				pop_heap(min.begin(), min.end(), greater<int>());
				min.pop_back();
			}
			max.push_back(num);
			push_heap(max.begin(), max.end(), less<int>());
		}
	}
	double GetMedian()
	{
		double medium;
		if (max.size() == 0 && min.size() == 0)
			medium = 0;
		else if (((max.size() + min.size()) & 1) != 0)//注意括号
			medium = min[0];
		else
			medium = ((double)max[0] + (double)min[0]) / 2;//先转出double再计算
		return medium;
	}
private:
	vector<int> max;
	vector<int> min;
};
//用priority_queue
class Solution41 {
public:
	void Insert(int num)
	{
		if ((maxHeap.size() + minHeap.size() & 1) == 1) { //插入右边
			if (maxHeap.size() && num < maxHeap.top()) {
				maxHeap.push(num);
				num = maxHeap.top();
				maxHeap.pop();
			}
			minHeap.push(num);
		}
		else {
			if (minHeap.size() > 0 && num > minHeap.top()) {
				minHeap.push(num);
				num = minHeap.top();
				minHeap.pop();
			}
			maxHeap.push(num);
		}
	}
	double GetMedian()
	{
		if ((maxHeap.size() + minHeap.size() & 1) == 0)
			return ((double)maxHeap.top() + minHeap.top()) / 2;
		else
			return maxHeap.top();
	}
private:
	priority_queue<int> maxHeap;  //左边
	priority_queue<int, vector<int>, greater<int>> minHeap;  //右边
};

//面试题42：连续子数组的最大和
int FindGreatestSumOfSubArray(vector<int> array) {
	int len = array.size();
	if (len == 0)
		return 0;
	int CurSum = array[0], maxSum = array[0];
	for (int i = 1; i < len; ++i) {
		if (array[i] + CurSum > array[i])
			CurSum = array[i] + CurSum;
		else
			CurSum = array[i];
		if (maxSum < CurSum)
			maxSum = CurSum;
	}
	return maxSum;
}
/*-------------------------分类2：字符串----------------------------*/

//面试题5：替换空格
//length表示str指向的内存可以存放char的个数。从后向前复制，用两个指针
void replaceSpace(char *str, int length) {
	if (str == nullptr || length <= 0)
		return;
	int oldlength = 0, blanknum = 0, i = 0;
	while (str[i] != '\0') {
		oldlength++;
		if (str[i] == ' ')
			blanknum++;
		i++;
	}
	int newlength = oldlength + 2 * blanknum;
	if (newlength >= length)
		return;
	int oldp = oldlength, newp = newlength;
	while (oldp >= 0 && oldp < newp) {
		if (str[oldp] == ' ') {
			str[newp--] = '0';
			str[newp--] = '2';
			str[newp--] = '%';
		}
		else
			str[newp--] = str[oldp];
		oldp--;
	}
}

//面试题17：打印从1到最大的n位数
//方法1：在字符串上模拟数字加法
bool Increment(char* num) {
	int len = strlen(num);
	int flag = 0;
	for (int i = len - 1; i >= 0; --i) {
		int tempsum = num[i] - '0' + flag;
		if (i == len - 1)
			tempsum += 1;
		if (tempsum >= 10) {
			if (i == 0) {
				return false;
			}
			else {
				flag = tempsum / 10;
				num[i] = '0' + tempsum % 10;
			}
		}
		else {
			num[i] = '0' + tempsum;
			break;
		}
	}
	return true;
}
void PrintNum(char* num) {
	bool flag = true; //前面还没有碰到非零字符
	int len = strlen(num);
	for (int i = 0; i < len; ++i) {
		if (flag && num[i] != '0')
			flag = false;
		if (!flag)
			cout << num[i];
	}
	cout << endl;
}
void Print1ToMaxOfNDigits(int n) {
	if (n <= 0)
		return;
	char* num = new char[n + 1];
	memset(num, '0', n);
	num[n] = '\0';
	while (Increment(num))
		PrintNum(num);
	delete[] num;
}
//方法2：每一位排列组合0-9
void Print1ToMaxOfNDigits2Core(char* num, int len, int index) { //第index位已经设置好了
	if (index == len - 1) {
		PrintNum(num);
		return;
	}
	for (int i = 0; i < 10; ++i) {
		num[index + 1] = '0' + i;
		Print1ToMaxOfNDigits2Core(num, len, index + 1);
	}
}
void Print1ToMaxOfNDigits2(int n) {
	if (n <= 0)
		return;
	char* num = new char[n + 1];
	memset(num, '0', n);
	num[n] = '\0';
	for (int i = 0; i < 10; ++i) {
		num[0] = '0' + i;
		Print1ToMaxOfNDigits2Core(num, n, 0);
	}
	delete[] num;
}
//两个表示数字的字符串相加
string addStrings(string num1, string num2) {
	int len1 = num1.size(), len2 = num2.size();
	string result = "";
	int i = len1 - 1, j = len2 - 1, flag = 0;
	while (i >= 0 || j >= 0 || flag >0) {
		int temp = flag;
		if (i >= 0)
			temp += num1[i--] - '0';
		if (j >= 0)
			temp += num2[j--] - '0';
		flag = temp / 10;
		result = char('0' + temp % 10) + result;
	}
	return result;
}

//面试题19：正则表达式匹配
bool matchCore(char* str, char* pattern) {
	if (*str == '\0' && *pattern == '\0')
		return true;
	if (*str != '\0' && *pattern == '\0')
		return false;
	if (*(pattern + 1) == '*') {
		if (*str != '\0' && (*str == *pattern || *pattern == '.'))
			return matchCore(str + 1, pattern) || matchCore(str + 1, pattern + 2) || matchCore(str, pattern + 2);
		else
			return matchCore(str, pattern + 2);
	}
	else if (*str == *pattern || (*pattern == '.' && *str != '\0'))
		return matchCore(str + 1, pattern + 1);
	else
		return false;
}
bool match(char* str, char* pattern){
	return matchCore(str, pattern);
}

//面试题20：表示数值的字符串
//数值的正确形式：A[.[B]][e|EC]或者.B[e|EC],A和C可能有正负号，B没有正负号
bool scanUnsignedInteger(const char** string) {
	const char* before = *string;
	while (**string != '\0'&& **string >= '0' && **string <= '9')
		++(*string);
	return *string > before;
}
bool scanInteger(const char** string) {
	if (**string == '-' || **string == '+')
		++(*string);
	return scanUnsignedInteger(string);
}
bool isNumeric(const char* string) {
	if (string == nullptr)
		return nullptr;
	bool flag = scanInteger(&string);
	if (*string == '.') {
		string++;
		flag = scanUnsignedInteger(&string) || flag; //不能写成flag || scanUnsignedInteger(&string),因为调用scanUnsignedInteger会改变string
	}
	if (*string == 'e' || *string == 'E') {
		string++;
		flag = scanInteger(&string) && flag;
	}
	return flag && *string == '\0';
}

//面试题38：字符串的排列
//方法1
void PermutationCore(const string str, int i, vector<string>& result) {
	if (i == str.size() - 1)
		return;
	int inext = i + 1;
	PermutationCore(str, inext, result);
	for (int j = i + 1; j < str.size(); ++j) {
		if (str[i] != str[j]) {
			string strCopy = str;
			char jstr = strCopy[j]; //细节：不能直接交换i和j处的字符
			for (int jj = j; jj > i; --jj)//而是j放到i位置处，然后依次后移，不然结果的排列顺序在牛客网上不对
				strCopy[jj] = strCopy[jj - 1];
			strCopy[i] = jstr;
			result.push_back(strCopy);
			PermutationCore(strCopy, inext, result);
		}
	}
}
vector<string> Permutation(string str) {
	int len = str.size();
	vector<string> result;
	if (len == 0)
		return result;
	int i = 0;
	result.push_back(str);
	PermutationCore(str, i, result);
	return result;
}
//方法2：DFS
void PermutationCore(string str, int left, const int& len, vector<string>& res) {
	if (left == len) {
		res.push_back(str);
		return;
	}
	set<char> check;
	for (int i = left; i < len; ++i) {
		auto temp = check.insert(str[i]);
		if (temp.second == true) {
			swap(str[left], str[i]);
			PermutationCore(str, left + 1, len, res);
			swap(str[left], str[i]);
		}
	}
}
vector<string> Permutation(string str) {
	int len = str.size();
	vector<string> res;
	if (len == 0)
		return res;
	PermutationCore(str, 0, len, res);
	sort(res.begin(), res.end());
	return res;
}
	

//面试题43：1~n整数中1出现的次数
int NumberOf1Between1AndN(const char* num) {
	if (num == nullptr || *num<'0' || *num>'9' || *num == '\0')
		return 0;
	int len = strlen(num);
	int first = *num - '0';
	if (len == 1 && first >= 1)
		return 1;
	if (len == 1 && first < 1)
		return 0;
	int Sum1 = 0;
	if (first > 1)
		Sum1 = pow(10, len - 1);
	else if (first == 1)//注意first可能是0
		Sum1 = atoi(num + 1) + 1;
	int Sum2 = first*(len - 1)*pow(10, len - 2);
	int Sum3 = NumberOf1Between1AndN(num + 1);
	return Sum1 + Sum2 + Sum3;
}
int NumberOf1Between1AndN_Solution(int n)
{
	if (n <= 0)
		return 0;
	char num[11]; //int最大2147483647
	sprintf_s(num, "%d", n);
	return NumberOf1Between1AndN(num);
}

//面试题45：把数组排成最小的数
class Solution45 {
	static bool compare(int num1, int num2) {
		string A = "", B = "";
		A += to_string(num1);
		A += to_string(num2);
		B += to_string(num2);
		B += to_string(num1);
		return A < B;
	}
public:
	string PrintMinNumber(vector<int> numbers) {
		sort(numbers.begin(), numbers.end(), compare);
		string result = "";
		for (auto& i : numbers) {
			result += to_string(i);
		}
		return result;
	}
};
//面试题58：翻转字符串
void Reverse(string& str, int left, int right) {//翻转区间[left，right]内的字符
	while (left < right) {
		char temp = str[left];
		str[left] = str[right];
		str[right] = temp;
		left++;
		right--;
	}
}
string ReverseSentence(string str) {
	int len = str.size();
	Reverse(str, 0, len - 1);
	int left = 0, right = 0;
	while (right<len) {
		while (right<len&&str[right] != ' ')
			right++;
		Reverse(str, left, right - 1);
		right++;
		left = right;
	}
	return str;
}

//左旋转字符串
string LeftRotateString(string str, int n) {
	int len = str.size();
	if (len == 0 || n <= 0 || n > len)
		return str;
	Reverse(str, 0, n - 1);
	Reverse(str, n, len - 1);
	Reverse(str, 0, len - 1);
	return str;
}
//直接用库函数reverse
string LeftRotateString(string str, int n) {
	int len = str.size();
	if (len <= 1 || n > len)
		return str;
	reverse(str.begin(), str.begin() + len);
	reverse(str.begin(), str.begin() + len - n);
	reverse(str.begin() + len - n, str.begin() + len);
	return str;
}

//面试题67：把字符串转换成整数
//不符合要求的输入返回0且gMark被设置为-1,符合要求的输入返回数值且gMark被设置为0
//边界条件：前导空字符，上下溢出，有无正负号，只有正负号，空字符串，非法字符
int gMark = 0;
int StrToInt(string str) {
	int len = str.size();
	bool positive = true;
	int i = 0;
	long result = 0;
	while (i < len && str[i] == ' ')  //前导空字符：忽略
		i++;
	if (i < len && (str[i] == '+' || str[i] == '-'))
		positive = str[i++] == '+' ? true : false;
	if (i == len) { //!空字符串，只有前导空字符，只有正负号
		gMark = -1;
		return 0;
	}
	for (i; i<len; ++i) {
		if (str[i] >= '0'&&str[i] <= '9') {
			result = result * 10 + str[i] - '0';
		}
		else {
			gMark = -1;  //非法字符
			return 0;
		}
	}
	result = positive ? result : 0 - result;
	if (result > INT_MAX || result < INT_MIN) {  //上下溢出
		gMark = -1;
		return 0;
	}
	return result;
}

/*-------------------------分类3：链表----------------------------*/

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int v):val(v),next(nullptr){}
};
//往链表的末尾添加一个节点
//当原来的链表为空的时候需要修改pHead。把指针作为参数传入的是指针的副本，使函数对指针的修改可以传出来要用指针的指针
void AddToTail(ListNode** pHead, int value) {
	if (pHead == nullptr)
		return;
	ListNode* pNew = new ListNode(value);
	if (*pHead == nullptr)
		*pHead = pNew;
	else {
		ListNode* walk = *pHead;
		while (walk->next != nullptr)
			walk = walk->next;
		walk->next = pNew;
	}
}

//找到链表中含某值的节点并删除
//可能删除头结点，所以传入指针的指针
void RemoveNode(ListNode** pHead, int value) {
	if (pHead == nullptr || *pHead == nullptr)
		return;
	ListNode* ToBeDeleted = nullptr;
	if ((*pHead)->val == value) {
		ToBeDeleted = *pHead;
		*pHead = (*pHead)->next;
	}
	else {
		ListNode* walk = *pHead;
		while (walk->next != nullptr && walk->next->val != value)
			walk = walk->next;
		if (walk->next != nullptr && walk->next->val == value) {
			ToBeDeleted = walk->next;
			walk->next = walk->next->next;
		}
	}
	if (ToBeDeleted != nullptr) {
		delete ToBeDeleted;
		ToBeDeleted = nullptr;
	}
}
//面试题6：从尾到头打印链表
//基于栈
vector<int> printListFromTailToHead1(ListNode* head) {
	stack<ListNode*> temp;
	ListNode* walk = head;
	while (walk != nullptr)
	{
		temp.push(walk);
		walk = walk->next;
	}
	vector<int> re;
	while (!temp.empty()) {
		re.push_back(temp.top()->val);
		temp.pop();
	}
	return re;
}

//递归（递归在本质上就是一个栈结构）
vector<int> printListFromTailToHead2(ListNode* head) {
	vector<int> re;
	if (head != nullptr)
	{
		re = printListFromTailToHead2(head->next);
		re.push_back(head->val);
	}
	return re;
}

//面试题18：删除链表中的节点
//在O(1)时间内删除链表节点：把要删除节点的下一个节点的值复制到要删除节点，再删除下一个节点
//特殊情况：删除尾节点还是要从头开始遍历；要删除头节点，且链表中只有一个节点，注意要将头结点设为nullptr
//因为有O（1)时间复杂度的限制，所以只能假设要删除的节点确实在链表中
void DeleteNode(ListNode** pListHead, ListNode* pToBeDeleted) {
	if (pListHead == nullptr || pToBeDeleted == nullptr)
		return;
	if (pToBeDeleted->next != nullptr) {  // 不是尾节点
		pToBeDeleted->val = pToBeDeleted->next->val;
		ListNode* temp = pToBeDeleted->next;
		pToBeDeleted->next = temp->next;
		delete temp;
	} else if (*pListHead == pToBeDeleted) {  //只有一个节点
		delete *pListHead;
		*pListHead = nullptr;
		pToBeDeleted = nullptr;
	} else {  // 不止一个节点，且为尾节点
		ListNode* walk = *pListHead;
		while (walk->next != pToBeDeleted)
			walk = walk->next;
		walk->next = nullptr;
		delete pToBeDeleted;
		pToBeDeleted = nullptr;
	}
}
//删除链表中的重复节点
//头结点也有可能被删除，因此参数类型为ListNode**
ListNode* deleteDuplication(ListNode** pHead) {
	if (pHead == nullptr)
		return nullptr;
	ListNode* pre = nullptr;
	ListNode* walk = *pHead;
	ListNode* newHead = *pHead;
	while (walk != nullptr) {
		if (walk->next != nullptr && walk->val == walk->next->val) {  // 需要删除
			int num = walk->val;
			while (walk != nullptr && walk->val == num) {
				ListNode* pNext = walk->next;
				if (pre == nullptr) {
					delete walk;
					walk = pNext;
					newHead = walk;
				} else {
					delete walk;
					walk = pNext;
					pre->next = walk;
				}
			}
		} else {  // 不需要删除
			pre = walk;
			walk = walk->next;
		}
	}
	return newHead;
}

//面试题22：链表中倒数第k个节点
ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
	if (pListHead == nullptr || k <= 0)  // 鲁棒性
		return nullptr;
	ListNode* fast = pListHead;
	for (int i = 1; i < k; i++) {
		if (fast->next == nullptr)  // 可能少于k个节点
			return nullptr;
		fast = fast->next;
	}
	ListNode* slow = pListHead;
	while (fast->next != nullptr) {
		fast = fast->next;
		slow = slow->next;
	}
	return slow;
}

//面试题23:链表中环的入口节点
ListNode* Meet(ListNode* pHead) {
	ListNode* fast = pHead, *slow = pHead;
	while (fast->next != nullptr && fast->next->next != nullptr) {
		fast = fast->next->next;
		slow = slow->next;
		if (slow == fast)
			return fast;
	}
	return nullptr;
}
ListNode* EntryNodeOfLoop(ListNode* pHead) {
	if (pHead == nullptr)
		return nullptr;
	ListNode* meetNode = Meet(pHead);  // 1.确定有环：两个指针，快指针步长是慢指针的两倍
	if (meetNode == nullptr)
		return nullptr;
	ListNode* walk = meetNode;
	int loopLen = 0;
	do {
		walk = walk->next;
		loopLen++;
	} while (walk != meetNode);  // 2.确定环的长度
	walk = pHead;
	for (int i = 0; i < loopLen; ++i)
		walk = walk->next;
	ListNode* loopEntry = pHead;
	while (loopEntry != walk) {
		walk = walk->next;
		loopEntry = loopEntry->next;  // 3.找到环入口：两个指针，一个指针先走环的长度
	}
	return loopEntry;
}

//面试题24：反转链表
ListNode* ReverseList(ListNode* pHead) {
	if (pHead == nullptr)
		return nullptr;
	ListNode* preHead = new ListNode(0);
	preHead->next = pHead;
	while (pHead->next != nullptr) {
		ListNode* reverseNode = pHead->next;
		pHead->next = reverseNode->next;
		reverseNode->next = preHead->next;
		preHead->next = reverseNode;
	}
	ListNode* walk = preHead->next;
	delete preHead;
	return walk;
}
//面试题25：合并两个排序的链表
ListNode* Merge(ListNode* pHead1, ListNode* pHead2) {
	if (pHead1 == nullptr)
		return pHead2;
	if (pHead2 == nullptr)
		return pHead1;
	ListNode* newHead = nullptr;
	if (pHead1->val <= pHead2->val) {
		newHead = pHead1;
		newHead->next = Merge(pHead1->next, pHead2);
	} else {
		newHead = pHead2;
		newHead->next = Merge(pHead1, pHead2->next);
	}
	return newHead;
}
ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
{
	if (pHead1 == nullptr)
		return pHead2;
	if (pHead2 == nullptr)
		return pHead1;
	ListNode* newHead, *masterWalk, *branchWalk;
	if (pHead1->val <= pHead2->val) {
		newHead = pHead1;
		masterWalk = pHead1;
		branchWalk = pHead2;
	}
	else {
		newHead = pHead2;
		masterWalk = pHead2;
		branchWalk = pHead1;
	}
	while (masterWalk->next != nullptr && branchWalk != nullptr) {
		if (masterWalk->next->val > branchWalk->val) {
			ListNode* temp = branchWalk->next;
			branchWalk->next = masterWalk->next;
			masterWalk->next = branchWalk;
			branchWalk = temp;
		}
		masterWalk = masterWalk->next;
	}
	if (branchWalk != nullptr) {
		masterWalk->next = branchWalk;
	}
	return newHead;
}

//面试题35：复杂链表的复制
//复制主链，把复制节点放在原节点的后面
//复制random链
//拆分原链表和复制后的链表
struct RandomListNode {
	int label;
	RandomListNode* next, *random;
	RandomListNode(int x) :label(x), next(nullptr), random(nullptr) {}
};
void CloneMainChain(RandomListNode*  pHead) {
	RandomListNode* pHeadWalk = pHead;
	while (pHeadWalk) {
		RandomListNode* newNode = new RandomListNode(pHeadWalk->label);
		newNode->next = pHeadWalk->next;
		newNode->random = nullptr;
		pHeadWalk->next = newNode;
		pHeadWalk = newNode->next;
	}
}
void CloneRandom(RandomListNode* pHead) {
	RandomListNode* pHeadWalk = pHead;
	while (pHeadWalk) {
		if (pHeadWalk->random)
			pHeadWalk->next->random = pHeadWalk->random->next;
		pHeadWalk = pHeadWalk->next->next;
	}
}
RandomListNode* SplitChain(RandomListNode* pHead) {
	if (pHead == nullptr)
		return nullptr;
	RandomListNode* newHead = pHead->next;
	RandomListNode* newHeadWalk = newHead;
	pHead->next = newHeadWalk->next;
	pHead = pHead->next;
	while (pHead) {
		newHeadWalk->next = pHead->next;
		newHeadWalk = newHeadWalk->next;
		pHead->next = newHeadWalk->next;
		pHead = pHead->next;
	}
	return newHead;
}
RandomListNode* Clone(RandomListNode* pHead)
{
	CloneMainChain(pHead);
	CloneRandom(pHead);
	return SplitChain(pHead);
}



//面试题52：两个链表的第一个公共节点
//首先得到两个链表的长度，以及长度差x；在较长的链表上先走x步，然后一起走，那么第一个相同的节点就是公共节点
ListNode* FindFirstCommonNode(ListNode* pHead1, ListNode* pHead2) {
	int len1 = 0, len2 = 0;
	ListNode* walk1 = pHead1, *walk2 = pHead2;
	while (walk1 != nullptr) {
		len1++;
		walk1 = walk1->next;
	}
	while (walk2 != nullptr) {
		len2++;
		walk2 = walk2->next;
	}
	if (len1 == 0 || len2 == 0)
		return nullptr;
	walk1 = pHead1;
	walk2 = pHead2;
	if (len1 > len2) {
		int distance = len1 - len2;
		while (distance) {
			walk1 = walk1->next;
			distance--;
		}
	}
	if (len2 > len1) {
		int distance = len2 - len1;
		while (distance) {
			walk2 = walk2->next;
			distance--;
		}
	}
	while (walk1 != walk2) {
		walk1 = walk1->next;
		walk2 = walk2->next;
	}
	return walk1;
}

//面试题62：圆圈中最后剩下的数字，0~n-1，每次删除第m个数字
int LastRemaining_Solution(int n, int m)
{
	if (n <= 0 || m <= 0)
		return -1;
	list<int> l;
	for (int i = 0; i < n; ++i)
		l.push_back(i);
	auto itr = l.begin();
	while (l.size() > 1) {
		for (int j = 1; j < m; ++j) {
			++itr;
			if (itr == l.end())
				itr = l.begin();
		}
		itr = l.erase(itr); //erase返回删除的元素之后的元素的迭代器
		if (itr == l.end())
			itr = l.begin();
	}
	return *l.begin();
}
/*-------------------------分类4：二叉树----------------------------*/

//面试题7：根据前序遍历和中序遍历序列重建二叉树
//前序遍历，中序遍历：根节点在前序遍历的首位，找出根节点在中序遍历中所在的位置
TreeNode* reConstructBinaryTreeCore(vector<int>::iterator pre_begin, vector<int>::iterator pre_end,
	vector<int>::iterator in_begin, vector<int>::iterator in_end) {  // 左闭右开区间
	TreeNode* root = new TreeNode(*pre_begin);  // 注意：通过new分配的内存在堆上，才能返回地址。不能写成TreeNode root(*pre_begin),返回*root,因为局部变量在函数返回时被销毁
	int length = pre_end - pre_begin;
	if (length > 1) {
		int left_len = 0;
		while (left_len < length && *(in_begin + left_len) != *pre_begin) {
			left_len++;
		}
		if(left_len>0)
			root->left = reConstructBinaryTreeCore(pre_begin + 1, pre_begin + 1 + left_len, in_begin, in_begin + left_len);
		if(length-left_len-1>0)
			root->right = reConstructBinaryTreeCore(pre_begin + left_len + 1, pre_end, in_begin + left_len + 1, in_end);
	}
	return root;
}
TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> in) {
	int length = pre.size();
	if (length == 0)
		return nullptr;
	return reConstructBinaryTreeCore(pre.begin(), pre.end(), in.begin(), in.end());
}

//面试题8：二叉树的下一个节点(中序遍历）
//树中的节点包含指向父节点的指针
//case1:如果该节点有右子树,它的下一个节点就是右子树中最左子节点
//case2.1：如果该节点没有右子树而且它是父节点的左子节点，则它的下一个节点就是它的父节点
//case2.2: 如果该节点没有右子树而且它是父节点的右子节点，则沿着它的指向父节点的指针遍历，直到找到一个是他父节点的左子节点的节点，如果这样的节点存在，则它的父节点就是我们要找的节点
struct TreeLinkNode {
	int val;
	TreeLinkNode* left;//左子节点
	TreeLinkNode* right;//右子节点
	TreeLinkNode* next;//父节点
	TreeLinkNode(int v) :val(v), left(nullptr), right(nullptr), next(nullptr) {}
};
TreeLinkNode* GetNext1(TreeLinkNode* pNode) {
	if (pNode == nullptr)
		return nullptr;
	if (pNode->right != nullptr) {  // 如果有右子树
		TreeLinkNode* walk = pNode->right;
		while (walk->left != nullptr)
			walk = walk->left;
		return walk;
	} else if (pNode->next != nullptr && pNode->next->left == pNode) {  // 如果没有右子树，且为父节点的左子节点
		return pNode->next;
	} else if (pNode->next != nullptr && pNode->next->right == pNode) {  // 如果没有右子树，且为父节点的右子节点
		TreeLinkNode* walk = pNode->next;
		while (walk->next != nullptr&&walk != walk->next->left)
			walk = walk->next;
		if (walk->next != nullptr&& walk->next->left == walk)
			return walk->next;
		else
			return nullptr;
	}
	else
		return nullptr;
}
//把代码重构一下
TreeLinkNode* GetNext2(TreeLinkNode* pNode) {
	if (pNode == nullptr)
		return nullptr;
	if (pNode->right != nullptr) {
		TreeLinkNode* walk = pNode->right;
		while (walk->left != nullptr)
			walk = walk->left;
		return walk;
	} else if (pNode->next != nullptr) {
		TreeLinkNode* parent = pNode->next;
		TreeLinkNode* current = pNode;
		while (parent != nullptr && parent->right == current) {
			current = parent;
			parent = parent->next;
		}
		return parent;
	} else
		return nullptr;
}
//重构
TreeLinkNode* GetNext3(TreeLinkNode* pNode) {
	if (pNode == nullptr)
		return nullptr;
	if (pNode->right != nullptr) {
		TreeLinkNode* walk = pNode->right;
		while (walk->left != nullptr)
			walk = walk->left;
		return walk;
	}
	else {
		TreeLinkNode* parent = pNode->next;
		TreeLinkNode* current = pNode;
		while (parent != nullptr && parent->right == current) {
			current = parent;
			parent = parent->next;
		}
		return parent;
	}
}
//面试题26：树的子结构
bool Tree1HasTree2(TreeNode* pRoot1, TreeNode* pRoot2) {
	if (pRoot2 == nullptr)
		return true;
	if (pRoot1 == nullptr)
		return false;

	if (pRoot1->val != pRoot2->val)
		return false;
	return Tree1HasTree2(pRoot1->left, pRoot2->left) && Tree1HasTree2(pRoot1->right, pRoot2->right);
}
bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
{
	bool result = false;
	if (pRoot1 != nullptr && pRoot2 != nullptr) {
		if (pRoot1->val == pRoot2->val)
			result = Tree1HasTree2(pRoot1, pRoot2);
		if (!result)
			result = HasSubtree(pRoot1->left, pRoot2);
		if (!result)
			result = HasSubtree(pRoot1->right, pRoot2);
	}
	return result;
}

//判断两个double值是不是相等
//因为计算机表示小数都有误差
bool Equal(double num1, double num2) {
	if (((num1 - num2) > -0.0000001) && ((num1 - num2) < 0.0000001))
		return true;
	else
		return false;
}

//面试题27：二叉树的镜像
//前序遍历这棵树的每个节点，如果遍历到的节点有子节点，则交换它的两个子节点
//循环解法
void alongLeft(stack<TreeNode*> &s, TreeNode* root) {
	while (root) {
		if (root->left || root->right)  //先swap
			swap(root->left, root->right);
		if (root->right != nullptr)
			s.push(root->right);
		root = root->left;
	}
}
void Mirror(TreeNode *pRoot) {
	stack<TreeNode*> s;
	while (true) {
		alongLeft(s, pRoot);
		if (s.empty())
			break;
		pRoot = s.top();
		s.pop();
	}
}

//递归解法
void Mirror(TreeNode *pRoot) {
	if (pRoot == nullptr || (pRoot->left == nullptr && pRoot->right == nullptr))
		return;
	swap(pRoot->left, pRoot->right);
	Mirror(pRoot->left);
	Mirror(pRoot->right);
}

//面试题28：对称的二叉树
bool isSymmetricalCore(TreeNode* pRoot1, TreeNode* pRoot2) {
	if (pRoot1 == nullptr&&pRoot2 == nullptr)
		return true;
	if (pRoot1 == nullptr || pRoot2 == nullptr)
		return false;
	if (pRoot1->val != pRoot2->val)
		return false;
	return isSymmetricalCore(pRoot1->left, pRoot2->right) &&
		isSymmetricalCore(pRoot1->right, pRoot2->left);
}
bool isSymmetrical(TreeNode* pRoot)
{
	return isSymmetricalCore(pRoot, pRoot);
}

//面试题32：从上到下打印二叉树
vector<int> PrintFromTopToBottom(TreeNode* root) {
	vector<int> result;
	if (root == nullptr)
		return result;
	queue<TreeNode*> q;
	q.push(root);
	while (!q.empty()) {
		TreeNode* temp = q.front();
		result.push_back(temp->val);
		if (temp->left)
			q.push(temp->left);
		if (temp->right)
			q.push(q.front()->right);
		q.pop();
	}
	return result;
}
//把二叉树打印成多行
//用两个额外的变量：当前层还没有打印的节点数，下一层节点数
vector<vector<int> > Print(TreeNode* pRoot) {
	vector<vector<int>> result;
	queue<TreeNode*> q;
	if (pRoot)
		q.push(pRoot);
	while (!q.empty()) {
		int len = q.size();
		vector<int> re;
		while (len > 0) {
			len--;
			auto temp = q.front();
			re.push_back(temp->val);
			if (temp->left)
				q.push(temp->left);
			if (temp->right)
				q.push(temp->right);
			q.pop();
		}
		result.push_back(re);
	}
	return result;
}
//按之字型打印二叉树
//用两个栈
vector<vector<int> > Print1(TreeNode* pRoot) {
	vector<vector<int>> result;
	if (pRoot == nullptr)
		return result;
	stack<TreeNode*> sOdd, sEven;
	sOdd.push(pRoot);
	int row = 1;
	while (!sOdd.empty() || !sEven.empty()) {
		vector<int> oneRow;
		if (row & 0x1 != 0) {//奇行
			while (!sOdd.empty()) {
				TreeNode* temp = sOdd.top();
				sOdd.pop();
				oneRow.push_back(temp->val);
				if (temp->left)
					sEven.push(temp->left);
				if (temp->right)
					sEven.push(temp->right);
			}
		}
		else {//偶行
			while (!sEven.empty()) {
				TreeNode* temp = sEven.top();
				sEven.pop();
				oneRow.push_back(temp->val);
				if (temp->right)
					sOdd.push(temp->right);
				if (temp->left)
					sOdd.push(temp->left);
			}
		}
		result.push_back(oneRow);
		row++;
	}
	return result;
}

//面试题33：二叉搜索树的后续遍历序列
bool verify(const vector<int>& sequence, int left, int right) {
	if (right <= left)
		return true;
	int i = right - 1;
	while (i >= left && sequence[i] >= sequence[right])
		--i;
	for (int j = i; j >= left; --j) {
		if (sequence[j] > sequence[right])
			return false;
	}
	return verify(sequence, left, i) && verify(sequence, i + 1, right - 1);
}
bool VerifySquenceOfBST(vector<int> sequence) {
	int len = sequence.size();
	if (len == 0)
		return false;
	return verify(sequence, 0, len - 1);
}
	

//面试题34：二叉树中和为某一值的路径
void findPathCore(TreeNode* root, int& curSum, const int& expectNumber,
	vector<int>& re, vector<vector<int>>& result) {
	curSum += root->val;
	re.push_back(root->val);
	if (root->left == nullptr && root->right == nullptr && curSum == expectNumber) {
		result.push_back(re);
	}
	else {
		if (root->left != nullptr)
			findPathCore(root->left, curSum, expectNumber, re, result);
		if (root->right != nullptr)
			findPathCore(root->right, curSum, expectNumber, re, result);
	}
	curSum -= root->val;
	re.pop_back();
}
vector<vector<int> > FindPath(TreeNode* root, int expectNumber) {
	vector<vector<int>> result;
	if (root == nullptr)
		return result;
	vector<int> re;
	int curSum = 0;
	findPathCore(root, curSum, expectNumber, re, result);
	return result;
}

//面试题36：二叉搜索树与双向链表
//递归
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int v) :val(v), left(nullptr), right(nullptr) {}
};
void ConvertCore(TreeNode* pCurrent, TreeNode** pLastNodeInList) {
	if (pCurrent->left != nullptr)
		ConvertCore(pCurrent->left, pLastNodeInList);
	pCurrent->left = *pLastNodeInList;
	if (*pLastNodeInList != nullptr)
		(*pLastNodeInList)->right = pCurrent;
	*pLastNodeInList = pCurrent;
	if (pCurrent->right != nullptr)
		ConvertCore(pCurrent->right, pLastNodeInList);
}
TreeNode* Convert(TreeNode* pRootOfTree) {
	if (pRootOfTree == nullptr)
		return nullptr;
	TreeNode* pLastNodeInList = nullptr;
	ConvertCore(pRootOfTree, &pLastNodeInList);
	while (pLastNodeInList->left != nullptr)
		pLastNodeInList = pLastNodeInList->left;
	return pLastNodeInList;
}
	

//面试题37：序列化二叉树
void SerializeCore(TreeNode* root, string& s) {
	if (root == nullptr) {
		s += "$,";
		return;
	}
	string temp = to_string(root->val);
	s += temp;
	s += ",";
	SerializeCore(root->left, s);
	SerializeCore(root->right, s);
}
char* Serialize(TreeNode *root) {
	if (root == nullptr)
		return nullptr;
	string s;
	SerializeCore(root, s);
	char* result = new char[s.size()]; //末尾的，不能放进去
	for (int i = 0; i < s.size() - 1; ++i)
		result[i] = s[i];
	result[s.size() - 1] = '\0';
	return result;
}
//反序列化二叉树
TreeNode* DeserializeCore(char** str) { //注意要声明成**
	if (**str == '$') {
		(*str) += 2;
		return nullptr;
	}
	int num = 0;
	while (**str != ',') {
		num = 10 * num + (**str) - '0';
		++(*str);
	}
	++(*str);
	TreeNode* root = new TreeNode(num);
	root->left = DeserializeCore(str);
	root->right = DeserializeCore(str);
	return root;
}
TreeNode* Deserialize(char *str) {
	if (str == nullptr)
		return nullptr;
	TreeNode* root = DeserializeCore(&str);
	return root;
}

//面试题54：二叉搜索树的第K大节点
TreeNode* KthNode(TreeNode* pRoot, int k)
{
	stack<TreeNode*> s;
	TreeNode* ans = nullptr;
	while (k) {
		if (pRoot) {
			s.push(pRoot);
			pRoot = pRoot->left;
		}
		else if (!s.empty()) {
			k--;
			ans = s.top();
			pRoot = s.top()->right;
			s.pop();
		}
		else
			break;
	}
	return k>0 ? nullptr : ans;
}

//面试题55：二叉树的深度
//解法1：递归
int TreeDepth1(TreeNode* pRoot)
{
	if (pRoot == nullptr)
		return 0;
	int left = TreeDepth(pRoot->left);
	int right = TreeDepth(pRoot->right);
	return left > right ? left + 1 : right + 1;
}
//解法2：层次遍历
int TreeDepth2(TreeNode* pRoot)
{
	if (pRoot == nullptr)
		return 0;
	queue<TreeNode*> q;
	q.push(pRoot);
	int res = 0;
	while (!q.empty()) {
		int len = q.size();
		while (len) {
			if (q.front()->left != nullptr)
				q.push(q.front()->left);
			if (q.front()->right != nullptr)
				q.push(q.front()->right);
			len--;
			q.pop();
		}
		res++;
	}
	return res;
}
//判断一棵二叉树是否为平衡二叉树
//后序遍历，并且更新深度值
class Solution {
public:
	bool IsBalanced_Solution(TreeNode* pRoot) {
		int depth = 0;
		return isBalanced(pRoot, depth);
	}
private:
	bool isBalanced(TreeNode* pRoot, int& depth) {
		if (pRoot == nullptr)
		{
			depth = 0;
			return true;
		}
		int left = 0, right = 0;
		if (isBalanced(pRoot->left, left) && isBalanced(pRoot->right, right)) {
			if (left - right >= -1 && left - right <= 1) {
				depth = max(left, right) + 1;
				return true;
			}
		}
		return false;
	}
};

//面试题68：二叉树中两个节点的最低公共祖先
//情况1：是二叉搜索树
//情况2：每个节点有指向父节点的指针
//情况3：不是二叉搜索树，没有指向父节点的指针
class Solution_Leetcode236 {
private:
	//多叉树
	bool getNodePath1(TreeNode* pRoot, TreeNode* pNode, list<TreeNode*>& path) {
		path.push_back(pRoot);
		if (pRoot == pNode)
			return true;
		bool found = false;
		auto itr = pRoot->children.begin();
		while (!found && itr != pRoot->children.end()) {
			found = getNodePath1(*itr, pNode, path);
			itr++;
		}
		if (!found)
			path.pop_back();
		return found;
	}
	//二叉树
	bool getNodePath2(TreeNode* pRoot, TreeNode* pNode, list<TreeNode*>& path) {
		path.push_back(pRoot);
		if (pRoot == pNode)
			return true;
		bool found = false;
		if (pRoot->left)
			found = getNodePath2(pRoot->left, pNode, path);
		if (!found && pRoot->right)
			found = getNodePath2(pRoot->right, pNode, path);
		if (!found)
			path.pop_back();
		return found;
	}
	TreeNode* getLowestCommonAncestor(const list<TreeNode*>& route1, const list<TreeNode*>& route2) {
		auto itr1 = route1.begin(), itr2 = route2.begin();
		TreeNode* result = nullptr;
		while (itr1 != route1.end() && itr2 != route2.end() && (*itr1 == *itr2)) {
			result = *itr1;
			itr1++;
			itr2++;
		}
		return result;
	}
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		TreeNode* result = nullptr;
		if (root != nullptr && p != nullptr&&q != nullptr) {
			list<TreeNode*> pathP;
			getNodePath2(root, p, pathP);
			list<TreeNode*> pathQ;
			getNodePath2(root, q, pathQ);
			result = getLowestCommonAncestor(pathP, pathQ);
		}
		return result;
	}
};
/*-------------------------分类5：栈和队列----------------------------*/

//面试题9：用两个栈实现队列
//压入栈1，从栈2弹出
class Solution {
public:
	void push(int node) {
		stack1.push(node);
	}

	int pop() {
		if (stack2.empty()) {
			while (!stack1.empty()) {
				stack2.push(stack1.top());
				stack1.pop();
			}
		}
		int temp = stack2.top();
		stack2.pop();
		return temp;
	}

private:
	stack<int> stack1;
	stack<int> stack2;
};

//面试题30：包含min函数的栈
class StackWithMin {
	stack<int> m_data;
	stack<int> m_min;
public:
	void push(int value) {
		if (m_data.empty())
			m_min.push(value);
		else
			m_min.push(m_data.top()<value ? m_data.top() : value);
		m_data.push(value);
	}
	void pop() {
		m_data.pop();
		m_min.pop();
	}
	int top() {
		return m_data.top();
	}
	int min() {
		return m_min.top();
	}
};

//面试题31：栈的压入、弹出序列
bool IsPopOrder(vector<int> pushV, vector<int> popV) {
	int lenPush = pushV.size(), lenPop = popV.size();
	if (lenPush == 0 || lenPop == 0 || lenPush != lenPop)
		return false;
	stack<int> s;
	int i = 0, j = 0;
	while (j < lenPop) {
		if (s.empty() || s.top() != popV[j]) {
			while (i < lenPush && pushV[i] != popV[j])
				s.push(pushV[i++]);
			if (i < lenPush && pushV[i] == popV[j]) {
				++i;
				++j;
			}
			else
				return false;
		}
		else {
			s.pop();
			j++;
		}
	}
	return true;
}
//面试题59：队列的最大值
vector<int> maxInWindows(const vector<int>& num, unsigned int size)
{
	int len = num.size();
	deque<int> maxRecord;
	vector<int> result;
	if (size > len)
		return result;
	for (int i = 0; i < len; ++i) {
		if ((!maxRecord.empty()) && (maxRecord.front() == i - size))
			maxRecord.pop_front();
		while ((!maxRecord.empty()) && (num[i] > num[maxRecord.back()]))
			maxRecord.pop_back();
		maxRecord.push_back(i);
		if (i >= size - 1)
			result.push_back(num[maxRecord.front()]);
	}
	return result;
}
//实现一个队列，max(),push_back(),pop_front()的时间复杂度都是O(1)
template<typename T>
class maxQueue{
public:
	maxQueue():currentIndex(0){}
	void push_back(T n) {
		while (!maxRecord.empty() && maxRecord.front().num < n)
			maxRecord.pop_back();
		InternalData temp = { currentIndex++, n };
		maxRecord.push_back(temp);
		data.push(temp);
	}
	void pop_front() {
		if (!data.empty()) {
			if (data.front().index == maxRecord.front().index)
				maxRecord.pop_front();
			data.pop();
		}
	}
	T max() {
		if (!maxRecord.empty())
			return maxRecord.front().num;
	}
private:
	struct InternalData {
		int index;
		T num;
	};
	queue<InternalData> data;
	deque<InternalData> maxRecord;
	int currentIndex;
}


/*-------------------------分类6：递归和循环----------------------------*/

//面试题10：斐波那契数列
//递归解法由于有很多重复计算，效率很低
//从下往上计算，只要记录最后两个值就可以
int Fibonacci(int n) {
	if (n < 2)
		return n;
	int minusOne = 1;
	int minusTwo = 0;
	int re = 0;
	for (int i = 2; i <= n; ++i) {
		re = minusOne + minusTwo;
		minusTwo = minusOne;
		minusOne = re;
	}
	return re;
}
//跳台阶
//和计算斐波那契数列类似，f(n)=f(n-1)+f(n-2)
int jumpFloor(int number) {
	if (number <= 2)
		return number;
	int minusOne = 2, minusTwo = 1, re = 0;
	for (int i = 3; i <= number; ++i) {
		re = minusOne + minusTwo;
		minusTwo = minusOne;
		minusOne = re;
	}
	return re;
}
//变态跳台阶
//数学归纳法：f(n)=2^(n-1)
int jumpFloorII(int number) {
	int re = 1;
	for (int i = 1; i < number; ++i)
		re *= 2;
	return re;
}

//面试题44：数字序列中某一位的数字
int NthNumCore(const int& count, const int& n) {//所有具有count位中的数字的第n位
	int first = pow(10, count - 1);
	int num = first + n / count - 1;
	if (n%count == 0)
		return num % 10;
	else {
		num += 1;
		int seqFromRight = count + 1 - (n%count);
		int re;
		for (int i = 0; i < seqFromRight; ++i) {
			re = num % 10;
			num /= 10;
		}
		return re;
	}
}
int NthNum(int n) {
	if (n <= 0)
		return -1;
	int count = 1;
	while (true) {
		int numOfCount = count==1 ? 10 : 9 * pow(10, count - 1);//有count位的数字一共占多少位
		if (numOfCount > n) {
			return NthNumCore(count, n);
		}
		else {
			n -= numOfCount;
			count++;
		}
	}
}

/*-------------------------分类7：查找和排序----------------------------*/

//面试题11：旋转数组的最小数字
int minSearchInorder(vector<int>& rotateArray, int left, int right) {
	int min = rotateArray[left];
	for (int i = left + 1; i <= right; ++i) {
		if (rotateArray[i] < min) {
			min = rotateArray[i];
			break;
		}		
	}
	return min;
}
int minNumberInRotateArray(vector<int> rotateArray) {  // 给出的所有元素都大于0，若数组大小为0，请返回0
	int left = 0, right = rotateArray.size() - 1,mid = 0;
	while (rotateArray[left] >= rotateArray[right]) {  // 如果数组本来就有序，返回第一个元素，所以mid初始化为0
		if (right - left == 1) {
			mid = right;
			break;
		}
		mid = (left + right) / 2;
		if (rotateArray[left] == rotateArray[right] && rotateArray[left] == rotateArray[mid])
			return minSearchInorder(rotateArray, left, right);  // 特殊情况，只能顺序查找，例如10111和11101
		if (rotateArray[mid] >= rotateArray[left])
			left = mid;
		else if (rotateArray[mid] <= rotateArray[right])
			right = mid;
	}
	return rotateArray[mid];
}

//面试题51：数组中的逆序对，输出P%1000000007（类似归并排序)
void MergeCount(vector<int>& data, const int& left, const int& mid, const int& right, long& pairs) {
	vector<int> copy(data.begin() + left, data.begin() + right + 1);
	int P1 = mid - left, P2 = right - left, P3 = right, rightLen = right - mid;
	while (P1 >= 0 && P2 > mid - left) {
		if (copy[P1] > copy[P2]) {
			pairs += rightLen;
			data[P3--] = copy[P1--];
		}
		else {
			data[P3--] = copy[P2--];
			rightLen--;
		}
	}
	while (P1 >= 0) {
		data[P3--] = copy[P1--];
	}
	while (P2 > mid - left) {
		data[P3--] = copy[P2--];
	}
}
void InversePairsCore(vector<int>& data, const int& left, const int& right, long& pairs) {
	if (right - left < 1)
		return;
	int mid = (left + right) / 2;
	InversePairsCore(data, left, mid, pairs);
	InversePairsCore(data, mid + 1, right, pairs);
	MergeCount(data, left, mid, right, pairs);
}
int InversePairs(vector<int> data) {
	int len = data.size();
	if (len < 2)
		return 0;
	long pairs = 0;
	InversePairsCore(data, 0, len - 1, pairs);
	return pairs % 1000000007;
}
// 51题重构代码，仍然是归并排序
class Solution {
public:
	int InversePairs(vector<int> data) {
		int len = data.size();
		vector<int> copyData;
		for (auto& i : data)
			copyData.push_back(i);
		return CountPairs(data, copyData, 0, len - 1) % 1000000007;
	}
private:
	long CountPairs(vector<int>& data, vector<int>& copyData, int left, int right) {  // [left, right],排好序的放在CopyData数组
		if (left == right)
			return 0;
		int mid = (left + right) / 2;
		long leftCount = CountPairs(copyData, data, left, mid);  //注意这里copyData和data换了位置
		long rightCount = CountPairs(copyData, data, mid + 1, right);
		int rightLen = right - mid, i = mid, j = right, walk = right;
		long count = 0;
		while (i >= left && j > mid) {
			if (data[i] > data[j]) {
				copyData[walk--] = data[i--];
				count += rightLen;
			}
			else {
				copyData[walk--] = data[j--];
				rightLen--;
			}
		}
		while (i >= left)
			copyData[walk--] = data[i--];
		while (j > mid)
			copyData[walk--] = data[j--];
		return leftCount + rightCount + count;
	}
};

//面试题53：在排序数组中查找数字
//数字在排序数组中出现的次数
int FirstPlace(const vector<int>& data, int left, int right, const int& k) {
	if (right < left)
		return -1;
	int mid = (left + right) / 2;
	if (data[mid] > k || (data[mid] == k&&mid - 1 >= left&&data[mid - 1] == k))
		right = mid - 1;
	else if (data[mid] < k)
		left = mid + 1;
	else
		return mid;
	return FirstPlace(data, left, right, k);
}
int LastPlace(const vector<int>& data, int left, int right, const int& k) {
	if (right < left)
		return -1;
	int mid = (left + right) / 2;
	if (data[mid] > k)
		right = mid - 1;
	else if (data[mid] < k || (data[mid] == k&&mid + 1 <= right&&data[mid + 1] == k))
		left = mid + 1;
	else
		return mid;
	return LastPlace(data, left, right, k);
}
int GetNumberOfK(vector<int> data, int k) {
	int number = 0;
	int len = data.size();
	if (len > 0) {
		int first = FirstPlace(data, 0, len - 1, k);
		int last = LastPlace(data, 0, len - 1, k);
		if (first != -1 && last != -1)
			number = last - first + 1;
	}
	return number;
}

//0~n中缺失的数字，数组是排好序的
int MissNumber(vector<int> data) {
	int len = data.size();
	if (len == 0)
		return -1;
	int left = 0, right = len - 1;
	while (left <= right) {
		int mid = (left + right) / 2;
		if (data[mid] != mid) {
			if (mid == 0 || data[mid - 1] == mid - 1)
				return mid;
			right = mid - 1;
		}
		else
			left = mid + 1;
	}
	if (left == len)
		return len;
	return -1; //无效输入
}
//数组中数值和小标相等的元素,数组是递增的并且每个元素都是整数且唯一
int GetNumberSameAsIndex(const vector<int>& data) {
	int len = data.size();
	if (len == 0)
		return -1;
	int left = 0, right = len - 1;
	while (left <= right) {
		int mid = (left + right) / 2;
		if (data[mid] == mid)
			return mid;
		else if (data[mid] > mid)
			right = mid - 1;
		else
			left = mid + 1;
	}
	return -1;
}

//面试题57：和为s的数字
//数组是递增排序的，若有多对数组和为s，输出乘积最小的一对
vector<int> FindNumbersWithSum(vector<int> array, int sum) {
	int len = array.size();
	vector<int> res;
	if (len < 2)
		return res;
	int left = 0, right = len - 1, multi = INT_MAX;
	while (left < right) {
		int temp1 = array[left] * array[right];
		int temp2 = array[left] + array[right];
		if (temp2 == sum && temp1 < multi) {
			if (temp1 < multi) {
				if (!res.empty()) {
					res.pop_back();
					res.pop_back();
				}
				res.push_back(array[left]);
				res.push_back(array[right]);
				multi = temp1;
			}
			left++;
			right--;

		}
		else if (temp2 < sum) {
			left++;
		}
		else {
			right--;
		}
	}
	return res;
}
//和为s的连续正数序列
vector<vector<int> > FindContinuousSequence(int sum) {
	int mid = (sum + 1) / 2, left = 1, right = 2, temp = 3;
	vector<vector<int>> result;
	while (left < mid) {
		if (temp < sum) {
			right++;
			temp += right;
		}
		else if (temp > sum) {
			temp -= left;
			left++;
		}
		else {
			vector<int> res;
			for (int i = left; i <= right; ++i)
				res.push_back(i);
			result.push_back(res);
			temp -= left;
			left++;
			right++;
			temp += right;
		}
	}
	return result;
}

//重构代码
void pushAns(int left, int right, vector<vector<int>>& result) {
	vector<int> ans;
	for (int i = left; i <= right; ++i)
		ans.push_back(i);
	result.push_back(ans);
}
vector<vector<int> > FindContinuousSequence1(int sum) {
	if (sum < 3)
		return vector<vector<int>>();
	int left = 1, right = 2, middle = (sum + 1) / 2, sumTemp = 3;
	vector<vector<int>> result;
	while (left < middle) {
		if (sumTemp == sum)
			pushAns(left, right, result);
		while (sumTemp > sum&&left < middle) {
			sumTemp -= left;
			left++;
			if (sumTemp == sum)
				pushAns(left, right, result);
		}
		right++;
		sumTemp += right;
	}
	return result;
}

//面试题61：扑克牌中的顺子
bool IsContinuous(vector<int> numbers) {
	int len = numbers.size();
	if (len < 1)
		return false;
	sort(numbers.begin(), numbers.end(), less<int>());
	int numOf0 = 0, mark = 0;
	for (mark = 0; mark < len&&numbers[mark] == 0; ++mark)
		numOf0++;
	int numOfBreak = 0;
	for (int i = mark + 1; i < len; ++i) {
		if (numbers[i] == numbers[i - 1])
			return false;
		if (numbers[i] - numbers[i - 1] > 1)
			numOfBreak += numbers[i] - numbers[i - 1] - 1;
	}
	return numOf0 >= numOfBreak ? true : false;
}

/*-------------------------分类8：回溯法----------------------------*/

//面试题12：矩阵中的路径
//当在矩阵中定位了路径中前n个字符的位置之后，在与第n个字符对应的格子的周围都没有找到第n+1个字符，这时候只好在路径上回到第n-1个字符
bool hasPathCore(char* matrix, int rows, int cols, int row, int col, char* str, bool* visited, int& pathLength) {
	if (str[pathLength] == '\0')
		return true;
	bool hasPath = false;
	if (row >= 0 && row < rows && col >= 0 && col < cols&&matrix[row*cols + col] == str[pathLength] && visited[row*cols + col] == false) {
		pathLength++;
		visited[row*cols + col] = true;
		hasPath = hasPathCore(matrix, rows, cols, row, col + 1, str, visited, pathLength)
			|| hasPathCore(matrix, rows, cols, row, col - 1, str, visited, pathLength)
			|| hasPathCore(matrix, rows, cols, row + 1, col, str, visited, pathLength)
			|| hasPathCore(matrix, rows, cols, row - 1, col, str, visited, pathLength);
		if (!hasPath) {
			pathLength--;
			visited[row*cols + col] = false;
		}
	}
	return hasPath;
}
bool hasPath(char* matrix, int rows, int cols, char* str) {
	if (matrix == nullptr || rows == 0 || cols == 0 || str == nullptr)
		return false;
	bool* visited = new bool[rows*cols];
	memset(visited, false, rows*cols);
	int pathLength = 0;
	for (int row = 0; row<rows; ++row)
		for (int col = 0; col < cols; ++col) {
			if (hasPathCore(matrix, rows, cols, row, col, str, visited, pathLength))
				return true;
		}
	delete[] visited;
	return false;
}

//面试题13：机器人的运动范围
int getDigit(int num) {
	int re = 0;
	while (num > 0) {
		re += num % 10;
		num /= 10;
	}
	return re;
}
bool check(int threshold, int rows, int cols, int row, int col, bool* visited) {
	if (row >= 0 && row < rows && col >= 0 && col < cols 
		&& !visited[row*cols + col] && getDigit(row) + getDigit(col) <= threshold)
		return true;
	else
		return false;
}
int movingCountCore(int threshold, int rows, int cols, int row, int col, bool* visited) {
	int count = 0;
	if (check(threshold, rows, cols, row, col, visited)) {
		visited[row*cols + col] = true;
		count = 1 + movingCountCore(threshold, rows, cols, row, col + 1, visited) +
			movingCountCore(threshold, rows, cols, row, col - 1, visited) +
			movingCountCore(threshold, rows, cols, row - 1, col, visited) +
			movingCountCore(threshold, rows, cols, row + 1, col, visited);
	}
	return count;
}
int movingCount(const int& threshold, const int& rows, const int& cols) {
	if (rows < 0 || cols < 0)
		return 0;
	bool* visited = new bool[rows*cols];
	memset(visited, false, rows*cols);
	int count = movingCountCore(threshold, rows, cols, 0, 0, visited);
	delete[] visited;
	return count;
}

/*-------------------------分类9：动态规划与贪婪算法----------------------------*/

//面试题14：剪绳子(动态规划)
//f(n)=f(i)*f(n-i)，从下到上算
//时间复杂度O(n^2),空间复杂度O(n)
int maxProductAfterCutting(int length) {
	if (length < 2)
		return 0;
	if (length == 2)
		return 1;
	if (length == 3)
		return 2;
	int* re = new int[length + 1];
	re[0] = 0; // 为了长度和下标对齐，有用的下标从1开始
	re[1] = 1;
	re[2] = 2;
	re[3] = 3; //不切分比切分要大
	int max;
	for (int i = 4; i <= length; ++i) {
		max = 0;
		for (int j = 1; j <= i / 2; ++j)
			if (re[j] * re[i - j] > max)
				max = re[j] * re[i - j];
		re[i] = max;
	}
	max = re[length];
	delete[] re;
	return max;
}
//剪绳子（贪婪算法）
//当n>=5,尽可能多地剪长度为3的绳子；当n=4时，把绳子剪成两段长度为2的绳子
int maxProductAfterCutting1(int length) {
	if (length < 2)
		return 0;
	if (length == 2)
		return 1;
	if (length == 3)
		return 2;
	int timesOfThree = length / 3;
	if (length % 3 == 1)
		timesOfThree -= 1;
	int timesOfTwo = (length - timesOfThree * 3) / 2;
	return ((int)pow(3, timesOfThree)*(int)pow(2, timesOfTwo));
}

//面试题46：把数字翻译成字符串
//0->a,...,25->z
int TransNum(const vector<int>& num) {
	int len = num.size();
	if (len <= 1)
		return len;
	vector<int> re(len, 0);
	re[len - 1] = 1;
	if (num[len - 2] * 10 + num[len - 1] < 26)
		re[len - 2] = 2;
	else
		re[len - 2] = 1;
	for (int i = len - 3; i >= 0; --i) {
		if (num[i] * 10 + num[i + 1] < 26)
			re[i] = re[i + 1] + re[i + 2];
		else
			re[i] = re[i + 1];
	}
	return re[0];
}
//1->A,..,26->Z
//只需要记录前两个值
class Solution {
	bool isValid(char a) {
		return a>'0' && a <= '9';
	}
	bool isValid(char a, char b) {
		return (a == '1' || (a == '2' && b <= '6'));
	}
public:
	int numDecodings(string s) {
		int len = s.size();
		if (len == 0 || s[0] == '0')
			return 0;
		if (len == 1)
			return 1;
		int pre1 = 1, pre2 = 1, res;
		for (int i = 1; i < len; ++i) {
			bool check1 = isValid(s[i]), check2 = isValid(s[i - 1], s[i]);
			if (check1 && check2)
				res = pre1 + pre2;
			else if (check1 && !check2)
				res = pre1;
			else if (!check1 && check2)
				res = pre2;
			else
				res = 0;
			pre2 = pre1;
			pre1 = res;

		}
		return res;
	}
};

//面试题47：礼物的最大价值
//需要一个二维数组保存中间结果
int MaxPresentsValue1(const vector<vector<int>>& present) {
	int row = present.size();
	if (row == 0)
		return 0;
	int col = present[0].size();
	int** re = new int*[row];
	for (int i = 0; i < row; ++i)
		re[i] = new int[col];
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j) {
			int left = 0, up = 0;
			if (i > 0)
				up = re[i - 1][j];
			if (j > 0)
				left = re[i][j - 1];
			re[i][j] = max(left, up) + present[i][j];
		}
	int result = re[row - 1][col - 1];
	for (int i = 0; i < row; ++i)
		delete[] re[i];
	delete[] re;
	return result;
}
//优化：只需要一个一维数组保存中间结果，这个一维数组的前面j个元素已经更新过了，后面col-j个元素还没更新（属于上一行）
int MaxPresentsValue2(const vector<vector<int>>& present) {
	int rows = present.size();
	if (rows == 0)
		return 0;
	int cols = present[0].size();
	int* maxValue = new int[cols];
	for (int i = 0; i<rows; ++i)
		for (int j = 0; j < cols; ++j) {
			int left = 0, up = 0;
			if (i > 0)
				up = maxValue[j];
			if (j > 0)
				left = maxValue[j - 1];
			maxValue[j] = max(left, up) + present[i][j];
		}
	return maxValue[cols - 1];
}

//面试题48：最长不包含重复字符的子字符串
int longestSubstringWithoutDuplicate(const string& s) {
	int len = s.size();
	if (len == 0)
		return 0;
	int* longest = new int[len];
	longest[0] = 1;
	int mark[26];
	for (int i = 0; i < 26; ++i)
		mark[i] = -1;
	mark[s[0] - 'a'] = 0;
	int result = 1;
	for (int i = 1; i < len; ++i) {
		if (mark[s[i] - 'a'] == -1) {
			mark[s[i] - 'a'] = i;
			longest[i] = longest[i - 1] + 1;
		}
		else {
			int d = i - mark[s[i] - 'a'];
			mark[s[i] - 'a'] = i;
			if (d > longest[i - 1])
				longest[i] = longest[i - 1] + 1;
			else
				longest[i] = d;
		}
		if (longest[i] > result)
			result = longest[i];
	}
	delete[] longest;
	return result;
}
int longestSubstringWithoutDuplicate2(const string& s) { // 只需要保存前面一个记录值
	int len = s.size();
	if (len == 0)
		return 0;
	int mark[26];
	for (int i = 0; i < 26; ++i)
		mark[i] = -1;
	mark[s[0] - 'a'] = 0;
	int preLongest = 1, longest = 0;
	for (int i = 1; i < len; ++i) {
		int j = s[i] - 'a';
		if (mark[j] == -1) {
			mark[j] = i;
			longest = preLongest + 1;
		}
		else {
			int d = i - mark[j];
			mark[j] = i;
			if (d > preLongest)
				longest = preLongest + 1;
			else
				longest = d;
		}
		preLongest = longest;
	}
	return longest;
}
//maxLen记录了以第i个字符为结尾的不包含重复字符的子字符串的最大长度
//res记录所有maxLen的最大值
int lengthOfLongestSubstring3(string s) {
	int len = s.size();
	if (len == 0)
		return 0;
	int maxLen = 1, res = 1;
	int mark[128];
	for (int i = 0; i < 128; ++i)
		mark[i] = -1;
	mark[s[0]] = 0;
	for (int i = 1; i < len; ++i) {
		int temp = mark[s[i]];
		if (temp == -1 || i - temp > maxLen)
			maxLen++;
		else if (i - temp < maxLen)
			maxLen = i - temp;
		mark[s[i]] = i;
		res = max(res, maxLen);
	}
	return res;
}
//面试题63：股票的最大利润
int MaxDiff(const vector<int>& prices) {
	int len = prices.size();
	if (len < 2)
		return 0;
	int minPrice = prices[0], re = 0;
	for (int i = 1; i < len; ++i) {
		re = max(re, prices[i] - minPrice);
		minPrice = min(minPrice, prices[i]);
	}
	return re;
}
/*-------------------------分类10：位运算----------------------------*/

//面试题15：二进制中1的个数
//思路1：flag=1,n&flag,flag=flag<<1;要循环32次
//思路2：把1个整数减去1再与原来的数做&运算，会把最右边的1变成0，整数中有几个1就循环几次
int  NumberOf1(int n) {
	int count = 0;
	while (n) {
		count++;
		n = (n - 1)&n;  
	}
	return count;
}
//面试题56：数组中只出现一次的两个数字，其他数字都出现两次
//如果数组中只有一个数字出现一次，其他数字都出现两次，那么可以通过异或操作找到这个数字
//推广到有两个数字出现一次的情况，可以把这个数字分为两个数组，每个数组都只有一个数字出现一次
void FindNumsAppearOnce(vector<int> data, int* num1, int *num2) {
	int mark = 0;
	for (auto& i : data)
		mark = mark^i;
	int temp = 1;
	while ((mark & temp) == 0) {  //通过mark从右边数第一位是否为0分割数组
		temp = temp << 1;
	}
	*num1 = 0;
	*num2 = 0;
	for (auto& i : data) {
		if ((i&temp) == 0)
			*num1 = (*num1) ^ i;
		else
			*num2 = (*num2) ^ i;
	}
}
//数组中只出现一次的数字，其他数字都出现三次
//统计每一位出现1的次数，%3
int FindNumAppearOnce(vector<int> nums) {
	int len = nums.size();
	int mark[32] = { 0 };
	for (int i = 0; i < len; ++i) {
		int bitMask = 1;
		for (int j = 0; j < 32; ++j) {
			if ((nums[i] & bitMask) != 0)
				++mark[j];
			bitMask = bitMask << 1;
		}
	}
	int ans = 0;
	for (int i = 31; i >= 0; --i) {
		ans = ans << 1;  //注意这两句的顺序
		ans += (mark[i] % 3);
	}
	return ans;
}
//面试题65：不用加减乘除做加法
int Add(int num1, int num2)
{
	int sum, carry;
	do {
		sum = num1^num2;
		carry = (num1&num2) << 1;
		num1 = sum;
		num2 = carry;
	} while (carry != 0);
	return sum;
}
/*-------------------------分类11：代码的完整性----------------------------*/

//面试题16：数值的整数次方（不得使用库函数，不考虑大数问题）
//非法输入：底数是0，指数是负数。可以用返回值、全局变量、异常告诉调用者出现了错误
//0的0次方在数学上没有意义，输出0或1都行
//求a的n次方，可以分解成：若n为偶数a^n=a^(n/2)*a^(n/2)，若n为奇数a^n=a^((n-1)/2)*a^((n-1)/2)*a
//用位运算判断奇数偶数
int invalidInput = false;
double PowerCore(double base, int exponent) {
	if (exponent == 0)
		return 1.0;
	if (exponent == 1)
		return base;
	double result = PowerCore(base, exponent >> 1);
	result *= result;
	if ((exponent & 0x01) == 1)
		result *= base;
	return result;
}
double Power(double base, int exponent) {
	invalidInput = false;
	if (base == 0.0 && exponent < 0) {
		invalidInput = true;
		return 0;
	}
	int absexponent = exponent;
	if (exponent < 0)
		absexponent = -exponent;
	double re = PowerCore(base, absexponent);
	if (exponent < 0)
		return 1.0 / re;
	return re;
}


//--------------分类12：空间换时间--------------------
//面试题49：丑数
int GetUglyNumber_Solution(int index) {
	if (index == 1)
		return 1;
	int* mark = new int[index];
	mark[0] = 1;
	int I2 = 0, I3 = 0, I5 = 0;
	for (int i = 1; i < index; ++i) {
		mark[i] = min(2 * mark[I2], min(3 * mark[I3], 5 * mark[I5]));
		while (2 * mark[I2] <= mark[i])
			I2++;
		while (3 * mark[I3] <= mark[i])
			I3++;
		while (5 * mark[I5] <= mark[i])
			I5++;
	}
	int result = mark[index - 1];
	delete[] mark;
	return result;
}

//面试题50：第一个只出现一次的字符的位置,需要区分大小写
int FirstNotRepeatingChar(const string& str) {
	int markA[26], marka[26];
	for (int i = 0; i < 26; ++i) {
		markA[i] = 0;
		marka[i] = 0;
	}
	int len = str.size();
	for (int i = 0; i < len; ++i) {
		if ((str[i] - 'A') < 26)
			markA[str[i] - 'A']++;
		else
			marka[str[i] - 'a']++;
	}
	for (int i = 0; i < len; ++i) {
		if ((((str[i] - 'A') < 26) && (markA[str[i] - 'A'] == 1)) || (((str[i] - 'a')< 26) && (marka[str[i] - 'a'] == 1)))
			return i;
	}
	return -1;
}
//如果是以stream输入
int FirstNotRepeatingCharInStream(const string& str) {
	int len = str.size();
	if (len == 0)
		return -1;
	int* mark = new int[52];//大写在前
	for (int i = 0; i < 52; ++i)
		mark[i] = -1;//未出现过
	for (int i = 0; i < len; ++i) {
		int j = (str[i] - 'A'<26) ? str[i] - 'A' : str[i] - 'a' + 26;
		if (mark[j] == -1)
			mark[j] = i;
		else if (mark[j] >= 0)
			mark[j] = -2;
	}
	int minIndex = INT_MAX;
	for (int i = 0; i < 52; ++i)
	{
		if (mark[i] >= 0 && mark[i] < minIndex)
			minIndex = mark[i];
	}
	delete[] mark;
	return minIndex;
}

/*--------------------------分类13：数学分析和建模------------------------------*/
//面试题60：n个骰子的点数
void printProbility(int number) {
	if (number < 1)
		return;
	int maxValue = 6, len = maxValue*number + 1; // number个骰子的点数之和最大值为maxValue*number
	int* probility[2];

	probility[0] = new int[len];
	probility[1] = new int[len];
	for (int i = 0; i < len; ++i) {
		probility[0][i] = 0;
		probility[1][i] = 0;
	}
	int flag = 0;
	for (int i = 1; i <= maxValue; ++i)
		probility[flag][i] = 1;
	for (int i = 2; i <= number; ++i) {//加入第i个骰子
		for (int j = 1; j <= i*maxValue; ++j) {
			for (int jj = j; jj > 0 && j - jj < maxValue; --jj) {
				probility[1 - flag][j] += probility[flag][jj]; // 点数和为j的骰子数之和上一轮循环中点数和为j-1,j-2,...,j-maxValue的骰子数之和
			}
		}
		flag = 1 - flag;
	}
	double total = pow(maxValue, number);
	for (int i = 1; i < len; ++i) {
		cout << "count=" << probility[flag][i] << endl;
		double ratio = (double)probility[flag][i] / total;
		cout << i << "=" << ratio << endl;
	}
	delete[] probility[0];
	delete[] probility[1];
}

//面试题66：构建乘积数组
vector<int> multiply(const vector<int>& A) {
	int len = A.size();
	vector<int> result;
	if (len > 0) {
		int temp = 1;
		for (int i = 0; i < len; ++i) {
			result.push_back(temp);
			temp *= A[i];
		}
		temp = 1;
		for (int i = len - 1; i >= 0; --i) {
			result[i] *= temp;
			temp *= A[i];
		}
	}
	return result;
}


/*--------------------分类14：创新解法-------------------------------------*/

//面试题64：求1+2+...+n，要求不能用乘除法，不能用for、while、if、else、switch、case等关键字及条件判断语句
//解法1：利用类的静态成员和类的构造函数
class Temp {
public:
	Temp() { ++num; sum += num; }
	static void reset() { num = 0; sum = 0; }
	static unsigned int getSum() { return sum; }

private:
	static unsigned int num;
	static unsigned int sum;
};
unsigned int Temp::num = 0;
unsigned int Temp::sum = 0;
int Sum_Solution(int n) {
	Temp::reset();
	Temp* tempInstance = new Temp[n];
	delete[] tempInstance;
	return Temp::getSum();
}
//解法2:利用虚函数
class A {
public:
	virtual int sum(int n) { return 0; }
};
A* Array[2];
class B :public A {
public:
	virtual int sum(int n) {
		return Array[!!n]->sum(n - 1) + n;
	}
};
int Sum_Solution(int n) {
	A a;
	B b;
	Array[0] = &a;
	Array[1] = &b;
	return Array[1]->sum(n);
}
//解法3：用函数指针
typedef int(*fun)(int);
int funTerminate(int n) {
	return 0;
}
int funSum(int n) {
	static fun f[2] = { funTerminate, funSum };
	return f[!!n](n - 1) + n;
}
//解法4：利用模板在编译期计算
template<int n> struct sum {
	enum value { N = sum<n - 1>::N + n };
};
template<>struct sum<1> {
	enum value { N = 1 };
};
int main() {
	auto i = sum<4>::N; //缺点是不能动态的输入n,这里n=4
	cout << i << endl;
	system("PAUSE");
	return 0;
}



