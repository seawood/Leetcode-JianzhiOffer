//牛客Shopee 2019校招部分编程题汇总
//编程题4：建物流中转站

#include <iostream>
#include <climits>
using namespace std;
 
int main(){
    int n;
    cin>>n;
    int** num = new int*[n];
    for(int i = 0; i < n;++i)
        num[i] = new int[n];
    int *rowSum = new int[n], *colSum = new int[n];
    for(int i = 0; i <n;++i)
        for(int j = 0; j <n ;++j){
            cin>>num[i][j];
            rowSum[i]+=num[i][j];
            colSum[j]+=num[i][j];
        }
    int *rowDis = new int[n],*colDis = new int[n];
    for(int i = 0; i < n; ++i){
        rowDis[i]=0;
        colDis[i]=0;
        for(int j = 0; j < n;++j){
            rowDis[i]+=rowSum[j]*abs(j-i);
            colDis[i]+=colSum[j]*abs(j-i);
        }
    }
    int res = INT_MAX;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n;++j){
            if(num[i][j]==0)
                res = min(res, rowDis[i]+colDis[j]);
        }
    delete[] rowSum;
    delete[] colSum;
    delete[] rowDis;
    delete[] colDis;
    for(int i = 0; i < n;++i)
        delete[] num[i];
    cout<<res<<endl;
    return 0;
}