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
//187
vector<string> findRepeatedDnaSequences(string s)
{
	unordered_map<string, int> record;
	int len = s.size();
	vector<string> re;
	for (int i = 0; i < len - 9; i++)
	{
		string temp(s.begin() + i, s.begin() + i + 10);
		if (record.find(temp) == record.end())
			record[temp] = 1;
		else if (record[temp] == 1)
		{
			re.push_back(temp);
			record[temp]++;
		}
		else
			record[temp]++;

	}
	return re;
}