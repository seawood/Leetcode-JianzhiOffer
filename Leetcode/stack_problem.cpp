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

//225
class MyStack {
	queue<int> q1, q2;
	bool flag;
public:
	/** Initialize your data structure here. */
	MyStack() {
		flag = true;
	}

	/** Push element x onto stack. */
	void push(int x) {
		if (flag)
			q1.push(x);
		else
			q2.push(x);
	}

	/** Removes the element on top of the stack and returns that element. */
	int pop() {
		int re;
		if (flag)
		{
			while (q1.size() > 1)
			{
				q2.push(q1.front());
				q1.pop();
			}
			flag = false;
			re = q1.front();
			q1.pop();
		}
		else
		{
			while (q2.size() > 1)
			{
				q1.push(q2.front());
				q2.pop();

			}
			flag = true;
			re = q2.front();
			q2.pop();
		}
		return re;
	}

	/** Get the top element. */
	int top() {
		int re;
		if (flag)
		{
			while (q1.size() > 1)
			{
				q2.push(q1.front());
				q1.pop();

			}
			flag = false;
			re = q1.front();
			q2.push(re);
			q1.pop();
		}
		else
		{
			while (q2.size() > 1)
			{
				q1.push(q2.front());
				q2.pop();

			}
			flag = true;
			re = q2.front();
			q1.push(re);
			q2.pop();
		}
		return re;
	}

	/** Returns whether the stack is empty. */
	bool empty() {
		return flag ? q1.empty() : q2.empty();
	}
};

//155
class MinStack {
	stack<int> s, sMin;

public:
	/** initialize your data structure here. */
	MinStack() {

	}

	void push(int x) {
		s.push(x);
		if (sMin.empty() || sMin.top() >= x)
			sMin.push(x);
	}

	void pop() {
		if (!s.empty())
		{
			if (sMin.top() == s.top())
				sMin.pop();
			s.pop();
		}
	}

	int top() {
		return s.top();
	}

	int getMin() {
		return sMin.top();
	}
};
//394Ã»¶®
string decodeString(string s) {
	stack<int> number;  //´æÊý×Ö
	stack<string> str;  //´æ×Ö·û´®
	string ans;
	int i = 0;
	while (i<s.length()) {
		if (s[i] <= '9' && s[i] >= '0') {
			int count = 0;
			while (s[i] <= '9' && s[i] >= '0') {
				count = count * 10 + (s[i] - '0');
				i++;
			}//while
			number.push(count);
		}
		else if (s[i] == '[') {
			str.push(ans);
			ans = "";
			i++;
		}
		else if (s[i] == ']') {
			string tmp = str.top();
			str.pop();
			int cnt = number.top();
			number.pop();
			for (int j = 0; j<cnt; j++) {
				tmp += ans;
			}//for
			ans = tmp;
			i++;
		}
		else {
			ans += s[i];
			i++;
		}
	}//while
	return ans;
}

class NestedInteger {
public:
	// Return true if this NestedInteger holds a single integer, rather than a nested list.
	bool isInteger() const;

	// Return the single integer that this NestedInteger holds, if it holds a single integer
	// The result is undefined if this NestedInteger holds a nested list
	int getInteger() const;

	// Return the nested list that this NestedInteger holds, if it holds a nested list
	// The result is undefined if this NestedInteger holds a single integer
	const vector<NestedInteger> &getList() const;

};

class NestedIterator {
	stack<NestedInteger> s;
public:
	NestedIterator(vector<NestedInteger> &nestedList) {
		int len = nestedList.size();
		for (int i = len - 1; i >= 0; i--)
			s.push(nestedList[i]);
	}

	int next() {
		NestedInteger temp = s.top();
		s.pop();
		if (temp.isInteger())
			return temp.getInteger();
		else
		{
			vector<NestedInteger> v = temp.getList();
			for (int i = v.size() - 1; i >= 0; i--)
				s.push(v[i]);
			return this->next();
		}
	}

	bool hasNext() {
		if (!s.empty())
		{
			if (s.top().isInteger())
				return true;
			else
			{
				vector<NestedInteger> v = s.top().getList();
				s.pop();
				for (int i = v.size() - 1; i >= 0; i--)
				{
					if (v[i].isInteger() || v[i].getList().size() != 0)
						s.push(v[i]);
				}
				return this->hasNext();
			}
		}
		return false;
	}
};
