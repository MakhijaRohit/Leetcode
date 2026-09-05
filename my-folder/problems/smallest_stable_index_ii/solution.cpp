class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();
        if(n == 0) return 0;

        vector<int> leftMax(n);
        vector<int> rightMin(n);

        leftMax[0] = nums[0];
        for(int i = 1; i < n; i++)
            leftMax[i] = max(leftMax[i - 1], nums[i]);

        rightMin[n - 1] = nums[n - 1];
        for(int i = n - 2; i >= 0; i--)
            rightMin[i] = min(rightMin[i + 1], nums[i]);

        for(int i = 0; i < n; i++)
            if((leftMax[i] - rightMin[i]) <= k) return i;

        return -1;
    }
};