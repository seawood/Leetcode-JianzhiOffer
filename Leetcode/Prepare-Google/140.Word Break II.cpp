//140 Word Break II
//DFS+剪枝
class Solution {
	void wordBreakCore(const string& s, const unordered_set<string>& wordSet, const vector<bool>& breakable,
		int left, string& re, vector<string>& result) {
		if (left == s.size() && !re.empty()) {
			result.push_back(re.substr(0, re.size() - 1));
			return;
		}
		string origin = re;
		for (int i = left; i < s.size(); ++i) {
			string word = s.substr(left, i - left + 1);
			if (wordSet.find(word) != wordSet.end() && breakable[i + 1]) {
				re += word + " ";
				wordBreakCore(s, wordSet, breakable, i+1, re, result);
				re = origin;
			}
		}
	}
public:
	vector<string> wordBreak(string s, vector<string>& wordDict) {
		int lenS = s.size();
		int lenDict = wordDict.size();
		vector<string> result;
		string re = "";
	vector<bool> breakable(lenS + 1, false); //为了剪枝
	breakable[lenS] = true;
	unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
	for (int i = lenS - 1; i >= 0; --i)
		for (int j = i; j < lenS; ++j) {
			if (wordSet.find(s.substr(i, j-i + 1)) != wordSet.end() && breakable[j + 1]) {
				breakable[i] = true;
				break;
			}
		}
		wordBreakCore(s, wordSet, breakable, 0, re, result);
		return result;
	}
};

//DFS, 没有剪枝会超时
class Solution {
    void wordBreakCore(const string& s, const int& lenS, const vector<string>& wordDict,
	const int& lenDict, int left, string re, vector<string>& result) {
	if (left == lenS && !re.empty()) {
		result.push_back(re.substr(0, re.size() - 1));
		return;
	}
	for (int i = 0; i < lenDict; ++i) {
		int lenWord = wordDict[i].size();
		if (left + lenWord <= lenS && s.substr(left, lenWord) == wordDict[i]) {

			wordBreakCore(s, lenS, wordDict, lenDict, left + lenWord, re + wordDict[i] + " ", result);

		}
	}
}
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        int lenS = s.size();
        int lenDict = wordDict.size();
        vector<string> result;
        string re = "";
        wordBreakCore(s, lenS, wordDict, lenDict, 0, re, result);
        return result;
    }
};