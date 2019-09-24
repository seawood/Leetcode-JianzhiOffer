//Leetcode 139. Word Break

//类似背包问题的写法
bool wordBreak(string s, vector<string>& wordDict) {
    int len = wordDict.size(), s_len = s.size();
    if(s_len == 0 || len == 0)
        return false;
    vector<bool> record(s_len+1, false);
    record[0] = true;
    for(int i = 0; i < len; ++i){
        for(int j = 0; j <= s_len; ++j){
            for(int k = 0; k <= i; ++k){
                int word_len = wordDict[k].size();
                if(j >= word_len && record[j-word_len] == true && wordDict[k] == s.substr(j-word_len, word_len))
                    record[j] = true;
            }

        }
    }
    return record[s_len];
}

bool wordBreak(string s, vector<string>& wordDict) {
   int len = s.size();
   vector<bool> mark(len+1, false);
   mark[0] = true;
   for (int i = 1; i <= len; i++)
   {
        for (int j = i - 1; j >= 0; j--)
        {
            if (mark[j] && find(wordDict.begin(), wordDict.end(), s.substr(j, i - j)) != wordDict.end())
            {
                mark[i] = true;
                break;
            }
        }
    }
    return mark[len];
}