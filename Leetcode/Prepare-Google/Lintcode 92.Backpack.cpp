//0-1背包：动态规划
//Lintcode 92.Backpack: https://www.lintcode.com/problem/backpack/description
//时间复杂度O(n*m),空间复杂度O(n*m)

int backPack(int m, vector<int> &A) {
    int len = A.size();
    if(len == 0)
        return 0;
    int** record = new int*[len];
    for(int i = 0; i < len; ++i)
        record[i] = new int[m+1];
    for(int i = 0; i <= m; ++i)
        record[0][i] = i>=A[0] ? A[0] : 0;
    for(int i = 1; i < len; ++i){
        for(int j = 0; j <= m; ++j){
            if(j >= A[i])
                record[i][j] = max(record[i-1][j], record[i-1][j-A[i]]+A[i]);
            else
                record[i][j] = record[i-1][j];
        }
    }
    int result = record[len-1][m];
    for(int i = 0; i < len; ++i)
        delete[] record[i];
    delete[] record;
    return result;
}

//优化空间复杂度，因为每次只用到记录矩阵的前后两行，所以空间复杂度可以优化到O(m)
int backPack(int m, vector<int> &A) {
    int len = A.size();
    if(len == 0)
        return 0;
    int* pre = new int[m+1], *current = new int[m+1];
    for(int i = 0; i <= m; ++i)
        pre[i] = i >= A[0] ? A[0] : 0;
    for(int i = 1; i < len; ++i){
        for(int j = 0; j <= m; ++j){
            if(j >= A[i])
                current[j] = max(pre[j], pre[j-A[i]]+A[i]);
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