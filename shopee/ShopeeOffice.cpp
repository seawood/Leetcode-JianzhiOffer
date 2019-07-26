//牛客Shopee 2019校招部分编程题汇总
//编程题1：shopee的办公室(二)

#include <iostream>
using namespace std;
int main(){
    int x,y,n;
    cin >> x>>y>>n;
    bool** mark = new bool*[x+1];
    long long** re = new long long*[x+1];
    for(int i = 0; i < x+1;++i){
        mark[i] = new bool[y+1];
        re[i] = new long long[y+1];
    }
    for(int i = 0; i < x+1;++i)
        for(int j = 0; j < y+1;++j){
            mark[i][j] = false;
            re[i][j]=0;
        }
    for(int i = 0;i<n;++i){
        int xi,yi;
        cin>>xi>>yi;
        mark[xi][yi]=true;
    }
    for(int i = 0; i < x+1;++i)
        re[i][0]=1;
    for(int j = 0;j < y+1;++j)
        re[0][j] = 1;
    for(int i = 1; i < x+1;++i)
        for(int j = 1; j < y+1;++j)
            if(!mark[i][j])
                re[i][j] = re[i-1][j]+re[i][j-1];
    long long result = re[x][y];
    for(int i = 0;i < x+1;++i){
        delete[] mark[i];
        delete[] re[i];
    }
    cout<<result<<endl;
    return 0;
}
