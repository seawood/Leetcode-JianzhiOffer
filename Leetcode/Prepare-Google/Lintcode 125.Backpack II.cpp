//Lintcode 125.Backpack II: 0-1背包有价值
//动态规划+空间优化

int backPackII(int m, vector<int> &A, vector<int> &V) {
    int len = V.size();
    if(len == 0)
        return 0;
    int* pre = new int[m+1], *current = new int[m+1];
    for(int i = 0; i <= m; ++i)
        pre[i] = i >= A[0] ? V[0] : 0;
    for(int i = 1; i < len; ++i){
        for(int j = 0; j <= m; ++j){
            if(j >= A[i])
                current[j] = max(pre[j], pre[j-A[i]]+V[i]);
            else
                current[j] = pre[j];
        }
        swap(pre, current);
    }
    int result = pre[m];
    delete[] pre;
    delete[] current;
    return result;
}