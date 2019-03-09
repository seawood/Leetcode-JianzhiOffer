/***
Leetcode Tag:LinkedList
***/

#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <map>
#include <sstream>
#include <unordered_map>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
//83
ListNode* deleteDuplicates(ListNode* head) {
	ListNode* rec = head;
	while (head && head->next)
	{
		if (head->val == head->next->val)
		{
			ListNode* temp = head->next;
			head->next = head->next->next;
			free(temp);
		}
		else
			head = head->next;

	}
	return rec;
}
//141.linked list cycle
bool hasCycle(ListNode *head) {
	ListNode* walker = head, *runner = head;
	while (runner&&runner->next)
	{
		walker = walker->next;
		runner = runner->next->next;
		if (walker == runner)
			return true;
	}
	return false;

}
//142
ListNode *detectCycle(ListNode *head) {

	ListNode* runner = head, *walker = head;
	while (runner && runner->next)
	{
		walker = walker->next;
		runner = runner->next->next;
		if (walker == runner)
			break;
	}
	if (runner == NULL || runner->next == NULL)
		return NULL;
	walker = head;
	while (runner != walker)
	{
		runner = runner->next;
		walker = walker->next;
	}
	return runner;
}
//143
void reorderList(ListNode* head)
{
	int total = 0;
	ListNode* p = head;
	while (p)
	{
		total++;
		p = p->next;
	}
	if (total <= 2)
		return;
	total /= 2;
	p = head;
	while (total > 1)
	{
		p = p->next;
		total--;
	}
	ListNode* pre = p, *cur = p->next;
	while (cur&&cur->next)
	{
		ListNode* temp = cur->next;
		cur->next = temp->next;
		temp->next = pre->next;
		pre->next = temp;
	}
	while (head != p)
	{
		ListNode* temp = p->next;
		p->next = temp->next;
		temp->next = head->next;
		head->next = temp;
		head = head->next->next;
	}
}
//147
ListNode* insertionSortList(ListNode* head)
{
	if (head == NULL)
		return head;
	ListNode* dummy = new ListNode(INT_MIN);
	dummy->next = head;
	ListNode* shead = head;
	head = head->next;
	shead->next = NULL;
	ListNode* temp;
	while (head)
	{
		shead = dummy;
		while (shead->next && shead->next->val < head->val)
			shead = shead->next;
		temp = head;
		head = head->next;
		temp->next = shead->next;
		shead->next = temp;
	}
	return dummy->next;
}

struct RandomListNode {
	int label;
	RandomListNode *next, *random;
	RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};
//138
RandomListNode *copyRandomList(RandomListNode *head)
{
	if (!head)
		return nullptr;
	RandomListNode* headCopy = head;
	RandomListNode* newHead = new RandomListNode(head->label);
	unordered_map<RandomListNode*, RandomListNode*> pmap;
	pmap[head] = newHead;
	head = head->next;
	while (head)
	{
		RandomListNode * temp = new RandomListNode(head->label);
		newHead->next = temp;
		newHead = newHead->next;
		pmap[head] = newHead;
		head = head->next;
	}
	newHead->next = NULL;
	head = headCopy;
	while (head)
	{
		pmap[head]->random = pmap[head->random];
		head = head->next;
	}
	return pmap[headCopy];
}

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
//109
TreeNode* sortedBST(ListNode* head, ListNode* tail)
{
	if (head == tail)
		return nullptr;
	ListNode* fast = head, *slow = head;
	while (fast != tail && fast->next != tail)
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	TreeNode* root = new TreeNode(slow->val);
	root->left = sortedBST(head, slow);
	root->right = sortedBST(slow->next, tail);
	return root;
}
TreeNode* sortedListToBST(ListNode* head)
{
	return sortedBST(head, nullptr);
}


//92
ListNode* reverseBetween(ListNode* head, int m, int n)
{
	ListNode* dummy = new ListNode(0);
	dummy->next = head;
	ListNode* walk = dummy;
	for (int i = 0; i < m - 1; i++)
		walk = walk->next;
	ListNode* hhead = walk->next;
	while (m < n)
	{
		ListNode* temp = hhead->next;
		hhead->next = temp->next;
		temp->next = walk->next;
		walk->next = temp;
		m++;
	}
	return dummy->next;

}
//86
ListNode* partition(ListNode* head, int x)
{
	ListNode* dummy = new ListNode(0);
	dummy->next = head;
	ListNode* walk1 = dummy, *walk2 = dummy;
	while (walk2->next != nullptr)
	{
		if (walk2->next->val < x && walk1 == walk2)
		{
			walk1 = walk1->next;
			walk2 = walk2->next;
		}
		else if (walk2->next->val < x)
		{
			ListNode* temp = walk2->next;
			walk2->next = temp->next;
			temp->next = walk1->next;
			walk1->next = temp;
			walk1 = walk1->next;
		}
		else
			walk2 = walk2->next;
	}
	return dummy->next;
}
//82
ListNode* deleteDuplicates2(ListNode* head)
{

	ListNode* dummy = new ListNode(0);
	dummy->next = head;
	ListNode* walk = dummy;
	int mark;
	bool del = false;
	while (walk->next != nullptr)
	{
		if (walk->next->next != nullptr&&walk->next->val == walk->next->next->val)
		{
			del = true;
			mark = walk->next->val;
			ListNode* temp1 = walk->next;
			ListNode* temp2 = walk->next->next;
			walk->next = temp2->next;
			free(temp1);
			free(temp2);

		}
		else if (del && walk->next->val == mark)
		{
			ListNode* temp = walk->next;
			walk->next = temp->next;
			free(temp);
		}
		else
		{
			walk = walk->next;
			del = false;
		}
	}
	return dummy->next;
}

//61
ListNode* rotateRight(ListNode* head, int k)
{
	int len = 0;
	ListNode* walk = head;
	while (walk != nullptr)
	{
		len++;
		walk = walk->next;
	}
	if (!len || !k)
		return head;
	k %= len;
	if (!k)
		return head;
	walk = head;
	for (int i = 1; i < len - k; i++)
		walk = walk->next;
	ListNode* dummy = walk->next;
	walk->next = nullptr;
	walk = dummy;
	while (walk->next != nullptr)
		walk = walk->next;
	walk->next = head;
	return dummy;
}
//24
ListNode* swapPairs(ListNode* head)
{
	ListNode* dummy = new ListNode(0);
	dummy->next = head;
	ListNode* walk = dummy;
	while (walk->next != nullptr && walk->next->next != nullptr)
	{
		ListNode* temp = walk->next->next;
		walk->next->next = temp->next;
		temp->next = walk->next;
		walk->next = temp;
		walk = walk->next->next;
	}
	return dummy->next;
}

//148
ListNode* merge(ListNode* left, ListNode* right)
{
	if (left == nullptr)
		return right;
	else if (right == nullptr)
		return left;
	else
	{
		ListNode* head, *walk1, *walk2;
		if (left->val < right->val)
		{
			head = left;
			walk2 = right;
		}
		else
		{
			head = right;
			walk2 = left;
		}
		walk1 = head;
		while (walk1->next != nullptr && walk2 != nullptr)
		{
			if (walk1->next->val <= walk2->val)
				walk1 = walk1->next;
			else
			{
				ListNode* temp = walk2;
				walk2 = walk2->next;
				temp->next = walk1->next;
				walk1->next = temp;
				walk1 = temp;
			}
		}
		if (walk2 != nullptr)
			walk1->next = walk2;
		return head;
	}
}
ListNode* sortList(ListNode* head)
{
	if (head == nullptr || head->next == nullptr)
		return head;
	int len = 0;
	ListNode* dummy = new ListNode(0);
	dummy->next = head;
	ListNode* slow = dummy, *fast = dummy;
	while (fast->next != nullptr&&fast->next->next != nullptr)
	{
		slow = slow->next;
		fast = fast->next->next;
	}

	ListNode* right = slow->next;
	slow->next = nullptr;
	ListNode* sortLeft = sortList(head);
	ListNode* sortRight = sortList(right);
	return merge(sortLeft, sortRight);

}