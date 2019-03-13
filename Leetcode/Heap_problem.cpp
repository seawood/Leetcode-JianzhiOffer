#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <map>
#include <sstream>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <stack>
#include <cstdlib>
#include <climits>
#include <queue>
#include <functional>


using namespace std;
//378二分法
int kthSmallest(vector<vector<int>>& matrix, int k)
{
	int n = matrix.size();
	int left = matrix[0][0], right = matrix[n - 1][n - 1];
	int mid, count;
	while (left<right)
	{
		mid = (left + right) / 2;
		count = 0;
		for (int i = 0; i < n; i++)
			count += upper_bound(matrix[i].begin(), matrix[i].end(), mid) - matrix[i].begin();//小于等于mid的数的个数
		if (count < k)
			left = mid + 1;//+1很关键，写成left=mid会可能死循环
		else
			right = mid;
	}
	return left;
}

//373我自己写的
struct cmp
{
	bool operator()(pair<int, int> a, pair<int, int> b)
	{
		return (a.first + a.second) > (b.first + b.second);
	}
};
vector<pair<int, int>> kSmallestPairs1(vector<int>& nums1, vector<int>& nums2, int k)
{
	vector<pair<int, int>> re;
	int len1 = nums1.size(), len2 = nums2.size();
	if (len1 == 0 || len2 == 0)
		return re;
	priority_queue<pair<int, int>, vector<pair<int, int>>, cmp > q;
	for (int i = 0; i < len1; i++)
		for (int j = 0; j < len2; j++)
			q.push(pair<int, int>(nums1[i], nums2[j]));
	int len_r = min(len1*len2, k);
	for (int i = 0; i < len_r; i++)
	{
		re.push_back(q.top());
		q.pop();
	}
	return re;
}
//373别人的代码
vector<pair<int, int>> kSmallestPairs2(vector<int>& nums1, vector<int>& nums2, int k) {
	vector<pair<int, int>> result;
	if (nums1.empty() || nums2.empty() || k <= 0)
		return result;
	auto comp = [&nums1, &nums2](pair<int, int> a, pair<int, int> b) {
		return nums1[a.first] + nums2[a.second] > nums1[b.first] + nums2[b.second]; };
	priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> min_heap(comp);
	min_heap.emplace(0, 0);
	while (k-- > 0 && min_heap.size())
	{
		auto idx_pair = min_heap.top(); min_heap.pop();
		result.emplace_back(nums1[idx_pair.first], nums2[idx_pair.second]);
		if (idx_pair.first + 1 < nums1.size())
			min_heap.emplace(idx_pair.first + 1, idx_pair.second);
		if (idx_pair.first == 0 && idx_pair.second + 1 < nums2.size())
			min_heap.emplace(idx_pair.first, idx_pair.second + 1);
	}
	return result;
}

//313
int nthSuperUglyNumber(int n, vector<int>& primes)
{
	int len = primes.size();
	vector<int> re(n, 0), record(len, 0);
	re[0] = 1;
	auto cmp = [](int a, int b)->bool {
		return a > b;
	};
	for (int i = 1; i < n; i++)
	{
		priority_queue<int, vector<int>, decltype(cmp)> temp(cmp);
		for (int j = 0; j < len; j++)
			temp.push(primes[j] * re[record[j]]);
		re[i] = temp.top();
		for (int j = 0; j < len; j++)
			if (re[i] == primes[j] * re[record[j]])
				record[j]++;

	}
	return re[n - 1];
}

//264
int nthUglyNumber(int n)
{
	int primes[3]{ 2,3,5 };
	vector<int> re(n, 0), record(3, 0);
	re[0] = 1;
	auto cmp = [](int a, int b)->bool {
		return a > b;
	};
	for (int i = 1; i < n; i++)
	{
		priority_queue<int, vector<int>, decltype(cmp)> temp(cmp);
		for (int j = 0; j < 3; j++)
			temp.push(primes[j] * re[record[j]]);
		re[i] = temp.top();
		for (int j = 0; j < 3; j++)
			if (re[i] == primes[j] * re[record[j]])
				record[j]++;

	}
	return re[n - 1];
}