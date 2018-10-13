#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <map>
#include <sstream>
#include <unordered_map>
#include <set>
using namespace std;

//389
char findTheDifference(string s, string t)
{
	int record[26] = { 0 };
	int len = t.size(), i = 0;
	for (i = 0; i < len; i++)
		record[t[i] - 'a']++;
	for (i = 0; i < len - 1; i++)
		record[s[i] - 'a']--;
	for (i = 0; i < 26; i++)
		if (record[i] == 1)
			return int('a') + i;
	return 'a';
}

//387
int firstUniqChar(string s) {
	int mark[26] = { 0 };
	int len = s.size();
	int i;
	for (i = 0; i < len; i++)
	{
		mark[s[i] - 'a']++;

	}

	for (i = 0; i < len; i++)
	{
		if (mark[s[i] - 'a'] == 1)
			return i;
	}

	return -1;
}
//349
vector<int> intersection(vector<int>& nums1, vector<int>& nums2)
{
	int len1 = nums1.size(), len2 = nums2.size(), i = 0;
	vector<int> result;
	set<int> record1, record2;
	for (i = 0; i < len1; i++)
		record1.insert(nums1[i]);
	for (i = 0; i < len2; i++)
		record2.insert(nums2[i]);
	for (auto j = record2.begin(); j != record2.end(); j++)
	{
		if (record1.find(*j) != record1.end())
			result.push_back(*j);
	}
	return result;
}

//350
vector<int> intersect(vector<int>& nums1, vector<int>& nums2)
{
	int len1 = nums1.size(), len2 = nums2.size(), i = 0;
	map<int, int> record;
	vector<int> result;
	for (i = 0; i < len1; i++)
	{

		record[nums1[i]]++;
	}
	for (i = 0; i < len2; i++)
	{
		if (record.find(nums2[i]) != record.end() && record[nums2[i]] > 0)
		{
			result.push_back(nums2[i]);
			record[nums2[i]]--;
		}
	}
	return result;
}

//290
bool wordPattern(string pattern, string str)
{
	stringstream sstr(str);
	string temp;
	map<char, string> record;
	set<char> set1;
	set<string> set2;
	int i = 0;
	while (getline(sstr, temp, ' '))
	{

		if (set1.find(pattern[i]) == set1.end() && set2.find(temp) == set2.end())
		{
			set1.insert(pattern[i]);
			set2.insert(temp);
			record[pattern[i++]] = temp;
		}
		else if (record[pattern[i]] != temp)
			return false;
		else
			i++;
	}
	int len = pattern.size();
	return i == len ? true : false;
}

//205
bool isIsomorphic(string s, string t)
{

	map<char, char> record;
	set<char> set1, set2;
	int len1 = s.size(), len2 = t.size();
	int i, j;
	for (i = 0, j = 0; i < len1, j < len2; )
	{
		if (set1.find(s[i]) == set1.end() && set2.find(t[j]) == set2.end())
		{
			set1.insert(s[i]);
			set2.insert(t[j]);
			record[s[i++]] = t[j++];
		}
		else if (record[s[i]] != t[j])
			return false;
		else
		{
			i++;
			j++;
		}

	}
	return i == len1 && j == len2 ? true : false;
}
//204¶òÀ­¶àÈûÉ¸·¨
int countPrimes(int n)
{
	vector<bool> record(n, false);
	int j = 0, temp = 0;;
	for (int i = 2; i <= sqrt(n - 1); i++)
	{
		if (!record[i])
		{
			temp = i, j = i;
			j += temp;
			while (j < n)
			{
				record[j] = true;
				j += temp;
			}
		}
	}
	int result = 0;
	for (int i = 2; i < n; i++)
		if (record[i] == false)
			result++;
	return result;
}

//202
bool isHappy(int n)
{
	int record = 0;
	set<int> t;
	while (n != 1)
	{
		record = 0;
		while (n)
		{
			record += pow(n % 10, 2);
			n /= 10;
		}
		if (t.insert(record).second == false)
			return false;
		n = record;
	}
	return true;
}


//136
int singleNumber(vector<int>& nums)
{
	set<int> record;
	int len = nums.size();
	for (int i = 0; i < len; i++)
	{
		if (record.insert(nums[i]).second == false)
			record.erase(nums[i]);
	}
	for (auto i : record)
		return i;
}
int singleNumber2(vector<int>& nums)
{
	int len = nums.size();
	for (int i = 1; i < len; i++)
		nums[i] ^= nums[i - 1];
	return nums[nums.size() - 1];
}
//380
class RandomizedSet {
	unordered_map<int, int> m;
	vector<int> v;

public:
	/** Initialize your data structure here. */
	RandomizedSet() {

	}

	/** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
	bool insert(int val) {
		if (m.find(val) != m.end())
			return false;
		else
		{
			v.push_back(val);
			m[val] = v.size() - 1;
			return true;
		}
	}

	/** Removes a value from the set. Returns true if the set contained the specified element. */
	bool remove(int val) {
		if (m.find(val) == m.end())
			return false;
		else
		{
			int len = v.size();
			m[v[len - 1]] = m[val];
			v[m[val]] = v[len - 1];
			v.pop_back();
			m.erase(val);
			return true;
		}
	}

	/** Get a random element from the set. */
	int getRandom() {
		return v[rand() % v.size()];

	}
};

//355 unsolved
class Twitter {
	unordered_map<int, deque<int>> NewsFeed;//user,10 news
	unordered_map<int, set<int>> followID;//followee, followers
	unordered_map<int, vector<pair<int, int>>> Tweet;//user, posted news
	int time_r;


public:
	/** Initialize your data structure here. */
	Twitter() {
		time_r = 0;
	}

	/** Compose a new tweet. */
	void postTweet(int userId, int tweetId) {
		if (Tweet.find(userId) != Tweet.end()) //userId not first appear
		{
			pair<int, int> m(tweetId, time_r++);
			Tweet[userId].push_back(m);
			for (auto i : followID[userId])
			{
				if (NewsFeed[i].size() == 10)
					NewsFeed[i].pop_front();
				NewsFeed[i].push_back(tweetId);
			}
		}

		else //userId first appear
		{
			vector<pair<int, int>> temp;
			pair<int, int>m(tweetId, time_r++);
			temp.push_back(m);
			Tweet[userId] = temp;

			set<int> s;
			s.insert(userId);
			followID[userId] = s;

			deque<int> d;
			d.push_back(tweetId);
			NewsFeed[userId] = d;
		}

	}

	/** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
	vector<int> getNewsFeed(int userId) {
		vector<int> re;
		for (int i = NewsFeed[userId].size() - 1; i >= 0; i--)
			re.push_back(NewsFeed[userId][i]);
		return re;
	}

	/** Follower follows a followee. If the operation is invalid, it should be a no-op. */
	void follow(int followerId, int followeeId) {

		if (Tweet.find(followerId) == Tweet.end())
		{
			vector<pair<int, int>> s;
			Tweet[followerId] = s;
			deque<int> d;
			NewsFeed[followerId] = d;
			set<int> s1;
			s1.insert(followerId);
			followID[followerId] = s1;
		}
		if (Tweet.find(followeeId) == Tweet.end())
		{
			vector<pair<int, int>> s;
			Tweet[followeeId] = s;
			deque<int> d;
			NewsFeed[followeeId] = d;
			set<int> s1;
			s1.insert(followeeId);
			followID[followeeId] = s1;
		}
		if (followerId != followeeId&&followID[followeeId].find(followerId) == followID[followeeId].end())
		{
			followID[followeeId].insert(followerId);
			int j = Tweet[followeeId].size() - 1;
			int i = NewsFeed[followerId].size() - 1;
			while (j >= 0 && i >= 0)
			{
				if (Tweet[followeeId][j].second > NewsFeed[followerId][i])
				{
					NewsFeed[followerId].push_back(Tweet[followeeId][j].first);
					j--;
					i -= 2;
					if (NewsFeed[followerId].size() > 10)
						NewsFeed[followerId].pop_front();

				}
				else if (i<0 && NewsFeed[followerId].size() == 10)
				{
					i--;
				}
			}
			if (i <= 0 && j >= 0 && NewsFeed[followerId].size() < 10)
			{
				NewsFeed[followerId].push_back(Tweet[followeeId][j].first);
				j--;
			}

		}



	}

	/** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
	void unfollow(int followerId, int followeeId) {

		if (followerId != followeeId&&followID.find(followeeId) != followID.end() && followID[followeeId].find(followerId) != followID[followeeId].end())
		{
			followID[followeeId].erase(followerId);
			for (int i = 0; i < NewsFeed[followerId].size(); i++)
			{
				for (auto it : Tweet[followeeId])
				{
					if (it.first == *(NewsFeed[followerId].begin() + i))
						NewsFeed[followerId].erase(NewsFeed[followerId].begin() + i);
				}

			}

		}
	}
};

//347
//use nth_element
vector<int> topKFrequent(vector<int>& nums, int k)
{
	map<int, int> count;
	vector<int> num;
	for (auto i : nums)
	{
		count[i]++;
		if (count[i] == 1)
			num.push_back(i);
	}
	nth_element(num.begin(), num.begin() + k, num.end(), [&count](int l, int r)->bool {
		return count[l] > count[r];
	});
	return vector<int>(num.begin(), num.begin() + k);
}

//299
string getHint(string secret, string guess)
{
	unordered_map<char, set<int>> map_sec, map_gue, map_con;
	int len = secret.size();
	int bull = 0, cow = 0;
	for (int i = 0; i < len; i++)
	{
		map_sec[secret[i]].insert(i);
		map_gue[guess[i]].insert(i);
		map_con[secret[i]].insert(i);
		map_con[guess[i]].insert(i);
	}
	int temp1 = 0, temp2 = 0, temp3 = 0, temp = 0;;
	for (auto i : map_sec)
	{
		if (map_gue.find(i.first) != map_gue.end())
		{
			temp1 = i.second.size();
			temp2 = map_gue[i.first].size();
			temp3 = map_con[i.first].size();
			temp = temp1 + temp2 - temp3;
			bull += temp;
			cow += min(temp1 - temp, temp2 - temp);

		}
	}
	string re(to_string(bull) + "A" + to_string(cow) + "B");
	return re;

}
//274
int hIndex(vector<int>& citations)
{
	int len = citations.size();
	if (len == 0)
		return 0;
	if (len == 1 && citations[0] >= 1)
		return 1;
	sort(citations.begin(), citations.end(), [&citations](int l, int r)->bool {
		return l > r;
	});

	int mark = 0;
	for (int i = 0; i < len - 1; i++)
	{
		if (citations[i] >= i + 1 && citations[i + 1] <= i + 1)
			mark = i + 1;
	}
	if (len>1 && citations[len - 1] >= len - 1)
		mark = len;
	return mark;
}
int hIndex2(vector<int>& citations)
{
	int len = citations.size();
	if (len == 0)
		return 0;
	if (len == 1 && citations[0] >= 1)
		return 1;
	sort(citations.begin(), citations.end(), [&citations](int l, int r)->bool {
		return l > r;
	});

	int i;
	for (i = 0; i < len; i++)
	{
		if (citations[i] < i + 1)
			break;
	}
	return i;
}

//36
bool isValidSudoku(vector<vector<char>>& board)
{
	int count = 0;
	for (int i = 0; i < 9; i++)
	{
		count = 0;
		unordered_set<char> s;
		for (int j = 0; j < 9; j++)
			if (board[i][j] != '.')
			{
				count++;
				s.insert(board[i][j]);
			}
		if (count != s.size())
			return false;
	}
	for (int i = 0; i < 9; i++)
	{
		count = 0;
		unordered_set<char> s;
		for (int j = 0; j < 9; j++)
			if (board[j][i] != '.')
			{
				count++;
				s.insert(board[j][i]);
			}
		if (count != s.size())
			return false;
	}



	for (int i = 0; i < 9; i += 3)
		for (int j = 0; j < 9; j += 3)
		{
			count = 0;
			unordered_set<char> s;
			for (int ii = 0; ii < 3; ii++)
				for (int jj = 0; jj < 3; jj++)
					if (board[i + ii][j + jj] != '.')
					{
						count++;
						s.insert(board[i + ii][j + jj]);
					}
			if (count != s.size())
				return false;
		}
	return true;
}

//94
//Definition for a binary tree node.
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}

};
void goAlongLeftBranch(TreeNode* x, stack<TreeNode*>& s)
{
	while (x)
	{
		s.push(x);
		x = x->left;
	}
}
vector<int> inorderTraversal(TreeNode* root)
{
	stack<TreeNode*> s;
	vector<int> v;
	TreeNode* x = root;
	while (true)
	{
		goAlongLeftBranch(x, s);
		if (s.empty())
			break;
		x = s.top();
		s.pop();
		v.push_back(x->val);
		x = x->right;
	}
	return v;
}

//166
string fractionToDecimal(int numerator, int denominator) {
	long long numerator1 = numerator, denominator1 = denominator;

	if (numerator1 == 0)
		return to_string(0);

	bool below_zero = (numerator1*denominator1)<0 ? true : false;

	numerator1 = numerator1 < 0L ? 0L - numerator1 : numerator1;
	denominator1 = denominator1 < 0 ? 0 - denominator1 : denominator1;

	map<int, long long> record;
	vector<int> num;
	long long re;
	int repeat_num, below_num;
	bool repeat = false, below = false;
	while (true)
	{
		if (numerator1 == 0)
			break;

		if (numerator1 < denominator1)
		{
			numerator1 *= 10;
			if (!below)
			{
				below = true;
				below_num = numerator1;
			}
		}
		if (record.find(numerator1) == record.end())
		{
			num.push_back(numerator1);
			re = numerator1 / denominator1;
			record[numerator1] = re;
			numerator1 %= denominator1;
		}
		else
		{
			repeat = true;
			repeat_num = numerator1;
			break;
		}

	}
	string result("");
	if (below_zero)
		result += "-";
	if (below&&below_num == num[0])
	{
		result += "0.";
		below = false;
	}
	for (int k = 0; k < num.size(); k++)
	{
		if (below&&num[k] == below_num)
			result += ".";
		if (repeat&&num[k] == repeat_num)
			result += "(";

		result += to_string(record[num[k]]);
	}
	if (repeat)
		result += ")";

	return result;

}