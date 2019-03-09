#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
using namespace std;

//经典算法之查找：1.二分查找
//1.1：A为有序数组且无重复数字，若不存在返回-1,
int getPos1(vector<int> A, int n, int val) {
	int left = 0, right = n - 1;
	while (left <= right) {
		int mid = (left + right) / 2;
		if (A[mid] == val)
			return mid;
		else if (val < A[mid])
			right = mid - 1;
		else
			left = mid + 1;
	}
	return -1;
}
//1.2：A为有序数组且可能有重复数字，若不存在返回-1，若存在返回第一个出现的下标
int getPos2(vector<int> A, int n, int val) {
	int left = 0, right = n - 1;
	while (left <= right) {
		int mid = (left + right) / 2;
		if (val <= A[mid])
			right = mid - 1;
		else
			left = mid + 1;
	}
	if (left < n && A[left] == val)
		return left;
	return -1;
}
//1.3：A为有序数组且可能有重复数字，若不存在返回-1，若存在返回最后一个出现的下标
int getPos3(vector<int> A, int n, int val) {
	int left = 0, right = n - 1;
	while (left <= right) {
		int mid = (left + right) / 2;
		if (val >= A[mid])
			left = mid + 1;
		else
			right = mid - 1;
	}
	if (right >= 0 && A[right] == val)
		return right;
	return -1;
}

//经典算法之排序（以leetcode 75题.Sort Colors为例）
/*
*1.冒泡排序
*算法：遍历待排序序列，相邻元素若逆序则交换位置，重复上述步骤直到待排序序列为空或者在一趟遍历中没有交换发生
*时间：最差时间复杂度O(n^2),最优时间复杂度O(n)，平均时间复杂度O(n^2)
*空间：所需辅助空间O(1)
*稳定性：稳定
*/
void sortColors_BubbleSort(vector<int>& nums) {
	int len = nums.size();
	bool flag = false;//借助辅助标志，当有序时提前退出循环
	for (int i = 0; i < len; ++i) {
		flag = false;
		for (int j = len - 1; j > i; --j)
			if (nums[j] < nums[j - 1]) {
				swap(nums[j], nums[j - 1]);
				flag = true;
			}
		if (!flag)
			break;
	}
}
/*
*2.选择排序
*算法：在待排序序列中找到最小元素放在序列起始位置作为已排序序列；从剩下的待排序序列中找到最小元素放在已排序序列的末尾；重复上述步骤直到待排序序列为空
*时间：最差时间复杂度O(n^2),最优时间复杂度O(n^2),平均时间复杂度O(n^2)
*空间：所需辅助空间O(1)
*稳定性：不稳定
*/
void sortColors_SelectSort(vector<int>& nums) {
	int len = nums.size();
	for (int i = 0; i < len; ++i) {
		int index = i;
		for (int j = i + 1; j < len; ++j)
			if (nums[j] < nums[index])
				index = j;
		if (index != i)
			swap(nums[i], nums[index]);
	}
}

/*
*3.插入排序
*算法：第一个元素作为已排序，
      取出下一个元素，对已排序序列从后向前遍历，若已排序元素大于新元素，把已排序元素向后挪一个位置，直到找到新元素应该插入的位置，将新元素插入
	  重复这个步骤直到所有元素有序
*时间：最差时间复杂度O(n^2),最优时间复杂度O(n),平均时间复杂度O(n^2)
*空间：所需辅助空间O（1）
*稳定性：稳定
*/
void sortColors_InsertSort(vector<int>& nums) {
	int len = nums.size();
	for (int i = 1; i <len; ++i) {
		int mark = nums[i];
		int j = i - 1;
		while (nums[j] > mark&&j>=0) {
			nums[j + 1] = nums[j];
			--j;
		}
		nums[j+1] = mark;
	}
}
/*
*4.快速排序
*算法：选择一个元素作为基准值，经过一趟排序之后，基准值位于排好序的位置，基准值左边的元素都小于基准值，基准值右边的元素都大于基准值,递归对左右两边的序列进行快速排序
      一趟排序：记录指针l处的元素值为mark;指针l和r分别指向最左边和最右边的元素，指针r从右往左找第一个小于等于基准值的元素，将r处的元素值赋给l处元素，指针l从左往右找第一个大于基准值的元素，将l处的元素值赋给r处的元素
	           重复上述过程，直到l和r指针相遇，指针相遇处赋值为mark
*时间：最差时间复杂度O(n^2),最优时间复杂度O(nlogn),平均时间复杂度O(nlogn)
*空间：所需辅助空间O(logn)
*稳定性：不稳定
*/
void sortColors_QuickSortCore(vector<int>& nums, int left, int right) {
	if (right - left <= 0)
		return;
	int mark = nums[left];
	int l = left, r = right;
	while (r > l) {
		while (nums[r] > mark&&r >l)
			r--;
		nums[l] = nums[r];
		while (nums[l] <= mark&&l < r)
			l++;
		nums[r] = nums[l];
	}
	nums[l] = mark;
	sortColors_QuickSortCore(nums, left, l-1);
	sortColors_QuickSortCore(nums, l + 1, right);
}
void sortColors_QuickSort(vector<int>& nums) {
	int len = nums.size();
	if (len < 2)
		return;
	sortColors_QuickSortCore(nums, 0, len - 1);
}

/*
*5.归并排序
*算法：将两个有序序列归并成一个有序序列
*时间：最优时间复杂度O(nlogn),最坏时间复杂度O(nlogn),平均时间复杂度O(nlogn)
*空间：辅助空间大小O(n)
*稳定性：稳定
*/
void merge(vector<int>& nums, int left, int mid, int right) {
	vector<int> numsCopy(nums.begin() + left, nums.begin() + right + 1);
	int i = 0, j = mid - left + 1, walk = left;
	while (i <= mid - left&&j <= right - left) {
		if (numsCopy[i] <= numsCopy[j])
			nums[walk++] = numsCopy[i++];
		else
			nums[walk++] = numsCopy[j++];
	}
	while (i <= mid - left)
		nums[walk++] = numsCopy[i++];
	while (j <= right - left)
		nums[walk++] = numsCopy[j++];
}
void sortColors_mergeSortCore(vector<int>& nums, int left, int right) {
	if (right - left < 1)
		return;
	int mid = (left + right) / 2;
	sortColors_mergeSortCore(nums, left, mid);
	sortColors_mergeSortCore(nums, mid + 1, right);
	merge(nums, left, mid, right);
}
void sortColors_mergeSort(vector<int>& nums) {
	int len = nums.size();
	sortColors_mergeSortCore(nums, 0, len - 1);
}

/*
*6.堆排序
*算法：把最大堆的堆首元素与无序序列的最后一个元素交换，重构无序序列构成的最大堆，重复上述步骤，直到无序序列长度为1
	   层次遍历下：R[i]的父节点R[(i-1)/2],左子节点R[2*i+1],R[2*i+2]
*时间：最优/最坏/平均时间复杂度O(nlogn)
*空间：O(1)
*稳定性:不稳定
*/
void reconstructHeapTopDown(vector<int>& nums, int j, int right) {
	while (true) {
		int lChild = 2 * j + 1, rChild = 2 * j + 2;
		if (lChild <= right&&rChild <= right&&nums[j] < nums[lChild] && nums[j] < nums[rChild]) {
			if (nums[lChild] > nums[rChild]) {
				swap(nums[j], nums[lChild]);
				j = lChild;
			}
			else {
				swap(nums[j], nums[rChild]);
				j = rChild;
			}
		}
		else if (lChild <= right&&nums[j] < nums[lChild]) {
			swap(nums[j], nums[lChild]);
			j = lChild;
		}
		else if (rChild <= right&&nums[j] < nums[rChild]) {
			swap(nums[j], nums[rChild]);
			j = rChild;
		}
		else
			break;
	}
}
void sortColors_heapSort(vector<int>& nums) {
	int len = nums.size();
	//从下往上初始化最大堆
	for (int i = len - 1; i >= 0; --i) {
		int parent = (i - 1) / 2;
		if (parent >= 0 && nums[i] > nums[parent]) {
			swap(nums[i], nums[parent]);
			reconstructHeapTopDown(nums, i, len - 1);
		}
	}
	int i = len - 1;
	while (i > 0) {
		swap(nums[0], nums[i]);//把堆首放到无序队列的最后
		reconstructHeapTopDown(nums, 0, i - 1);//重构最大堆
		--i;
	}
}

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x):val(x),left(nullptr),right(nullptr){}
};
//经典算法之二叉树遍历
//先序遍历（leetcode 144)
//1.1先序遍历递归版
void preorderTraversalCore(vector<int>& result, TreeNode* root) {
	if (root == nullptr)
		return;
	else {
		result.push_back(root->val);
		preorderTraversalCore(result, root->left);
		preorderTraversalCore(result, root->right);
	}
}
vector<int> preorderTraversal_recursive(TreeNode* root) {
	vector<int> result;
	preorderTraversalCore(result, root);
	return result;
}
//1.2先序遍历迭代版:先延最左侧通路自顶向下访问沿途节点，再自底向上依次访问这些节点的右子树
void walkAlongLeftBranch(vector<int>& result,stack<TreeNode*>& s, TreeNode* root) {
	while (root) {
		result.push_back(root->val);
		s.push(root->right);
		root = root->left;
	}
}
vector<int> preorderTraversal_iterative(TreeNode* root) {
	vector<int> result;
	stack<TreeNode*> s;
	while (true) {
		walkAlongLeftBranch(result, s, root);
		if (s.empty())
			break;
		root = s.top();
		s.pop();
	}
	return result;
}

//2.层次遍历
vector<int> LevelTrversal(TreeNode* root) {
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

//3.1中序遍历,迭代版本1（Leetcode 94）
void goLeft(TreeNode* root, stack<TreeNode*>& s) {
	while (root) {
		s.push(root);
		root = root->left;
	}
}
vector<int> inorderTraversal_iterative1(TreeNode* root) {
	vector<int> result;
	if (root == nullptr)
		return result;
	stack<TreeNode*> s;
	while (true) {
		goLeft(root, s);
		if (s.empty())
			break;
		result.push_back(s.top()->val);
		root = s.top()->right;
		s.pop();
	}
	return result;
}
//3.2中序遍历，迭代版本2
vector<int> inorderTraversal_iterative2(TreeNode* root) {
	vector<int> result;
	stack<TreeNode*> s;
	while (true) {
		if (root) {
			s.push(root);
			root = root->left;
		}
		else if (!s.empty()) {
			result.push_back(s.top()->val);
			root = s.top()->right;
			s.pop();
		}
		else
			break;
	}
	return result;
}
//3.3中序遍历，递归版本
vector<int> inorderTraversal_recursive(TreeNode* root) {
	if (!root)
		return vector<int>();
	vector<int> ans = inorderTraversal_recursive(root->left);
	ans.push_back(root->val);
	vector<int> back = inorderTraversal_recursive(root->right);
	ans.insert(ans.end(), back.begin(), back.end());
	return ans;
}

//4.1后序遍历,迭代版本（Leetcode 145)
void gotoHL(stack<TreeNode*>& s) {
	while (TreeNode* x = s.top()) {
		if (x->left) {
			if (x->right)
				s.push(x->right);
			s.push(x->left);
		}
		else
			s.push(x->right);
	}
	s.pop();
}
vector<int> postorderTraversal_iterative(TreeNode* root) {
	vector<int> result;
	stack<TreeNode*> s;
	if (root)
		s.push(root);
	while (!s.empty()) {
		if (root != s.top()->left&&root != s.top()->right)
			gotoHL(s);
		root = s.top();
		result.push_back(s.top()->val);
		s.pop();
	}
	return result;
}
//4.2后序遍历，递归版本
vector<int> postorderTraversal_recursive(TreeNode* root) {
	if (!root)
		return vector<int>();
	vector<int> left = postorderTraversal_recursive(root->left);
	vector<int> right = postorderTraversal_recursive(root->right);
	left.insert(left.end(), right.begin(), right.end());
	left.push_back(root->val);
	return left;
}