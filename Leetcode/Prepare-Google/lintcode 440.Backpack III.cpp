//Lintcode 440>Backpack III：完全背包问题有价值

int backPackIII(int m, vector<int> &A, vector<int> &V) {
	int len = V.size();
	if(len == 0)
		return 0;
	int* pre = new int[m+1], *current = new int[m+1];
	for(int i = 0; i <= m; ++i)
		pre[i] = i/A[0]*V[0];
	for(int i = 1; i < len; ++i){
		for(int j = 0; j <= m; ++j){
			if(j >= A[i])
				current[j] = max(pre[j], current[j-A[i]]+V[i]); //第i个物体放>=1个
			else
				current[j] = pre[j]; //第i个物体放0个
		}
		swap(pre, current);
	}
	int result = pre[m];
	delete[] pre;
	delete[] current;
	return result;
}