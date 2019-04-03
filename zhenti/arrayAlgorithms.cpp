#牛客网->2018校招真题

//三个数乘积的最大值（拼多多）
//https://www.nowcoder.com/practice/5f29c72b1ae14d92b9c3fa03a037ac5f?tpId=90&tqId=30776&tPage=1&rp=1&ru=/ta/2018test&qru=/ta/2018test/question-ranking
int MaxMultiplyOf3() {
    int len;
    cin >> len;
    long long max1 = 0, max2 = 0, max3 = 0, min1 = 0, min2 = 0; //注意声明为long long型，因为最后要算乘积
    long long tmp;
    for (int i = 0; i < len; ++i) {
        cin >> tmp;
        if (tmp > max1) {
            max3 = max2;
            max2 = max1;
            max1 = tmp;
        }
        else if (tmp > max2) {
            max3 = max2;
            max2 = tmp;
        }
        else if (tmp > max3) {
            max3 = tmp;
        }
        else if (tmp < min1) {
            min2 = min1;
            min1 = tmp;
        }
        else if (tmp < min2) {
            min2 = tmp;
        }
    }
    long long sum1 = max1*max2*max3;
    long long sum2 = max1*min1*min2;
    cout << ((sum1 > sum2) ? sum1 : sum2); //三个数乘积的结果只能是这两者之一
    return 0;
}