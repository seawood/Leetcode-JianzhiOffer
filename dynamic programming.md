# Leetcode:Dynamic Programming


### 198. House Robber

  - a[0,i]表示抢劫前i家商店能获得的最大收益
  - 子问题的递推关系：a[0,i]=max(a[0,i-2]+nums[i],a[i-1])
  - 代码：https://leetcode.com/problems/house-robber/description/

### 213. House Robber II
  - 和198题的不同是：可以分两种情况来考虑：是否抢劫第一家，然后将环形转化为线形
  - 代码:https://leetcode.com/problems/house-robber-ii/description/

### 53. Maximum Subarray
  - 最大字段和问题
  - 确定子问题的边界，设C[i]是输入A[0,i]中必须包含C[i]的最大字段和，C[i+1]=max(C[i]+A[i+1],A[i+1])。初始值C[0]=max(0,A[0])。
  - 原问题的解即为所有C[i]中的最大值。
  - 代码：https://leetcode.com/problems/maximum-subarray/description/
 
### 121.Best Time to Buy and Cell Stock
  - min[i]表示输入A[0,i]所有数中的最小值，C[i]表示输入A[0,i]能获得的最大收益，则C[i+1]=max(C[i],A[i+1]-min[i])
  - 代码：https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/

### 70.Climbing Stairs
  - C[i]=C[i-1]+C[i-2],最后一次可以走两步或者走一步
  - 初始值C[1]=1,C[2]=2
  - 代码：https://leetcode.com/problems/climbing-stairs/description/
  
### 5.Longest Palindromic Substring

### 10.Regular Expression Matching


