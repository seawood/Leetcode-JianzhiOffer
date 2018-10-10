/***
Leetcode Tag:String
***/

#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <map>
#include <sstream>
#include <unordered_map>
#include <stack>
using namespace std;

//686
int repeatedStringMatch(string A, string B)
{
	string Adup = A;
	int lenB = B.size();
	int lenA = A.size();
	int n = 1;
	while (Adup.find(B) == Adup.npos && Adup.size() < lenB)
	{
		Adup += A;
		n++;
	}
	if (Adup.find(B) == Adup.npos)
	{
		Adup += A;
		n++;
		if (Adup.find(B) == Adup.npos)
			return -1;
		else return n;
	}
	else
		return n;
}

//387
int firstUniqChar387(string s) 
{
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
//383
bool canConstruct(string ransomNote, string magazine) 
{
	int a[26] = { 0 }, b[26] = { 0 };
	int len1 = ransomNote.size(), len2 = magazine.size();
	int i;
	for (i = 0; i < len1; i++)
	{
		a[ransomNote[i] - 'a']++;
	}
	for (i = 0; i < len2; i++)
	{
		b[magazine[i] - 'a']++;

	}
	for (i = 0; i < 26; i++)
	{
		if (a[i] > b[i])
			return false;
	}
	return true;
}
//345
string reverseVowels(string s) 
{
	string mark("aeiouAEIOU");
	int len = s.size();
	int l = 0, r = len - 1;
	while (r > l)
	{
		while (mark.find(s[l]) == string::npos)
			l++;
		while (mark.find(s[r]) == string::npos)
			r--;
		if (r > l)
		{
			char temp = s[l];
			s[l] = s[r];
			s[r] = temp;
			l++;
			r--;
		}
	}
	return s;
}
//125
bool isPalindrome(string s)
{
	int len = s.size();
	int l = 0, r = len - 1;
	while (l < r)
	{
		while (isalnum(s[l]) == false && l < r)l++;
		while (isalnum(s[r]) == false && l < r)r--;
		if (tolower(s[l]) != tolower(s[r])) return false;
		l++;
		r--;
	}
	return true;
}
//67
string addBinary(string a, string b)
{
	string re = "";
	int i = a.size() - 1, j = b.size() - 1, c = 0;

	while (i >= 0 || j >= 0 || c == 1)
	{
		c += i >= 0 ? a[i--] - '0' : 0;
		c += j >= 0 ? b[j--] - '0' : 0;
		re = char(c % 2 + '0') + re;
		c /= 2;
	}
	return re;
}
//58
int lengthOfLastWord(string s) 
{
	int len = s.size();

	int i = len - 1, l;
	while (i >= 0 && isblank(s[i]))
		i--;
	if (i < 0)
		return 0;
	l = i;
	while (i >= 0 && !isblank(s[i]))
		i--;

	return l - i;
}
//38
string countAndSay(int n)
{
	int len = 1;
	string re = "1";
	if (n == 1)
		return re;
	len++;
	while (len <= n)
	{

		string result = "";
		int leni = re.size();
		int i = 0;
		char temp = re[i++];
		int count = 1;

		while (i < leni)
		{

			if (re[i] == temp)
			{
				i++;
				count++;
			}
			else
			{
				result += to_string(count);
				result.push_back(temp);
				temp = re[i++];
				count = 1;
			}

		}
		result += to_string(count);
		result.push_back(temp);
		re = result;
		len++;


	}
	return re;
}
//28
int strStr(string haystack, string needle) 
{
	if (needle.size() == 0)
		return 0;
	int re;
	if ((re = haystack.find(needle)) != string::npos)
		return re;
	else
		return -1;
}
//13
int romanToInt(string s) {
	unordered_map<char, int> table{ { 'I',1 },{ 'V',5 },{ 'X',10 },{ 'L',50 },{ 'C',100 },{ 'D',500 },{ 'M',1000 } };
	int len = s.size();
	int result = 0;
	for (int i = 0; i < len; i++)
	{
		int val = table[s[i]];
		if (i == len - 1 || table[s[i + 1]] <= val)
			result += val;
		else
			result -= val;

	}
	return result;
}
//227
int calculate(string s)
{
	int len = s.size();
	if (len == 0)
		return 0;
	stack<int> num;
	int i = 0;
	char op = '+';
	while (i < len)
	{
		char temp = s[i];
		int num_temp = 0;
		if (temp >= '0' && temp <= '9')
		{
			num_temp = temp - '0';
			i++;
			while (s[i] >= '0' && s[i] <= '9')
			{
				num_temp = 10 * num_temp + s[i] - '0';
				i++;
			}

			if (op == '+')
				num.push(num_temp);
			else if (op == '-')
				num.push(-num_temp);
			else if (op == '*' || '/')
			{
				int a = num.top();
				num.pop();
				num.push(op == '*' ? a*num_temp : a / num_temp);
			}

		}
		else if (temp == ' ')
			i++;
		else
		{
			op = temp;
			i++;
		}

	}
	int result = 0;
	while (!num.empty())
	{
		result += num.top();
		num.pop();

	}

	return result;
}

//151
void reverseWords(string &s)
{
	istringstream stem(s);
	s = "";
	string temp;
	while (stem >> temp)
		s = temp + " " + s;
	s = s.substr(0, s.size() - 1);
}
//91
bool isValid(char a)
{
	return (a == '0');
}

bool isValid(char a, char b)
{
	return (a == '1' || a == '2' && b <= '6');
}
int numDecodings(string s) 
{
	int len = s.size();
	if (!len || s[0] == '0') return 0;
	if (len == 1) return 1;
	int res = 0, fn_1 = 1, fn_2 = 1, temp;
	for (int i = 1; i < len; i++)
	{
		if (!isValid(s[i]) && isValid(s[i - 1], s[i])) res = fn_1 + fn_2;
		if (isValid(s[i]) && isValid(s[i - 1], s[i])) res = fn_2;
		if (isValid(s[i]) && !isValid(s[i - 1], s[i])) res = 0;
		if (!isValid(s[i]) && !isValid(s[i - 1], s[i])) res = fn_1;
		fn_2 = fn_1;
		fn_1 = res;
	}
	return res;
}


//22
vector<string> generateParenthesis(int n) {
	vector<deque<char>> S(2 * n, deque<char>({ '(',')' }));
	int k = 0;
	vector<string> result;
	string re(2 * n, '*');
	int l_count = 0, r_count = 0;
loop:while (!S[k].empty())
{
	if (re[k] == '(')
		l_count--;
	else if (re[k] == ')')
		r_count--;
	re[k] = S[k].front();
	S[k].front() == '(' ? l_count++ : r_count++;
	S[k].pop_front();
	if (k < 2 * n - 1)
	{
		if (l_count == n)
			S[++k] = deque<char>({ ')' });
		else if (r_count == l_count)
			S[++k] = deque<char>({ '(' });
		else if (r_count > l_count)
			S[++k] = deque<char>();
		else
			S[++k] = deque<char>({ '(',')' });
	}
	else
		result.push_back(re);
}
	 if (k > 0)
	 {
		 re[k] == '(' ? l_count-- : r_count--;
		 re[k] = '*';
		 k--;
		 goto loop;
	 }
	 return result;
}

//43大数相乘
string multiply(string num1, string num2) {
	if (num1[0] == '0' || num2[0] == '0')
		return to_string(0);
	int len1 = num1.size(), len2 = num2.size(), m = len1 + len2 - 2, temp = 0, a = 0;
	string result = "";
	string n1 = "", n2 = "";
	for (int i = len1 - 1; i >= 0; i--)
		n1 += num1[i];
	for (int i = len2 - 1; i >= 0; i--)
		n2 += num2[i];
	for (int i = 0; i <= m; i++)
	{
		temp = 0;
		for (int j = max(0, i - len2 + 1); j <= min(len1 - 1, i); j++)
			temp += (n1[j] - '0')*(n2[i - j] - '0');
		temp += a;
		a = temp / 10;
		temp = temp % 10;
		result += to_string(temp);
	}
	if (a != 0)
		result += to_string(a);
	string re;
	for (int i = result.size() - 1; i >= 0; i--)
		re += result[i];
	return re;
}

//49
vector<vector<string>> groupAnagrams1(vector<string>& strs)
{
	vector<vector<string>> re;
	vector<vector<int>> re_num;
	int len = strs.size();
	vector<int> temp(26, 0);
	for (int j = 0; j < strs[0].size(); j++)
		temp[strs[0][j] - 'a'] = 1;
	re_num.push_back(temp);
	vector<string> temp_s;
	temp_s.push_back(strs[0]);
	re.push_back(temp_s);
	for (int i = 1; i < len; i++)
	{
		vector<int> temp(26, 0);
		int j;
		for (j = 0; j < strs[i].size(); j++)
			temp[strs[i][j] - 'a'] ++;
		for (j = 0; j < re_num.size(); j++)
			if (re_num[j] == temp)
			{
				re[j].push_back(strs[i]);
				break;
			}
		if (j == re_num.size())
		{
			re_num.push_back(temp);
			vector<string> temp_s;
			temp_s.push_back(strs[i]);
			re.push_back(temp_s);
		}

	}
	return re;

}
vector<vector<string>> groupAnagrams2(vector<string>& strs)
{
	int len = strs.size();
	map<string, vector<string>> re;
	for (int i = 0; i < len; i++)
	{
		string temp = strs[i];
		sort(temp.begin(), temp.end());
		re[temp].push_back(strs[i]);
	}
	vector<vector<string>> result;
	for (auto it = re.begin(); it != re.end(); it++)
		result.push_back(it->second);
	return result;
}

//71
string simplifyPath(string path) {
	stringstream pt(path);
	vector<string> re;
	string temp;
	while (getline(pt, temp, '/'))
		if (temp == "" || temp == ".")
			continue;
		else if (temp == ".." && !re.empty())
			re.pop_back();
		else if (temp != "..")
			re.push_back(temp);
	string result = "";
	for (auto i : re)
		result += "/" + i;
	return result.empty() ? "/" : result;
}
//93
vector<string> restoreIpAddresses(string s) {
	int len = s.size();
	vector<string> result;
	int k = 0, left = 0, temp;
	deque<string> a;
	vector<deque<string>> S(4, a);
	vector<string> re;
	for (int i = 1; i <= 3; i++)
	{
		if (left + i <= len)
		{
			if (s.substr(left, 1) == "0"&&i != 1)
				continue;
			temp = stoi(s.substr(left, i));
			if (temp >= 0 && temp < 256)
				S[k].push_back(s.substr(left, i));
		}
	}
loop:while (!S[k].empty())
{
	while (re.size() > k)
	{
		left -= re.back().size();
		re.pop_back();
	}

	re.push_back(S[k].front());
	left += S[k].front().size();
	S[k].pop_front();
	if (k < 3)
	{
		k++;
		for (int i = 1; i <= 3; i++)
		{
			if (left + i <= len)
			{
				if (s.substr(left, 1) == "0"&&i != 1)
					continue;
				temp = stoi(s.substr(left, i));
				if (temp >= 0 && temp < 256)
					S[k].push_back(s.substr(left, i));
			}
		}
	}
	else if (left == len)
	{

		string temp_re = "";
		for (int i = 0; i < re.size(); i++)
			temp_re += re[i] + ".";
		result.push_back(temp_re.substr(0, temp_re.size() - 1));
	}
	else
	{
		left -= re.back().size();
		re.pop_back();
	}
}
	 if (k >0)
	 {
		 left -= re.back().size();
		 re.pop_back();
		 k--;
		 goto loop;
	 }
	 return result;
}

//165
int compareVersion(string version1, string version2) {
	stringstream s1(version1), s2(version2);
	vector<int> v1, v2;
	string temp;
	while (getline(s1, temp, '.'))
		v1.push_back(stoi(temp));
	while (getline(s2, temp, '.'))
		v2.push_back(stoi(temp));
	int len1 = v1.size(), len2 = v2.size();
	int i = 0;
	while (i < min(len1, len2))
	{
		if (v1[i] > v2[i])
			return 1;
		else if (v1[i] < v2[i])
			return -1;
		else
			i++;
	}
	if (i == len1)
	{
		while (i < len2 && v2[i] == 0)
			i++;
		if (i == len2)
			return 0;
	}

	if (i == len2)
	{
		while (i < len1 && v1[i] == 0)
			i++;
		if (i == len1)
			return 0;
	}

	return len1 > len2 ? 1 : -1;

}
//468判断IPv4和IPv6地址的有效性
string validIPAddress(string IP)
{
	stringstream s4(IP);
	string temp;
	int t, a = 0, num = 0;
	bool IPv4 = true, IPv6 = true;

	while (IPv4 == true && getline(s4, temp, '.'))
	{
		num++;
		if (num > 4 || temp.size() == 0 || temp.size() > 3)
			IPv4 = false;
		else
		{
			for (int i = 0; i < temp.size(); i++)
				if (!isdigit(temp[i]))
				{
					IPv4 = false;
					break;
				}
			if (IPv4)
			{
				t = stoi(temp);
				if (t < 0 || t > 255)
					IPv4 = false;
				else
				{
					a = 0;
					while (t /= 10)
						a++;
					if (a + 1 != temp.size())
						IPv4 = false;
				}
			}
		}
	}
	if (temp == "" || num != 4)
		IPv4 = false;
	if (!IPv4)
	{
		stringstream s6(IP);
		num = 0;
		while (IPv6 == true && getline(s6, temp, ':'))
		{
			num++;
			if (num > 8 || temp.size()>4 || temp.size() == 0)
				IPv6 = false;
			else
			{
				for (int i = 0; i < temp.size(); i++)
				{
					if (!(temp[i] >= '0'&&temp[i] <= '9' || temp[i] >= 'a'&&temp[i] <= 'f' || temp[i] >= 'A'&&temp[i] <= 'F'))
					{
						IPv6 = false;
						break;
					}

				}
			}
		}
		if (temp == "" || num != 8)
			IPv6 = false;

	}
	return IPv4 | IPv6 ? (IPv4 ? "IPv4" : "IPv6") : "Neither";
}

//8
int myAtoi(string str)
{
	int len = str.size();
	if (len != 0)
	{
		size_t pos = str.find_first_not_of(" ");
		if (pos != string::npos && (str[pos] == '-' || str[pos] == '+' || isdigit(str[pos])))
		{

			bool flag;
			if (str[pos] == '-')
			{
				flag = false;
				pos++;
			}
			else if (str[pos] == '+')
			{
				flag = true;
				pos++;
			}
			else
				flag = true;
			pos = str.find_first_not_of("0", pos);
			long long re = 0;
			int i, total = 0;
			for (i = pos; i< len&&isdigit(str[i]) && total < 10; i++)
			{
				re = re * 10 + (str[i] - '0');
				total++;
			}
			if (total == 10 && isdigit(str[i]))
				return flag ? INT_MAX : INT_MIN;
			else
				return flag ? min(re, (long long)INT_MAX) : max(-re, (long long)(INT_MIN));
		}
	}
	return 0;
}
