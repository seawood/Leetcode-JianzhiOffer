//牛客Shopee 2019校招部分编程题汇总
//编程题3：实现字通配符*
#include <iostream>
#include <set>
#include <string>
using namespace std;
void match(set<pair<int,int>>& ans, const string& pattern, const string& target,
          int pattern_cur_pos, int target_cur_pos, const int& start){
    if(pattern_cur_pos == (int)pattern.size()){
        if(target_cur_pos-start>0)
            ans.insert(make_pair(start, target_cur_pos-start));
        return;
    }
    if(target_cur_pos == (int)target.size())
        return;
    if(pattern[pattern_cur_pos] == '*'){
        match(ans, pattern, target, pattern_cur_pos+1, target_cur_pos+1, start);
        match(ans, pattern, target, pattern_cur_pos, target_cur_pos+1, start);
        match(ans, pattern, target, pattern_cur_pos+1, target_cur_pos, start);
    }else if(pattern[pattern_cur_pos] == target[target_cur_pos])
        match(ans, pattern, target, pattern_cur_pos+1, target_cur_pos+1, start);
}
int main(){
    string pattern, target;
    cin>>pattern>>target;
    set<pair<int,int>> ans;
    for(int i = 0; i < target.size(); ++i)
        match(ans, pattern, target, 0, i, i);
    if(ans.size() == 0)
        cout<<-1<<" "<<0<<endl;
    else{
        for(auto &i : ans)
            cout<<i.first<<" "<<i.second<<endl;
    }
    return 0;
}