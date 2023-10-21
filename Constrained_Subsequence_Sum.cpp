// Problem Link: https://leetcode.com/problems/constrained-subsequence-sum/

// Problem: Given an integer array nums and an integer k, return the maximum sum of a non-empty subsequence 
// of that array such that for every two consecutive integers in the subsequence, nums[i] and nums[j], 
// where i < j, the condition j - i <= k is satisfied.

// A subsequence of an array is obtained by deleting some number of elements (can be zero) from the array, 
// leaving the remaining elements in their original order.


// **INTUITION**: We first think of using our standar approach of recursion + memoization, as it is talking about
// subsequences, but it gives TLE.

// The Tabulation method, is important because our optimised approach will be derived from it.
// So in our tabulation approach we start from index 1, and then keep a pointer j at i-1,
// and iterate j backwards till i-j<=k and j>=0, and we will be keeping track of maximum sum of subsequence till the
// current index.

// So how does it work ?
// Eg: nums = [10,-2,-10,-5,20], k = 2
// we will kep a res variable to store the maximum sum we can get among all possible subsequences.
// res is initally set to nums[0].
// i pointer will point to 2, and j pointer will point to i-1 = 0 index.
// now maximum sum till index 0, is nums[0], only because there is no previous elemnt to it.
// so we will update v[i], with max(v[i] , nums[i] + v[j]);, which means to the current ith element 
// should we add the previous index maximum sum , or let the nums[i], element be as it is.
// becuase it might happen that adding previous sum leads to more negative value for the ith index if previous index has already a negative value
// so in that case we not consider it, and let the current ith element be as it is.

// SImilarly just do a dry run, for the eg: [-1, -2,-3], k=2,

// OPTImised approach
// we can optimise the inner j loop, becuase purpose of using inner j loop is to get the maximum by iterating backwards, for every ith index
// So to get the maximum element from backwards in O(1) time we can use max-heap priority_queue,
// where insertion and deletion takes log(n) time.

// SO while moving for every ith index we will also push the previous element with their index in the pq. and for i-j<=k condition
// we will use it for popping the element from top if it not in bound for a certain index.



class Solution {
public:
    int constrainedSubsetSum(vector<int>& nums, int k) {

        //    tabulation -------- BRUTE FORCE --- GIVES TLE ---------------------

        // int n = nums.size();

        // vector<int> v(nums.begin() , nums.end());

        //     int res = nums[0];
        // for(int i= 1 ; i  < n; i++)
        // {
        //     for(int j = i-1 ; j >=0 && i-j<=k ; j--)
        //     {
        //            v[i] =  max(v[i] , nums[i] + v[j]);
        //             res = max(res, v[i] );

        //     }
        // }
        // return res;





        // -------------------- USING PRIORITY QUEUE SLIDING WINDOW------------
         
         priority_queue<pair<int,int>> pq;  // element , index
         
         int n = nums.size();
         pq.push({nums[0], 0});
         int res = nums[0];
         for(int i = 1 ; i < n ; i++)
         {
             while(!pq.empty() && i - pq.top().second >k ) 
             pq.pop();

            int maxSum_till_this_Index = max(pq.top().first + nums[i], nums[i]);

            res = max(res, maxSum_till_this_Index);
            pq.push({maxSum_till_this_Index, i});

         }
         return res;

    }
};