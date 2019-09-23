//Lintcode: Backpack IV: 背包问题方案数

//选取数组nums里的数字相加之和为m，nums里的数字可以重复使用
//递推方程f(n,m) = f(n-1, m) + f(n, m-nums[n])
//f(n,m)表示用nums的前n个数字组成和为m的组合数，f(0,0)=1
int backpackIV(int m, const vector<int>& nums){
	int len = nums.size();
	vector<int> record(m+1, 0);
	record[0] = 1;
	for(int i = 0; i < len; ++i){
		for(int j = 0; j <= m; ++j){
			record[j] += j >= nums[i] ? record[j-nums[i]] : 0;
		}
	}
	return record[m];
}
